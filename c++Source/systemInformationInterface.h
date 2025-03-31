#ifndef SystemInformationInterface_H
#define SystemInformationInterface_H

/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------

 This file is a header file and it is the model file of system information window.

 **********************************************************************************************************/



#include <QObject>
#include <QString>
#include "shareDefine.h"
#include "communicationinterface.h"
#include "systemTypeDef.h"


class SystemInformationInterface : public QObject
{
    Q_OBJECT
public:
    static SystemInformationInterface *getInstance();
        ~SystemInformationInterface();

    Q_INVOKABLE void loadSystemInformation();
    Q_INVOKABLE bool isShownTheItem(int itemType);
    Q_INVOKABLE int getSystemType();

    //model details
    Q_PROPERTY(QString strModelName READ getModelName WRITE updateModelName NOTIFY signalModelNameChanged);
    Q_PROPERTY(int iGerneralAlarm READ getGeneralAlarm WRITE updateGerneralAlarm NOTIFY signalGeneralAlarmChanged);

    //software version
    Q_PROPERTY(QString strUIController READ getUIController WRITE updateUIController NOTIFY signalUIControllerChanged);
    Q_PROPERTY(QString strSupervisoryController READ getSupervisoryController WRITE updateSupervisoryController NOTIFY signalSupervisoryControllerChanged);
    Q_PROPERTY(QString strActuatorController READ getActuatorController WRITE updateActuatorController NOTIFY signalActuatorControllerChanged);
    Q_PROPERTY(QString strPowerController READ getPowerController WRITE updatePowerController NOTIFY signalPowerControllerChanged);

    //Power Supply
    Q_PROPERTY(int iPSLifeWelds READ getPSLifeWelds WRITE updatePSLifeWelds NOTIFY signalPSLifeWeldsChanged);
    Q_PROPERTY(int iPSOverloads READ getPSOverloads WRITE updatePSOverloads NOTIFY signalPSOverloadsChanged);
    Q_PROPERTY(int iPSType READ getPSType WRITE updatePSType NOTIFY signalPSTypeChanged);
    Q_PROPERTY(int iPSFrequency READ getPSFrequency WRITE updatePSFrequency NOTIFY signalPSFrequencyChanged);
    Q_PROPERTY(int iPSWattage READ getPSWattage WRITE updatePSWattage NOTIFY signalPSWattageChanged);

    //Actuator actuatorlifecounter
    Q_PROPERTY(int iActuatorLifeCycle READ getActuatorLifeCycle WRITE updateActuatorLifeCycle NOTIFY signalActuatorLifeCycleChanged);
    Q_PROPERTY(int iActuatorType READ getActuatorType WRITE updateActuatorType NOTIFY signalActuatorTypeChanged);
    Q_PROPERTY(QString strActuatorCalibrationDate READ getActuatorCaliDate WRITE updateActuatorCaliDate NOTIFY signalActuatorCaliDateChanged);
    Q_PROPERTY(int iActuatorOverloads READ getActuatorOverloads WRITE updateActuatorOverloads NOTIFY signalActuatorOverloadsChanged);
    Q_PROPERTY(int iStrokeLength READ getStrokeLength WRITE updateStrokeLength NOTIFY signalStrokeLengthChanged);

    /********************NIST******************************/
    Q_PROPERTY(QString strNISTCalibrationDate READ getNISTCalibrationDate WRITE updateNISTCalibrationDate NOTIFY signalNISTCalibrationDateChanged);

    //Connectivity MAC ID
    Q_PROPERTY(QString strMACAddress READ getMACAddress WRITE updateMACAddress NOTIFY signalMACAddressChanged);


signals:
    void signalModelNameChanged();
    void signalGeneralAlarmChanged();
    void signalUIControllerChanged();
    void signalSupervisoryControllerChanged();
    void signalActuatorControllerChanged();
    void signalPowerControllerChanged();
    void signalPSLifeWeldsChanged();
    void signalPSOverloadsChanged();
    void signalPSTypeChanged();
    void signalPSFrequencyChanged();
    void signalPSWattageChanged();
    void signalActuatorLifeCycleChanged();
    void signalActuatorCaliDateChanged();
    void signalActuatorOverloadsChanged();
    void signalActuatorTypeChanged();
    void signalNISTCalibrationDateChanged();
    void signalStrokeLengthChanged();
    void signalMACAddressChanged();
public:
    /********************Model Details******************************/
    //model name
    QString getModelName() const;
    void updateModelName(const QString& strModelName);
    //Gerneral Alarm
    int getGeneralAlarm() const;
    void updateGerneralAlarm(const int& iGerneralAlarm);
    /********************Software version******************************/
    //UI controller
    QString getUIController() const;
    void updateUIController(const QString& strUIController);

    //Supervisory Controller
    QString getSupervisoryController() const;
    void updateSupervisoryController(const QString& strSupervisoryController);

    //Actuator Controller
    QString getActuatorController() const;
    void updateActuatorController(const QString& strActuatorController);

    //Power Controller
    QString getPowerController() const;
    void updatePowerController(const QString& strPowerController);
    /********************Power Supply******************************/
    //PS life time welds
    int getPSLifeWelds() const;
    void updatePSLifeWelds(const int& iPSLifeWelds);
    //PS Overload
    int getPSOverloads() const;
    void updatePSOverloads(const int& iOverloads);
    //PS Type
    int getPSType() const;
    void updatePSType(const int& iPSType);
    //PS Frequency
    int getPSFrequency() const;
    void updatePSFrequency(const int& iPSFrequency);
    //PS wattage
    int getPSWattage() const;
    void updatePSWattage(const int& iPSWattage);
    /********************Actuator******************************/
    //Lfit Cycle time
    int getActuatorLifeCycle() const;
    void updateActuatorLifeCycle(const int& iLifeCycle);
    //Actuator type
    int getActuatorType() const;
    void updateActuatorType(const int& iActuatorType);
    //Actuator Calibration Date
    QString getActuatorCaliDate() const;
    void updateActuatorCaliDate(const QString& strCalirationDate);
    //Actuator Overloads
    int getActuatorOverloads() const;
    void updateActuatorOverloads(const int& iActuatorOverloads);
    //Stroke Length
    int getStrokeLength() const;
    void updateStrokeLength(const int& iStrkenLenth);

    /********************NIST******************************/
    //NIST Calibration Date
    QString getNISTCalibrationDate() const;
    void updateNISTCalibrationDate(const QString& strNISTCalibrationDate);

    /********************Connectivity******************************/
    QString getMACAddress() const;
    void updateMACAddress(const QString& strMacAddress);

protected:
private:
    SystemInformationInterface(QObject *parent = nullptr);

private:
    static SystemInformationInterface* m_systemInformationInstance;

    /********************Model Details******************************/
    QString m_strModelName;
    int m_iGeneralAlarm;
    /********************Software version******************************/
    QString m_strUIController;
    QString m_strSupervisory;
    QString m_strActuatorController;
    QString m_strPowerController;
    /********************Power Supply******************************/
    int m_iPSLifeWelds;
    int m_iPSOverloads;
    int m_iPSType;
    int m_iPSFrequency;
    int m_iPSWattage;
    /********************Actuator******************************/
    int m_iActuatorLifeCycle;
    int m_iActuatorType;
    QString m_strCalibrationDate;
    int m_iActuatorOverloads;
    int m_iStrokeLength;
    /********************NIST******************************/
    QString m_strNISTCalibrationDate;
     /********************Connectivity******************************/
    QString m_strMacAddress;


    int m_iSystemType;

};



#endif // SystemInformationInterface_H

