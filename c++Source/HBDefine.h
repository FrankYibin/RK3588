#ifndef HBDEFINE_H
#define HBDEFINE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QPointF>


// Ground serial port system

struct _GroundSerial
{
    int Port;
    int BaudRate;
    int DataBit;
    int SerialType;
};

//Ground gauge

struct _Ground_Network
{
    int GProtocol;       //networking protocol
    QString GLocalIP;    //local ip
    int GLocalPort;      //local port
    int GRemoteIP;       //remote ip
    QString GRemotePort; //remote port
};

//cloud platform
struct _Cloud_Network
{
    int CProtocol;        //networking protocol
    QString CLocalIP;     //local ip
    int CLocalPort;       //local port
    int CRemoteIP;        //remote ip
    QString CRemotePort;  //remote ip
};

struct _WellParameter {

    int id= 0;
    QString wellNumber;
    QString areaBlock;
    int wellType = 0;
    QString wellDepth;
    QString harnessWeight;
    QString sensorWeight;
    int harnessType = 0;
    QString harnessForce;
    int tensionUnit = 0;
    int workType = 0;
    QString userName;
    QString operatorType;

};

struct _DepthSet {
    int id;
    int targetLayerDepth;
    int depthOrientation;
    int meterDepth;
    int depthCalculateType;
    int codeOption;
    int pulse;
};

struct _DepthSafe {
    int id;
    int depthPreset;
    int wellWarnig;
    int brake;
    int velocityLimit;
    int depthWarning;
    int totalDepth;
    int depthBrake;
    int depthVelocityLimit;
};

struct _TensionSafe {
    int id;
    QString wellType;
    int maxTension;
    QString weakForce;
    QString tensionSafeFactor;
};

struct _TensionSet {
    int id;
    int kValue;
    int tensionUnit;
};

struct TensiometerData {
    int id;
    QString tensiometerNumber;
    int tensiometerType;           //0 数字无线  1 数字有线   2 模拟有线
    int tensiometerRange;          //0 10T      1 15T       2 20T           3  30T
    int tensiometerSignal;         //0 无       1 30mV      2 0-1.5V 3      3 0-5V

};


struct _Measurements_data{
    int id;                                // id
    QString wellnum;                       // wellnum
    double depth;                          // depth
    double speed;                          // speed
    double target_depth;                   // target_depth
    double surface_depth;                  // surface_depth
    double pulse_count;                    // pulse_count
    double depth_dir;                      // depth_dir
    double depth_calcu;                    // depth_calcu
    double coder_cho;                      // coder_cho
    double coder1_depth;                   // coder1_depth
    double coder2_depth;                   // coder2_depth
    double coder3_depth;                   // coder3_depth
    double coder_error;                    // coder_error
    double depth_countdown;                // depth_countdown
    double cumulative_depth;               // cumulative_depth
    double tension;                        // tension
    double tension_increment;              // tension_increment
    double K_value;                        // K_value
    double tensioner_status;               // tensioner_status
    double tension_meter_bat;              // tension_meter_bat
    double tensioner_num;                  // tensioner_num
    double scale_end_num;                  // scale_end_num
    double end_scale;                      // end_scale
    double end_tension;                    // end_tension
    double end_nums;                       // end_nums
    double calibrate_or;                   // calibrate_or
    double limit_tension;                  // limit_tension
    double limit_tension_increment;        // limit_tension_increment
    double limit_speed;                    // limit_speed
    double head_tension;                   // head_tension
    double cv_status;                      // cv_status
    double cv_let;                         // cv_let
    double cv_speed;                       // cv_speed
    double pump_down_current;              // pump_down_current
    double pump_up_current;                // pump_up_current
    double motor_current;                  // motor_current
    double invalid_reservation;            // invalid_reservation
    double volt;                           // volt
    double tension_channel;                // tension_channel
    double pump_speed_potentiometer;       // pump_speed_potentiometer
    double speed_trimmer_potentiometer;    // speed_trimmer_potentiometer
    double tension_bar_m;                  // tension_bar_m
    double cable_specification;            // cable_specification
    double well_depth;                     // well_depth
    double well_deviation;                 // well_deviation
    double work_type;                      // work_type
    double cable_breaking_f;               // cable_breaking_f
    double weak_pull_f;                    // weak_pull_f
    double m_per_km;                       // m_per_km
    double instruments_m;                  // instruments_m
    double safe_tension_paras;             // safe_tension_paras
    double now_safe_tension;               // now_safe_tension
    double now_limit_tension;              // now_limit_tension
    double cable_tension_changing;         // cable_tension_changing
    double safe_stop_time;                 // safe_stop_time
    double depth_tension_status;           // depth_tension_status
    QString timestamp;                   // timestamp
    QString current_user;                  // current_user
    QString speed_unit;                    // speed_unit
    QString tension_unit;                  //tension_unit

};

struct _USER_DATA {
    int id;
    QString username;
    int  password;
};






//

#endif // HBDEFINE_H
