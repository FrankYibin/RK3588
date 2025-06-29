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
#include "c++Source/HBScreen/tensionsetting.h"
#include "c++Source/clientsocket.h"
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
        int Type;
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
        RECV_DATA m_ScaleCurrent;
        RECV_DATA m_K_Value;
        RECV_DATA m_TensiometerEncoder;
        RECV_DATA m_TensiometerAnalog;
        // above total 10 register
        RECV_DATA m_TensiometerBattery;
        RECV_DATA m_TensiometerNum;

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
        RECV_DATA m_DepthStartSetting;
        RECV_DATA m_DepthFinishSetting;
    };

    union MODBUS_IO_VALUE0
    {
        unsigned char byte_Value0;
        struct BITS_VALUE0
        {
            unsigned char m_IsMute : 1;
            unsigned char m_OrientationDepth : 1;
            unsigned char m_EnableVelocityControl : 1;
            unsigned char m_EnableTensiometerCalibration : 1;
            unsigned char m_StatusTensionProtected : 1;
            unsigned char m_IndicateTensionReset : 1;
            unsigned char m_StatusTensiometerOnline : 1;
            unsigned char m_IndicateMoveUpMoveDown : 1;
        }bits_Value0;
    };

    union MODBUS_IO_VALUE1
    {
        unsigned char byte_Value1;
        struct BITS_VALUE1
        {
            unsigned char m_IndicateSafetyStop : 1;
            unsigned char m_IndicateSimanAlert : 1;
            unsigned char m_IndicateSimanStop : 1;
            unsigned char m_ReservedValue1: 5;
        }bits_Value1;
    };

    union MODBUS_IO_VALUE2
    {
        unsigned char byte_Value2;
        struct BITS_VALUE2
        {
            unsigned char m_AlarmVelocity: 1;
            unsigned char m_AlarmWellSurface : 1;
            unsigned char m_AlarmTargetLayer : 1;
            unsigned char m_AlarmSurfaceCover : 1;
            unsigned char m_AlarmTension : 1;
            unsigned char m_AlarmTensionDeltaSlow : 1;
            unsigned char m_AlarmTensionDeltaStop : 1;
            unsigned char m_AlarmTensionCableHeadSlow : 1;
        }bits_Value2;
    };

    union MODBUS_IO_VALUE3
    {
        unsigned char byte_Value3;
        struct BITS_VALUE3
        {
            unsigned char m_AlarmTensionCableHeadStop : 1;
            unsigned char m_AlarmEncoder1 : 1;
            unsigned char m_AlarmEncoder2 : 1;
            unsigned char m_AlarmEncoder3 : 1;
            unsigned char m_AlarmDrowsy : 4;
        }bits_Value3;
    };

    union MODBUS_IO_VALUE4
    {
        unsigned char byte_Value4;
        struct BITS_VALUE4
        {
            unsigned char m_EnableSimanControl : 1;
            unsigned char m_EnableSimanFunction : 1;
            unsigned char m_EnableMoveForward : 1;
            unsigned char m_EnableMoveBackward : 1;
            unsigned char m_StatusBrakeValve1 : 1;
            unsigned char m_StatusBrakeValve2 : 1;
            unsigned char m_EnableManualControl : 1;
            unsigned char m_ModeVelocityControl : 1;
        }bits_Value4;
    };

    union MODBUS_IO_VALUE5
    {
        unsigned char byte_Value5;
        struct BITS_VALUE5
        {
            unsigned char m_StatusHandle : 1;
            unsigned char m_FailureHandle : 1;
            unsigned char m_FailureMoveDownValve : 1;
            unsigned char m_FailureMoveUpValve : 1;
            unsigned char m_FailureMotor : 1;
            unsigned char m_FailureInitialization : 1;
            unsigned char m_ReservedValue5 : 2;
        }bits_Value5;
    };

    REGISTER_DATA m_RegisterData;

    static MODBUS_REGISTER m_RecvReg;
    static MODBUS_REGISTER m_PrevRecvReg;
    static MODBUS_IO_VALUE0 m_IO_Value0;
    static MODBUS_IO_VALUE1 m_IO_Value1;
    static MODBUS_IO_VALUE2 m_IO_Value2;
    static MODBUS_IO_VALUE3 m_IO_Value3;
    static MODBUS_IO_VALUE4 m_IO_Value4;
    static MODBUS_IO_VALUE5 m_IO_Value5;

    static QModbusClient *_ptrModbus;
    static HBModbusClient *_ptrHBModbusClient;
    static int m_timerIdentifier;
    static QMap<int, SEND_DATA> m_RegisterSendMap;
    static QMutex m_mutexSending;

    static constexpr int ONE_SECOND         = 100;
    static constexpr int MAX_TRIED_COUNT    = 5;

    static clientSocket* _ptrSocketObj;
public:
    static HBModbusClient *GetInstance();
    ~HBModbusClient();

    Q_INVOKABLE void writeRegister  (const int address, const QVariant  value);
    Q_INVOKABLE void writeCoil      (const int address, const int       value);
protected:
    explicit HBModbusClient(QObject *parent = nullptr);
    void timerEvent(QTimerEvent *event) override;

private:
    void connectToServer    ();
    void readRegisters      (const int address, const int count = 1);
    void readCoils          (const int address, const int count = 1);

    void handleParseRegisters(const QModbusDataUnit &result);
    void handleParseCoils(const QModbusDataUnit &result);


    void handleWriteRequest();
    void handleWriteRegister(const int address, const QVector<quint16> &values);
    void handleWriteCoil(const int address, const int value);
    void handleRawData();

    void handleDevice();
    void handleAlarm();
    void handleCANbus();

    void Insert4GData();

    //historydata
    void InsertDataToDatabase();

    //Dashboard
    QString updateDepthInterface    (const int hexData, const int hexAddress);
    QString updateVelocityInterface (const int hexData, const int hexAddress);
    QString updateTensionInterface  (const int hexData, const int hexAddress);
    QString updatePulseCount        (const int hexData, const int hexAddress);
    QString updateKValue            (const int hexData, const int hexAddress);
    //Depth Setting
    void    updateDepthOrientation  (const int hexData, const int hexAddress);
    int     updateDepthEncoder      (const int hexData, const int hexAddress);
    int     updateWellType          (const int hexData, const int hexAddress);
    int     updateWorkType          (const int hexData, const int hexAddress);
    int     updateCalbeHeadTrend    (const int hexData, const int hexAddress);
    int     updateCableSpec         (const int hexData, const int hexAddress);
    int     updateTensiometerEncoder(const int hexData, const int hexAddress);
    int     updateTensiometerAnalog (const int hexData, const int hexAddress);
    QString updateIntegerInterface  (const int hexData, const int hexAddress);
    QString updateSafetyCoefficient (const int hexData, const int hexAddress);
    QString updateTimeSafetyStop    (const int hexData, const int hexAddress);
    QString updateSlopeAngleWell    (const int hexData, const int hexAddress);
    QString updateTonnageStick      (const int hexData, const int hexAddress);
    // void updateVelocityLimited(const int hexData, const int hexAddress);
    // void updateDepthEncoder(const int hexData, const int hexAddress);
    // void updateDepthEncoder(const int hexData, const int hexAddress);
    QString updateTwoDecimal        (const int hexData, const int hexAddress);

    int     getDepthInterface       (const QString strData, const int hexAddress);
    int     getTensionInterface     (const QString strData, const int hexAddress);
    int     getPulseCount           (const QString strData, const int hexAddress);
    int     getVelocityInterface    (const QString strData, const int hexAddress);
    int     getIntegerInterface     (const QString strData, const int hexAddress);
    int     getSafetyCoefficient    (const QString strData, const int hexAddress);
    int     getTimeSafetyStop       (const QString strData, const int hexAddress);
    int     getSlopeAngleWell       (const QString strData, const int hexAddress);
    int     getTonnageStick         (const QString strData, const int hexAddress);
    int     getKValue               (const QString strData, const int hexAddress);

    int     MakeReportData(char* pBuffer, int deep, int speed, int tension, int tension_delta, short pulse, short kValue, char* wellNum);
    int     MakeReport(const char* pData, int len, char* pOutbuf);

signals:

private:
    DepthSetting::VELOCITY_UNIT m_VelocityUnit;
    DepthSetting::DISTANCE_UNIT m_DistanceUnit;
    DepthSetting::TIME_UNIT     m_TimeUnit;
    TensionSetting::FORCE_UNIT  m_ForceUnit;

    MODBUS_IO_VALUE2 m_LastIO_Value2{};
    MODBUS_IO_VALUE3 m_LastIO_Value3{};
};

#endif // HBMODBUSCLIENT_H
