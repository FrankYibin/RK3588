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
        // 静音
        DEPTHORIENTATION = 2, //     深度方向
        //         自动控速使能
        //             张力计校准使能
        //                 保护
        //                     张力清零标识位
        //                         张力计在线状态

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
    Q_ENUM(COILS_REGISTERS)

    enum HOLDING_REGISTERS
    {
        DEPTH_CURRENT_H = 8,        //深度高十六位
        DEPTH_CURRENT_L,            //深度低十六位
        VELOCITY_CURRENT_H,         //速度高十六位
        VELOCITY_CURRENT_L,         //速度高十六位
        VELOCITY_LIMITED_H,         //极限速度高十六位
        VELOCITY_LIMITED_L,         //极限速度低十六位
        DEPTH_TARGET_LAYER_H,       //目的层深度高十六位
        DEPTH_TARGET_LAYER_L,       //目的层深度低十六位
        DEPTH_SURFACE_COVER_H,      //表套深度高十六位
        DEPTH_SURFACE_COVER_L,      //表套深度低十六位
        PULSE_COUNT,                //脉冲数
        DEPTH_ENCODER,              //编码器源选择
        DEPTH_ENCODER_1_H,          //编码器1深度
        DEPTH_ENCODER_1_L,          //
        DEPTH_ENCODER_2_H,          //编码器2深度
        DEPTH_ENCODER_2_L,          //
        DEPTH_ENCODER_3_H,          //编码器3深度
        DEPTH_ENCODER_3_L,          //
        DEPTH_TOLERANCE_H,          //两个编码器深度实时误差
        DEPTH_TOLERANCE_L,          //

        DEPTH_CURRENT_DELTA,        //深度倒计功能深度
        TENSION_CURRENT_H,          //张力高十六位
        TENSION_CURRENT_L,          //张力低十六位
        TENSION_CURRENT_DELTA_H,    //张力增量高十六位
        TENSION_CURRENT_DELTA_L,    //张力增量低十六位
        TENSION_LIMITED_H,          //极限张力高十六位
        TENSION_LIMITED_L,          //极限张力低十六位
        TENSION_LIMITED_DELTA_H,    //极限张力增量高十六位
        TENSION_LIMITED_DELTA_L,    //极限张力增量低十六位
        TENSION_CABLE_HEAD_H,       //缆头张力高十六位
        TENSION_CABLE_HEAD_L,       //缆头张力低十六位

        K_VALUE,                    //K值
        TENSIOMETER_ENCODER,            //张力类型
        TENSIOMETER_ANALOG,             //模拟张力通道(张力计在线状态)
        TENSIOMETER_BATTERY,            //张力计电池电量(无线张力计有效)
        TENSIOMETER_NUM_H,              //张力计编号高十六位
        TENSIOMETER_NUM_L,              //张力计编号低十六位
        SCALE_1_H,
        SCALE_1_L,
        TENSION_1_H,
        TENSION_1_L,
        SCALE_2_H,
        SCALE_2_L,
        TENSION_2_H,
        TENSION_2_L,
        SCALE_3_H,
        SCALE_3_L,
        TENSION_3_H,
        TENSION_3_L,
        SCALE_4_H,
        SCALE_4_L,
        TENSION_4_H,
        TENSION_4_L,
        SCALE_5_H,
        SCALE_5_L,
        TENSION_5_H,
        TENSION_5_L,
        QUANTITY_OF_CALIBRATION,    //校准端点数量
        VELOCITY_STATUS,            //控速状态
        VELOCITY_SETTING_H,         //控速速度高十六位
        VELOCITY_SETTING_L,         //控速速度低十六位
        VELOCITY_SIMAN_H,           //四慢速度高十六位
        VELOCITY_SIMAN_L,           // 四慢速度低十六位
        CURRENT_PUMP_MOVE_DOWN,     //泵下放电流（液压泵前进电磁铁电流值）
        CURRENT_PUMP_MOVE_UP,       //泵上提电流（液压后退进电磁铁电流值）
        CURRENT_MOTOR,              //马达电流（马达电磁铁电流值）
        VOLOTAGE_MOTOR,             //微调电位计电压（马达速度电位器值）
        PERCENT_PUMP,               //液压泵速度电位器值
        PERCENT_VELOCITY,           //速度微调电位计值
        TONNAGE_TENSION_STICK,      //拉力棒吨位
        CABLE_SPEC,                 //电缆规格
        DEPTH_WELL_SETTING_H,       //作业井深度高十六位
        DEPTH_WELL_SETTING_L,
        WELL_TYPE,                  //油气井类型
        WOKE_TYPE,                  //作业类型
        BREAKING_FORCE_CABLE,       //电缆拉断力
        BREAKING_FORCE_WEAKNESS,    //弱点拉断力
        WEIGHT_EACH_KILOMETER_CABLE,//电缆每千米重量
        WEIGHT_INSTRUMENT_STRING,   //仪器串重量

        TENSION_SAFETY_COEFFICIENT, //安全张力系数
        TENSION_CURRENT_SAFETY_H,   //当前安全张力
        TENSION_CURRENT_SAFETY_L,
        TENSION_CURRENT_LIMITED_H,  //当前极限张力
        TENSION_CURRENT_LIMITED_L,
        TENSION_CABLE_HEAD_TREND,   //揽头张力变化趋势
        TIME_SAFETY_STOP,           //安全停车时间

        DISTANCE_UPPER_WELL_SETTING_H,  //  井口报警距离设置高字节
        DISTANCE_UPPER_WELL_SETTING_L,  //  井口报警距离设置低字节

        DISTANCE_LOWER_WELL_SETTING_H,  // 井底报警距离设置高字节
        DISTANCE_LOWER_WELL_SETTING_L,  //   井底报警距离设置低字节
        SLOPE_ANGLE_WELL_SETTING,       // 大斜度井斜度设置
        MAX_REGISTR

    };
    Q_ENUM(HOLDING_REGISTERS)

    enum TENSION_UNIT{

        UnitLb,
        UnitKg,
        UnitKn

    };Q_ENUM(TENSION_UNIT)

    enum DEPTH_UNIT{

        UnitMPerMin,
        UnitMPerHour,
        UnitFtPerMin,
        UnitFtPerHour

    };Q_ENUM(DEPTH_UNIT)



public:
    explicit HQmlEnum(QObject *parent = nullptr){}

signals:


};

#endif // HBQMLENUM_H
