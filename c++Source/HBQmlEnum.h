#ifndef HBQMLENUM_H
#define HBQMLENUM_H

#include <QObject>

class HQmlEnum: public QObject
{
    Q_OBJECT
public:

    enum RS232_COLUMN
    {
        RS232_port = 0,
        RS232_baud_rate,
        RS232_data_bit,
        RS232_parity_bit,
        RS232_protocol,
    };
    Q_ENUM(RS232_COLUMN)

    enum COILS_REGISTERS
    {
        ALARM_BIT0 = 0,
        ALARM_BIT1,
        ALARM_BIT2,
        ALARM_BIT3,
        ALARM_BIT4,
        ALARM_BIT5,
        ALARM_BIT6,
        ALARM_BIT7,

        PROTECTION_STATE_BIT0,
        PROTECTION_STATE_BIT1,
        PROTECTION_STATE_BIT2,

        CAN_STATE_BIT3,
        CAN_STATE_BIT4,
        CAN_STATE_BIT5,
        CAN_STATE_BIT6,
        CAN_STATE_BIT7,

        CAN_STATE_bit0,
        CAN_STATE_bit1,
        CAN_STATE_bit2,
        CAN_STATE_bit3,
        CAN_STATE_bit4,
        CAN_STATE_bit5,
        CAN_STATE_bit6,
        CAN_STATE_bit7,

        ALARM_STATE_bit0,
        ALARM_STATE_bit1,
        ALARM_STATE_bit2,
        ALARM_STATE_bit3,

    };


    enum HOLDING_REGISTERS
    {
        DEPTH_H = 9,
        DEPTH_L,
        SPEED_H,
        SPEED_L,
        TARGET_DEPTH_H,
        TARGET_DEPTH_L,
        DEPTH_CASING_H,
        DEPTH_CASING_L,
        PULSE,
        DEPTH_DIRECTION,
        DEPTH_CALCD_TYPE,


        CODE_OPTION,
        DEPTH_CODE1_H,
        DEPTH_CODE1_L,
        DEPTH_CODE2_H,
        DEPTH_CODE2_L,
        DEPTH_CODE3_H,
        DEPTH_CODE3_L,

        CODE_COUNT_H,
        CODE_COUNT_L,
        DEPTH_COUNTDOWN,

        TENSION_H = 32,
        TENSION_L,
        TENSION_INCREMENT_H,
        TENSION_INCREMENT_L,
        K_VALUE,
        TENSIOMETER_STATUS,
        TENSIOMETER_BATTERY,
        TESIOMETER_NUM_H,
        TESIOMETER_NUM_L,
        CURRENT_TICK_ENDPOINT_NUM,
        ENDPOINT_VLAUE,
        TENSIOMETER_ENDPOINT_H,
        TENSIOMETER_ENDPOINT_L,
        CALIBRATION_ENDPOINT_NUM,
        CALIBRATION_ENABLE,
        MAX_TENSION_H,
        MAX_TENSION_L,
        MAX_TENSION_INCREMENT_H,
        MAX_TENSION_INCREMENT_L,
        MAX_SPEED_H,
        MAX_SPEED_L,
        MAX_DEPTH_H,
        MAX_DEPTH_L,
        CABLE_TENSION_H,
        CABLE_TENSION_L,
        SPEED_CONTROL_STATE,
        SPEED_ENABLE,
        SPEED_CONTROL_H,
        SPEED_CONTROL_L,

        TENSION_BAR_TONNAGE = 67,
        CABLE_TYPE,
        DEPTH_OPERATION_H,
        DEPTH_OPERATION_L,
        WELL_TYPE,
        OPERATION_TYPE,
        HARNESS_FORCE,
        WEAK_FORCE,
        CABLE_UINT,
        SENSOR_WEIGHT,
        TENSION_SAFE_FACTOR,
        CURRENT_TENSION_SAFE_H,
        CURRENT_TENSION_SAFE_L,
        CIRRENT_TENSION_MAX_H,
        CIRRENT_TENSION_MAX_L,
        HARNESS_TENSION_TREND,
        PARKING_SAFE_TIME,
        DEPTH_TENSION_STATE,

    };




public:
    explicit HQmlEnum(QObject *parent = nullptr){}

signals:


};

#endif // HBQMLENUM_H
