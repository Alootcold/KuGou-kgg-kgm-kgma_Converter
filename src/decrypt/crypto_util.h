#ifndef CRYPTO_UTIL_H
#define CRYPTO_UTIL_H

#include <QByteArray>
#include <QVector>

class CryptoUtil
{
public:
    static QByteArray rc4Decrypt(const QByteArray& data, const QVector<uint8_t>& key);
    static uint8_t transformByte(uint8_t byte, const QVector<uint8_t>& key, size_t pos);
};

#endif // CRYPTO_UTIL_H
