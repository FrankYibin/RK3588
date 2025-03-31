/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 All the alarm Index definition
 
 **********************************************************************************************************/

#ifndef ALARMINDEXDEF_H
#define ALARMINDEXDEF_H
#include <QObject>
#include <QQmlEngine>

#define ALARMINDEXENUM_URI_NAME "Com.Branson.AlarmIndexEnum"
#define ALARMINDEXENUM_QML_MAJOR_VERSION 1
#define ALARMINDEXENUM_QML_MINOR_VERSION 0
#define ALARMINDEXENUM_QML_NAME "AlarmIndexEnum"

#define DUMMY_CHANGE_TEST 1

class AlarmIndexEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(ALARMINDEX)
public:
    enum ALARMINDEX
    {
        ALARM_PHASE_OVERLOAD_ID =					1,  // base number for weld overloads
        ALARM_CURR_OVERLOAD_ID =	 				2,
        ALARM_FREQ_OVERLOAD_ID =					3,
        ALARM_POWER_OVERLOAD_ID =					4,
        ALARM_VOLT_OVERLOAD_ID =					5,
        ALARM_TEMP_OVERLOAD_ID =					6,

        ALARM_EB_PHASE_OVERLOAD_ID =				17,  // base number for Energy Brake overloads
        ALARM_EB_CURR_OVERLOAD_ID =                 18,
        ALARM_EB_FREQ_OVERLOAD_ID =                 19,
        ALARM_EB_POWER_OVERLOAD_ID =				20,
        ALARM_EB_VOLT_OVERLOAD_ID =                 21,
        ALARM_EB_TEMP_OVERLOAD_ID =                 22,

        ALARM_AB_PHASE_OVERLOAD_ID =				33,  // base number for Afterburst overloads
        ALARM_AB_CURR_OVERLOAD_ID =                 34,
        ALARM_AB_FREQ_OVERLOAD_ID =                 35,
        ALARM_AB_POWER_OVERLOAD_ID =				36,
        ALARM_AB_VOLT_OVERLOAD_ID =                 37,
        ALARM_AB_TEMP_OVERLOAD_ID =                 38,

        ALARM_POST_SEEK_PHASE_OVERLOAD_ID =         49,  // base number for Post Weld Seek overloads
        ALARM_POST_SEEK_CURR_OVERLOAD_ID =          50,
        ALARM_POST_SEEK_FREQ_OVERLOAD_ID =          51,
        ALARM_POST_SEEK_POWER_OVERLOAD_ID =         52,
        ALARM_POST_SEEK_VOLT_OVERLOAD_ID =          53,
        ALARM_POST_SEEK_TEMP_OVERLOAD_ID =          54,

        /* No Cycle Alarm names */
        ALARM_NOCYCLE_EXTERNAL_SONIC_ID =           1795,
        ALARM_NOCYCLE_MISSING_PART_ID =             1798,
        ALARM_NOCYCLE_PART_CONTACT_ID =             1800,
        ALARM_NOCYCLE_EXTERNAL_CYCLE_ID =           1802,
        ALARM_NOCYCLE_ABSOLUTE_DISTANCE_ID =        1804,
        ALARM_NOCYCLE_EXTRA_TOOLING_ID =            1812,
        ALARM_NOCYCLE_EXTRA_TIMEOUT_ID =            1813,
        ALARM_NOCYCLE_PART_PRESENT_ID =             1814,
        ALARM_NOCYCLE_SERVO_MOTOR_ID =              1815,
        ALARM_NOCYCLE_READY_POS_ID =                1816,
        ALARM_NOCYCLE_RECIPE_NOTVALID_ID =          1817,
        ALARM_NOCYCLE_BATCH_COUNT_ID =              1818,
        ALARM_NOCYCLE_ACTIVERECIPE_NOTVALID_ID =    1819,
        ALARM_NOCYCLE_PC_ASS_MISMATCH_ID =          1824,
        ALARM_NOCYCLE_AC_ASS_MISMATCH_ID =          1825,
        ALARM_NOCYCLE_STACK_ASS_MISMATCH_ID =       1826,
        ALARM_NOCYCLE_TRIGGER_TIMEOUT_ID =          1827,

        /* Hardware failure alarm names */
        ALARM_HW_START_SWITCH_FAIL_ID =             1537,
        ALARM_HW_ULS_ACTIVE_ID =                    1538,
        ALARM_HW_ULS_NONACTIVE_ID =                 1540,
        ALARM_HW_GD_BEFORE_TRIGGER_ID =             1541,
        ALARM_HW_START_SWITCH_LOST_ID =             1545,
        ALARM_HW_ALARM_LOG_ID =                     1553,
        ALARM_HW_EVENT_LOG_ID =                     1554,
        ALARM_HW_WELD_RESULT_ID =                   1555,
        ALARM_HW_WELD_GRAPH_ID =                    1556,
        ALARM_HW_HORN_SCAN_ID =                     1557,
        ALARM_HW_PRETRIGGER_TIMEOUT_ID =            1568,
        ALARM_HW_ENCODER_FAIL_ID =                  1569,
        ALARM_HW_DATA_ERROR_ID =                    1572,
        ALARM_HW_HOME_RETURN_TIMEOUT_ID =           1573,
        ALARM_HW_ACTUATOR_NOVARM_ID =               1574,
        ALARM_HW_PS_NOVARM_ID =                     1575,
        ALARM_HW_START_SWITCH_TIME_ID =             1576,
        ALARM_HW_MEM_FULL_ID =                      1577,
        ALARM_HW_INTERNAL_STORAGE_FAIL_ID =         1578,
        ALARM_HW_RECALIBRATE_ACT_ID =               1583,
        ALARM_HW_ACT_CLR_FUN_ID =                   1584,
        ALARM_HW_EXTRA_TOOLING_ACTIVE_ID =          1585,
        ALARM_HW_ACT_TYPE_CHANGED_ID =              1586,
        ALARM_HW_SYS_PRESSURE_INCORRECT_ID =        1587,
        ALARM_HW_SYS_PART_PRESENT_ACTIVE_ID =       1588,
        ALARM_HW_USB_MEM_LOST_ID =                  1589,
        ALARM_INTERNAL_COMM_ENET =                  1592,
        ALARM_HW_ETH_LINK_LOST_ID =                 1593,
        ALARM_HW_CABLE_FAIL_ID =                    1594,
        ALARM_HW_PROFINET_OR_IP_NOT_ID =            1595,
        ALARM_HW_AC_LINE_LOST_ID =                  1596,
        ALARM_HW_TRIGGER_ACTIVE_READY_ID =          1597,
        ALARM_HW_INTERNAL_COMM_FAIL_ID =            1598,
        ALARM_HW_SC_COMPONENT_FAIL_ID =             1599,
        ALARM_HW_RTC_LOW_BATT_ID =                  1092,

        /* Cycle modified alarm names */
        ALARM_CYCLE_GROUND_DETECT_ABORT_ID =        771,
        ALARM_CYCLE_MAXTIMEOUT_ID =                 772,
        ALARM_CYCLE_NOFORCESTEP_ID =                774,
        ALARM_CYCLE_TRIGGER_GREATER_ENDFORCE_ID =   789,	//not E1
        ALARM_CYCLE_LL_NOT_REACHED_ID =             791,
        ALARM_CYCLE_PEAKPOWER_CUTOFF_ID =           1051,
        ALARM_CYCLE_ABSOLUTE_CUTOFF_ID =            1052,
        ALARM_CYCLE_COLLAPSE_CUTOFF_ID =            1055,
        ALARM_CYCLE_ULTRASONICS_DISABLED_ID =       1057,
        ALARM_CYCLE_CUSTOM1_CUTOFF_ID =             1060,
        ALARM_CYCLE_CUSTOM2_CUTOFF_ID =             1061,
        ALARM_CYCLE_FREQLOW_CUTOFF_ID =             1062,
        ALARM_CYCLE_FREQHIGH_CUTOFF_ID =            1063,
        ALARM_CYCLE_CUST_DIGITAL_CUTOFF_ID =        1064,
        ALARM_CYCLE_ENERGY_CUTOFF_ID =              1065,
        ALARM_CYCLE_GD_CUTOFF_ID =                  1066,
        ALARM_CYCLE_TIME_CUTOFF_ID =                1067,
        ALARM_CYCLE_NO_PRESSURE_STEP_ID =           1081,

        /* Suspect alarms */
        ALARM_ENERGY_SLLIMIT_ID =                   1361,
        ALARM_ENERGY_SHLIMIT_ID =                   1362,
        ALARM_POWER_SLLIMIT_ID =                    1363,
        ALARM_POWER_SHLIMIT_ID =                    1364,
        ALARM_COLLAPSE_SLLIMIT_ID =                 1365,
        ALARM_COLLAPSE_SHLIMIT_ID =                 1366,
        ALARM_ABSOLUTE_SLLIMIT_ID =                 1367,
        ALARM_ABSOLUTE_SHLIMIT_ID =                 1368,
        ALARM_TRIGGER_SLLIMIT_ID =                  1369,
        ALARM_TRIGGER_SHLIMIT_ID =                  1370,
        ALARM_WELD_FORCE_SLLIMIT_ID =               1371,
        ALARM_WELD_FORCE_SHLIMIT_ID =               1372,
        ALARM_TIME_SLLIMIT_ID =                     1373,
        ALARM_TIME_SHLIMIT_ID =                     1374,
        ALARM_VELOCITY_SLLIMITS_ID =                1376,
        ALARM_VELOCITY_SHLIMITS_ID =                1377,
        ALARM_FREQ_SLLIMITS_ID =                    1378,
        ALARM_FREQ_SHLIMITS_ID =                    1379,

        /* Reject alarms */
        ALARM_VELOCITY_RLLIMITS_ID =                1281,
        ALARM_VELOCITY_RHLIMITS_ID =                1282,
        ALARM_POWER_RLLIMIT_ID =                    1283,
        ALARM_POWER_RHLIMIT_ID =                    1284,
        ALARM_TIME_RLLIMIT_ID =                     1285,
        ALARM_TIME_RHLIMIT_ID =                     1286,
        ALARM_ENERGY_RLLIMIT_ID =                   1287,
        ALARM_ENERGY_RHLIMIT_ID =                   1288,
        ALARM_COLLAPSE_RLLIMIT_ID =                 1289,
        ALARM_COLLAPSE_RHLIMIT_ID =                 1290,
        ALARM_ABSOLUTE_RLLIMIT_ID =                 1291,
        ALARM_ABSOLUTE_RHLIMIT_ID =                 1292,
        ALARM_TRIGGER_RLLIMIT_ID =                  1293,
        ALARM_TRIGGER_RHLIMIT_ID =                  1294,
        ALARM_WELD_FORCE_RLLIMIT_ID =               1295,
        ALARM_WELD_FORCE_RHLIMIT_ID =               1296,
        ALARM_FREQ_RLLIMITS_ID =                    1298,
        ALARM_FREQ_RHLIMITS_ID =                    1299,
        ALARM_POWER_MATCH_CURVE_RLLIMITS_ID =       1300,
        ALARM_POWER_MATCH_CURVE_RHLIMITS_ID =       1301,

        /* Warnings */
        ALARM_WARNING_TRIGGERLOST_ID =              1025,
        ALARM_WARNING_ACTUATOR_CLR_NOT_RCHD_ID =    1047,
        ALARM_WARNING_ACTU_RECAL_ID =               1054,
        ALARM_WARNING_USBMEMORY_ID =                1058,
        ALARM_WARNING_DISK_MEMORY_ID =              1059,
        ALARM_WARNING_ALARM_LOG_ID =                1093,
        ALARM_WARNING_EVENT_LOG_ID =                1094,
        ALARM_WARNING_WELD_RESULT_ID =              1095,
        ALARM_WARNING_WELD_GRAPH_ID =               1096,
        ALARM_WARNING_HORN_SCAN_ID =                1097,
        ALARM_WARNING_EEPROM_CORRUPT_ID =           1104,

        /*  No Cycle Overloads - Overloads that happen before trigger or outside the weld cycle */
        ALARM_TEST_OVERLOAD_PHASE_ID =              2113,	// base number for Test overloads
        ALARM_TEST_OVERLOAD_CURRENT_ID =            2114,
        ALARM_TEST_OVERLOAD_FREQUENCY_ID =          2115,
        ALARM_TEST_OVERLOAD_POWER_ID =              2116,
        ALARM_TEST_OVERLOAD_VOLTAGE_ID =            2117,
        ALARM_TEST_OVERLOAD_TEMPERATURE_ID =        2118,
        ALARM_PRETRIGGER_OVERLOAD_PHASE_ID =        2129,	// base number for Pretrigger overloads
        ALARM_PRETRIGGER_OVERLOAD_CURRENT_ID =      2130,
        ALARM_PRETRIGGER_OVERLOAD_FREQUENCY_ID =    2131,
        ALARM_PRETRIGGER_OVERLOAD_POWER_ID =        2132,
        ALARM_PRETRIGGER_OVERLOAD_VOLTAGE_ID =      2133,
        ALARM_PRETRIGGER_OVERLOAD_TEMPERATURE_ID =  2134,
        ALARM_SEEK_OVERLOAD_PHASE_ID =              2145,	// base number for Seek overloads
        ALARM_SEEK_OVERLOAD_CURRENT_ID =            2146,
        ALARM_SEEK_OVERLOAD_FREQUENCY_ID =          2147,
        ALARM_SEEK_OVERLOAD_POWER_ID =              2148,
        ALARM_SEEK_OVERLOAD_VOLTAGE_ID =            2149,
        ALARM_SEEK_OVERLOAD_TEMPERATURE_ID =        2150,
        ALARM_PRE_SEEK_PHASE_OVERLOAD_ID =          2177,  // base number for Pre Weld Seek overloads
        ALARM_PRE_SEEK_CURR_OVERLOAD_ID =           2178,
        ALARM_PRE_SEEK_FREQ_OVERLOAD_ID =           2179,
        ALARM_PRE_SEEK_POWER_OVERLOAD_ID =          2180,
        ALARM_PRE_SEEK_VOLT_OVERLOAD_ID =           2181,
        ALARM_PRE_SEEK_TEMP_OVERLOAD_ID =           2182,

        /* EN Faults */
        ALARM_MULTIPLE_FAULTS_ID =                  3824,
        ALARM_PALM_BUTTON_FAULT_ID =                3825,
        ALARM_24V_FAULT_ID =                        3826,
        ALARM_ESTOP_FAULT_ID =                      3827,
        ALARM_LINEAR_ENCODER_FAULT_ID =             3828,
        ALARM_S_BEAM_FAULT_ID =                     3829,
        ALARM_TRIGGER_SWITCH_FAULT_ID =             3830,
        ALARM_DRIVE_FAULT_ID =                      3831,
        ALARM_CROSS_MONITORING_FAULT_ID =           3832,
        ALARM_LOGIC_FAULT_ID =                      3833,
        ALARM_SONICS_ENABLE_FAULT_ID =              3834
    };

    static void registerQMLType()
    {
        qmlRegisterType<AlarmIndexEnum>(ALARMINDEXENUM_URI_NAME,
                                       ALARMINDEXENUM_QML_MAJOR_VERSION,
                                       ALARMINDEXENUM_QML_MINOR_VERSION,
                                       ALARMINDEXENUM_QML_NAME);
    }
};

#endif // ALARMINDEXDEF_H
