#include "datetime.h"
#include "c++Source/HBUtility/hbutilityclass.h"
DateTime* DateTime::_ptrDateTime = nullptr;
DateTime *DateTime::GetInstance()
{
    if(_ptrDateTime == nullptr)
        _ptrDateTime = new DateTime();
    return _ptrDateTime;
}

bool DateTime::setSystemDateTime(QString datetime) const
{
#if RK3588
    if(HBUtilityClass::GetInstance()->SetSystemClock(datetime) == true)
    { HBUtilityClass::GetInstance()->SyncHardwareRTC();
        return true;
    }else{
        return false;
    }
#endif
}

DateTime::DateTime(QObject *parent)
    : QObject{parent}
{}
