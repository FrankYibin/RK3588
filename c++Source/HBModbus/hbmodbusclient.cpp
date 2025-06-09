#include "hbmodbusclient.h"
#include <QDebug>
#include <QSerialPort>
#include <QModbusReply>
#include "c++Source/HBQmlEnum.h"
#include "c++Source/HBScreen/hbhome.h"
#include "c++Source/HBScreen/depthsetting.h"
#include "c++Source/HBScreen/tensionsafety.h"
#include "c++Source/HBDefine.h"
#include "c++Source/HBData/hbdatabase.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBUtility/hbutilityclass.h"
#include <QtConcurrent>
#include <QHash>
#include <cstring>
#include <QVariant>

HBModbusClient::MODBUS_REGISTER HBModbusClient::m_RecvReg;
HBModbusClient::MODBUS_REGISTER HBModbusClient::m_PrevRecvReg;

HBModbusClient::MODBUS_IO_VALUE0 HBModbusClient::m_IO_Value0;
HBModbusClient::MODBUS_IO_VALUE1 HBModbusClient::m_IO_Value1;
HBModbusClient::MODBUS_IO_VALUE2 HBModbusClient::m_IO_Value2;
HBModbusClient::MODBUS_IO_VALUE3 HBModbusClient::m_IO_Value3;
HBModbusClient::MODBUS_IO_VALUE4 HBModbusClient::m_IO_Value4;
HBModbusClient::MODBUS_IO_VALUE5 HBModbusClient::m_IO_Value5;

QModbusClient* HBModbusClient::_ptrModbus = nullptr;
int HBModbusClient::m_timerIdentifier = -1;
QMap<int, HBModbusClient::SEND_DATA> HBModbusClient::m_RegisterSendMap;
QMutex HBModbusClient::m_mutexSending;


HBModbusClient::HBModbusClient(QObject *parent)
    : QObject{parent}
{
    _ptrModbus = new QModbusRtuSerialMaster(this);
    connectToServer();
    m_timerIdentifier = startTimer(100);
    m_RegisterSendMap.clear();

    m_VelocityUnit  = DepthSetting::M_PER_HOUR;
    m_DistanceUnit  = DepthSetting::METER;
    m_TimeUnit      = DepthSetting::HOUR;
    m_ForceUnit     = TensionSetting::LB;
    memset(&m_PrevRecvReg, 0xff, sizeof(MODBUS_REGISTER));
}

void HBModbusClient::timerEvent(QTimerEvent *event)
{
    static int iTick10MS = 0;
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState)
    {
        // qWarning() << "Modbus is not connected.";
        return;
    }

    if(event->timerId() == m_timerIdentifier)
    {
        handleRawData();
        handleAlarm();
        handleDevice();
        handleCANbus();
        if(iTick10MS % 10 == 0)
        {
            readRegisters   (0, HQmlEnum::MAX_REGISTR);
            readCoils       (0, HQmlEnum::MAX_COIL);
        }
        else
        {
            handleWriteRequest();
        }
        iTick10MS++;
    }
}

HBModbusClient::~HBModbusClient()
{
    if (_ptrModbus)
        _ptrModbus->disconnectDevice();
    delete _ptrModbus;
}

void HBModbusClient::connectToServer()
{
    if (_ptrModbus == nullptr)
        return;
#ifdef RK3588
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyS3");
#else
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM6");
#endif
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    _ptrModbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    _ptrModbus->setTimeout(200);
    _ptrModbus->setNumberOfRetries(5);
    if (!_ptrModbus->connectDevice())
    {
        qWarning() << "Connection failed:" << _ptrModbus->errorString();
    }
    else
    {
        qDebug() << "Modbus serial connection established.";
    }
}

void HBModbusClient::readRegisters(const int address, const int count)
{
    QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, count);

    if (auto *reply = _ptrModbus->sendReadRequest(request, 1))
    {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit result = reply->result();
                handleParseRegisters(result);
            } else {
                qWarning() << "Read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
    else
    {
        qWarning() << "Failed to send read request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::handleParseRegisters(const QModbusDataUnit &result)
{
    int startAddress = result.startAddress();
    int count = result.valueCount();
    int tmpData;
    for (int i = 0; i < count; ++i)
    {
        int currentAddress = startAddress + i;
        // qDebug() << "Start Address: " << currentAddress;
        quint16 value = result.value(i);

        switch (currentAddress) {
        case HQmlEnum::DEPTH_CURRENT_H: // DEPTH_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_CURRENT_L: // DEPTH_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthCurrent.Data      = tmpData;
            m_RecvReg.m_DepthCurrent.Address   = currentAddress;
            break;
        case HQmlEnum::VELOCITY_CURRENT_H: // SPEED_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::VELOCITY_CURRENT_L: // SPEED_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_VelocityCurrent.Data      = tmpData;
            m_RecvReg.m_VelocityCurrent.Address   = currentAddress;
            break;
        case HQmlEnum::VELOCITY_LIMITED_H: // MAX_SPEED_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::VELOCITY_LIMITED_L: // MAX_SPEED_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_VelocityLimited.Data = tmpData;
            m_RecvReg.m_VelocityLimited.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_TARGET_LAYER_H: // MAX_SPEED_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_TARGET_LAYER_L: // MAX_SPEED_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthTargetLayer.Data = tmpData;
            m_RecvReg.m_DepthTargetLayer.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_SURFACE_COVER_H: // 表套深度高
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_SURFACE_COVER_L: //
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthSurfaceCover.Data = tmpData;
            m_RecvReg.m_DepthSurfaceCover.Address = currentAddress;
            break;
        case HQmlEnum::PULSE_COUNT: // PULSE
            m_RecvReg.m_PulseCount.Data = value;
            m_RecvReg.m_PulseCount.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_ENCODER:
            m_RecvReg.m_DepthEncoder.Data = value;
            m_RecvReg.m_DepthEncoder.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_ENCODER_1_H: // DEPTH_CODE1_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_ENCODER_1_L: // DEPTH_CODE1_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthEncoder1.Data = tmpData;
            m_RecvReg.m_DepthEncoder1.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_ENCODER_2_H: // DEPTH_CODE2_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_ENCODER_2_L: // DEPTH_CODE2_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthEncoder2.Data = tmpData;
            m_RecvReg.m_DepthEncoder2.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_ENCODER_3_H: // DEPTH_CODE3_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_ENCODER_3_L: // DEPTH_CODE3_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthEncoder3.Data = tmpData;
            m_RecvReg.m_DepthEncoder3.Address =  currentAddress;
            break;
        case HQmlEnum::DEPTH_TOLERANCE_H: // CODE_COUNT_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_TOLERANCE_L: // CODE_COUNT_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthTolerance.Data = tmpData;
            m_RecvReg.m_DepthTolerance.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_CURRENT_DELTA:
            m_RecvReg.m_DepthCurrentDelta.Data = value;
            m_RecvReg.m_DepthCurrentDelta.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_CURRENT_H: // TENSION_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_CURRENT_L: // TENSION_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionCurrent.Data = tmpData;
            m_RecvReg.m_TensionCurrent.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_CURRENT_DELTA_H: // TENSION_INCREMENT_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_CURRENT_DELTA_L: // TENSION_INCREMENT_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionCurrentDelta.Data = tmpData;
            m_RecvReg.m_TensionCurrentDelta.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_LIMITED_H: // MAX_TENSION_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_LIMITED_L: // MAX_TENSION_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionLimited.Data = tmpData;
            m_RecvReg.m_TensionLimited.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_LIMITED_DELTA_H: // MAX_TENSION_INCREMENT_L
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_LIMITED_DELTA_L: // MAX_TENSION_INCREMENT_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionLimitedDelta.Data = tmpData;
            m_RecvReg.m_TensionLimitedDelta.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_CABLE_HEAD_H: // CABLE_TENSION_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_CABLE_HEAD_L: // CABLE_TENSION_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionCableHead.Data = tmpData;
            m_RecvReg.m_TensionCableHead.Address = currentAddress;
            break;
        case HQmlEnum::K_VALUE:
            m_RecvReg.m_K_Value.Data = value;
            m_RecvReg.m_K_Value.Address = currentAddress;
            break;
        case HQmlEnum::TENSIOMETER_ENCODER:
            m_RecvReg.m_TensiometerEncoder.Data = value;
            m_RecvReg.m_TensiometerEncoder.Address = currentAddress;
            break;
        case HQmlEnum::TENSIOMETER_ANALOG:
            m_RecvReg.m_TensiometerAnalog.Data = value;
            m_RecvReg.m_TensiometerAnalog.Address = currentAddress;
            break;
        case HQmlEnum::TENSIOMETER_BATTERY:
            m_RecvReg.m_TensiometerBattery.Data = value;
            m_RecvReg.m_TensiometerBattery.Address = currentAddress;
            break;
        case HQmlEnum::TENSIOMETER_NUM_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSIOMETER_NUM_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensiometerNum.Data = tmpData;
            m_RecvReg.m_TensiometerNum.Address = currentAddress;
            break;
        case HQmlEnum::SCALE_1_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::SCALE_1_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point1Scale.Data = tmpData;
            m_RecvReg.m_Point1Scale.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_1_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_1_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point1Tension.Data = tmpData;
            m_RecvReg.m_Point1Tension.Address = currentAddress;
            break;
        case HQmlEnum::SCALE_2_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::SCALE_2_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point2Scale.Data = tmpData;
            m_RecvReg.m_Point2Scale.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_2_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_2_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point2Tension.Data = tmpData;
            m_RecvReg.m_Point2Tension.Address = currentAddress;
            break;
        case HQmlEnum::SCALE_3_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::SCALE_3_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point3Scale.Data = tmpData;
            m_RecvReg.m_Point3Scale.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_3_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_3_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point3Tension.Data = tmpData;
            m_RecvReg.m_Point3Tension.Address = currentAddress;
            break;
        case HQmlEnum::SCALE_4_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::SCALE_4_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point4Scale.Data = tmpData;
            m_RecvReg.m_Point4Scale.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_4_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_4_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point4Tension.Data = tmpData;
            m_RecvReg.m_Point4Tension.Address = currentAddress;
            break;
        case HQmlEnum::SCALE_5_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::SCALE_5_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point5Scale.Data = tmpData;
            m_RecvReg.m_Point5Scale.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_5_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_5_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_Point5Tension.Data = tmpData;
            m_RecvReg.m_Point5Tension.Address = currentAddress;
            break;
        case HQmlEnum::QUANTITY_OF_CALIBRATION:
            m_RecvReg.m_QuantityOfCalibration.Data = value;
            m_RecvReg.m_QuantityOfCalibration.Address = currentAddress;
            break;
        case HQmlEnum::VELOCITY_STATUS:
            m_RecvReg.m_VelocityStatus.Data = value;
            m_RecvReg.m_VelocityStatus.Address = currentAddress;
            break;
        case HQmlEnum::VELOCITY_SETTING_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::VELOCITY_SETTING_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_VelocitySetting.Data = tmpData;
            m_RecvReg.m_VelocitySetting.Address = currentAddress;
            break;
        case HQmlEnum::VELOCITY_SIMAN_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::VELOCITY_SIMAN_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_VelocitySiman.Data = tmpData;
            m_RecvReg.m_VelocitySiman.Address = currentAddress;
            break;
        case HQmlEnum::CURRENT_PUMP_MOVE_DOWN:
            m_RecvReg.m_CurrentPumpMoveDown.Data = value;
            m_RecvReg.m_CurrentPumpMoveDown.Address = currentAddress;
            break;
        case HQmlEnum::CURRENT_PUMP_MOVE_UP:
            m_RecvReg.m_CurrentPumpMoveUp.Data = value;
            m_RecvReg.m_CurrentPumpMoveUp.Address = currentAddress;
            break;
        case HQmlEnum::CURRENT_MOTOR:
            m_RecvReg.m_CurrentMotor.Data = value;
            m_RecvReg.m_CurrentMotor.Address = currentAddress;
            break;
        case HQmlEnum::VOLOTAGE_MOTOR:
            m_RecvReg.m_VoltageMotor.Data = value;
            m_RecvReg.m_VoltageMotor.Address = currentAddress;
            break;
        case HQmlEnum::PERCENT_PUMP:
            m_RecvReg.m_PercentPump.Data = value;
            m_RecvReg.m_PercentPump.Address = currentAddress;
            break;
        case HQmlEnum::PERCENT_VELOCITY:
            m_RecvReg.m_PercentVelocity.Data = value;
            m_RecvReg.m_PercentVelocity.Address = currentAddress;
            break;
        case HQmlEnum::TONNAGE_TENSION_STICK:
            m_RecvReg.m_TonnageTensionStick.Data = value;
            m_RecvReg.m_TonnageTensionStick.Address = currentAddress;
            break;
        case HQmlEnum::CABLE_SPEC:
            m_RecvReg.m_CableSpec.Data = value;
            m_RecvReg.m_CableSpec.Address = currentAddress;
            break;
        case HQmlEnum::DEPTH_WELL_SETTING_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DEPTH_WELL_SETTING_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DepthWellSetting.Data = tmpData;
            m_RecvReg.m_DepthWellSetting.Address = currentAddress;
            break;
        case HQmlEnum::WELL_TYPE:
            m_RecvReg.m_WellType.Data = value;
            m_RecvReg.m_WellType.Address = currentAddress;
            break;
        case HQmlEnum::WOKE_TYPE:
            m_RecvReg.m_WorkType.Data = value;
            m_RecvReg.m_WorkType.Address = currentAddress;
            break;
        case HQmlEnum::BREAKING_FORCE_CABLE:
            m_RecvReg.m_BreakingForceCable.Data = value;
            m_RecvReg.m_BreakingForceCable.Address = currentAddress;
            break;
        case HQmlEnum::BREAKING_FORCE_WEAKNESS:
            m_RecvReg.m_BreakingForceWeakness.Data = value;
            m_RecvReg.m_BreakingForceWeakness.Address = currentAddress;
            break;
        case HQmlEnum::WEIGHT_EACH_KILOMETER_CABLE:
            m_RecvReg.m_WeightEachKilometerCable.Data = value;
            m_RecvReg.m_WeightEachKilometerCable.Address = currentAddress;
            break;
        case HQmlEnum::WEIGHT_INSTRUMENT_STRING:
            m_RecvReg.m_WeightInstrumentString.Data = value;
            m_RecvReg.m_WeightInstrumentString.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_SAFETY_COEFFICIENT:
            m_RecvReg.m_TensionSafetyCoefficient.Data = value;
            m_RecvReg.m_TensionSafetyCoefficient.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_CURRENT_SAFETY_H: // CURRENT_TENSION_SAFE_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_CURRENT_SAFETY_L: // CURRENT_TENSION_SAFE_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionCurrentSafety.Data = tmpData;
            m_RecvReg.m_TensionCurrentSafety.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_CURRENT_LIMITED_H: // CIRRENT_TENSION_MAX_H
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_CURRENT_LIMITED_L: // CIRRENT_TENSION_MAX_L
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionCurrentLimited.Data = tmpData;
            m_RecvReg.m_TensionCurrentLimited.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_CABLE_HEAD_TREND: // HARNESS_TENSION_TREND
            m_RecvReg.m_TensionCableHeadTrend.Data = value;
            m_RecvReg.m_TensionCableHeadTrend.Address = currentAddress;
            break;
        case HQmlEnum::TIME_SAFETY_STOP: // PARKING_SAFE_TIME
            m_RecvReg.m_TimeSafetyStop.Data = value;
            m_RecvReg.m_TimeSafetyStop.Address = currentAddress;
            break;
        case HQmlEnum::DISTANCE_UPPER_WELL_SETTING_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DISTANCE_UPPER_WELL_SETTING_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DistanceUpperWellSetting.Data = tmpData;
            m_RecvReg.m_DistanceUpperWellSetting.Address = currentAddress;
            break;
        case HQmlEnum::DISTANCE_LOWER_WELL_SETTING_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::DISTANCE_LOWER_WELL_SETTING_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_DistanceLowerWellSetting.Data = tmpData;
            m_RecvReg.m_DistanceLowerWellSetting.Address = currentAddress;
            break;
        case HQmlEnum::SLOPE_ANGLE_WELL_SETTING:
            m_RecvReg.m_SlopeAngleWellSetting.Data = value;
            m_RecvReg.m_SlopeAngleWellSetting.Address = currentAddress;
            break;
        default:
            // 其他地址不处理
            break;
        }
    }
    // insertDataToDatabase();
}

void HBModbusClient::handleWriteRequest()
{
    m_mutexSending.lock();
    QVector<quint16> valueArray;
    quint32 value;
    int type = -1;
    static int prevKey = -1;
    static int triedCount = 0;
    if(m_RegisterSendMap.size() > 0)
    {
        QMap<int, HBModbusClient::SEND_DATA>::const_iterator iter = m_RegisterSendMap.constBegin();
        if(prevKey != iter.key() || (triedCount < MAX_TRIED_COUNT))
        {
            type = iter.value().Type;
            if(type == QModbusDataUnit::HoldingRegisters)
            {
                value = iter.value().Data;
                if(iter.value().Size == sizeof(unsigned int))
                {
                    valueArray.push_back(static_cast<quint16>(value >> 16));
                    valueArray.push_back(static_cast<quint16>(value & 0x0000ffff));
                }
                else
                {
                    valueArray.push_back(static_cast<quint16>(value));
                }
                qDebug()<< "Register Value: " << value;
                qDebug()<< "Register Address: " << iter.key();
                handleWriteRegister(iter.key(), valueArray);
            }
            else
            {
                value = iter.value().Data;
                handleWriteCoil(iter.key(), value);
            }

            if(prevKey == iter.key())
                triedCount++;
            else
            {
                prevKey = iter.key();
                triedCount = 0;
            }
        }
        else
        {
            m_RegisterSendMap.remove(iter.key());
        }
    }
    else
        prevKey = -1;
    m_mutexSending.unlock();
}

void HBModbusClient::handleRawData()
{
    int hashCode = qHashBits(&m_RecvReg, sizeof(MODBUS_REGISTER));
    int prevHashCode = qHashBits(&m_PrevRecvReg, sizeof(MODBUS_REGISTER));

    QString strData;
    int iData;

    m_VelocityUnit  = static_cast<DepthSetting::VELOCITY_UNIT>(DepthSetting::GetInstance()->VelocityUnit());
    m_DistanceUnit  = static_cast<DepthSetting::DISTANCE_UNIT>(DepthSetting::GetInstance()->DistanceUnit());
    m_TimeUnit      = static_cast<DepthSetting::TIME_UNIT>(DepthSetting::GetInstance()->TimeUnit());
    m_ForceUnit     = static_cast<TensionSetting::FORCE_UNIT>(TensionSetting::GetInstance()->TensionUnit());
#ifndef RK3588
    if(hashCode != prevHashCode)
    {
        qDebug() << "previous Register Hash Code: " << prevHashCode;
        qDebug() << "current Register Hash Code: " << hashCode;
#endif
        for(int i = HQmlEnum::DEPTH_CURRENT_H; i < HQmlEnum::MAX_REGISTR; i++)
        {
            switch(i)
            {
            case HQmlEnum::HQmlEnum::DEPTH_CURRENT_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthCurrent.Data != m_RecvReg.m_DepthCurrent.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthCurrent.Data, m_RecvReg.m_DepthCurrent.Address);
                    HBHome::GetInstance()->setDepthCurrent(strData);
                    DepthSetting::GetInstance()->setDepthCurrent(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::VELOCITY_CURRENT_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_VelocityCurrent.Data != m_RecvReg.m_VelocityCurrent.Data)
                {
#endif
                    strData = updateVelocityInterface(m_RecvReg.m_VelocityCurrent.Data, m_RecvReg.m_VelocityCurrent.Address);
                    HBHome::GetInstance()->setVelocityCurrent(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_CURRENT_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionCurrent.Data != m_RecvReg.m_TensionCurrent.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_TensionCurrent.Data, m_RecvReg.m_TensionCurrent.Address);
                    HBHome::GetInstance()->setTensionCurrent(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_CURRENT_DELTA_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionCurrentDelta.Data != m_RecvReg.m_TensionCurrentDelta.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_TensionCurrentDelta.Data, m_RecvReg.m_TensionCurrentDelta.Address);
                    HBHome::GetInstance()->setTensionCurrentDelta(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::PULSE_COUNT:
#ifndef RK3588
                if(m_PrevRecvReg.m_PulseCount.Data != m_RecvReg.m_PulseCount.Data)
                {
#endif
                    strData = updatePulseCount(m_RecvReg.m_PulseCount.Data, m_RecvReg.m_PulseCount.Address);
                    HBHome::GetInstance()->setPulseCount(strData);
                    DepthSetting::GetInstance()->setPulseCount(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_LIMITED_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionLimited.Data != m_RecvReg.m_TensionLimited.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_TensionLimited.Data, m_RecvReg.m_TensionLimited.Address);
                    HBHome::GetInstance()->setTensionLimited(strData);
                    TensionSafety::GetInstance()->setTensionLimited(strData);
                    TensionSetting::GetInstance()->setTensionLimited(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_TARGET_LAYER_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthTargetLayer.Data != m_RecvReg.m_DepthTargetLayer.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthTargetLayer.Data, m_RecvReg.m_DepthTargetLayer.Address);
                    HBHome::GetInstance()->setDepthTargetLayer(strData);
                    DepthSetting::GetInstance()->setDepthTargetLayer(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::VELOCITY_LIMITED_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_VelocityLimited.Data != m_RecvReg.m_VelocityLimited.Data)
                {
#endif
                    strData = updateVelocityInterface(m_RecvReg.m_VelocityLimited.Data, m_RecvReg.m_VelocityLimited.Address);
                    HBHome::GetInstance()->setVelocityLimited(strData);
                    DepthSetting::GetInstance()->setVelocityLimited(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_LIMITED_DELTA_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionLimitedDelta.Data != m_RecvReg.m_TensionLimitedDelta.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_TensionLimitedDelta.Data, m_RecvReg.m_TensionLimitedDelta.Address);
                    HBHome::GetInstance()->setTensionLimitedDelta(strData);
                    TensionSetting::GetInstance()->setTensionLimitedDelta(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::K_VALUE:
#ifndef RK3588
                if(m_PrevRecvReg.m_K_Value.Data != m_RecvReg.m_K_Value.Data)
                {
#endif
                    strData = updateKValue(m_RecvReg.m_K_Value.Data, m_RecvReg.m_K_Value.Address);
                    HBHome::GetInstance()->setKValue(strData);
                    TensionSetting::GetInstance()->setKValue(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_CABLE_HEAD_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionCableHead.Data != m_RecvReg.m_TensionCableHead.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_TensionCableHead.Data, m_RecvReg.m_TensionCableHead.Address);
                    HBHome::GetInstance()->setTensionCableHead(strData);
                    TensionSafety::GetInstance()->setTensionCableHead(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_SURFACE_COVER_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthSurfaceCover.Data != m_RecvReg.m_DepthSurfaceCover.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthSurfaceCover.Data, m_RecvReg.m_DepthSurfaceCover.Address);
                    DepthSetting::GetInstance()->setDepthSurfaceCover(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_ENCODER:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthEncoder.Data != m_RecvReg.m_DepthEncoder.Data)
                {
#endif
                    iData = updateDepthEncoder(m_RecvReg.m_DepthEncoder.Data, m_RecvReg.m_DepthEncoder.Address);
                    DepthSetting::GetInstance()->setDepthEncoder(iData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::WELL_TYPE:
#ifndef RK3588
                if(m_PrevRecvReg.m_WellType.Data != m_RecvReg.m_WellType.Data)
                {
#endif
                    iData = updateWellType(m_RecvReg.m_WellType.Data, m_RecvReg.m_WellType.Address);
                    TensionSafety::GetInstance()->setWellType(iData);
                    WellParameter::GetInstance()->setWellType(iData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::WOKE_TYPE:
#ifndef RK3588
                if(m_PrevRecvReg.m_WorkType.Data != m_RecvReg.m_WorkType.Data)
                {
#endif
                    iData = updateWorkType(m_RecvReg.m_WorkType.Data, m_RecvReg.m_WorkType.Address);
                    TensionSafety::GetInstance()->setWorkType(iData);
                    WellParameter::GetInstance()->setWorkType(iData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::WEIGHT_EACH_KILOMETER_CABLE:
#ifndef RK3588
                if(m_PrevRecvReg.m_WeightEachKilometerCable.Data != m_RecvReg.m_WeightEachKilometerCable.Data)
                {
#endif
                    strData = updateIntegerInterface(m_RecvReg.m_WeightEachKilometerCable.Data, m_RecvReg.m_WeightEachKilometerCable.Address);
                    TensionSafety::GetInstance()->setWeightEachKilometerCable(strData);
                    WellParameter::GetInstance()->setWeightEachKilometerCable(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::WEIGHT_INSTRUMENT_STRING:
#ifndef RK3588
                if(m_PrevRecvReg.m_WeightInstrumentString.Data != m_RecvReg.m_WeightInstrumentString.Data)
                {
#endif
                    strData = updateIntegerInterface(m_RecvReg.m_WeightInstrumentString.Data, m_RecvReg.m_WeightInstrumentString.Address);
                    TensionSafety::GetInstance()->setWeightInstrumentString(strData);
                    WellParameter::GetInstance()->setWeightInstrumentString(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::BREAKING_FORCE_CABLE:
#ifndef RK3588
                if(m_PrevRecvReg.m_BreakingForceCable.Data != m_RecvReg.m_BreakingForceCable.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_BreakingForceCable.Data, m_RecvReg.m_BreakingForceCable.Address);
                    TensionSafety::GetInstance()->setBreakingForceCable(strData);
                    WellParameter::GetInstance()->setBreakingForceCable(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::BREAKING_FORCE_WEAKNESS:
#ifndef RK3588
                if(m_PrevRecvReg.m_BreakingForceWeakness.Data != m_RecvReg.m_BreakingForceWeakness.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_BreakingForceWeakness.Data, m_RecvReg.m_BreakingForceWeakness.Address);
                    TensionSafety::GetInstance()->setBreakingForceWeakness(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_CABLE_HEAD_TREND:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionCableHeadTrend.Data != m_RecvReg.m_TensionCableHeadTrend.Data)
                {
#endif
                    iData = updateCalbeHeadTrend(m_RecvReg.m_TensionCableHeadTrend.Data, m_RecvReg.m_TensionCableHeadTrend.Address);
                    TensionSafety::GetInstance()->setTensionCableHeadTrend(iData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_SAFETY_COEFFICIENT:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionSafetyCoefficient.Data != m_RecvReg.m_TensionSafetyCoefficient.Data)
                {
#endif
                    strData = updateSafetyCoefficient(m_RecvReg.m_TensionSafetyCoefficient.Data, m_RecvReg.m_TensionSafetyCoefficient.Address);
                    TensionSafety::GetInstance()->setTensionSafetyCoefficient(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSION_CURRENT_SAFETY_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensionCurrentSafety.Data != m_RecvReg.m_TensionCurrentSafety.Data)
                {
#endif
                    strData = updateTensionInterface(m_RecvReg.m_TensionCurrentSafety.Data, m_RecvReg.m_TensionCurrentSafety.Address);
                    TensionSafety::GetInstance()->setTensionCurrentSafety(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TIME_SAFETY_STOP:
#ifndef RK3588
                if(m_PrevRecvReg.m_TimeSafetyStop.Data != m_RecvReg.m_TimeSafetyStop.Data)
                {
#endif
                    strData = updateTimeSafetyStop(m_RecvReg.m_TimeSafetyStop.Data, m_RecvReg.m_TimeSafetyStop.Address);
                    TensionSafety::GetInstance()->setTimeSafetyStop(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_TOLERANCE_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthTolerance.Data != m_RecvReg.m_DepthTolerance.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthTolerance.Data, m_RecvReg.m_DepthTolerance.Address);
                    TensionSafety::GetInstance()->setDepthTolerance(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_ENCODER_1_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthEncoder1.Data != m_RecvReg.m_DepthEncoder1.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthEncoder1.Data, m_RecvReg.m_DepthEncoder1.Address);
                    TensionSafety::GetInstance()->setDepthEncoder1(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_ENCODER_2_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthEncoder2.Data != m_RecvReg.m_DepthEncoder2.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthEncoder2.Data, m_RecvReg.m_DepthEncoder2.Address);
                    TensionSafety::GetInstance()->setDepthEncoder2(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_ENCODER_3_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthEncoder3.Data != m_RecvReg.m_DepthEncoder3.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthEncoder3.Data, m_RecvReg.m_DepthEncoder3.Address);
                    TensionSafety::GetInstance()->setDepthEncoder3(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::DEPTH_WELL_SETTING_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_DepthWellSetting.Data != m_RecvReg.m_DepthWellSetting.Data)
                {
#endif
                    strData = updateDepthInterface(m_RecvReg.m_DepthWellSetting.Data, m_RecvReg.m_DepthWellSetting.Address);
                    WellParameter::GetInstance()->setDepthWell(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::SLOPE_ANGLE_WELL_SETTING:
#ifndef RK3588
                if(m_PrevRecvReg.m_SlopeAngleWellSetting.Data != m_RecvReg.m_SlopeAngleWellSetting.Data)
                {
#endif
                    strData = updateSlopeAngleWell(m_RecvReg.m_SlopeAngleWellSetting.Data, m_RecvReg.m_SlopeAngleWellSetting.Address);
                    WellParameter::GetInstance()->setSlopeAngleWellSetting(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::CABLE_SPEC:
#ifndef RK3588
                if(m_PrevRecvReg.m_CableSpec.Data != m_RecvReg.m_CableSpec.Data)
                {
#endif
                    iData = updateCableSpec(m_RecvReg.m_CableSpec.Data, m_RecvReg.m_CableSpec.Address);
                    WellParameter::GetInstance()->setCableSpec(iData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TONNAGE_TENSION_STICK:
#ifndef RK3588
                if(m_PrevRecvReg.m_TonnageTensionStick.Data != m_RecvReg.m_TonnageTensionStick.Data)
                {
#endif
                    strData = updateTonnageStick(m_RecvReg.m_TonnageTensionStick.Data, m_RecvReg.m_TonnageTensionStick.Address);
                    WellParameter::GetInstance()->setTonnageTensionStick(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSIOMETER_NUM_H:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensiometerNum.Data != m_RecvReg.m_TensiometerNum.Data)
                {
#endif
                    strData = updateIntegerInterface(m_RecvReg.m_TensiometerNum.Data, m_RecvReg.m_TensiometerNum.Address);
                    Tensiometer::GetInstance()->setTensiometerNumber(strData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSIOMETER_ENCODER:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensiometerEncoder.Data != m_RecvReg.m_TensiometerEncoder.Data)
                {
#endif
                    iData = updateTensiometerEncoder(m_RecvReg.m_TensiometerEncoder.Data, m_RecvReg.m_TensiometerEncoder.Address);
                    Tensiometer::GetInstance()->setTensiometerEncoder(iData);
#ifndef RK3588
                }
#endif
                break;
            case HQmlEnum::TENSIOMETER_ANALOG:
#ifndef RK3588
                if(m_PrevRecvReg.m_TensiometerAnalog.Data != m_RecvReg.m_TensiometerAnalog.Data)
                {
#endif
                    iData = updateTensiometerAnalog(m_RecvReg.m_TensiometerAnalog.Data, m_RecvReg.m_TensiometerAnalog.Address);
                    Tensiometer::GetInstance()->setTensiometerAnalog(iData);
#ifndef RK3588
                }
#endif
                break;
            default:
                break;
            }
#ifndef RK3588
            memcpy(&m_PrevRecvReg, &m_RecvReg, sizeof(MODBUS_REGISTER));
        }
#endif
    }
}

void HBModbusClient::handleWriteRegister(const int address, const QVector<quint16> &values)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, values.size());
    for (int i = 0; i < values.size(); ++i)
    {
        writeUnit.setValue(i, values[i]);
    }

    if(QModbusReply *reply = _ptrModbus->sendWriteRequest(writeUnit, 1))
    { // Slave ID = 1
        connect(reply, &QModbusReply::finished, this, [reply, address]() {
            if (reply->error() == QModbusDevice::NoError)
            {
                m_mutexSending.lock();
                m_RegisterSendMap.remove(address);
                m_mutexSending.unlock();

            }
            else
            {
                qWarning() << "Write failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
    else
    {
        qWarning() << "Failed to send write request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::handleWriteCoil(const int address, const int value)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, address, 1);
    writeUnit.setValue(0, value ? 1 : 0); // 确保是 0 或 1

    if (auto *reply = _ptrModbus->sendWriteRequest(writeUnit, 1))
    {
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() == QModbusDevice::NoError)
            {
                qDebug() << "Coil write successful";
            }
            else
            {
                qWarning() << "Failed to write coil:" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
    else
    {
        qWarning() << "Failed to send coil write request:" << _ptrModbus->errorString();
    }
}

QString HBModbusClient::updateDepthInterface(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Depth Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_DistanceUnit)
    {
    case DepthSetting::METER:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, hexData);
        break;
    case DepthSetting::FEET:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, hexData);
        break;
    }
    return strData;
}

QString HBModbusClient::updateVelocityInterface(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Velocity Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_VelocityUnit)
    {
    case DepthSetting::M_PER_HOUR:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_HOUR, hexData);
        break;
    case DepthSetting::M_PER_MIN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_MIN, hexData);
        break;
    case DepthSetting::FT_PER_HOUR:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET_PER_HOUR, hexData);
        break;
    case DepthSetting::FT_PER_MIN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET_PER_MIN, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_HOUR, hexData);
        break;
    }
    return strData;
}

QString HBModbusClient::updateTensionInterface(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_ForceUnit)
    {
    case TensionSetting::LB:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, hexData);
        break;
    case TensionSetting::KG:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, hexData);
        break;
    case TensionSetting::KN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    }
    return strData;
}

QString HBModbusClient::updatePulseCount(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Current Delta Address: " << hexAddress << "----- Updated depth:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2PULSE, hexData);
    return strData;
}

QString HBModbusClient::updateKValue(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "K Value Address: " << hexAddress << "----- Updated depth:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2K_VALUE, hexData);
    return strData;
}

void HBModbusClient::updateDepthOrientation(const int hexData, const int hexAddress)
{
    Q_UNUSED(hexData)
    Q_UNUSED(hexAddress)
}

int HBModbusClient::updateDepthEncoder(const int hexData, const int hexAddress)
{
    qDebug() << "Depth Encoder Address: " << hexAddress << "----- Updated depth:" << hexData;
    return hexData;
}

int HBModbusClient::updateWellType(const int hexData, const int hexAddress)
{
    qDebug() << "Well Type Address: " << hexAddress << "----- Updated Well Type:" << hexData;
    return hexData;
}

int HBModbusClient::updateWorkType(const int hexData, const int hexAddress)
{
    qDebug() << "Work Type Address: " << hexAddress << "----- Updated Work Type:" << hexData;
    return hexData;
}

int HBModbusClient::updateCalbeHeadTrend(const int hexData, const int hexAddress)
{
    qDebug() << "Cable Head Trend Address: " << hexAddress << "----- Updated Head Trend: " << hexData;
    return hexData;
}

int HBModbusClient::updateCableSpec(const int hexData, const int hexAddress)
{
    qDebug() << "Cable Spec Address: " << hexAddress << "----- Updated Cable Spec: " << hexData;
    return hexData;
}

int HBModbusClient::updateTensiometerEncoder(const int hexData, const int hexAddress)
{
    qDebug() << "Tensiometer Encoder Address: " << hexAddress << "----- Updated Tensiometer Encoder: " << hexData;
    return hexData;
}

int HBModbusClient::updateTensiometerAnalog(const int hexData, const int hexAddress)
{
    qDebug() << "Tensiometer Analog Address: " << hexAddress << "----- Updated Tensiometer Analogr: " << hexData;
    return hexData;
}

QString HBModbusClient::updateIntegerInterface(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Integer Address: " << hexAddress << "----- Updated integer:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2INTEGER, hexData);
    return strData;
}

QString HBModbusClient::updateSafetyCoefficient(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Safety Coefficient Address: " << hexAddress << "----- Updated Coefficient:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FACTOR, hexData);
    return strData;
}

QString HBModbusClient::updateTimeSafetyStop(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Time Safety Stop Address: " << hexAddress << "----- Updated Time Safety Stop:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2SECOND, hexData);
    return strData;
}

QString HBModbusClient::updateSlopeAngleWell(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Slope Angle Well Address: " << hexAddress << "----- Updated Slope Angle Well:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2DEGREE, hexData);
    return strData;
}

QString HBModbusClient::updateTonnageStick(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tonnage Tension Stick Address: " << hexAddress << "----- Updated Tonnage Tension Stick:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2TONAGE, hexData);
    return strData;
}

int HBModbusClient::getDepthInterface(const QString strData, const int hexAddress)
{
    int iData = -1;
    switch(m_DistanceUnit)
    {
    case DepthSetting::METER:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2METER, strData);
        break;
    case DepthSetting::FEET:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2FEET, strData);
        break;
    default:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2METER, strData);
        break;
    }
    qDebug() << "Depth: " << hexAddress << "----- Updated depth:" << iData;
    return iData;
}

int HBModbusClient::getTensionInterface(const QString strData, const int hexAddress)
{
    int iData = -1;
    switch(m_ForceUnit)
    {
    case TensionSetting::LB:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2POUND, strData);
        break;
    case TensionSetting::KG:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2KILOGRAM, strData);
        break;
    case TensionSetting::KN:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2KILONEWTON, strData);
        break;
    default:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2POUND, strData);
        break;
    }
    qDebug() << "Depth: " << hexAddress << "----- Updated depth:" << iData;
    return iData;
}

int HBModbusClient::getPulseCount(const QString strData, const int hexAddress)
{
    int iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2PULSE, strData);
    qDebug() << "Pulse Count: " << hexAddress << "----- Updated Pulse:" << iData;
    return iData;
}

int HBModbusClient::getVelocityInterface(const QString strData, const int hexAddress)
{
    int iData = -1;
    switch(m_VelocityUnit)
    {
    case DepthSetting::M_PER_HOUR:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2METER_PER_HOUR, strData);
        break;
    case DepthSetting::M_PER_MIN:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2METER_PER_MIN, strData);
        break;
    case DepthSetting::FT_PER_HOUR:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2FEET_PER_HOUR, strData);
        break;
    case DepthSetting::FT_PER_MIN:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2FEET_PER_MIN, strData);
        break;
    default:
        iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2METER_PER_HOUR, strData);
        break;
    }
    qDebug() << "Velocity: " << hexAddress << "----- Updated velocity:" << iData;
    return iData;
}

int HBModbusClient::getIntegerInterface(const QString strData, const int hexAddress)
{
    int iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2INTEGER, strData);
    qDebug() << "Integer: " << hexAddress << "----- Updated Integer:" << iData;
    return iData;
}

int HBModbusClient::getSafetyCoefficient(const QString strData, const int hexAddress)
{
    int iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2FACTOR, strData);
    qDebug() << "Safety Coefficient: " << hexAddress << "----- Updated Safety Coefficient:" << iData;
    return iData;
}

int HBModbusClient::getTimeSafetyStop(const QString strData, const int hexAddress)
{
    int iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2SECOND, strData);
    qDebug() << "Time Safety Stop: " << hexAddress << "----- Updated Time Safety Stop:" << iData;
    return iData;
}

int HBModbusClient::getSlopeAngleWell(const QString strData, const int hexAddress)
{
    int iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2DEGREE, strData);
    qDebug() << "Slope Angle Well: " << hexAddress << "----- Update Slope Angle Well: " << iData;
    return iData;
}

int HBModbusClient::getTonnageStick(const QString strData, const int hexAddress)
{
    int iData = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2TONAGE, strData);
    qDebug() << "Tonnage Tension Stick: " << hexAddress << "----- Update Tonnage Tension Stick: " << iData;
    return iData;
}

void HBModbusClient::writeRegister(const int address, const QVariant value)
{
    int tmpValue = 0;
    QString strValue = "";
    SEND_DATA stData;
    m_mutexSending.lock();
    switch(address)
    {
    case HQmlEnum::DEPTH_TARGET_LAYER_H:
    case HQmlEnum::DEPTH_SURFACE_COVER_H:
    case HQmlEnum::DEPTH_CURRENT_H:
    case HQmlEnum::DEPTH_TOLERANCE_H:
    case HQmlEnum::DEPTH_ENCODER_1_H:
    case HQmlEnum::DEPTH_ENCODER_2_H:
    case HQmlEnum::DEPTH_ENCODER_3_H:
    case HQmlEnum::DEPTH_WELL_SETTING_H:
        strValue = value.toString();
        tmpValue = getDepthInterface(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned int);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::DEPTH_ENCODER:
    case HQmlEnum::WELL_TYPE:
    case HQmlEnum::WOKE_TYPE:
    case HQmlEnum::TENSION_CABLE_HEAD_TREND:
    case HQmlEnum::CABLE_SPEC:
    case HQmlEnum::TENSIOMETER_ENCODER:
    case HQmlEnum::TENSIOMETER_ANALOG:
        tmpValue = value.toInt();
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::PULSE_COUNT:
        strValue = value.toString();
        tmpValue = getPulseCount(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::VELOCITY_LIMITED_H:
        strValue = value.toString();
        tmpValue = getVelocityInterface(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned int);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::WEIGHT_EACH_KILOMETER_CABLE:
    case HQmlEnum::WEIGHT_INSTRUMENT_STRING:
    case HQmlEnum::BREAKING_FORCE_CABLE:
    case HQmlEnum::BREAKING_FORCE_WEAKNESS:
        strValue = value.toString();
        tmpValue = getIntegerInterface(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::TENSION_LIMITED_H:
    case HQmlEnum::TENSION_CURRENT_SAFETY_H:
    case HQmlEnum::TENSION_CABLE_HEAD_H:
    case HQmlEnum::TENSION_LIMITED_DELTA_H:
        strValue = value.toString();
        tmpValue = getTensionInterface(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned int);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::TENSION_SAFETY_COEFFICIENT:
        strValue = value.toString();
        tmpValue = getSafetyCoefficient(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::TIME_SAFETY_STOP:
        strValue = value.toString();
        tmpValue = getTimeSafetyStop(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::SLOPE_ANGLE_WELL_SETTING:
        strValue = value.toString();
        tmpValue = getSlopeAngleWell(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::TONNAGE_TENSION_STICK:
        strValue = value.toString();
        tmpValue = getTonnageStick(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned short);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    case HQmlEnum::TENSIOMETER_NUM_H:
        strValue = value.toString();
        tmpValue = getIntegerInterface(strValue, address);
        stData.Data = tmpValue;
        stData.Size = sizeof(unsigned int);
        stData.Type = QModbusDataUnit::HoldingRegisters;
        m_RegisterSendMap.insert(address, stData);
        break;
    default:
        break;
    }
    m_mutexSending.unlock();
}

void HBModbusClient::writeCoil(const int address, const int value)
{
    SEND_DATA stData;
    m_mutexSending.lock();
    stData.Data = value;
    stData.Size = 1;
    stData.Type = QModbusDataUnit::Coils;
    m_RegisterSendMap.insert(address, stData);
    m_mutexSending.unlock();
}


void HBModbusClient::readCoils(const int address, const int count)
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState)
    {
        qWarning() << "Modbus not connected";
        return;
    }
    if(count == 0)
    {
        qWarning() << "the count of Read Coils is ZERO";
        return;
    }
    QModbusDataUnit request(QModbusDataUnit::Coils, address, count);
    if (auto *reply = _ptrModbus->sendReadRequest(request, 1))
    {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if(reply->error() == QModbusDevice::NoError)
            {
                handleParseCoils(reply->result());
            }
            else
            {
                qWarning() << "Coil read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
    else
    {
        qWarning() << "Failed to send coil read request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::handleParseCoils(const QModbusDataUnit &result)
{
    int startAddress = result.startAddress();
    int count = result.valueCount();
    for (int i = 0; i < count; ++i)
    {
        int address = startAddress + i;
        bool val = result.value(i);
        switch(address)
        {
        case HQmlEnum::IS_MUTE:
            m_IO_Value0.bits_Value0.m_IsMute = val ? 1 : 0;
            break;
        case HQmlEnum::ORIENTATION_DEPTH:
            m_IO_Value0.bits_Value0.m_OrientationDepth = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_VELOCITY_CONTROL:
            m_IO_Value0.bits_Value0.m_EnableVelocityControl = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_TENSIOMETER_CALIBRATION:
            m_IO_Value0.bits_Value0.m_EnableTensiometerCalibration = val ? 1 : 0;
            break;
        case HQmlEnum::STATUS_TENSION_PROTECTED:
            m_IO_Value0.bits_Value0.m_StatusTensionProtected = val ? 1 : 0;
            break;
        case HQmlEnum::INDICATE_TENSION_RESET:
            m_IO_Value0.bits_Value0.m_IndicateTensionReset = val ? 1 : 0;
            break;
        case HQmlEnum::STATUS_TENSIOMETER_ONLINE:
            m_IO_Value0.bits_Value0.m_StatusTensiometerOnline = val ? 1 : 0;
            break;
        case HQmlEnum::INDICATE_MOVEUP_MOVEDOWN:
            m_IO_Value0.bits_Value0.m_IndicateMoveUpMoveDown = val ? 1 : 0;
            break;
        case HQmlEnum::INDICATE_SAFETY_STOP:
            m_IO_Value1.bits_Value1.m_IndicateSafetyStop = val ? 1 : 0;
            break;
        case HQmlEnum::INDICATE_SIMAN_ALERT:
            m_IO_Value1.bits_Value1.m_IndicateSimanAlert = val ? 1 : 0;
            break;
        case HQmlEnum::INDICATE_SIMAN_STOP:
            m_IO_Value1.bits_Value1.m_IndicateSimanStop = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_VELOCITY:
            m_IO_Value2.bits_Value2.m_AlarmVelocity = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_WELL_SURFACE:
            m_IO_Value2.bits_Value2.m_AlarmWellSurface = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_TARGET_LAYER:
            m_IO_Value2.bits_Value2.m_AlarmTargetLayer = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_SURFACE_COVER:
            m_IO_Value2.bits_Value2.m_AlarmSurfaceCover = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_TENSION:
            m_IO_Value2.bits_Value2.m_AlarmTension = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_TENSION_DELTA_SLOW:
            m_IO_Value2.bits_Value2.m_AlarmTensionDeltaSlow = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_TENSION_DELTA_STOP:
            m_IO_Value2.bits_Value2.m_AlarmTensionDeltaStop = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_TENSION_CABLE_HEAD_SLOW:
            m_IO_Value2.bits_Value2.m_AlarmTensionCableHeadSlow = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_TENSION_CABLE_HEAD_STOP:
            m_IO_Value3.bits_Value3.m_AlarmTensionCableHeadStop = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_ENCODER1:
            m_IO_Value3.bits_Value3.m_AlarmEncoder1 = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_ENCODER2:
            m_IO_Value3.bits_Value3.m_AlarmEncoder2 = val ? 1 : 0;
            break;
        case HQmlEnum::ALARM_ENCODER3:
            m_IO_Value3.bits_Value3.m_AlarmEncoder3 = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_SIMAN_CONTROL:
            m_IO_Value4.bits_Value4.m_EnableSimanControl = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_SIMAN_FUNCTION:
            m_IO_Value4.bits_Value4.m_EnableSimanFunction = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_MOVE_FORWARD:
            m_IO_Value4.bits_Value4.m_EnableMoveForward = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_MOVE_BACKWARD:
            m_IO_Value4.bits_Value4.m_EnableMoveBackward = val ? 1 : 0;
            break;
        case HQmlEnum::STATUS_BRAKE_VALVE1:
            m_IO_Value4.bits_Value4.m_StatusBrakeValve1 = val ? 1 : 0;
            break;
        case HQmlEnum::STATUS_BRAKE_VALVE2:
            m_IO_Value4.bits_Value4.m_StatusBrakeValve2 = val ? 1 : 0;
            break;
        case HQmlEnum::ENABLE_MANUAL_CONTROL:
            m_IO_Value4.bits_Value4.m_EnableManualControl = val ? 1 : 0;
            break;
        case HQmlEnum::MODE_VELOCITY_CONTROL:
            m_IO_Value4.bits_Value4.m_ModeVelocityControl = val ? 1 : 0;
            break;
        case HQmlEnum::STATUS_HANDLE:
            m_IO_Value5.bits_Value5.m_StatusHandle = val ? 1 : 0;
            break;
        case HQmlEnum::FAILURE_HANDLE:
            m_IO_Value5.bits_Value5.m_FailureHandle = val ? 1 : 0;
            break;
        case HQmlEnum::FAILURE_MOVE_DOWN_VALVE:
            m_IO_Value5.bits_Value5.m_FailureMoveDownValve = val ? 1 : 0;
            break;
        case HQmlEnum::FAILURE_MOVE_UP_VALVE:
            m_IO_Value5.bits_Value5.m_FailureMoveUpValve = val ? 1 : 0;
            break;
        case HQmlEnum::FAILURE_MOTOR:
            m_IO_Value5.bits_Value5.m_FailureMotor = val ? 1 : 0;
            break;
        case HQmlEnum::FAILURE_INITIALIZATION:
            m_IO_Value5.bits_Value5.m_FailureInitialization = val ? 1 : 0;
            break;
        default:
            break;
        }
    }
}

void HBModbusClient::handleAlarm()
{

}

void HBModbusClient::handleCANbus()
{

}

void HBModbusClient::handleDevice()
{
    DepthSetting::GetInstance()->setDepthOrientation(m_IO_Value0.bits_Value0.m_OrientationDepth);
}

void HBModbusClient::insertDataToDatabase()
{
    // HBHome* _dashboard = HBHome::getInstance();
    // ModbusData modData;
    // modData.wellNumber = WellParameter::getInstance()->WellNumber();
    // modData.operateType = WellParameter::getInstance()->OperatorType();
    // modData.operater = WellParameter::getInstance()->UserName();
    // modData.depth = _dashboard->DepthCurrent();
    // modData.velocity = _dashboard->Speed();
    // modData.tensions = _dashboard->Tension();
    // modData.tensionIncrement = _dashboard->TensionIncrement();
    // modData.harnessTension = m_RecvReg.m_TensionCableHead.Data;
    // modData.maxTension = _dashboard->MaxTension();
    // modData.safetyTension = m_RecvReg.m_TensionCurrentSafety.Data;
    // modData.exception = "none";

    // HBDatabase::getInstance().insertHistoryData(modData);
    // QtConcurrent::run([modData]() {
    //     HBDatabase::getInstance().insertHistoryData(modData);
    // });
}

