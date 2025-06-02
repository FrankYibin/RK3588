#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QVector>
#include <QMap>
#include <QMutex>
class HBModbusClient : public QObject
{
    Q_OBJECT

private:
    struct RAW_DATA
    {
        int Data;
        int Address;
    };
    struct REGISTER_DATA
    {
        quint16 HIGH_16BITS;
        quint16 LOW_16BITS;
    };

    struct MODBUS_REGISTER
    {
        //HOME
        RAW_DATA m_DepthCurrent;
        RAW_DATA m_VelocityCurrent;
        RAW_DATA m_VelocityLimited;
        RAW_DATA m_DepthTargetLayer;
        RAW_DATA m_DepthSurfaceCover;
        RAW_DATA m_PulseCount;
        RAW_DATA m_DepthEncoder;
        RAW_DATA m_DepthEncoder1;
        RAW_DATA m_DepthEncoder2;
        RAW_DATA m_DepthEncoder3;
        // above total 10 register
        RAW_DATA m_DepthTolerance;  //两个编码器深度实时误差
        RAW_DATA m_DepthCurrentDelta;   //深度倒计功能深度
        RAW_DATA m_TensionCurrent;
        RAW_DATA m_TensionCurrentDelta;
        RAW_DATA m_TensionLimited;
        RAW_DATA m_TensionLimitedDelta;
        RAW_DATA m_TensionCableHead;
        RAW_DATA m_K_Value;
        RAW_DATA m_TensionEncoder;
        RAW_DATA m_TensionAnalog;
        // above total 10 register
        RAW_DATA m_TensionBattery;
        RAW_DATA m_TensionNum;

        RAW_DATA m_Point1Scale;
        RAW_DATA m_Point1Tension;
        RAW_DATA m_Point2Scale;
        RAW_DATA m_Point2Tension;
        RAW_DATA m_Point3Scale;
        RAW_DATA m_Point3Tension;
        RAW_DATA m_Point4Scale;
        RAW_DATA m_Point4Tension;
        // above total 10 register
        RAW_DATA m_Point5Scale;
        RAW_DATA m_Point5Tension;

        RAW_DATA m_QuantityOfCalibration;
        RAW_DATA m_VelocityStatus;
        RAW_DATA m_VelocitySetting;
        RAW_DATA m_VelocitySiman;
        RAW_DATA m_CurrentPumpMoveDown;
        RAW_DATA m_CurrentPumpMoveUp;
        RAW_DATA m_CurrentMotor;
        RAW_DATA m_VoltageMotor;
        // above total 10 register
        RAW_DATA m_PercentPump;
        RAW_DATA m_PercentVelocity;
        RAW_DATA m_TonnageTensionStick;
        RAW_DATA m_CableSpec;
        RAW_DATA m_DepthWellSetting;
        //tensionsafe
        RAW_DATA m_WellType;
        RAW_DATA m_WorkType;
        RAW_DATA m_BreakingForceCable;
        RAW_DATA m_BreakingForceWeakness;
        RAW_DATA m_WeightEachKilometerCable;
        // above total 10 register
        RAW_DATA m_WeightInstrumentString;
        RAW_DATA m_TensionSafetyCoefficient;
        RAW_DATA m_TensionCurrentSafety;
        RAW_DATA m_TensionCurrentLimited;
        RAW_DATA m_TensionCableHeadTrend;
        RAW_DATA m_TimeSafetyStop;
        RAW_DATA m_DistanceUpperWellSetting;
        RAW_DATA m_DistanceLowerWellSetting;
        RAW_DATA m_SlopeAngleWellSetting;
    };
    static MODBUS_REGISTER m_RecvReg;
    static MODBUS_REGISTER m_PrevRecvReg;
    REGISTER_DATA m_RegisterData;

    static QModbusClient *_ptrModbus;
    static int m_timerIdentifier;
    static QMap<int, int> m_RegisterSendMap;
    static QMutex m_mutexSending;

public:
    explicit HBModbusClient(QObject *parent = nullptr);
    ~HBModbusClient();

    void readRegister(int address, int count = 1);

    Q_INVOKABLE bool writeRegister(const int address, const int value);

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
    void startBatchRead();
    void handleReadResult(const QModbusDataUnit &result);
    void compareRawData();

    void writeRegister(int address, const QVector<quint16> &values);
    void writeRegister(int address, const QVariantList &values);

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

};

#endif // HBMODBUSCLIENT_H
