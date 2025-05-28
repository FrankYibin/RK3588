#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QTimer>
#include <QVector>


class HBModbusClient : public QObject
{
    Q_OBJECT

public:

    //HOME
    int depth = 0;
    int speed = 0;
    int plus = 0;
    int tension = 0;
    int tensionIncrement = 0;
    int K_Value = 0;
    int maxTension = 0;
    int maxTensionIncrement = 0;
    int targetDepth = 0;
    int maxSpeed = 0;
    int cableTension = 0;

    //tensionsafe
    int wellType;
    int cableWeight;
    int TensionSafeFactor;
    int weakForce;
    //    int currentHarnessTension;
    int currentTensionSafe;
    int maxTensionSafe;
    int cableTensionTrend;
    int ptime;
    int depthLoss;
    int currentDepth1;
    int currentDepth2;
    int currentDepth3;

    //
    int m_targetLayerDepth = 0;
    int m_depthOrientation = 0;
    int m_meterDepth = 0;
    int depthCalculateType = 0;
    int m_velocityUnit = 0;
    int m_codeOption = 0;

    //

    int m_scale1;
    int m_scale2;
    int m_scale3;
    int m_scale4;
    int m_scale5;


public:
    explicit HBModbusClient(QObject *parent = nullptr);
    ~HBModbusClient();

    void readRegister(int address, int count = 1);
    Q_INVOKABLE void writeRegister(int address, const QVector<quint16> &values);
    Q_INVOKABLE void writeRegister(int address, const QVariantList &values);

    Q_INVOKABLE void readCoils();
    Q_INVOKABLE void writeCoil(int address, int value);
    void handleCoilResult(const QModbusDataUnit &result);
    void handleAlarm(int address, bool value);

    //historydata
    void insertDataToDatabase();


private:
    void connectToServer();
    void startBatchRead();
    void handleReadResult(const QModbusDataUnit &result);

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



private:
    QModbusClient *modbus = nullptr;
    QTimer *refreshTimer = nullptr;


    // HBHome *m_home;

};

#endif // HBMODBUSCLIENT_H
