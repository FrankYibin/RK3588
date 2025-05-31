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
    struct MODBUS_REGISTER
    {
        //HOME
        RAW_DATA m_Depth;
        RAW_DATA m_Speed;
        RAW_DATA m_MaxSpeed;
        RAW_DATA m_TargetLayerDepth;
        RAW_DATA m_MeterDepth;
        RAW_DATA m_Pulse;
        RAW_DATA m_DepthCalculateType;
        RAW_DATA m_EncoderDepth1;
        RAW_DATA m_EncoderDepth2;
        RAW_DATA m_EncoderDepth3;
        // above total 10 register
        RAW_DATA m_DeltaEncoderDepth;
        RAW_DATA m_DepthCountDown;
        RAW_DATA m_Tension;
        RAW_DATA m_TensionIncrement;
        RAW_DATA m_MaxTension;
        RAW_DATA m_MaxTensionIncrement;
        RAW_DATA m_CableTension;
        RAW_DATA m_K_Value;
        RAW_DATA m_TensionType;
        RAW_DATA m_AnalogTensionChannel;
        // above total 10 register
        RAW_DATA m_TensiometerBattery;
        RAW_DATA m_TensiometerNumber;
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
        RAW_DATA m_ScalesQuantity;
        RAW_DATA m_SpeedControlStatus;
        RAW_DATA m_ControlledSpeed;
        RAW_DATA m_4SlowSpeed;
        RAW_DATA m_PumpDownCurrent;
        RAW_DATA m_PumpUpCurrent;
        RAW_DATA m_MotorCurrent;
        RAW_DATA m_PotentiometerVol;
        // above total 10 register
        RAW_DATA m_PumpVol;
        RAW_DATA m_SpeedVol;
        RAW_DATA m_TensionBarWithTon;
        RAW_DATA m_CableSpec;
        RAW_DATA m_WellDepth;
        //tensionsafe
        RAW_DATA m_WellType;
        RAW_DATA m_OperatingType;
        RAW_DATA m_CableBrokenForce;
        RAW_DATA m_WeaknessForce;
        RAW_DATA m_CalbeWeightPerKiloMeter;
        // above total 10 register
        RAW_DATA m_CableWeight;
        RAW_DATA m_SenorWeight;
        RAW_DATA m_SafetyTensionFactor;
        RAW_DATA m_CurrentSafetyTension;
        RAW_DATA m_CurrentMaxTension;
        RAW_DATA m_CableTensionTrend;
        RAW_DATA m_ParkStopTimeStamp;
        RAW_DATA m_AlertDistanceForWellUpper;
        RAW_DATA m_AlertDistanceForWellLower;
        RAW_DATA m_InclinationAngle;
    };
    static MODBUS_REGISTER m_RecvReg;
    static MODBUS_REGISTER m_PrevRecvReg;

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
