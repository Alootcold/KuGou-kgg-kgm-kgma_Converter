#include "convertthread.h"
#include "decrypt/kgm_decrypt.h"
#include "decrypt/kgg_decrypt.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

ConvertThread::ConvertThread(QObject *parent)
    : QThread(parent)
    , m_cancelled(false)
{
}

ConvertThread::~ConvertThread()
{
    m_cancelled = true;
    wait();
}

void ConvertThread::setFiles(const QStringList& files)
{
    m_files = files;
}

void ConvertThread::setOutputDir(const QString& dir)
{
    m_outputDir = dir;
}

void ConvertThread::setFormat(const QString& format)
{
    m_format = format;
}

void ConvertThread::cancel()
{
    m_cancelled = true;
}

void ConvertThread::run()
{
    if (m_files.isEmpty()) {
        emit error("没有要转换的文件");
        return;
    }

    QDir outputDir(m_outputDir);
    if (!outputDir.exists()) {
        if (!outputDir.mkpath(m_outputDir)) {
            emit error("无法创建输出目录");
            return;
        }
    }

    int total = m_files.size();
    int current = 0;
    int successCount = 0;
    int failCount = 0;

    for (const QString& inputPath : m_files) {
        if (m_cancelled) {
            emit error("转换已取消");
            return;
        }

        QFileInfo fileInfo(inputPath);
        QString fileName = fileInfo.fileName();

        emit progress(current + 1, total, fileName);

        QString outputExt = getOutputExtension(inputPath);
        QString outputFileName = fileInfo.baseName() + "." + outputExt;
        QString outputPath = m_outputDir + "/" + outputFileName;

        if (convertFile(inputPath, outputPath)) {
            successCount++;
        } else {
            failCount++;
            qWarning() << "Failed to convert:" << inputPath;
        }

        current++;
    }

    if (failCount > 0) {
        QString errorMsg = QString("转换完成: 成功 %1 个, 失败 %2 个").arg(successCount).arg(failCount);
        emit error(errorMsg);
    } else {
        emit finished(m_outputDir);
    }
}

bool ConvertThread::convertFile(const QString& inputPath, const QString& outputPath)
{
    QFileInfo fileInfo(inputPath);
    QString ext = fileInfo.suffix().toLower();

    if (ext == "kgg") {
        return KggDecrypt::decrypt(inputPath, outputPath);
    }

    if (ext == "kgma" || ext == "kgm" || ext == "vpr") {
        return KgmDecrypt::decrypt(inputPath, outputPath, ext);
    }

    QFile file(inputPath);
    if (!file.copy(outputPath)) {
        return false;
    }

    return true;
}

QString ConvertThread::getOutputExtension(const QString& inputPath) const
{
    QFileInfo fileInfo(inputPath);
    QString ext = fileInfo.suffix().toLower();

    if (ext == "kgma") {
        if (m_format == "flac") {
            return "flac";
        } else {
            return "mp3";
        }
    }

    if (ext == "kgm" || ext == "vpr") {
        if (m_format == "flac") {
            return "flac";
        } else {
            return "mp3";
        }
    }

    return ext;
}
