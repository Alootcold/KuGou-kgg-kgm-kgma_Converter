#ifndef CONVERTTHREAD_H
#define CONVERTTHREAD_H

#include <QThread>
#include <QString>
#include <QStringList>
#include "../decrypt/decrypt_global.h"

class ConvertThread : public QThread
{
    Q_OBJECT

public:
    explicit ConvertThread(QObject *parent = nullptr);
    ~ConvertThread();

    void setFiles(const QStringList& files);
    void setOutputDir(const QString& dir);
    void setFormat(const QString& format);

public slots:
    void cancel();

signals:
    void progress(int current, int total, const QString& filename);
    void finished(const QString& outputDir);
    void error(const QString& msg);

protected:
    void run() override;

private:
    QStringList m_files;
    QString m_outputDir;
    QString m_format;
    bool m_cancelled;

    bool convertFile(const QString& inputPath, const QString& outputPath);
    QString getOutputExtension(const QString& inputPath) const;
};

#endif // CONVERTTHREAD_H
