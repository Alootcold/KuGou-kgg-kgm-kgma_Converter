#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QString>
#include <QStringList>

class StringUtil
{
public:
    static QString toUpper(const QString& str);
    static QString toLower(const QString& str);
    static QString trim(const QString& str);
    static QStringList split(const QString& str, const QString& separator);
    static QString join(const QStringList& list, const QString& separator);
    static bool contains(const QString& str, const QString& sub);
    static QString replace(const QString& str, const QString& before, const QString& after);
};

#endif // STRINGUTIL_H
