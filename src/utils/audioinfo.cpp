#include "audioinfo.h"
#include <QFile>
#include <QFileInfo>

QString AudioInfo::getAudioFormat(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return QString();
    }

    QByteArray header = file.read(16);
    file.close();

    if (header.size() >= 10) {
        if (header.startsWith("ID3")) {
            return "mp3";
        }
        if (header.startsWith("\xff\xfb") || header.startsWith("\xff\xf3") || header.startsWith("\xff\xf2")) {
            return "mp3";
        }
    }

    if (header.size() >= 4) {
        if (header.startsWith("fLaC")) {
            return "flac";
        }
        if (header.startsWith("OggS")) {
            return "ogg";
        }
        if (header.startsWith("RIFF") && header.mid(8, 4) == "WAVE") {
            return "wav";
        }
    }

    QFileInfo fileInfo(filePath);
    return fileInfo.suffix().toLower();
}

bool AudioInfo::isSupportedFormat(const QString& extension)
{
    static const QStringList supportedFormats = {
        "mp3", "flac", "wav", "ogg", "m4a", "aac", "wma"
    };
    return supportedFormats.contains(extension.toLower());
}

QMap<QString, QString> AudioInfo::getSupportedFormats()
{
    QMap<QString, QString> formats;
    formats["mp3"] = "MP3 Audio";
    formats["flac"] = "FLAC Lossless";
    formats["wav"] = "WAV Audio";
    formats["ogg"] = "OGG Vorbis";
    formats["m4a"] = "MPEG-4 Audio";
    formats["aac"] = "AAC Audio";
    formats["wma"] = "Windows Media Audio";
    return formats;
}
