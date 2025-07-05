/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QMutex>
#include <QObject>
#include "c++Source/userleveldef.h"
#include "c++Source/uiscreendef.h"
#include "c++Source/languagedef.h"
#include "c++Source/graphaxisdef.h"
#include "c++Source/alarmindexdef.h"
#include "c++Source/logindef.h"
#include "c++Source/upgradesoftwaredef.h"
#include "c++Source/languageconfig.h"
#include "c++Source/jsontreemodel.h"
#include "c++Source/recipemodel.h"
#include "c++Source/recipedef.h"
#include "c++Source/productionruninterface.h"
#include "c++Source/weldgraphdata.h"
#include "c++Source/upgradesoftware.h"
#include "c++Source/definition.h"
#include "c++Source/communicationinterface.h"
#include "c++Source/alarmnotification.h"
#include "c++Source/login.h"
#include "c++Source/systemInformationInterface.h"

#include "c++Source/HBScreen/hbhome.h"
#include "c++Source/HBScreen/autotestspeed.h"
#include "c++Source/HBScreen/depthsetting.h"
#include "c++Source/HBScreen/depthmeter.h"
#include "c++Source/HBScreen/depthsiman.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBScreen/tensionsafety.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/historydatatable.h"
#include "c++Source/HBScreen/tensionscalemanager.h"
#include "c++Source/HBScreen/tensionsetting.h"
#include "c++Source/HBScreen/tensiometermanager.h"
#include "c++Source/HBScreen/historyoperationmodel.h"
#include "c++Source/HBScreen/usermanagermodel.h"
#include "c++Source/HBScreen/datetime.h"
#include "c++Source/HBScreen/configuration.h"

#include "c++Source/HBModbus/hbmodbusclient.h"
// #include "c++Source/HBModbus/modbusutils.h"
#include "c++Source/HBData/hbdatabase.h"

#include "c++Source/HBGraph/GraphAxisDefineHB.h"
#include "c++Source/HBGraph/SensorGraphData.h"

#include "c++Source/HBVideoCapture/videocapture.h"

#include "c++Source/HBVoice/hbvoice.h"
#include "c++Source/HBQmlEnum.h"
#include "c++Source/HBUtility/hbutilityclass.h"
#include "c++Source/usermanual.h"
#include "c++Source/HBKeyboard/PinyinDict.h"

void messageHandler(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &message)
{
    static QMutex mutex;
    mutex.lock();
    static QFile logFile(logUrl);
    if(logFile.open(QIODevice::ReadWrite | QIODevice::Append))
    {
        QTextStream stream(&logFile);
        stream << qFormatLogMessage(type, context, message) << "\r\n";
        logFile.flush();
        logFile.close();
    }
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    //HB
    HBDatabase& db = HBDatabase::GetInstance();
    db.loadDataFromDatabase();
    //       db.testUpdate();
    // ModbusUtils modbusUtils;
    // modbusUtils.setModbusClient(&modbusClient);
//    HBVoice VoicePlayer;
    HBUtilityClass::GetInstance();

    QString strOSIndicator = "None";
#ifdef WIN32
    strOSIndicator = "WINDOWS OS";
#elif linux
#ifdef RASPBERRY
    strOSIndicator = "Raspbian OS";
#else
    strOSIndicator = "Ubuntu OS";
#endif
#endif
    LanguageConfig::getInstance()->checkLanguageFiles();

    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/BransonStyle.qml"), "Style", 1, 0, "Style");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/BransonNumpadDefine.qml"), "NumpadDefine", 1, 0, "NumpadDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/BransonChartViewAxisDefine.qml"), "AxisDefine", 1, 0, "AxisDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/HBChartViewAxisDefine.qml"), "HBAxisDefine", 1, 0, "HBAxisDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/AlarmMessageDefine.qml"), "AlarmDefine", 1, 0, "AlarmDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/DepthGlobalDefine.qml"), "DepthGlobalDefine", 1, 0, "DepthGlobalDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/ProfileGlobalDefine.qml"), "ProfileGlobalDefine", 1, 0, "ProfileGlobalDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/TensionsGlobalDefine.qml"), "TensionsGlobalDefine", 1, 0, "TensionsGlobalDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/UserGlobalDefine.qml"), "UserGlobalDefine", 1, 0, "UserGlobalDefine");

    //HB
    qmlRegisterSingletonInstance<HBModbusClient>("HB.Modbus", 1, 0, "ModbusClient", HBModbusClient::GetInstance());
    qmlRegisterSingletonInstance("HB.Database", 1, 0, "HBDatabase", &HBDatabase::GetInstance());
    qmlRegisterType<HistoryOperationModel>("HB.HistoryOperationModel", 1, 0, "HistoryOperationModel");
    qmlRegisterUncreatableType<HQmlEnum>("HB.Enums", 1, 0, "HQmlEnum",
                                          "HQmlEnum is an enum container and cannot be created in QML");



    UserLevelEnum::registerQMLType();
    UIScreenEnum::registerQMLType();
    LanguageEnum::registerQMLType();
    RecipeEnum::registerQMLType();
    UpgradeSoftwareEnum::registerQMLType();
    GraphAxisEnum::registerQMLType();
    HBGraphAxisEnum::registerQMLType();
    AlarmIndexEnum::registerQMLType();
    LoginIndexEnum::registerQMLType();
    SystemTypeDef::registerQMLType();


    QQmlApplicationEngine engine;

    QQmlContext *pQmlContext = engine.rootContext();
    // pQmlContext->setContextProperty("ModbusUtils", &modbusUtils);
    pQmlContext->setContextProperty("HBHome", HBHome::GetInstance());
    pQmlContext->setContextProperty("AutoTestSpeed", AutoTestSpeed::GetInstance());
    pQmlContext->setContextProperty("Depth", DepthSetting::GetInstance());
    pQmlContext->setContextProperty("DepthMeter", DepthMeter::getInstance());
    pQmlContext->setContextProperty("DepthSiMan", DepthSiMan::GetInstance());
    pQmlContext->setContextProperty("Tensiometer", Tensiometer::GetInstance());
    pQmlContext->setContextProperty("TensionSafety", TensionSafety::GetInstance());
    pQmlContext->setContextProperty("WellParameter", WellParameter::GetInstance());
    pQmlContext->setContextProperty("TensiometerManager", TensiometerManager::GetInstance());
    pQmlContext->setContextProperty("TensionSetting", TensionSetting::GetInstance());
    pQmlContext->setContextProperty("TensiometerScale", TensionScaleManager::GetInstance());
    pQmlContext->setContextProperty("UserModel", &UserManagerModel::GetInstance());
    pQmlContext->setContextProperty("UserManual", UserManual::GetInstance());
    pQmlContext->setContextProperty("SensorGraphData", SensorGraphData::GetInstance());
    pQmlContext->setContextProperty("HistoryDataTable", HistoryDataTable::GetInstance());
    pQmlContext->setContextProperty("Configuration", Configuration::GetInstance());
    pQmlContext->setContextProperty("DateTime", DateTime::GetInstance());
    pQmlContext->setContextProperty("VideoCapture", VideoCapture::GetInstance());
    PinyinDict pinyinDict;
    pQmlContext->setContextProperty("PinyinDict", &pinyinDict);

#ifdef QT_DEBUG
    pQmlContext->setContextProperty("debug", true);
#else
    pQmlContext->setContextProperty("debug", false);
#endif
    pQmlContext->setContextProperty("languageConfig", LanguageConfig::getInstance());
    // pQmlContext->setContextProperty("languageModel", LanguageConfig::getInstance()->getLanguageModelInstance());
    // pQmlContext->setContextProperty("productionRunInterface", ProductionRun::getInstance());
    // pQmlContext->setContextProperty("weldGraphObj", WeldGraphData::getInstance());
    // pQmlContext->setContextProperty("softwareUpgrade", SoftwareUpgrading::getInstance());
    // pQmlContext->setContextProperty("recipeModel", RecipeModel::getInstance());
    // pQmlContext->setContextProperty("alarmNotification", AlarmNotification::getInstance());
    pQmlContext->setContextProperty("login", Login::getInstance());
    // pQmlContext->setContextProperty("communicationInterface", CommunicationInterface::getInstance(&app));
    pQmlContext->setContextProperty("systemInformationModel", SystemInformationInterface::getInstance());

    if(QFile::exists(logUrl) == true)
        QFile::remove(logUrl);
#ifdef QT_DEBUG //if need to debug you need to comment out these two lines code
    // qInstallMessageHandler(messageHandler);
    // qSetMessagePattern("%{time yyyy-MM-dd hh:mm:ss:zzz}|%{type}|%{file}|%{function}|%{line}|%{message}");
#else
    qInstallMessageHandler(messageHandler);
    qSetMessagePattern("%{time yyyy-MM-dd hh:mm:ss:zzz}|%{type}|%{file}|%{function}|%{line}|%{message}");
#endif

    if(QFile::exists(logUrl) == true)
        QFile::remove(logUrl);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
