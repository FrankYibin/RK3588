#include "datetime.h"
#include "c++Source/HBUtility/hbutilityclass.h"
static DateTime* _ptrDateTime = nullptr;
DateTime *DateTime::GetInstance()
{
    if(_ptrDateTime == nullptr)
        _ptrDateTime = new DateTime();
    return _ptrDateTime;
}

void DateTime::setSystemDateTime(QString datetime) const
{
    if(HBUtilityClass::GetInstance()->SetSystemClock(datetime) == true)
        HBUtilityClass::GetInstance()->SyncHardwareRTC();
}

DateTime::DateTime(QObject *parent)
    : QObject{parent}
{}
