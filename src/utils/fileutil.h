#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>
#include <QStringList>

class FileUtil
{
public:
    static QString getExtension(const QString& filePath);
    static QString getFileName(const QString& filePath);
    static QString getBaseName(const QString& filePath);
    static QString getDirPath(const QString& filePath);
    static QString createOutputPath(const QString& inputPath, const QString& outputDir, const QString& outputExt);
    static bool isKugouFile(const QString& filePath);
    static QStringList getKugouFilesInDir(const QString& dirPath);
};

#endif // FILEUTIL_H
