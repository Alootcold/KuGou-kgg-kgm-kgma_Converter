#ifndef KGM_DECRYPT_H
#define KGM_DECRYPT_H

#include <QString>
#include <QByteArray>
#include "decrypt_global.h"

class KgmDecrypt
{
public:
    static FileType detectType(const QByteArray& header);
    static FileType detectTypeFromFile(const QString& filePath);

    static bool decrypt(const QString& inputPath, const QString& outputPath, const QString& ext);
    static bool decryptData(QByteArray& data, const QString& ext);

private:
    static bool isValidHeader(const QByteArray& header, const QVector<uint8_t>& expectedHeader);
    static size_t preDec(uint8_t* data, size_t size, bool isVpr);
    static void decryptDataBlock(uint8_t* data, size_t size, size_t offset, bool isVpr);

    static uint8_t s_staticKey[17];
    static bool s_staticKeyLock;
};

#endif // KGM_DECRYPT_H
