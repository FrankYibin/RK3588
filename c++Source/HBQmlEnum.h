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
        ALARM_SPEED = 16,                //速度报警
        ALARM_WELL,                      //井口报警
        ALARM_TARGETLAYERDEPTH,          //目的层报警
        ALARM_METERDEPTH,                //表套深度报警
        ALARM_TENSION,                      //张力报警
        ALARM_TENSIONINC_1,                      //张力增量报警（遇阻）
        ALARM_TENSIONINC_2,                      //张力增量报警（遇卡）
        ALARM_CABLETENSION_1,                      //揽头张力遇阻报警
        ALARM_CABLETENSION_2,           //揽头张力遇卡报警
        ALARM_CODE1,                  //编码器1报警
        ALARM_CODE2,                  //编码器2报警
        ALARM_CODE3,                  //编码器3报警
    };


    //    enum HOLDING_REGISTERS
    //    {
    //        DEPTH_H = 9,
    //        DEPTH_L,
    //        SPEED_H,
    //        SPEED_L,
    //        TARGET_DEPTH_H,
    //        TARGET_DEPTH_L,
    //        DEPTH_CASING_H,
    //        DEPTH_CASING_L,
    //        PULSE,
    //        DEPTH_DIRECTION,
    //        DEPTH_CALCD_TYPE,


    //        CODE_OPTION,
    //        DEPTH_CODE1_H,
    //        DEPTH_CODE1_L,
    //        DEPTH_CODE2_H,
    //        DEPTH_CODE2_L,
    //        DEPTH_CODE3_H,
    //        DEPTH_CODE3_L,

    //        CODE_COUNT_H,
    //        CODE_COUNT_L,
    //        DEPTH_COUNTDOWN,

    //        TENSION_H = 32,
    //        TENSION_L,
    //        TENSION_INCREMENT_H,
    //        TENSION_INCREMENT_L,
    //        K_VALUE,
    //        TENSIOMETER_STATUS,
    //        TENSIOMETER_BATTERY,
    //        TESIOMETER_NUM_H,
    //        TESIOMETER_NUM_L,
    //        CURRENT_TICK_ENDPOINT_NUM,
    //        ENDPOINT_VLAUE,
    //        TENSIOMETER_ENDPOINT_H,
    //        TENSIOMETER_ENDPOINT_L,
    //        CALIBRATION_ENDPOINT_NUM,
    //        CALIBRATION_ENABLE,
    //        MAX_TENSION_H,
    //        MAX_TENSION_L,
    //        MAX_TENSION_INCREMENT_H,
    //        MAX_TENSION_INCREMENT_L,
    //        MAX_SPEED_H,
    //        MAX_SPEED_L,
    //        MAX_DEPTH_H,
    //        MAX_DEPTH_L,
    //        CABLE_TENSION_H,
    //        CABLE_TENSION_L,
    //        SPEED_CONTROL_STATE,
    //        SPEED_ENABLE,
    //        SPEED_CONTROL_H,
    //        SPEED_CONTROL_L,

    //        TENSION_BAR_TONNAGE = 67,
    //        CABLE_TYPE,
    //        DEPTH_OPERATION_H,
    //        DEPTH_OPERATION_L,
    //        WELL_TYPE,
    //        OPERATION_TYPE,
    //        HARNESS_FORCE,
    //        WEAK_FORCE,
    //        CABLE_UINT,
    //        SENSOR_WEIGHT,
    //        TENSION_SAFE_FACTOR,
    //        CURRENT_TENSION_SAFE_H,
    //        CURRENT_TENSION_SAFE_L,
    //        CIRRENT_TENSION_MAX_H,
    //        CIRRENT_TENSION_MAX_L,
    //        HARNESS_TENSION_TREND,
    //        PARKING_SAFE_TIME,
    //        DEPTH_TENSION_STATE,

    //    };

    enum HOLDING_REGISTERS
    {

        DEPTH_H = 8,      //深度高十六位
        DEPTH_L,          //深度低十六位
        SPEED_H,          // 速度高十六位
        SPEED_L,          //速度高十六位
        MAX_SPEED_H,      // 极限速度高十六位
        MAX_SPEED_L,      //极限速度低十六位
        TARGET_DEPTH_H,   //目的层深度高十六位
        TARGET_DEPTH_L,   //  目的层深度低十六位
        METER_DEPTH_H,    //表套深度高十六位
        METER_DEPTH_L,      //表套深度低十六位
        PULSE,            //脉冲数

        DEPTHCALCULATETYPE,   //深度计算方式
        DEPTH_CODE1_H,        //编码器1深度
        DEPTH_CODE1_L,        //
        DEPTH_CODE2_H,        //编码器2深度
        DEPTH_CODE2_L,        //
        DEPTH_CODE3_H,        //编码器3深度
        DEPTH_CODE3_L,        //
        CODE_COUNT_H,         //两个编码器深度实时误差
        CODE_COUNT_L,         //

        DEPTH_COUNTDOWN,      //深度倒计功能深度
        TENSION_H,            // 张力高十六位
        TENSION_L,            //张力低十六位
        TENSION_INCREMENT_H,  //  张力增量高十六位
        TENSION_INCREMENT_L,  // 张力增量低十六位
        MAX_TENSION_H,        //极限张力高十六位
        MAX_TENSION_L,        //极限张力低十六位
        MAX_TENSION_INCREMENT_H,   //极限张力增量高十六位
        MAX_TENSION_INCREMENT_L,  //  极限张力增量低十六位
        CABLE_TENSION_H,      //  缆头张力高十六位
        CABLE_TENSION_L,      //缆头张力低十六位

        K_VALUE,              //K值
        TENSION_TYPE,         //张力类型
        TENSIOMETER_STATUS,   //模拟张力通道(张力计在线状态)
        TENSIOMETER_BATTERY,  //张力计电池电量(无线张力计有效)
        TESIOMETER_NUM_H,     //张力计编号高十六位
        TESIOMETER_NUM_L,     //张力计编号低十六位
        SCALE_1_H,
        SCALE_1_L,
        SCALE_1_TENSION_H,
        SCALE_1_TENSION_L,
        SCALE_2_H,
        SCALE_2_L,
        SCALE_2_TENSION_H,
        SCALE_2_TENSION_L,
        SCALE_3_H,
        SCALE_3_L,
        SCALE_3_TENSION_H,
        SCALE_3_TENSION_L,
        SCALE_4_H,
        SCALE_4_L,
        SCALE_4_TENSION_H,
        SCALE_4_TENSION_L,
        SCALE_5_H,
        SCALE_5_L,
        SCALE_5_TENSION_H,
        SCALE_5_TENSION_L,

        ENABLE_NUMBER,           //校准端点数量
        SPEED_CONTROL_STATE,     //控速状态
        CONTROL_SPEED_H,         //控速速度高十六位
        CONTROL_SPEED_L,         //控速速度低十六位
        F4_SPEED_H,              //四慢速度高十六位
        F4_SPEED_L,              // 四慢速度低十六位
        BEN_UP,                  //泵下放电流（液压泵前进电磁铁电流值）
        BEN_DOWN,                //泵上提电流（液压后退进电磁铁电流值）
        MOTOR_CURRENT,            //马达电流（马达电磁铁电流值）
        TRI_VOLOTAGE,             //微调电位计电压（马达速度电位器值）
        HYDRAULIC_PUMP,           //液压泵速度电位器值
        SPEED_TRIM_POTENTIOMETER,   //速度微调电位计值
        TENSION_BAR_TONNAGE,      //拉力棒吨位
        CABLE_TYPE,               //电缆规格
        WORK_WELL_H,              //作业井深度高十六位
        WORK_WELL_L,
        OIL_WELL_TYPE,            //油气井类型
        WOKE_TYPE,                //作业类型
        HARNESS_FORCE,            //电缆拉断力
        WEAK_FORCE,               //弱点拉断力
        CABLE_UINT,               //电缆每千米重量
        SENSOR_WEIGHT,            //仪器串重量

        TENSION_SAFE_FACTOR,     //安全张力系数
        CURRENT_TENSION_SAFE_H,   //当前安全张力
        CURRENT_TENSION_SAFE_L,
        CIRRENT_TENSION_MAX_H,    //当前极限张力
        CIRRENT_TENSION_MAX_L,
        HARNESS_TENSION_TREND,     //揽头张力变化趋势
        PARKING_SAFE_TIME,         //安全停车时间

        WELL_UP_ALARM_H,          //  井口报警距离设置高字节
        WELL_UP_ALARM_L,         //  井口报警距离设置低字节

        WELL_DOWN_ALARM_H,        // 井底报警距离设置高字节
        WELL_DOWN_ALARM_L,       //   井底报警距离设置低字节
        HIGH_ANGLE_WELL,         // 大斜度井斜度设置

    };

public:
    explicit HQmlEnum(QObject *parent = nullptr){}

signals:


};

#endif // HBQMLENUM_H
