#include "kgm_decrypt.h"
#include "kgm_mask_table.h"
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <cstring>

uint8_t KgmDecrypt::s_staticKey[17] = {0};
bool KgmDecrypt::s_staticKeyLock = false;

FileType KgmDecrypt::detectType(const QByteArray& header)
{
    if (header.size() < 16) {
        return FileType::Unknown;
    }

    if (isValidHeader(header, DecryptConsts::KGM_HEADER)) {
        return FileType::KGMA;
    }

    if (isValidHeader(header, DecryptConsts::VPR_HEADER)) {
        return FileType::VPR;
    }

    const QByteArray kgmSig = header.left(4);
    if (kgmSig == "kgm" || kgmSig == "KGM") {
        return FileType::KGM;
    }

    return FileType::Unknown;
}

FileType KgmDecrypt::detectTypeFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return FileType::Unknown;
    }

    QByteArray header = file.read(16);
    file.close();

    return detectType(header);
}

bool KgmDecrypt::decrypt(const QString& inputPath, const QString& outputPath, const QString& ext)
{
    QFile file(inputPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file:" << inputPath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.size() < 0x30) {
        qWarning() << "File too small:" << inputPath;
        return false;
    }

    if (!decryptData(data, ext)) {
        qWarning() << "Decryption failed for:" << inputPath;
        return false;
    }

    QFile outFile(outputPath);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot create output file:" << outputPath;
        return false;
    }

    outFile.write(data);
    outFile.close();

    return true;
}

bool KgmDecrypt::decryptData(QByteArray& data, const QString& ext)
{
    bool isVpr = (ext.toLower() == "vpr");

    if (data.size() < 0x30) {
        qWarning() << "File too small";
        return false;
    }

    uchar* buffer = reinterpret_cast<uchar*>(data.data());
    size_t size = static_cast<size_t>(data.size());

    uint8_t savedKey[17] = {0};
    memcpy(savedKey, buffer + 0x1C, 16);
    savedKey[16] = 0;

    size_t headerLen = preDec(buffer, size, isVpr);

    if (headerLen >= size) {
        qWarning() << "Invalid header length:" << headerLen;
        return false;
    }

    memmove(buffer, buffer + headerLen, size - headerLen);
    size -= headerLen;

    s_staticKeyLock = true;
    memcpy(s_staticKey, savedKey, 17);

    const size_t blockSize = 2 * 1024 * 1024;
    size_t offset = 0;

    while (offset < size) {
        size_t block = qMin(blockSize, size - offset);
        decryptDataBlock(buffer + offset, block, offset, isVpr);
        offset += block;
    }

    s_staticKeyLock = false;
    memset(s_staticKey, 0, 17);

    return true;
}

bool KgmDecrypt::isValidHeader(const QByteArray& header, const QVector<uint8_t>& expectedHeader)
{
    if (header.size() < 16) {
        return false;
    }

    for (int i = 0; i < 16; ++i) {
        if (static_cast<uint8_t>(header[i]) != expectedHeader[i]) {
            return false;
        }
    }

    return true;
}

size_t KgmDecrypt::preDec(uint8_t* data, size_t size, bool isVpr)
{
    Q_UNUSED(isVpr);

    if (size < 0x30) {
        return 0;
    }

    quint32 headerLen = *reinterpret_cast<quint32*>(data + 0x10);
    if (headerLen > size || headerLen < 0x30) {
        headerLen = 0x30;
    }

    uint8_t key[17] = {0};
    memcpy(key, data + 0x1C, 16);
    key[16] = 0;

    for (size_t i = 0; i < qMin<size_t>(headerLen, size); ++i) {
        data[i] ^= key[i % 17];
    }

    return headerLen;
}

void KgmDecrypt::decryptDataBlock(uint8_t* data, size_t size, size_t offset, bool isVpr)
{
    if (!s_staticKeyLock) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        uint8_t med8 = s_staticKey[(i + offset) % 17] ^ data[i];
        med8 ^= (med8 & 0x0f) << 4;

        uint8_t msk8 = KgmMaskTable::getMask(i + offset);
        msk8 ^= (msk8 & 0x0f) << 4;
        data[i] = med8 ^ msk8;

        if (isVpr) {
            data[i] ^= DecryptConsts::VPR_MASK_DIFF[(i + offset) % 17];
        }
    }
}
