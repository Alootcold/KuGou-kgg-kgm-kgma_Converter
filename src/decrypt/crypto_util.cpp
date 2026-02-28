#include "crypto_util.h"
#include <QDebug>

QByteArray CryptoUtil::rc4Decrypt(const QByteArray& data, const QVector<uint8_t>& key)
{
    if (key.isEmpty()) {
        return data;
    }

    QByteArray result = data;

    for (int i = 0; i < result.size(); ++i) {
        result[i] = transformByte(static_cast<uint8_t>(result[i]), key, static_cast<size_t>(i));
    }

    return result;
}

uint8_t CryptoUtil::transformByte(uint8_t byte, const QVector<uint8_t>& key, size_t pos)
{
    if (key.isEmpty()) {
        return byte;
    }

    uint8_t keyByte = key[pos % key.size()];

    uint8_t result = byte ^ keyByte;
    result ^= (result & 0x0F) << 4;
    result ^= (result & 0x0F) << 4;

    return result;
}
