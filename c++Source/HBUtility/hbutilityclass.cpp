#include "hbutilityclass.h"
HBUtilityClass* HBUtilityClass::_ptrInstance = nullptr;
void HBUtilityClass::SetTextData(DATA_FORMAT index, int data, float factor, QString formater)
{
    txtData[index].Data = data;
    txtData[index].Factor = factor;
    txtData[index].Format = formater;
}

void HBUtilityClass::InitTextData()
{
    SetTextData(HEX2METER,          0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2FEET,           0, static_cast<float>(0.01 * 3.28),             QString("%.2f"));
    SetTextData(HEX2METER_PER_HOUR, 0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2FEET_PER_HOUR,  0, static_cast<float>(0.01 * 3.28),             QString("%.2f"));
    SetTextData(HEX2METER_PER_MIN,  0, static_cast<float>(0.01/60),                 QString("%.2f"));
    SetTextData(HEX2FEET_PER_MIN,   0, static_cast<float>(0.01 * 3.28 / 60),        QString("%.2f"));
    SetTextData(HEX2POUND,          0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2KILOGRAM,       0, static_cast<float>(0.01 * 0.454),            QString("%.2f"));
    SetTextData(HEX2KILONEWTON,     0, static_cast<float>(0.01 * 0.004448230531),   QString("%.2f"));
    SetTextData(HEX2PULSE,          0, static_cast<float>(1.0),                     QString("%d"));
    SetTextData(HEX2K_VALUE,        0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2AMPERE,         0, static_cast<float>(1.0),                     QString("%d"));
    SetTextData(HEX2VOLTAGE,        0, static_cast<float>(0.001),                   QString("%.3f"));
    SetTextData(HEX2PERCENT,        0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2TONAGE,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2FACTOR,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2SECOND,         0, static_cast<float>(0.01),                    QString("%.2f"));
    SetTextData(HEX2DEGREE,         0, static_cast<float>(0.01),                    QString("%.2f"));
}

QString HBUtilityClass::FormatedDataToString(const DATA_FORMAT index, const int data)
{
    QString tmpStr;
    if(txtData[index].Format.contains("d") == true)
        tmpStr.sprintf(txtData[index].Format.toStdString().c_str(), data);
    else
        tmpStr.sprintf(txtData[index].Format.toStdString().c_str(), static_cast<double>(data * txtData[index].Factor));
    return tmpStr;
}

int HBUtilityClass::StringToFormatedData(const DATA_FORMAT index, const QString strData)
{
    QString tmpStr = strData.trimmed();
    if(tmpStr.isEmpty() == true)
        return -1;
    QByteArray tmpArray = tmpStr.toLatin1();
    const char *s = tmpArray.data();
    int i = 0;
    while(((*s >= '0') && (*s <= '9')) || (*s == '.') || (*s == '-'))
    {
        s++;
        i++;
    }
    tmpStr.remove(i, tmpStr.size() -1);
    double tmpValue = tmpStr.toDouble();
    const double d_factor = 1.0 / txtData[index].Factor;
    return static_cast<int>(tmpValue * d_factor);
}

HBUtilityClass* HBUtilityClass::GetInstance()
{
    if(_ptrInstance == nullptr)
    {
        _ptrInstance = new HBUtilityClass();
    }
    return _ptrInstance;
}

HBUtilityClass::HBUtilityClass()
{
    InitTextData();
}
