#ifndef KGM_MASK_TABLE_H
#define KGM_MASK_TABLE_H

#include <QVector>
#include <cstddef>

class KgmMaskTable
{
public:
    static const QVector<uint8_t>& getTable1();
    static const QVector<uint8_t>& getTable2();
    static const QVector<uint8_t>& getMaskV2PreDef();

    static uint8_t getMask(size_t pos);

private:
    KgmMaskTable() = default;

    static QVector<uint8_t> initTable1();
    static QVector<uint8_t> initTable2();
    static QVector<uint8_t> initMaskV2PreDef();
};

#endif // KGM_MASK_TABLE_H
