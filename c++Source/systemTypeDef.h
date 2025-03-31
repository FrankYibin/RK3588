#ifndef SYSTEMTYPEDEF_H
#define SYSTEMTYPEDEF_H

#include <QObject>
#include <QQmlEngine>

#define SYSTEMTYPE_URI_NAME "Com.Branson.SystemTypeEnum"
#define SYSTEMTYPE_QML_MAJOR_VERSION 1
#define SYSTEMTYPE_QML_MINOR_VERSION 0
#define SYSTEMTYPE_QML_NAME "SystemTypeEnum"




class SystemTypeDef : public QObject
{
    Q_OBJECT
    Q_ENUMS(SYSTEMTYPE)
public:

    enum SYSTEMTYPE{
        ALLTYPE = 0x01,
        GSX_E1 = 0x02,
        GSX_P1_BASE = 0x04
    };



    static void registerQMLType()
    {
        qmlRegisterType<SystemTypeDef>(SYSTEMTYPE_URI_NAME,
                                       SYSTEMTYPE_QML_MAJOR_VERSION,
                                       SYSTEMTYPE_QML_MINOR_VERSION,
                                       SYSTEMTYPE_QML_NAME);
    }
};









#endif // SYSTEMTYPEDEF_H
