#include "fileutil.h"
#include <QFileInfo>
#include <QDir>
#include <QFile>

QString FileUtil::getExtension(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.suffix().toLower();
}

QString FileUtil::getFileName(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}

QString FileUtil::getBaseName(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.baseName();
}

QString FileUtil::getDirPath(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.absolutePath();
}

QString FileUtil::createOutputPath(const QString& inputPath, const QString& outputDir, const QString& outputExt)
{
    QFileInfo fileInfo(inputPath);
    QString baseName = fileInfo.baseName();

    QString outputFileName = baseName + "." + outputExt;
    QString outputPath = outputDir + "/" + outputFileName;

    QFileInfo outInfo(outputPath);
    if (outInfo.exists()) {
        int counter = 1;
        while (true) {
            outputFileName = QString("%1 (%2).%3").arg(baseName).arg(counter).arg(outputExt);
            outputPath = outputDir + "/" + outputFileName;
            if (!QFile::exists(outputPath)) {
                break;
            }
            counter++;
        }
    }

    return outputPath;
}

bool FileUtil::isKugouFile(const QString& filePath)
{
    QString ext = getExtension(filePath);
    return ext == "kgm" || ext == "kgma" || ext == "kgg" || ext == "vpr";
}

QStringList FileUtil::getKugouFilesInDir(const QString& dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        return QStringList();
    }

    QStringList filters;
    filters << "*.kgm" << "*.kgma" << "*.kgg" << "*.vpr";

    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files);

    QStringList result;
    for (const QFileInfo& info : fileList) {
        result.append(info.absoluteFilePath());
    }

    return result;
}
