#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QVector>
#include <QMap>
#include <QMutex>
#include <QVariant>
#include <QString>
#include "c++Source/HBScreen/depthsetting.h"
#include "c++Source/HBScreen/tensiometer.h"
class HBModbusClient : public QObject
{
    Q_OBJECT

private:
    struct RECV_DATA
    {
        int Data;
        int Address;
    };
    struct SEND_DATA
    {
        int Data;
        int Size;
    };
    struct REGISTER_DATA
    {
        quint16 HIGH_16BITS;
        quint16 LOW_16BITS;
    };

    struct MODBUS_REGISTER
    {
        //HOME
        RECV_DATA m_DepthCurrent;
        RECV_DATA m_VelocityCurrent;
        RECV_DATA m_VelocityLimited;
        RECV_DATA m_DepthTargetLayer;
        RECV_DATA m_DepthSurfaceCover;
        RECV_DATA m_PulseCount;
        RECV_DATA m_DepthEncoder;
        RECV_DATA m_DepthEncoder1;
        RECV_DATA m_DepthEncoder2;
        RECV_DATA m_DepthEncoder3;
        // above total 10 register
        RECV_DATA m_DepthTolerance;  //两个编码器深度实时误差
        RECV_DATA m_DepthCurrentDelta;   //深度倒计功能深度
        RECV_DATA m_TensionCurrent;
        RECV_DATA m_TensionCurrentDelta;
        RECV_DATA m_TensionLimited;
        RECV_DATA m_TensionLimitedDelta;
        RECV_DATA m_TensionCableHead;
        RECV_DATA m_K_Value;
        RECV_DATA m_TensionEncoder;
        RECV_DATA m_TensionAnalog;
        // above total 10 register
        RECV_DATA m_TensionBattery;
        RECV_DATA m_TensionNum;

        RECV_DATA m_Point1Scale;
        RECV_DATA m_Point1Tension;
        RECV_DATA m_Point2Scale;
        RECV_DATA m_Point2Tension;
        RECV_DATA m_Point3Scale;
        RECV_DATA m_Point3Tension;
        RECV_DATA m_Point4Scale;
        RECV_DATA m_Point4Tension;
        // above total 10 register
        RECV_DATA m_Point5Scale;
        RECV_DATA m_Point5Tension;

        RECV_DATA m_QuantityOfCalibration;
        RECV_DATA m_VelocityStatus;
        RECV_DATA m_VelocitySetting;
        RECV_DATA m_VelocitySiman;
        RECV_DATA m_CurrentPumpMoveDown;
        RECV_DATA m_CurrentPumpMoveUp;
        RECV_DATA m_CurrentMotor;
        RECV_DATA m_VoltageMotor;
        // above total 10 register
        RECV_DATA m_PercentPump;
        RECV_DATA m_PercentVelocity;
        RECV_DATA m_TonnageTensionStick;
        RECV_DATA m_CableSpec;
        RECV_DATA m_DepthWellSetting;
        //tensionsafe
        RECV_DATA m_WellType;
        RECV_DATA m_WorkType;
        RECV_DATA m_BreakingForceCable;
        RECV_DATA m_BreakingForceWeakness;
        RECV_DATA m_WeightEachKilometerCable;
        // above total 10 register
        RECV_DATA m_WeightInstrumentString;
        RECV_DATA m_TensionSafetyCoefficient;
        RECV_DATA m_TensionCurrentSafety;
        RECV_DATA m_TensionCurrentLimited;
        RECV_DATA m_TensionCableHeadTrend;
        RECV_DATA m_TimeSafetyStop;
        RECV_DATA m_DistanceUpperWellSetting;
        RECV_DATA m_DistanceLowerWellSetting;
        RECV_DATA m_SlopeAngleWellSetting;
    };

    REGISTER_DATA m_RegisterData;

    static MODBUS_REGISTER m_RecvReg;
    static MODBUS_REGISTER m_PrevRecvReg;

    static QModbusClient *_ptrModbus;
    static int m_timerIdentifier;
    static QMap<int, SEND_DATA> m_RegisterSendMap;
    static QMutex m_mutexSending;

    static constexpr int ONE_SECOND         = 100;
    static constexpr int MAX_TRIED_COUNT    = 5;
public:
    explicit HBModbusClient(QObject *parent = nullptr);
    ~HBModbusClient();

    void readRegister(int address, int count = 1);

    Q_INVOKABLE void writeRegister(const int address, const QVariant value);

    Q_INVOKABLE void readCoils();
    Q_INVOKABLE void writeCoil(int address, int value);
    void handleCoilResult(const QModbusDataUnit &result);
    void handleAlarm(int address, bool value);

    //historydata
    void insertDataToDatabase();
protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void connectToServer();
    void handleReadResult(const QModbusDataUnit &result);
    void handleWriteRequest();
    void compareRawData();

    void writeRegister(int address, const QVector<quint16> &values);


    //Dashboard
    QString updateDepthInterface    (const int hexData, const int hexAddress);
    QString updateVelocityInterface (const int hexData, const int hexAddress);
    QString updateTensionInterface  (const int hexData, const int hexAddress);
    QString updatePulseCount        (const int hexData, const int hexAddress);
    QString updateKValue            (const int hexData, const int hexAddress);
    //Depth Setting
    void    updateDepthOrientation  (const int hexData, const int hexAddress);
    int     updateDepthEncoder      (const int hexData, const int hexAddress);
    // void updateVelocityLimited(const int hexData, const int hexAddress);
    // void updateDepthEncoder(const int hexData, const int hexAddress);
    // void updateDepthEncoder(const int hexData, const int hexAddress);

    int     getDepthInterface       (const QString strData, const int hexAddress);
    int     getPulseCount           (const QString strData, const int hexAddress);
    int     getVelocityInterface    (const QString strData, const int hexAddress);
signals:

private:
    quint16 Depth_H = 0;
    quint16 Depth_L = 0;
    quint16 Speed_H = 0;
    quint16 Speed_L = 0;
    quint16 Tension_H = 0;
    quint16 Tension_L = 0;
    quint16 TensionIncrement_H = 0;
    quint16 TensionIncrement_L = 0;
    quint16 MaxTension_H = 0;
    quint16 MaxTension_L = 0;
    quint16 MaxTensionIncrement_H = 0;
    quint16 MaxTensionIncrement_L = 0;
    quint16 MaxSpeed_H = 0;
    quint16 MaxSpeed_L = 0;
    quint16 TargetDepth_H = 0;
    quint16 TargetDepth_L = 0;
    quint16 CableTension_H = 0;
    quint16 CableTension_L = 0;

    quint16 TensionNum_H;
    quint16 TensionNum_L;

    //tensionsafe


    quint16 currentTensionSafe_H;
    quint16 currentTensionSafe_L;
    quint16 maxTensionSafe_H;
    quint16 maxTensionSafe_L;
    quint16 depthLoss_H;
    quint16 depthLoss_L;
    quint16 currentDepth1_H;
    quint16 currentDepth1_L;
    quint16 currentDepth2_H;
    quint16 currentDepth2_L;
    quint16 currentDepth3_H;
    quint16 currentDepth3_L;
    //    quint16 currentHarnessTension_H;
    //    quint16 currentHarnessTension_L;

    quint16 scale1_H;
    quint16 scale1_L;

    quint16 scale2_H;
    quint16 scale2_L;


    quint16 scale3_H;
    quint16 scale3_L;
    quint16 scale4_H;
    quint16 scale4_L;
    quint16 scale5_H;
    quint16 scale5_L;

    DepthSetting::VELOCITY_UNIT m_VelocityUnit;
    DepthSetting::DISTANCE_UNIT m_DistanceUnit;
    DepthSetting::TIME_UNIT     m_TimeUnit;
    Tensiometer::FORCE_UNIT     m_ForceUnit;
};

#endif // HBMODBUSCLIENT_H
