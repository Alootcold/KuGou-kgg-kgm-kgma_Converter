#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QString>
#include <QMap>

class AudioInfo
{
public:
    static QString getAudioFormat(const QString& filePath);
    static bool isSupportedFormat(const QString& extension);
    static QMap<QString, QString> getSupportedFormats();

private:
    AudioInfo() = default;
};

#endif // AUDIOINFO_H
