#include "hbmodbusclient.h"
#include <QDebug>
#include <QSerialPort>
#include <QModbusReply>
#include "c++Source/HBQmlEnum.h"
#include "c++Source/HBScreen/hbhome.h"
#include "c++Source/HBScreen/tensionsafe.h"
#include "c++Source/HBDefine.h"
#include "c++Source/HBData/hbdatabase.h"
#include "c++Source/HBScreen/wellparameter.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBUtility/hbutilityclass.h"
#include <QtConcurrent>
#include <QHash>
#include <cstring>
HBModbusClient::MODBUS_REGISTER HBModbusClient::m_RecvReg;
HBModbusClient::MODBUS_REGISTER HBModbusClient::m_PrevRecvReg;
QModbusClient* HBModbusClient::_ptrModbus = nullptr;
int HBModbusClient::m_timerIdentifier = -1;
QMap<int, int> HBModbusClient::m_RegisterSendMap;
QMutex HBModbusClient::m_mutexSending;
HBModbusClient::HBModbusClient(QObject *parent)
    : QObject{parent}
{
    _ptrModbus = new QModbusRtuSerialMaster(this);
    connectToServer();
    m_timerIdentifier = startTimer(500);
    m_RegisterSendMap.clear();

    m_VelocityUnit = Depth::M_PER_HOUR;
    m_DistanceUnit = Depth::METER;
    m_TimeUnit = Depth::HOUR;
    m_ForceUnit = Tensiometer::LB;
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
    _ptrModbus->setTimeout(1000);
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

void HBModbusClient::readRegister(int address, int count)
{
    QModbusDataUnit request(QModbusDataUnit::HoldingRegisters, address, count);

    if (auto *reply = _ptrModbus->sendReadRequest(request, 1)) {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit result = reply->result();
                handleReadResult(result);
            } else {
                qWarning() << "Read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send read request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::timerEvent(QTimerEvent *event)
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState)
    {
        // qWarning() << "Modbus is not connected.";
        return;
    }

    if(event->timerId() == m_timerIdentifier)
    {
        readRegister(0, HQmlEnum::MAX_REGISTR);
        compareRawData();
        readCoils();
    }
}

void HBModbusClient::handleReadResult(const QModbusDataUnit &result)
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
        case HQmlEnum::TENSION_ENCODER:
            m_RecvReg.m_TensionEncoder.Data = value;
            m_RecvReg.m_TensionEncoder.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_ANALOG:
            m_RecvReg.m_TensionAnalog.Data = value;
            m_RecvReg.m_TensionAnalog.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_BATTERY:
            m_RecvReg.m_TensionBattery.Data = value;
            m_RecvReg.m_TensionBattery.Address = currentAddress;
            break;
        case HQmlEnum::TENSION_NUM_H:
            m_RegisterData.HIGH_16BITS = value;
            break;
        case HQmlEnum::TENSION_NUM_L:
            m_RegisterData.LOW_16BITS = value;
            tmpData = m_RegisterData.HIGH_16BITS;
            tmpData <<= 16;
            tmpData |= m_RegisterData.LOW_16BITS;
            m_RecvReg.m_TensionNum.Data = tmpData;
            m_RecvReg.m_TensionNum.Address = currentAddress;
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
            // Tensiometer::getInstance()->setScale1(m_scale1);
            // qDebug() << "Address" << currentAddress << "- Updated m_scale1:" << m_scale1;
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

void HBModbusClient::compareRawData()
{
    int hashCode = qHashBits(&m_RecvReg, sizeof(MODBUS_REGISTER));
    int prevHashCode = qHashBits(&m_PrevRecvReg, sizeof(MODBUS_REGISTER));

    m_VelocityUnit  = static_cast<Depth::VELOCITY_UNIT>(Depth::GetInstance()->VelocityUnit());
    m_DistanceUnit  = static_cast<Depth::DISTANCE_UNIT>(Depth::GetInstance()->DistanceUnit());
    m_TimeUnit      = static_cast<Depth::TIME_UNIT>(Depth::GetInstance()->TimeUnit());
    m_ForceUnit     = static_cast<Tensiometer::FORCE_UNIT>(Tensiometer::GetInstance()->TensionUnits());

    if(hashCode != prevHashCode)
    {
        qDebug() << "previous Register Hash Code: " << prevHashCode;
        qDebug() << "current Register Hash Code: " << hashCode;
        if(m_PrevRecvReg.m_DepthCurrent.Data != m_RecvReg.m_DepthCurrent.Data)
            updateDepthCurrent(m_RecvReg.m_DepthCurrent.Data, m_RecvReg.m_DepthCurrent.Address);

        if(m_PrevRecvReg.m_VelocityCurrent.Data != m_RecvReg.m_VelocityCurrent.Data)
            updateVelocityCurrent(m_RecvReg.m_VelocityCurrent.Data, m_RecvReg.m_VelocityCurrent.Address);

        if(m_PrevRecvReg.m_TensionCurrent.Data != m_RecvReg.m_TensionCurrent.Data)
            updateTensionCurrent(m_RecvReg.m_TensionCurrent.Data, m_RecvReg.m_TensionCurrent.Address);

        if(m_PrevRecvReg.m_TensionCurrentDelta.Data != m_RecvReg.m_TensionCurrentDelta.Data)
            updateTensionCurrentDelta(m_RecvReg.m_TensionCurrentDelta.Data, m_RecvReg.m_TensionCurrentDelta.Address);

        if(m_PrevRecvReg.m_PulseCount.Data != m_RecvReg.m_PulseCount.Data)
            updatePulseCount(m_RecvReg.m_PulseCount.Data, m_RecvReg.m_PulseCount.Address);

        if(m_PrevRecvReg.m_TensionLimited.Data != m_RecvReg.m_TensionLimited.Data)
            updateTensionLimited(m_RecvReg.m_TensionLimited.Data, m_RecvReg.m_TensionLimited.Address);

        if(m_PrevRecvReg.m_DepthTargetLayer.Data != m_RecvReg.m_DepthTargetLayer.Data)
            updateDepthTargetLayer(m_RecvReg.m_DepthTargetLayer.Data, m_RecvReg.m_DepthTargetLayer.Address);

        if(m_PrevRecvReg.m_VelocityLimited.Data != m_RecvReg.m_VelocityLimited.Data)
            updateVelocityLimited(m_RecvReg.m_VelocityLimited.Data, m_RecvReg.m_VelocityLimited.Address);

        if(m_PrevRecvReg.m_TensionLimitedDelta.Data != m_RecvReg.m_TensionLimitedDelta.Data)
            updateTensionLimitedDelta(m_RecvReg.m_TensionLimitedDelta.Data, m_RecvReg.m_TensionLimitedDelta.Address);

        if(m_PrevRecvReg.m_K_Value.Data != m_RecvReg.m_K_Value.Data)
            updateKValue(m_RecvReg.m_K_Value.Data, m_RecvReg.m_K_Value.Address);

        if(m_PrevRecvReg.m_TensionCableHead.Data != m_RecvReg.m_TensionCableHead.Data)
            updateTensionCableHead(m_RecvReg.m_TensionCableHead.Data, m_RecvReg.m_TensionCableHead.Address);
        memcpy(&m_PrevRecvReg, &m_RecvReg, sizeof(MODBUS_REGISTER));
    }
}

void HBModbusClient::writeRegister(int address, const QVector<quint16> &values)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, values.size());
    for (int i = 0; i < values.size(); ++i)
    {
        writeUnit.setValue(i, values[i]);
    }

    if (QModbusReply *reply = _ptrModbus->sendWriteRequest(writeUnit, 1)) { // Slave ID = 1
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "Write successful.";
            } else {
                qWarning() << "Write failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send write request:" << _ptrModbus->errorString();
    }

}

void HBModbusClient::writeRegister(int address, const QVariantList &values)
{
    QVector<quint16> data;
    for (const QVariant &v : values) {
        data.append(static_cast<quint16>(v.toUInt()));
    }
    writeRegister(address, data);
}

void HBModbusClient::updateDepthCurrent(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Depth Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_DistanceUnit)
    {
    case Depth::METER:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, hexData);
        break;
    case Depth::FEET:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, hexData);
        break;
    }
    HBHome::GetInstance()->setDepthCurrent(strData);
}

void HBModbusClient::updateVelocityCurrent(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Velocity Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_VelocityUnit)
    {
    case Depth::M_PER_HOUR:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_HOUR, hexData);
        break;
    case Depth::M_PER_MIN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_MIN, hexData);
        break;
    case Depth::FT_PER_HOUR:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET_PER_HOUR, hexData);
        break;
    case Depth::FT_PER_MIN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET_PER_MIN, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_HOUR, hexData);
        break;
    }
    HBHome::GetInstance()->setVelocityCurrent(strData);
}

void HBModbusClient::updateTensionCurrent(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_ForceUnit)
    {
    case Tensiometer::LB:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, hexData);
        break;
    case Tensiometer::KG:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, hexData);
        break;
    case Tensiometer::KN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    }
    HBHome::GetInstance()->setTensionCurrent(strData);
}

void HBModbusClient::updateTensionCurrentDelta(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Current Delta Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_ForceUnit)
    {
    case Tensiometer::LB:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, hexData);
        break;
    case Tensiometer::KG:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, hexData);
        break;
    case Tensiometer::KN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    }
    HBHome::GetInstance()->setTensionCurrentDelta(strData);
}

void HBModbusClient::updatePulseCount(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Current Delta Address: " << hexAddress << "----- Updated depth:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2PULSE, hexData);
    HBHome::GetInstance()->setPulseCount(strData);
}

void HBModbusClient::updateTensionLimited(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Limited Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_ForceUnit)
    {
    case Tensiometer::LB:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, hexData);
        break;
    case Tensiometer::KG:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, hexData);
        break;
    case Tensiometer::KN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    }
    HBHome::GetInstance()->setTensionLimited(strData);
}

void HBModbusClient::updateDepthTargetLayer(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Depth Target Layer Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_DistanceUnit)
    {
    case Depth::METER:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, hexData);
        break;
    case Depth::FEET:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER, hexData);
        break;
    }
    HBHome::GetInstance()->setDepthTargetLayer(strData);
}

void HBModbusClient::updateVelocityLimited(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Velocity Current Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_VelocityUnit)
    {
    case Depth::M_PER_HOUR:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_HOUR, hexData);
        break;
    case Depth::M_PER_MIN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_MIN, hexData);
        break;
    case Depth::FT_PER_HOUR:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET_PER_HOUR, hexData);
        break;
    case Depth::FT_PER_MIN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2FEET_PER_MIN, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2METER_PER_HOUR, hexData);
        break;
    }
    HBHome::GetInstance()->setVelocityLimited(strData);
}

void HBModbusClient::updateTensionLimitedDelta(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Limited Delta Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_ForceUnit)
    {
    case Tensiometer::LB:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, hexData);
        break;
    case Tensiometer::KG:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, hexData);
        break;
    case Tensiometer::KN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    }
    HBHome::GetInstance()->setTensionLimitedDelta(strData);
}

void HBModbusClient::updateKValue(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "K Value Address: " << hexAddress << "----- Updated depth:" << hexData;
    strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2K_VALUE, hexData);
    HBHome::GetInstance()->setKValue(strData);
}

void HBModbusClient::updateTensionCableHead(const int hexData, const int hexAddress)
{
    QString strData = "";
    qDebug() << "Tension Cable Head Address: " << hexAddress << "----- Updated depth:" << hexData;
    switch(m_ForceUnit)
    {
    case Tensiometer::LB:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, hexData);
        break;
    case Tensiometer::KG:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, hexData);
        break;
    case Tensiometer::KN:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    default:
        strData = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, hexData);
        break;
    }
    HBHome::GetInstance()->setTensionCableHead(strData);
}

bool HBModbusClient::writeRegister(int address, const int value)
{
    m_mutexSending.lock();
    m_RegisterSendMap.insert(address, value);
    m_mutexSending.unlock();
    return true;
}

void HBModbusClient::readCoils()
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus not connected";
        return;
    }

    QModbusDataUnit request(QModbusDataUnit::Coils, HQmlEnum::ALARM_SPEED, 12);

    if (auto *reply = _ptrModbus->sendReadRequest(request, 1)) {
        connect(reply, &QModbusReply::finished, this, [this, reply]() {
            if (reply->error() == QModbusDevice::NoError) {
                handleCoilResult(reply->result());
            } else {
                qWarning() << "Coil read failed:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        qWarning() << "Failed to send coil read request:" << _ptrModbus->errorString();
    }
}

void HBModbusClient::handleCoilResult(const QModbusDataUnit &result)
{
    int startAddress = result.startAddress();
    int count = result.valueCount();

    for (int i = 0; i < count; ++i) {
        int address = startAddress + i;
        bool val = result.value(i);
        // handleAlarm(address, val);
    }
}

void HBModbusClient::handleAlarm(int address, bool value)
{
    QString alarmName;
    bool alarmActive = value;

    switch (address) {
    case HQmlEnum::ALARM_SPEED:
        alarmName = "速度报警";
        if (alarmActive) {

            qDebug() << alarmName << "触发 - 限速或者停止设备";

        } else {
            qDebug() << alarmName << "解除 - 恢复正常运行";

        }
        break;

    case HQmlEnum::ALARM_WELL:
        alarmName = "井口报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 井口异常，执行安全停机";

        } else {
            qDebug() << alarmName << "解除 - 井口正常";
        }
        break;

    case HQmlEnum::ALARM_TARGETLAYERDEPTH:
        alarmName = "目的层报警";

        qDebug() << alarmName << (alarmActive ? "触发" : "解除");
        break;

    case HQmlEnum::ALARM_METERDEPTH:
        alarmName = "表套深度报警";
        if (alarmActive) {


        } else {
            qDebug() << alarmName << "解除";

        }
        break;

    case HQmlEnum::ALARM_TENSION:
        alarmName = "张力报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }
        break;


    case HQmlEnum::ALARM_TENSIONINC_1:
        alarmName = "张力增量报警（遇阻）";
        qDebug() << alarmName << (alarmActive ? "触发" : "解除");
        break;

    case HQmlEnum::ALARM_TENSIONINC_2:
        alarmName = "张力增量报警（遇卡）";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }
        break;

    case HQmlEnum::ALARM_CABLETENSION_1:
        alarmName = "揽头张力遇阻报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CABLETENSION_2:
        alarmName = "揽头张力遇卡报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CODE1:
        alarmName = "编码器1报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CODE2:
        alarmName = "编码器2报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    case HQmlEnum::ALARM_CODE3:
        alarmName = "编码器3报警";
        if (alarmActive) {
            qDebug() << alarmName << "触发 - 检查张力状态";

        } else {
            qDebug() << alarmName << "解除";
        }

        break;

    default:
        break;
    }
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

void HBModbusClient::writeCoil(int address, int value)
{
    if (!_ptrModbus || _ptrModbus->state() != QModbusDevice::ConnectedState)
    {
        qWarning() << "Modbus not connected";
        return;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, address, 1);
    writeUnit.setValue(0, value ? 1 : 0); // 确保是 0 或 1

    int serverAddress = 1;

    if (auto *reply = _ptrModbus->sendWriteRequest(writeUnit, serverAddress))
    {
        connect(reply, &QModbusReply::finished, this, [reply]()
                {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "Coil write successful";
            } else {
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
