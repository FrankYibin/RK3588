#ifndef HBUTILITYCLASS_H
#define HBUTILITYCLASS_H
#include <QString>

class HBUtilityClass
{
public:
    enum DATA_FORMAT
    {
        HEX2METER = 0,
        HEX2FEET,
        HEX2METER_PER_HOUR,
        HEX2FEET_PER_HOUR,
        HEX2METER_PER_MIN,
        HEX2FEET_PER_MIN,
        HEX2POUND,
        HEX2KILOGRAM,
        HEX2KILONEWTON,
        HEX2PULSE,
        HEX2K_VALUE,
        HEX2AMPERE,
        HEX2VOLTAGE,
        HEX2PERCENT,
        HEX2TONAGE,
        HEX2FACTOR,
        HEX2SECOND,
        HEX2DEGREE,
        END_FROMAT
    };
private:
    struct DATA_SHOW_STRUCT
    {
        int Data;
        float Factor;
        QString Format;
    };
    DATA_SHOW_STRUCT txtData[END_FROMAT];

    static HBUtilityClass* _ptrInstance;
    void SetTextData(DATA_FORMAT index, int data, float factor, QString formater);
    void InitTextData();
public:
    static HBUtilityClass* GetInstance();
    QString FormatedDataToString(const DATA_FORMAT index, const int data);
    int StringToFormatedData(const DATA_FORMAT index, const QString strData);
protected:
    HBUtilityClass();
};

#endif // HBUTILITYCLASS_H
