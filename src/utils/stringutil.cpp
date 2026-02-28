#include "stringutil.h"

QString StringUtil::toUpper(const QString& str)
{
    return str.toUpper();
}

QString StringUtil::toLower(const QString& str)
{
    return str.toLower();
}

QString StringUtil::trim(const QString& str)
{
    return str.trimmed();
}

QStringList StringUtil::split(const QString& str, const QString& separator)
{
    return str.split(separator);
}

QString StringUtil::join(const QStringList& list, const QString& separator)
{
    return list.join(separator);
}

bool StringUtil::contains(const QString& str, const QString& sub)
{
    return str.contains(sub);
}

QString StringUtil::replace(const QString& str, const QString& before, const QString& after)
{
    QString result = str;
    result.replace(before, after);
    return result;
}
