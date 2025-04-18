﻿/**********************************************************************************************************

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
#include "c++Source/HBModel/hbhome.h"
#include "c++Source/HBModel/autotestspeed.h"
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
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

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
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/AlarmMessageDefine.qml"), "AlarmDefine", 1, 0, "AlarmDefine");

    //qmlRegisterType<HBHome>("HBHome",1,0,"HBHome");
    UserLevelEnum::registerQMLType();
    UIScreenEnum::registerQMLType();
    LanguageEnum::registerQMLType();
    RecipeEnum::registerQMLType();
    UpgradeSoftwareEnum::registerQMLType();
    GraphAxisEnum::registerQMLType();
    AlarmIndexEnum::registerQMLType();
    LoginIndexEnum::registerQMLType();
    SystemTypeDef::registerQMLType();


    QQmlApplicationEngine engine;
    engine.addImportPath(":/VirtualKeyboardStyles");
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "styleVirtualKeyboard");
    QQmlContext *pQmlContext = engine.rootContext();
    pQmlContext->setContextProperty("HBHome",new HBHome());
    pQmlContext->setContextProperty("AutoTestSpeed",new AutoTestSpeed());
#ifdef QT_DEBUG
    pQmlContext->setContextProperty("debug", true);
#else
    pQmlContext->setContextProperty("debug", false);
#endif
    pQmlContext->setContextProperty("languageConfig", LanguageConfig::getInstance());
    pQmlContext->setContextProperty("languageModel", LanguageConfig::getInstance()->getLanguageModelInstance());
    pQmlContext->setContextProperty("productionRunInterface", ProductionRun::getInstance());
    pQmlContext->setContextProperty("weldGraphObj", WeldGraphData::getInstance());
    pQmlContext->setContextProperty("softwareUpgrade", SoftwareUpgrading::getInstance());
    pQmlContext->setContextProperty("recipeModel", RecipeModel::getInstance());
    pQmlContext->setContextProperty("alarmNotification", AlarmNotification::getInstance());
    pQmlContext->setContextProperty("login", Login::getInstance());
    pQmlContext->setContextProperty("communicationInterface", CommunicationInterface::getInstance(&app));
    pQmlContext->setContextProperty("systemInformationModel", SystemInformationInterface::getInstance());

    if(QFile::exists(logUrl) == true)
        QFile::remove(logUrl);
#ifdef QT_DEBUG

#else
    qInstallMessageHandler(messageHandler);
    qSetMessagePattern("%{time yyyy-MM-dd hh:mm:ss:zzz}|%{type}|%{file}|%{function}|%{line}|%{message}");
#endif
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
