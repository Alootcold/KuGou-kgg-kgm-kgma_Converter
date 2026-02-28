#include "kgg_decrypt.h"
#include <QDebug>
#include <QFile>

bool KggDecrypt::decrypt(const QString& inputPath, const QString& outputPath)
{
    qWarning() << "KGG decryption is not yet implemented.";
    qWarning() << "KGG format requires key database support.";
    qWarning() << "This feature will be available after community research.";

    QFile file(inputPath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QFile outFile(outputPath);
    if (!outFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    outFile.write(data);
    outFile.close();

    return false;
}

bool KggDecrypt::isSupported()
{
    return false;
}
