#ifndef KGG_DECRYPT_H
#define KGG_DECRYPT_H

#include <QString>

class KggDecrypt
{
public:
    static bool decrypt(const QString& inputPath, const QString& outputPath);

    static bool isSupported();
};

#endif // KGG_DECRYPT_H
