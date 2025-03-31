/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 Alarm showing utility for the alarm message translation and some normal function
 
 **********************************************************************************************************/

pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.0
import Com.Branson.AlarmIndexEnum 1.0
import Com.Branson.UIScreenEnum 1.0
Item {
    id: alarmMessageDefine

    property string qmltextAlarm:                                   qsTr("ALARM")
    property string qmltextErrorDescriptionTitle:                   qsTr("ERROR DESCRIPTION")
    property string qmltextReset:                                   qsTr("RESET")
    property string qmltextHide:                                    qsTr("HIDE")
    property var    qmlGeneralTextArray: [qmltextErrorDescriptionTitle, qmltextReset, qmltextHide]

    /* No Cycle Alarm names */
    property string qmlALARM_NOCYCLE_EXTERNAL_SONIC:                qsTr("External Sonics Delay Timeout")
    property string qmlALARM_NOCYCLE_MISSING_PART:                  qsTr("Part Window Abort")
    property string qmlALARM_NOCYCLE_PART_CONTACT:                  qsTr("Part Contact before Pretrigger")
    property string qmlALARM_NOCYCLE_EXTERNAL_CYCLE:                qsTr("External Cycle Abort")
    property string qmlALARM_NOCYCLE_ABSOLUTE_DISTANCE:             qsTr("Invalid Part Contact Distance")
    property string qmlALARM_NOCYCLE_EXTRA_TOOLING:                 qsTr("External Tooling Input Lost")
    property string qmlALARM_NOCYCLE_EXTRA_TIMEOUT:                 qsTr("External Tooling Input Timeout")
    property string qmlALARM_NOCYCLE_PART_PRESENT:                  qsTr("Part Present Input Lost")
    property string qmlALARM_NOCYCLE_SERVO_MOTOR:                   qsTr("Actuation Drive Error")
    property string qmlALARM_NOCYCLE_READY_POS:                     qsTr("Ready Position Timeout")
    property string qmlALARM_NOCYCLE_RECIPE_NOTVALID:               qsTr("Recipe Not Valid")
    property string qmlALARM_NOCYCLE_BATCH_COUNT:                   qsTr("Batch Count Complete")
    property string qmlALARM_NOCYCLE_ACTIVERECIPE_NOTVALID:         qsTr("Active Recipe not Validated")
    property string qmlALARM_NOCYCLE_PC_ASS_MISMATCH:               qsTr("Power Supply Assembly Component Mismatch")
    property string qmlALARM_NOCYCLE_AC_ASS_MISMATCH:               qsTr("Actuator Assembly Component Mismatch")
    property string qmlALARM_NOCYCLE_STACK_ASS_MISMATCH:            qsTr("Stack Assembly Component Mismatch")
    property string qmlALARM_NOCYCLE_TRIGGER_TIMEOUT:               qsTr("Trigger Timeout")

    /* No Cycle Alarm Descriptions */
    property string qmlALARM_NOCYCLE_EXTERNAL_SONIC_DESC:           qsTr("Trigger Delay has been turned on, but the assigned input did not become inactive within the 30 seconds allowed.")
    property string qmlALARM_NOCYCLE_MISSING_PART_DESC:             qsTr("The Missing Part Minimum Distance has not been reached before Trigger occurred or the Maximum Distance has been exceeded before Trigger has occurred.")
    property string qmlALARM_NOCYCLE_PART_CONTACT_DESC:             qsTr("The Part Contact Distance has been met before the defined Pretrigger Distance.")
    property string qmlALARM_NOCYCLE_EXTERNAL_CYCLE_DESC:           qsTr("The Cycle Abort Digital Input has been activated before trigger occurred.")
    property string qmlALARM_NOCYCLE_ABSOLUTE_DISTANCE_DESC:        qsTr("The Part Contact Distance is invalid or not set.")
    property string qmlALARM_NOCYCLE_EXTRA_TOOLING_DESC:            qsTr("The External Tooling Input became inactive before Hold Time ended.")
    property string qmlALARM_NOCYCLE_EXTRA_TIMEOUT_DESC:            qsTr("The External Tooling Input did not become active within the Tooling Delay Input time after the External Tooling Output became active.")
    property string qmlALARM_NOCYCLE_PART_PRESENT_DESC:             qsTr("The Part Present Input became inactive before the end of Hold Time.")
    property string qmlALARM_NOCYCLE_SERVO_MOTOR_DESC:              qsTr("The Actuator did not reach the target defined position or Actuation is being prevented.")
    property string qmlALARM_NOCYCLE_READY_POS_DESC:                qsTr("The Actuator did not return to the Ready Position within 4 seconds from end of Hold Time.")
    property string qmlALARM_NOCYCLE_RECIPE_NOTVALID_DESC:          qsTr("The External Recipe # is not valid through the I/O or Barcode scanner.")
    property string qmlALARM_NOCYCLE_BATCH_COUNT_DESC:              qsTr("The target number of welds for this Batch has been met.\n\nNavigate to the Recipe Production Screen to reset the count.")
    property string qmlALARM_NOCYCLE_ACTIVERECIPE_NOTVALID_DESC:    qsTr("The Operator is attempting to run a recipe that has not been Validated.")
    property string qmlALARM_NOCYCLE_PC_ASS_MISMATCH_DESC:          qsTr("The Power Supply Component Name defined in the System Configuration do not match the Name stored with this Recipe.")
    property string qmlALARM_NOCYCLE_AC_ASS_MISMATCH_DESC:          qsTr("The Actuator Component Name defined in the System Configuration do not match the Name stored with this Recipe.")
    property string qmlALARM_NOCYCLE_STACK_ASS_MISMATCH_DESC:       qsTr("The Ultrasonic Stack Component Name defined in the System Configuration do not match the Name stored with this Recipe.")
    property string qmlALARM_NOCYCLE_TRIGGER_TIMEOUT_DESC:          qsTr("The Trigger Force was not achieved within the 10 second allowed time.")

    /* Hardware failure alarm names */
    property string qmlALARM_HW_START_SWITCH_FAIL:                  qsTr("Start Switch Still Active")
    property string qmlALARM_HW_ULS_ACTIVE:                         qsTr("ULS Still Active")
    property string qmlALARM_HW_ULS_NONACTIVE:                      qsTr("ULS Not Active After Homing")
    property string qmlALARM_HW_GD_BEFORE_TRIGGER:                  qsTr("Ground Detect Before Trigger")
    property string qmlALARM_HW_START_SWITCH_LOST:                  qsTr("Start Switch Lost")
    property string qmlALARM_HW_ALARM_LOG:                          qsTr("Alarm Log Capacity Reached")
    property string qmlALARM_HW_EVENT_LOG:                          qsTr("Event Log Capacity Reached")
    property string qmlALARM_HW_WELD_RESULT:                        qsTr("Weld Result Capacity Reached")
    property string qmlALARM_HW_WELD_GRAPH:                         qsTr("Weld Graph Capacity Reached")
    property string qmlALARM_HW_HORN_SCAN:                          qsTr("Horn Scan Graph Capacity Reached")
    property string qmlALARM_HW_PRETRIGGER_TIMEOUT:                 qsTr("Pretrigger Timeout")
    property string qmlALARM_HW_ENCODER_FAIL:                       qsTr("Encoder Failure")
    property string qmlALARM_HW_DATA_ERROR:                         qsTr("Data Error")
    property string qmlALARM_HW_HOME_RETURN_TIMEOUT:                qsTr("Actuator Return Timeout")
    property string qmlALARM_HW_ACTUATOR_NOVARM:                    qsTr("Actuator Novram")
    property string qmlALARM_HW_PS_NOVARM:                          qsTr("P/S Novram")
    property string qmlALARM_HW_START_SWITCH_TIME:                  qsTr("Start Switch Time")
    property string qmlALARM_HW_MEM_FULL:                           qsTr("Data Storage Full")
    property string qmlALARM_HW_INTERNAL_STORAGE_FAIL:              qsTr("Internal Failure")
    property string qmlALARM_HW_RECALIBRATE_ACT:                    qsTr("Recalibrate Actuator")
    property string qmlALARM_HW_ACT_CLR_FUN:                        qsTr("Actuator Clear Function")
    property string qmlALARM_HW_EXTRA_TOOLING_ACTIVE:               qsTr("Ext Tooling Active")
    property string qmlALARM_HW_ACT_TYPE_CHANGED:                   qsTr("Actuator Type Changed")
    property string qmlALARM_HW_SYS_PRESSURE_INCORRECT:             qsTr("System Pressure Incorrect")
    property string qmlALARM_HW_SYS_PART_PRESENT_ACTIVE:            qsTr("Part Present Active")
    property string qmlALARM_HW_USB_MEM_LOST:                       qsTr("USB Memory Lost")
    property string qmlALARM_CONNECTION_LOST:                       qsTr("Connection Lost")
    property string qmlALARM_HW_ETH_LINK_LOST:                      qsTr("Ethernet Link Lost")
    property string qmlALARM_HW_CABLE_FAIL:                         qsTr("Cable Failure")
    property string qmlALARM_HW_PROFINET_OR_IP_NOT:                 qsTr("Profinet or Ethernet/IP not responding")
    property string qmlALARM_HW_AC_LINE_LOST:                       qsTr("AC Line Voltage Lost")
    property string qmlALARM_HW_TRIGGER_ACTIVE_READY:               qsTr("Trigger active in Ready")
    property string qmlALARM_HW_INTERNAL_COMM_FAIL:                 qsTr("HMI Connection Lost")
    property string qmlALARM_HW_SC_COMPONENT_FAIL:                  qsTr("Internal Component Failure")

    /* Hardware failure alarm descriptions */
    property string qmlALARM_HW_START_SWITCH_FAIL_DESC:             qsTr("The Start Switches are still active 6 seconds after the end of the Cycle.")
    property string qmlALARM_HW_ULS_ACTIVE_DESC:                    qsTr("The ULS has not become inactive after Trigger or Pretrigger has been reached.")
    property string qmlALARM_HW_ULS_NONACTIVE_DESC:                 qsTr("The ULS is not active after an Estop or qmlALARM.")
    property string qmlALARM_HW_GD_BEFORE_TRIGGER_DESC:             qsTr("The Ground Detect Input has become active before Trigger occurred.")
    property string qmlALARM_HW_START_SWITCH_LOST_DESC:             qsTr("The Start Switches became inactive before Trigger occurred.")
    property string qmlALARM_HW_ALARM_LOG_DESC:                     qsTr("ALARM Log Storage is Full.")
    property string qmlALARM_HW_EVENT_LOG_DESC:                     qsTr("Event Log Storage is Full.")
    property string qmlALARM_HW_WELD_RESULT_DESC:                   qsTr("Weld Result Storage is Full.")
    property string qmlALARM_HW_WELD_GRAPH_DESC:                    qsTr("Weld Graph Storage is Full.")
    property string qmlALARM_HW_HORN_SCAN_DESC:                     qsTr("Horn Scan Graph Storage is Full.")
    property string qmlALARM_HW_PRETRIGGER_TIMEOUT_DESC:            qsTr("Pre-trigger has not occurred within 10 seconds of ULS going inactive.")
    property string qmlALARM_HW_ENCODER_FAIL_DESC:                  qsTr("No distance after part contact is made.")
    property string qmlALARM_HW_DATA_ERROR_DESC:                    qsTr("Corrupted data in the Recipe checked at power up.")
    property string qmlALARM_HW_HOME_RETURN_TIMEOUT_DESC:           qsTr("The carriage has not returned home in 4 seconds.")
    property string qmlALARM_HW_ACTUATOR_NOVARM_DESC:               qsTr("The actuator Novram has corrupted data. This is checked at power up.")
    property string qmlALARM_HW_PS_NOVARM_DESC:                     qsTr("The power supply Novram has corrupted data. This is checked at power up.")
    property string qmlALARM_HW_START_SWITCH_TIME_DESC:             qsTr("Both Start Switches were not pressed within the allowed time frame.")
    property string qmlALARM_HW_MEM_FULL_DESC:                      qsTr("Internal Storage Device is full. Any operation which requires Data Storage will not be allowed.")
    property string qmlALARM_HW_INTERNAL_STORAGE_FAIL_DESC:			qsTr("Contact Branson Service for Assistance.")
    property string qmlALARM_HW_RECALIBRATE_ACT_DESC:               qsTr("The force calibration values loaded into the system are invalid.")
    property string qmlALARM_HW_ACT_CLR_FUN_DESC:                   qsTr("ULS is active before actuator clear condition was met.")
    property string qmlALARM_HW_EXTRA_TOOLING_ACTIVE_DESC:          qsTr("The External Tooling Input has not become inactive for more than 4 seconds after the end of a cycle.")
    property string qmlALARM_HW_ACT_TYPE_CHANGED_DESC:              qsTr("The actuator type detected at power up is different from power down or after an ESTOP.")
    property string qmlALARM_HW_SYS_PRESSURE_INCORRECT_DESC:        qsTr("The set air pressure is not achieved.")
    property string qmlALARM_HW_SYS_PART_PRESENT_ACTIVE_DESC:       qsTr("The Part Present Input is configured and is still active for more than 4 seconds after the end of a cycle.")
    property string qmlALARM_HW_USB_MEM_LOST_DESC:                  qsTr("The USB memory stick has been removed or it not functional. Since weld data was configured to be saved on the USB stick welding must be stopped until either the USB stick is functional or weld data is no longer required to be saved.")
    property string qmlALARM_INTERNAL_COMM_FAIL:                    qsTr("Communication between the HMI and the welder has been disconnected.")
    property string qmlALARM_HW_ETH_LINK_LOST_DESC:                 qsTr("The Ethernet link has been lost between the Supervisor, actuator, and power supply modules.")
    property string qmlALARM_HW_CABLE_FAIL_DESC:                    qsTr("If Cable Detect is configured and the pin goes inactive.")
    property string qmlALARM_HW_PROFINET_OR_IP_NOT_DESC:            qsTr("No Description available.")
    property string qmlALARM_HW_AC_LINE_LOST_DESC:                  qsTr("230V input to the Power Supply is not ON.")
    property string qmlALARM_HW_TRIGGER_ACTIVE_READY_DESC:          qsTr("Trigger force is detected in the Ready State.")
    property string qmlALARM_HW_INTERNAL_COMM_FAIL_DESC:            qsTr("Internal Communication failure. Contact Branson Service.")
    property string qmlALARM_HW_SC_COMPONENT_FAIL_DESC:             qsTr("There is an internal failure. Contact Branson Service")
    property string qmlALARM_HW_RTC_LOW_BATT_DESC:					qsTr("System time may not be reliable. Set system time.")

    /* Cycle modified alarm names */
    property string qmlALARM_CYCLE_GROUND_DETECT_ABORT:             qsTr("Ground Detect Abort")
    property string qmlALARM_CYCLE_MAXTIMEOUT:                      qsTr("Max Weld Time Exceeded")
    property string qmlALARM_CYCLE_NOFORCESTEP:                     qsTr("No Force Step")
    property string qmlALARM_CYCLE_TRIGGER_GREATER_ENDFORCE:        qsTr("Trigger Force greater than End Force")
    property string qmlALARM_CYCLE_LL_NOT_REACHED:                  qsTr("LL Not reached")
    property string qmlALARM_CYCLE_PEAKPOWER_CUTOFF:                qsTr("Peak Power Cutoff")
    property string qmlALARM_CYCLE_ABSOLUTE_CUTOFF:                 qsTr("Absolute Distance Cutoff")
    property string qmlALARM_CYCLE_COLLAPSE_CUTOFF:                 qsTr("Collapse Distance Cutoff")
    property string qmlALARM_CYCLE_ULTRASONICS_DISABLED:            qsTr("Ultrasonics disabled")
    property string qmlALARM_CYCLE_CUSTOM1_CUTOFF:                  qsTr("Custom Input 1 Cutoff")
    property string qmlALARM_CYCLE_CUSTOM2_CUTOFF:                  qsTr("Custom Input 2 Cutoff")
    property string qmlALARM_CYCLE_FREQLOW_CUTOFF:                  qsTr("Frequency Low Cutoff")
    property string qmlALARM_CYCLE_FREQHIGH_CUTOFF:                 qsTr("Frequency High Cutoff")
    property string qmlALARM_CYCLE_CUST_DIGITAL_CUTOFF:             qsTr("Custom Digital Cutoff")
    property string qmlALARM_CYCLE_ENERGY_CUTOFF:                   qsTr("Energy Cutoff")
    property string qmlALARM_CYCLE_GD_CUTOFF:                       qsTr("Ground Detect Cutoff")
    property string qmlALARM_CYCLE_TIME_CUTOFF:                     qsTr("Time Cutoff")
    property string qmlALARM_CYCLE_NO_PRESSURE_STEP:                qsTr("No Pressure Step")

    /* Cycle modified alarm descriptions */
    property string qmlALARM_CYCLE_GROUND_DETECT_ABORT_DESC:        qsTr("The Ground Detect Input has become active and the Cycle has been aborted.")
    property string qmlALARM_CYCLE_MAXTIMEOUT_DESC:                 qsTr("The maximum time allowed for Ultrasonic energy to be applied to the part has been reached.")
    property string qmlALARM_CYCLE_NOFORCESTEP_DESC:                qsTr("The force step trigger was not reached.")
    property string qmlALARM_CYCLE_NO_PRESSURE_STEP_DESC:           qsTr("The pressure step trigger was not reached.") // Not in E1
    property string qmlALARM_CYCLE_TRIGGER_GREATER_ENDFORCE_DESC:	qsTr("The force at the end of the cycle was greater than the trigger force.") // Not in E1
    property string qmlALARM_CYCLE_LL_NOT_REACHED_ID_DESC:			qsTr("No Description available")	// Not in E1
    property string qmlALARM_CYCLE_PEAKPOWER_CUTOFF_DESC:			qsTr("The Peak Power Cutoff value has been exceeded during the weld.")
    property string qmlALARM_CYCLE_ABSOLUTE_CUTOFF_DESC:			qsTr("The Absolute Distance Cutoff value has been exceeded during the weld.")
    property string qmlALARM_CYCLE_COLLAPSE_CUTOFF_DESC:			qsTr("The Collapse Distance Cutoff value has been exceeded during the weld.")
    property string qmlALARM_CYCLE_ULTRASONICS_DISABLED_DESC:		qsTr("The Ultrasonics Disable user input has been enabled during this cycle.")
    property string qmlALARM_CYCLE_CUSTOM1_CUTOFF_DESC:				qsTr("No Description available")	// Not in E1
    property string qmlALARM_CYCLE_CUSTOM2_CUTOFF_DESC:				qsTr("No Description available") 	// Not in E1
    property string qmlALARM_CYCLE_FREQLOW_CUTOFF_DESC:				qsTr("The Frequency Low Cutoff value has been exceeded during the weld.")
    property string qmlALARM_CYCLE_FREQHIGH_CUTOFF_DESC:			qsTr("The Frequency High Cutoff value has been exceeded during the weld.")
    property string qmlALARM_CYCLE_CUST_DIGITAL_CUTOFF_DESC:		qsTr("No Description available") // Not in E1
    property string qmlALARM_CYCLE_ENERGY_CUTOFF_DESC:				qsTr("The Energy Cutoff value has been exceeded during the weld.")
    property string qmlALARM_CYCLE_GD_CUTOFF_DESC:					qsTr("The Ground Detect Cutoff has triggered during the weld.")
    property string qmlALARM_CYCLE_TIME_CUTOFF_DESC:				qsTr("The Time Cutoff value has been exceeded during the weld.")

    /* Suspect Alarms */
    property string qmlALARM_SUSPECT_ENERGY_LIMIT:                  qsTr("Energy Suspect Limit")
    property string qmlALARM_SUSPECT_POWER_LIMIT:                   qsTr("Peak Power Suspect Limit")
    property string qmlALARM_SUSPECT_COLLAPSE_LIMIT:                qsTr("Collapse Distance Suspect Limit")
    property string qmlALARM_SUSPECT_ABSOLUTE_LIMIT:                qsTr("Absolute Distance Suspect limit")
    property string qmlALARM_SUSPECT_TRIGGER_LIMIT:                 qsTr("Trigger Distance Suspect Limit")
    property string qmlALARM_SUSPECT_WELD_FORCE_LIMIT:              qsTr("Weld Force Suspect  Limit")
    property string qmlALARM_SUSPECT_TIME_LIMIT:                    qsTr("Time Suspect Limit")
    property string qmlALARM_SUSPECT_VELOCITY_LIMITS:               qsTr("Velocity Suspect Limit")
    property string qmlALARM_SUSPECT_FREQ_LIMITS:                   qsTr("Frequency Suspect Limit")

    property string qmlALARM_LOW_ENERGY_LIMIT_DESC:                 qsTr("The total Weld Energy did not exceed the lower limit value")
    property string qmlALARM_HIGH_ENERGY_LIMIT_DESC:                qsTr("The total Weld Energy exceeded the upper limit value")
    property string qmlALARM_LOW_POWER_LIMIT_DESC:                  qsTr("The Peak Power did not exceed the lower limit value")
    property string qmlALARM_HIGH_POWER_LIMIT_DESC:                 qsTr("The Peak Power exceeded the upper limit value")
    property string qmlALARM_LOW_COLLAPSE_LIMIT_DESC:               qsTr("The total Collapse Distance did not exceed the lower limit value")
    property string qmlALARM_HIGH_COLLAPSE_LIMIT_DESC:              qsTr("The total Collapse Distance exceeded the upper limit value")
    property string qmlALARM_LOW_ABSOLUTE_LIMIT_DESC:               qsTr("The total Absolute Distance did not exceed the lower limit value")
    property string qmlALARM_HIGH_ABSOLUTE_LIMIT_DESC:              qsTr("The total Absolute Distance exceeded the upper limit value")
    property string qmlALARM_LOW_TRIGGER_LIMIT_DESC:                qsTr("The Trigger Distance did not exceed the lower limit value")
    property string qmlALARM_HIGH_TRIGGER_LIMIT_DESC:               qsTr("The Trigger Distance exceeded the upper limit value")
    property string qmlALARM_LOW_WELD_FORCE_LIMIT_DESC:             qsTr("The total Weld Force did not exceed the lower limit value")
    property string qmlALARM_HIGH_WELD_FORCE_LIMIT_DESC:            qsTr("The total Weld Force exceeded the upper limit value")
    property string qmlALARM_LOW_TIME_LIMIT_DESC:                   qsTr("The total Weld Time did not exceed the lower limit value")
    property string qmlALARM_HIGH_TIME_LIMIT_DESC:                  qsTr("The total Weld Time exceeded the upper limit value")
    property string qmlALARM_LOW_VELOCITY_LIMITS_DESC:              qsTr("The Weld Velocity did not exceed the lower limit value")
    property string qmlALARM_HIGH_VELOCITY_LIMITS_DESC:             qsTr("The Weld Velocity exceeded the upper limit value")
    property string qmlALARM_LOW_FREQ_LIMITS_DESC:                  qsTr("The Weld Frequency did not exceed the lower limit value")
    property string qmlALARM_HIGH_FREQ_LIMITS_DESC:                 qsTr("The Weld Velocity exceeded the upper limit value")

    /* Reject Alarms */
    property string qmlALARM_REJECT_ENERGY_LIMIT:                   qsTr("Energy Reject Limit")
    property string qmlALARM_REJECT_POWER_LIMIT:                    qsTr("Peak Power Reject Limit")
    property string qmlALARM_REJECT_COLLAPSE_LIMIT:                 qsTr("Collapse Distance Reject Limit")
    property string qmlALARM_REJECT_ABSOLUTE_LIMIT:                 qsTr("Absolute Distance Reject limit")
    property string qmlALARM_REJECT_TRIGGER_LIMIT:                  qsTr("Trigger Reject Limit")
    property string qmlALARM_REJECT_WELD_FORCE_LIMIT:               qsTr("Weld Force Reject Limit")
    property string qmlALARM_REJECT_TIME_LIMIT:                     qsTr("Time Reject Limit")
    property string qmlALARM_REJECT_VELOCITY_LIMITS:                qsTr("Velocity Reject Limit")
    property string qmlALARM_REJECT_FREQ_LIMITS:                    qsTr("Frequency Reject Limit")

    property string qmlALARM_POWER_MATCH_CURVE_LIMITS:				qsTr("Power Match Curve Limits")

    /* Warnings */
    property string qmlALARM_WARNING_TRIGGERLOST:                   qsTr("Trigger Force lost in Weld")
    property string qmlALARM_WARNING_ACTUATOR_CLR_NOT_RCHD:         qsTr("Actuator clear not reached")
    property string qmlALARM_WARNING_ACTU_RECAL:                    qsTr("Actuator Recal suggested")
    property string qmlALARM_WARNING_USBMEMORY:                     qsTr("USB Memory Nearly Full(80%)")
    property string qmlALARM_WARNING_DISK_MEMORY:                   qsTr("Internal Storage Capacity Warning")
    property string qmlALARM_WARNING_ALARM_LOG:                     qsTr("Alarm Log Capacity Warning")
    property string qmlALARM_WARNING_EVENT_LOG:                     qsTr("Event Log Capacity Warning")
    property string qmlALARM_WARNING_WELD_RESULT:                   qsTr("Weld Result Capacity Warning")
    property string qmlALARM_WARNING_WELD_GRAPH:                    qsTr("Weld Graph Capacity Warning")
    property string qmlALARM_WARNING_HORN_SCAN:                     qsTr("Horn Scan Graph Capacity Warning")
    property string qmlALARM_WARNING_EEPROM_CORRUPT:                qsTr("Possible Data Error")

    property string qmlALARM_WARNING_TRIGGERLOST_DESC:              qsTr("The applied Force dropped below the minimum Trigger Force during the Cycle.")
    property string qmlALARM_WARNING_DISK_MEMORY_DESC:              qsTr("Internal Storage is greater than 80% Full. Please consider extracting data to USB to avoid loss of data.")
    property string qmlALARM_WARNING_ALARM_LOG_DESC:                qsTr("Alarm Log Storage is greater than 80% Full.")
    property string qmlALARM_WARNING_EVENT_LOG_DESC:                qsTr("Event Log Storage is greater than 80% Full.")
    property string qmlALARM_WARNING_WELD_RESULT_DESC:              qsTr("Weld Result Storage is greater than 80% Full.")
    property string qmlALARM_WARNING_WELD_GRAPH_DESC:               qsTr("Weld Graph Storage is greater than 80% Full.")
    property string qmlALARM_WARNING_HORN_SCAN_DESC:                qsTr("Horn Scan Graph Storage is greater than 80% Full.")
    property string qmlALARM_WARNING_EEPROM_CORRUPT_DESC:			qsTr("System Configuration potentially incorrect. Double check the System Information")

    /* Overloads */
    property string qmlALARM_PHASE_OVERLOAD:						qsTr("Phase Overload")
    property string qmlALARM_CURR_OVERLOAD:							qsTr("Current Overload")
    property string qmlALARM_FREQ_OVERLOAD:							qsTr("Frequency Overload")
    property string qmlALARM_POWER_OVERLOAD:						qsTr("Power Overload")
    property string qmlALARM_VOLT_OVERLOAD:							qsTr("Voltage Overload")
    property string qmlALARM_TEMP_OVERLOAD:							qsTr("Temperature Overload")

    property string qmlALARM_PHASE_OVERLOAD_DESC:					qsTr("Phase Overload occurred during the weld")
    property string qmlALARM_CURR_OVERLOAD_DESC:					qsTr("Current Overload occurred during the weld")
    property string qmlALARM_FREQ_OVERLOAD_DESC:					qsTr("Frequency Overload occurred during the weld")
    property string qmlALARM_POWER_OVERLOAD_DESC:					qsTr("Power Overload occurred during the weld")
    property string qmlALARM_VOLT_OVERLOAD_DESC:					qsTr("Voltage Overload occurred during the weld")
    property string qmlALARM_TEMP_OVERLOAD_DESC:					qsTr("Temperature Overload occurred during the weld")
    property string qmlALARM_EB_PHASE_OVERLOAD_DESC:				qsTr("Phase Overload occurred during Energy Braking")
    property string qmlALARM_EB_CURR_OVERLOAD_DESC:					qsTr("Current Overload occurred during Energy Braking")
    property string qmlALARM_EB_FREQ_OVERLOAD_DESC:					qsTr("Frequency Overload occurred during Energy Braking")
    property string qmlALARM_EB_POWER_OVERLOAD_DESC:				qsTr("Power Overload occurred during Energy Braking")
    property string qmlALARM_EB_VOLT_OVERLOAD_DESC:					qsTr("Voltage Overload occurred during Energy Braking")
    property string qmlALARM_EB_TEMP_OVERLOAD_DESC:					qsTr("Temperature Overload occurred during Energy Braking")
    property string qmlALARM_AB_PHASE_OVERLOAD_DESC:				qsTr("Phase Overload occurred during Afterburst")
    property string qmlALARM_AB_CURR_OVERLOAD_DESC:					qsTr("Current Overload occurred during Afterburst")
    property string qmlALARM_AB_FREQ_OVERLOAD_DESC:					qsTr("Frequency Overload occurred during Afterburst")
    property string qmlALARM_AB_POWER_OVERLOAD_DESC:				qsTr("Power Overload occurred during Afterburst")
    property string qmlALARM_AB_VOLT_OVERLOAD_DESC:					qsTr("Voltage Overload occurred during Afterburst")
    property string qmlALARM_AB_TEMP_OVERLOAD_DESC:					qsTr("Temperature Overload occurred during Afterburst")
    property string qmlALARM_PRETRIG_PHASE_OVERLOAD_DESC:			qsTr("Phase Overload occurred during Pretrigger")
    property string qmlALARM_PRETRIG_CURR_OVERLOAD_DESC:			qsTr("Current Overload occurred during Pretrigger")
    property string qmlALARM_PRETRIG_FREQ_OVERLOAD_DESC:			qsTr("Frequency Overload occurred during Pretrigger")
    property string qmlALARM_PRETRIG_POWER_OVERLOAD_DESC:			qsTr("Power Overload occurred during Pretrigger")
    property string qmlALARM_PRETRIG_VOLT_OVERLOAD_DESC:			qsTr("Voltage Overload occurred during Pretrigger")
    property string qmlALARM_PRETRIG_TEMP_OVERLOAD_DESC:			qsTr("Temperature Overload occurred during Pretrigger")
    property string qmlALARM_PRE_SEEK_PHASE_OVERLOAD_DESC:			qsTr("Phase Overload occurred during Pre Weld Seek")
    property string qmlALARM_PRE_SEEK_CURR_OVERLOAD_DESC:			qsTr("Current Overload occurred during Pre Weld Seek")
    property string qmlALARM_PRE_SEEK_FREQ_OVERLOAD_DESC:			qsTr("Frequency Overload occurred during Pre Weld Seek")
    property string qmlALARM_PRE_SEEK_POWER_OVERLOAD_DESC:			qsTr("Power Overload occurred during Pre Weld Seek")
    property string qmlALARM_PRE_SEEK_VOLT_OVERLOAD_DESC:			qsTr("Voltage Overload occurred during Pre Weld Seek")
    property string qmlALARM_PRE_SEEK_TEMP_OVERLOAD_DESC:			qsTr("Temperature Overload occurred during Pre Weld Seek")
    property string qmlALARM_POST_SEEK_PHASE_OVERLOAD_DESC:			qsTr("Phase Overload occurred during Post Weld Seek")
    property string qmlALARM_POST_SEEK_CURR_OVERLOAD_DESC:			qsTr("Current Overload occurred during Post Weld Seek")
    property string qmlALARM_POST_SEEK_FREQ_OVERLOAD_DESC:			qsTr("Frequency Overload occurred during Post Weld Seek")
    property string qmlALARM_POST_SEEK_POWER_OVERLOAD_DESC:			qsTr("Power Overload occurred during Post Weld Seek")
    property string qmlALARM_POST_SEEK_VOLT_OVERLOAD_DESC:			qsTr("Voltage Overload occurred during Post Weld Seek")
    property string qmlALARM_POST_SEEK_TEMP_OVERLOAD_DESC:			qsTr("Temperature Overload occurred during Post Weld Seek")
    property string qmlALARM_SEEK_PHASE_OVERLOAD_DESC:				qsTr("Phase Overload occurred during Seek")
    property string qmlALARM_SEEK_CURR_OVERLOAD_DESC:				qsTr("Current Overload occurred during Seek")
    property string qmlALARM_SEEK_FREQ_OVERLOAD_DESC:				qsTr("Frequency Overload occurred during Seek")
    property string qmlALARM_SEEK_POWER_OVERLOAD_DESC:				qsTr("Power Overload occurred during Seek")
    property string qmlALARM_SEEK_VOLT_OVERLOAD_DESC:				qsTr("Voltage Overload occurred during Seek")
    property string qmlALARM_SEEK_TEMP_OVERLOAD_DESC:				qsTr("Temperature Overload occurred during Seek")
    property string qmlALARM_TEST_PHASE_OVERLOAD_DESC:				qsTr("Phase Overload occurred during Test")
    property string qmlALARM_TEST_CURR_OVERLOAD_DESC:				qsTr("Current Overload occurred during Test")
    property string qmlALARM_TEST_FREQ_OVERLOAD_DESC:				qsTr("Frequency Overload occurred during Test")
    property string qmlALARM_TEST_POWER_OVERLOAD_DESC:				qsTr("Power Overload occurred during Test")
    property string qmlALARM_TEST_VOLT_OVERLOAD_DESC:				qsTr("Voltage Overload occurred during Test")
    property string qmlALARM_TEST_TEMP_OVERLOAD_DESC:				qsTr("Temperature Overload occurred during Test")

    /*  No Cycle Overloads - Overloads that happen before trigger or outside the weld cycle */
    property string qmlALARM_SEEK_OVERLOAD:                         qsTr("Seek Overload")
    property string qmlALARM_TEST_OVERLOAD:                         qsTr("Test Overload")
    property string qmlALARM_PRETRIGGER_OVERLOAD:                   qsTr("Pretrigger Overload")
    property string qmlALARM_PREWELDSEEK_OVERLOAD:                  qsTr("Pre-Weld Seek")
    property string qmlALARM_THERMAL_OVERLOAD:                      qsTr("Thermal Overload")
    property string qmlALARM_THERMAL_OVERLOAD_DESC:                 qsTr("Power supply temperature above the maximum operating temperature.")

    /* EN Faults */
    property string qmlALARM_MULTIPLE_FAULTS:                       qsTr("Multiple Faults")
    property string qmlALARM_MULTIPLE_FAULTS_DESC:                  qsTr("Start Switches activated when system not Ready")
    property string qmlALARM_PALM_BUTTON_FAULT:                     qsTr("Palm Button Fault")
    property string qmlALARM_24V_FAULT:                             qsTr("24V Fault")
    property string qmlALARM_ESTOP_FAULT:                           qsTr("E-Stop Fault")
    property string qmlALARM_LINEAR_ENCODER_FAULT:                  qsTr("Linear Encoder Fault")
    property string qmlALARM_LINEAR_ENCODER_FAULT_DESC:             qsTr("No Description available")
    property string qmlALARM_S_BEAM_FAULT:                          qsTr("S-Beam Fault")
    property string qmlALARM_TRIGGER_SWITCH_FAULT:                  qsTr("Trigger Switch Fault")
    property string qmlALARM_DRIVE_FAULT:                           qsTr("Drive Fault")
    property string qmlALARM_CROSS_MONITORING_FAULT:                qsTr("Cross Monitoring Fault")
    property string qmlALARM_LOGIC_FAULT:                           qsTr("Logic Unit Fault ")
    property string qmlALARM_SONICS_ENABLE_FAULT:                   qsTr("Sonics Enable Fault")

    // As per the TOM's comment in the Bug:2676, Unknown alarm should be replaced with empty
    property string qmlALARM_UNKNOW_ALARM:                          qsTr("")
    property string qmlALARM_NO_DESC:                               qsTr("No Description available")

    property string qmlNOT_AVAIABLE:                                qsTr("NA")

    function updateLanguage()
    {
        qmltextAlarm = languageConfig.getLanguageMenuName(UIScreenEnum.ALARM, qmltextAlarm)
        qmlGeneralTextArray = languageConfig.getLanguageStringList(UIScreenEnum.ALARM_GENERAL, qmlGeneralTextArray)
        qmltextErrorDescriptionTitle = qmlGeneralTextArray[textGeneralEnum.textErrorDescriptionIdx]
        qmltextReset = qmlGeneralTextArray[textGeneralEnum.textResetIdx]
        qmltextHide = qmlGeneralTextArray[textGeneralEnum.textHideIdx]
    }

    function isCriticalAlarm(alarmId)
    {
        return false
    }

    function getAlarmDescription(alarmId)
    {
        var strAlarmDesc = qmlALARM_UNKNOW_ALARM
        switch(alarmId)
        {
            case AlarmIndexEnum.ALARM_NOCYCLE_EXTERNAL_SONIC_DESC:
                strAlarmDesc = qmlALARM_NOCYCLE_EXTERNAL_SONIC_DESC
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_MISSING_PART_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_MISSING_PART_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_PART_CONTACT_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_PART_CONTACT_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_EXTERNAL_CYCLE_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_EXTERNAL_CYCLE_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_ABSOLUTE_DISTANCE_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_ABSOLUTE_DISTANCE_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_EXTRA_TOOLING_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_EXTRA_TOOLING_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_EXTRA_TIMEOUT_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_EXTRA_TIMEOUT_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_PART_PRESENT_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_PART_PRESENT_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_SERVO_MOTOR_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_SERVO_MOTOR_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_READY_POS_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_READY_POS_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_RECIPE_NOTVALID_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_RECIPE_NOTVALID_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_BATCH_COUNT_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_BATCH_COUNT_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_ACTIVERECIPE_NOTVALID_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_ACTIVERECIPE_NOTVALID_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_PC_ASS_MISMATCH_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_PC_ASS_MISMATCH_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_AC_ASS_MISMATCH_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_AC_ASS_MISMATCH_DESC;
                break;
            case AlarmIndexEnum.ALARM_NOCYCLE_STACK_ASS_MISMATCH_ID:
                strAlarmDesc = qmlALARM_NOCYCLE_STACK_ASS_MISMATCH_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_START_SWITCH_FAIL_ID:
                strAlarmDesc = qmlALARM_HW_START_SWITCH_FAIL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ULS_ACTIVE_ID:
                strAlarmDesc = qmlALARM_HW_ULS_ACTIVE_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ULS_NONACTIVE_ID:
                strAlarmDesc = qmlALARM_HW_ULS_NONACTIVE_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_GD_BEFORE_TRIGGER_ID:
                strAlarmDesc = qmlALARM_HW_GD_BEFORE_TRIGGER_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_START_SWITCH_LOST_ID:
                strAlarmDesc = qmlALARM_HW_START_SWITCH_LOST_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ALARM_LOG_ID:
                strAlarmDesc = qmlALARM_HW_ALARM_LOG_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_EVENT_LOG_ID:
                strAlarmDesc = qmlALARM_HW_EVENT_LOG_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_WELD_RESULT_ID:
                strAlarmDesc = qmlALARM_HW_WELD_RESULT_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_WELD_GRAPH_ID:
                strAlarmDesc = qmlALARM_HW_WELD_GRAPH_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_HORN_SCAN_ID:
                strAlarmDesc = qmlALARM_HW_HORN_SCAN_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_PRETRIGGER_TIMEOUT_ID:
                strAlarmDesc = qmlALARM_HW_PRETRIGGER_TIMEOUT_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ENCODER_FAIL_ID:
                strAlarmDesc = qmlALARM_HW_ENCODER_FAIL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_DATA_ERROR_ID:
                strAlarmDesc = qmlALARM_HW_DATA_ERROR_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_HOME_RETURN_TIMEOUT_ID:
                strAlarmDesc = qmlALARM_HW_HOME_RETURN_TIMEOUT_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ACTUATOR_NOVARM_ID:
                strAlarmDesc = qmlALARM_HW_ACTUATOR_NOVARM_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_PS_NOVARM_ID:
                strAlarmDesc = qmlALARM_HW_PS_NOVARM_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_START_SWITCH_TIME_ID:
                strAlarmDesc = qmlALARM_HW_START_SWITCH_TIME_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_MEM_FULL_ID:
                strAlarmDesc = qmlALARM_HW_MEM_FULL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_INTERNAL_STORAGE_FAIL_ID:
                strAlarmDesc = qmlALARM_HW_INTERNAL_STORAGE_FAIL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_RECALIBRATE_ACT_ID:
                strAlarmDesc = qmlALARM_HW_RECALIBRATE_ACT_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ACT_CLR_FUN_ID:
                strAlarmDesc = qmlALARM_HW_ACT_CLR_FUN_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_EXTRA_TOOLING_ACTIVE_ID:
                strAlarmDesc = qmlALARM_HW_EXTRA_TOOLING_ACTIVE_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_ACT_TYPE_CHANGED_ID:
                strAlarmDesc = qmlALARM_HW_ACT_TYPE_CHANGED_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_SYS_PRESSURE_INCORRECT_ID:
                strAlarmDesc = qmlALARM_HW_SYS_PRESSURE_INCORRECT_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_SYS_PART_PRESENT_ACTIVE_ID:
                strAlarmDesc = qmlALARM_HW_SYS_PART_PRESENT_ACTIVE_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_USB_MEM_LOST_ID:
                strAlarmDesc = qmlALARM_HW_USB_MEM_LOST_DESC;
                break;
            case AlarmIndexEnum.ALARM_INTERNAL_COMM_ENET:
                strAlarmDesc = qmlALARM_INTERNAL_COMM_FAIL;
                break;
            case AlarmIndexEnum.ALARM_HW_ETH_LINK_LOST_ID:
                strAlarmDesc = qmlALARM_HW_ETH_LINK_LOST_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_CABLE_FAIL_ID:
                strAlarmDesc = qmlALARM_HW_CABLE_FAIL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_PROFINET_OR_IP_NOT_ID:
                strAlarmDesc = qmlALARM_HW_PROFINET_OR_IP_NOT_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_AC_LINE_LOST_ID:
                strAlarmDesc = qmlALARM_HW_AC_LINE_LOST_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_TRIGGER_ACTIVE_READY_ID:
                strAlarmDesc = qmlALARM_HW_TRIGGER_ACTIVE_READY_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_INTERNAL_COMM_FAIL_ID:
                strAlarmDesc = qmlALARM_HW_INTERNAL_COMM_FAIL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_SC_COMPONENT_FAIL_ID:
                strAlarmDesc = qmlALARM_HW_SC_COMPONENT_FAIL_DESC;
                break;
            case AlarmIndexEnum.ALARM_HW_RTC_LOW_BATT_ID:
                strAlarmDesc = qmlALARM_HW_RTC_LOW_BATT_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_GROUND_DETECT_ABORT_ID:
                strAlarmDesc = qmlALARM_CYCLE_GROUND_DETECT_ABORT_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_MAXTIMEOUT_ID:
                strAlarmDesc = qmlALARM_CYCLE_MAXTIMEOUT_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_NOFORCESTEP_ID:
                strAlarmDesc = qmlALARM_CYCLE_NOFORCESTEP_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_TRIGGER_GREATER_ENDFORCE_ID:
                strAlarmDesc = qmlALARM_CYCLE_TRIGGER_GREATER_ENDFORCE_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_LL_NOT_REACHED_ID:	// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_PEAKPOWER_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_PEAKPOWER_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_ABSOLUTE_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_ABSOLUTE_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_COLLAPSE_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_COLLAPSE_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_ULTRASONICS_DISABLED_ID:
                strAlarmDesc = qmlALARM_CYCLE_ULTRASONICS_DISABLED_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_CUSTOM1_CUTOFF_ID:	// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_CUSTOM2_CUTOFF_ID: // Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_FREQLOW_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_FREQLOW_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_FREQHIGH_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_FREQHIGH_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_CUST_DIGITAL_CUTOFF_ID:	// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_ENERGY_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_ENERGY_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_GD_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_GD_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_TIME_CUTOFF_ID:
                strAlarmDesc = qmlALARM_CYCLE_TIME_CUTOFF_DESC;
                break;
            case AlarmIndexEnum.ALARM_CYCLE_NO_PRESSURE_STEP_ID:		// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_ENERGY_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_ENERGY_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_ENERGY_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_ENERGY_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_POWER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_POWER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_COLLAPSE_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_COLLAPSE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_COLLAPSE_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_COLLAPSE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_ABSOLUTE_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_ABSOLUTE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_ABSOLUTE_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_ABSOLUTE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TRIGGER_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_TRIGGER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TRIGGER_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_TRIGGER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_WELD_FORCE_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_WELD_FORCE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_WELD_FORCE_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_WELD_FORCE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TIME_SLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_TIME_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TIME_SHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_TIME_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_VELOCITY_SLLIMITS_ID:
                strAlarmDesc = qmlALARM_LOW_VELOCITY_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_VELOCITY_SHLIMITS_ID:
                strAlarmDesc = qmlALARM_HIGH_VELOCITY_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_FREQ_SLLIMITS_ID:
                strAlarmDesc = qmlALARM_LOW_FREQ_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_FREQ_SHLIMITS_ID:
                strAlarmDesc = qmlALARM_HIGH_FREQ_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_ENERGY_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_ENERGY_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_ENERGY_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_ENERGY_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_POWER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_POWER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_COLLAPSE_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_COLLAPSE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_COLLAPSE_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_COLLAPSE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_ABSOLUTE_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_ABSOLUTE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_ABSOLUTE_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_ABSOLUTE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TRIGGER_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_TRIGGER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TRIGGER_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_TRIGGER_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_WELD_FORCE_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_WELD_FORCE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_WELD_FORCE_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_WELD_FORCE_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TIME_RLLIMIT_ID:
                strAlarmDesc = qmlALARM_LOW_TIME_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_TIME_RHLIMIT_ID:
                strAlarmDesc = qmlALARM_HIGH_TIME_LIMIT_DESC;
                break;
            case AlarmIndexEnum.ALARM_VELOCITY_RLLIMITS_ID:
                strAlarmDesc = qmlALARM_LOW_VELOCITY_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_VELOCITY_RHLIMITS_ID:
                strAlarmDesc = qmlALARM_HIGH_VELOCITY_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_FREQ_RLLIMITS_ID:
                strAlarmDesc = qmlALARM_LOW_FREQ_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_FREQ_RHLIMITS_ID:
                strAlarmDesc = qmlALARM_HIGH_FREQ_LIMITS_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_MATCH_CURVE_RLLIMITS_ID:	// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_MATCH_CURVE_RHLIMITS_ID:	// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;    //** Reject
                break;
            case AlarmIndexEnum.ALARM_WARNING_TRIGGERLOST_ID:
                strAlarmDesc = qmlALARM_WARNING_TRIGGERLOST_DESC;
                break;
            case AlarmIndexEnum.ALARM_WARNING_ACTUATOR_CLR_NOT_RCHD_ID:	// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_WARNING_ACTU_RECAL_ID:			// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_WARNING_USBMEMORY_ID:			// Not in E1
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_WARNING_DISK_MEMORY_ID:
                strAlarmDesc = qmlALARM_WARNING_DISK_MEMORY_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_WARNING_ALARM_LOG_ID:
                strAlarmDesc = qmlALARM_WARNING_ALARM_LOG_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_WARNING_EVENT_LOG_ID:
                strAlarmDesc = qmlALARM_WARNING_EVENT_LOG_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_WARNING_WELD_RESULT_ID:
                strAlarmDesc = qmlALARM_WARNING_WELD_RESULT_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_WARNING_WELD_GRAPH_ID:
                strAlarmDesc = qmlALARM_WARNING_WELD_GRAPH_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_WARNING_HORN_SCAN_ID:
                strAlarmDesc = qmlALARM_WARNING_HORN_SCAN_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_WARNING_EEPROM_CORRUPT_ID:
                strAlarmDesc = qmlALARM_WARNING_EEPROM_CORRUPT_DESC; //**warning
                break;
            case AlarmIndexEnum.ALARM_PHASE_OVERLOAD_ID:					//** Overloads
                strAlarmDesc = qmlALARM_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_CURR_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_FREQ_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POWER_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_VOLT_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEMP_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_EB_PHASE_OVERLOAD_ID:					//** Energy Brake Overloads
                strAlarmDesc = qmlALARM_EB_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_EB_CURR_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_EB_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_EB_FREQ_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_EB_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_EB_POWER_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_EB_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_EB_VOLT_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_EB_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_EB_TEMP_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_EB_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_AB_PHASE_OVERLOAD_ID:					//** Afterburst Overloads
                strAlarmDesc = qmlALARM_AB_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_AB_CURR_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_AB_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_AB_FREQ_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_AB_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_AB_POWER_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_AB_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_AB_VOLT_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_AB_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_AB_TEMP_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_AB_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POST_SEEK_PHASE_OVERLOAD_ID:					//** Post Weld Seek Overloads
                strAlarmDesc = qmlALARM_POST_SEEK_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POST_SEEK_CURR_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_POST_SEEK_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POST_SEEK_FREQ_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_POST_SEEK_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POST_SEEK_POWER_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_POST_SEEK_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POST_SEEK_VOLT_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_POST_SEEK_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_POST_SEEK_TEMP_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_POST_SEEK_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_PHASE_ID:					//** Seek Overloads
                strAlarmDesc = qmlALARM_SEEK_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_CURRENT_ID:
                strAlarmDesc = qmlALARM_SEEK_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_FREQUENCY_ID:
                strAlarmDesc = qmlALARM_SEEK_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_POWER_ID:
                strAlarmDesc = qmlALARM_SEEK_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_VOLTAGE_ID:
                strAlarmDesc = qmlALARM_SEEK_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_TEMPERATURE_ID:
                strAlarmDesc = qmlALARM_SEEK_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEST_OVERLOAD_PHASE_ID:					//** Test Overloads
                strAlarmDesc = qmlALARM_TEST_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEST_OVERLOAD_CURRENT_ID:
                strAlarmDesc = qmlALARM_TEST_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEST_OVERLOAD_FREQUENCY_ID:
                strAlarmDesc = qmlALARM_TEST_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEST_OVERLOAD_POWER_ID:
                strAlarmDesc = qmlALARM_TEST_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEST_OVERLOAD_VOLTAGE_ID:
                strAlarmDesc = qmlALARM_TEST_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_TEST_OVERLOAD_TEMPERATURE_ID:
                strAlarmDesc = qmlALARM_TEST_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_PHASE_ID:					//** Pretrigger Overloads
                strAlarmDesc = qmlALARM_PRETRIG_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_CURRENT_ID:
                strAlarmDesc = qmlALARM_PRETRIG_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_FREQUENCY_ID:
                strAlarmDesc = qmlALARM_PRETRIG_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_POWER_ID:
                strAlarmDesc = qmlALARM_PRETRIG_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_VOLTAGE_ID:
                strAlarmDesc = qmlALARM_PRETRIG_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_TEMPERATURE_ID:
                strAlarmDesc = qmlALARM_PRETRIG_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRE_SEEK_PHASE_OVERLOAD_ID:					//** Pre Weld Seek Overloads
                strAlarmDesc = qmlALARM_PRE_SEEK_PHASE_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRE_SEEK_CURR_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_PRE_SEEK_CURR_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRE_SEEK_FREQ_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_PRE_SEEK_FREQ_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRE_SEEK_POWER_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_PRE_SEEK_POWER_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRE_SEEK_VOLT_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_PRE_SEEK_VOLT_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_PRE_SEEK_TEMP_OVERLOAD_ID:
                strAlarmDesc = qmlALARM_PRE_SEEK_TEMP_OVERLOAD_DESC;
                break;
            case AlarmIndexEnum.ALARM_MULTIPLE_FAULTS_ID:
                strAlarmDesc = qmlALARM_MULTIPLE_FAULTS_DESC;
                break;
            case AlarmIndexEnum.ALARM_PALM_BUTTON_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_24V_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_ESTOP_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_LINEAR_ENCODER_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_S_BEAM_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_TRIGGER_SWITCH_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_DRIVE_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_CROSS_MONITORING_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_LOGIC_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            case AlarmIndexEnum.ALARM_SONICS_ENABLE_FAULT_ID:
                strAlarmDesc = qmlALARM_NO_DESC;
                break;
            default:
                strAlarmDesc = qmlALARM_UNKNOW_ALARM;
                break;
        }
        return strAlarmDesc
    }

    function getAlarmName(alarmId)
    {
        var strAlarmName = qmlALARM_UNKNOW_ALARM
        switch (alarmId)
        {
        case AlarmIndexEnum.ALARM_NOCYCLE_EXTERNAL_SONIC_ID:
            strAlarmName = qmlALARM_NOCYCLE_EXTERNAL_SONIC;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_MISSING_PART_ID:
            strAlarmName = qmlALARM_NOCYCLE_MISSING_PART;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_PART_CONTACT_ID:
            strAlarmName = qmlALARM_NOCYCLE_PART_CONTACT;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_EXTERNAL_CYCLE_ID:
            strAlarmName = qmlALARM_NOCYCLE_EXTERNAL_CYCLE;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_ABSOLUTE_DISTANCE_ID:
            strAlarmName = qmlALARM_NOCYCLE_ABSOLUTE_DISTANCE;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_EXTRA_TOOLING_ID:
            strAlarmName = qmlALARM_NOCYCLE_EXTRA_TOOLING;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_EXTRA_TIMEOUT_ID:
            strAlarmName = qmlALARM_NOCYCLE_EXTRA_TIMEOUT;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_PART_PRESENT_ID:
            strAlarmName = qmlALARM_NOCYCLE_PART_PRESENT;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_SERVO_MOTOR_ID:
            strAlarmName = qmlALARM_NOCYCLE_SERVO_MOTOR;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_READY_POS_ID:
            strAlarmName = qmlALARM_NOCYCLE_READY_POS;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_RECIPE_NOTVALID_ID:
            strAlarmName = qmlALARM_NOCYCLE_RECIPE_NOTVALID;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_BATCH_COUNT_ID:
            strAlarmName = qmlALARM_NOCYCLE_BATCH_COUNT;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_ACTIVERECIPE_NOTVALID_ID:
            strAlarmName = qmlALARM_NOCYCLE_ACTIVERECIPE_NOTVALID;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_PC_ASS_MISMATCH_ID:
            strAlarmName = qmlALARM_NOCYCLE_PC_ASS_MISMATCH;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_AC_ASS_MISMATCH_ID:
            strAlarmName = qmlALARM_NOCYCLE_AC_ASS_MISMATCH;
            break;
        case AlarmIndexEnum.ALARM_NOCYCLE_STACK_ASS_MISMATCH_ID:
            strAlarmName = qmlALARM_NOCYCLE_STACK_ASS_MISMATCH;
            break;
        case AlarmIndexEnum.ALARM_HW_START_SWITCH_FAIL_ID:
            strAlarmName = qmlALARM_HW_START_SWITCH_FAIL;
            break;
        case AlarmIndexEnum.ALARM_HW_ULS_ACTIVE_ID:
            strAlarmName = qmlALARM_HW_ULS_ACTIVE;
            break;
        case AlarmIndexEnum.ALARM_HW_ULS_NONACTIVE_ID:
            strAlarmName = qmlALARM_HW_ULS_NONACTIVE;
            break;
        case AlarmIndexEnum.ALARM_HW_GD_BEFORE_TRIGGER_ID:
            strAlarmName = qmlALARM_HW_GD_BEFORE_TRIGGER;
            break;
        case AlarmIndexEnum.ALARM_HW_START_SWITCH_LOST_ID:
            strAlarmName = qmlALARM_HW_START_SWITCH_LOST;
            break;
        case AlarmIndexEnum.ALARM_HW_ALARM_LOG_ID:
            strAlarmName = qmlALARM_HW_ALARM_LOG;
            break;
        case AlarmIndexEnum.ALARM_HW_EVENT_LOG_ID:
            strAlarmName = qmlALARM_HW_EVENT_LOG;
            break;
        case AlarmIndexEnum.ALARM_HW_WELD_RESULT_ID:
            strAlarmName = qmlALARM_HW_WELD_RESULT;
            break;
        case AlarmIndexEnum.ALARM_HW_WELD_GRAPH_ID:
            strAlarmName = qmlALARM_HW_WELD_GRAPH;
            break;
        case AlarmIndexEnum.ALARM_HW_HORN_SCAN_ID:
            strAlarmName = qmlALARM_HW_HORN_SCAN;
            break;
        case AlarmIndexEnum.ALARM_HW_PRETRIGGER_TIMEOUT_ID:
            strAlarmName = qmlALARM_HW_PRETRIGGER_TIMEOUT;
            break;
        case AlarmIndexEnum.ALARM_HW_ENCODER_FAIL_ID:
            strAlarmName = qmlALARM_HW_ENCODER_FAIL;
            break;
        case AlarmIndexEnum.ALARM_HW_DATA_ERROR_ID:
            strAlarmName = qmlALARM_HW_DATA_ERROR;
            break;
        case AlarmIndexEnum.ALARM_HW_HOME_RETURN_TIMEOUT_ID:
            strAlarmName = qmlALARM_HW_HOME_RETURN_TIMEOUT;
            break;
        case AlarmIndexEnum.ALARM_HW_ACTUATOR_NOVARM_ID:
            strAlarmName = qmlALARM_HW_ACTUATOR_NOVARM;
            break;
        case AlarmIndexEnum.ALARM_HW_PS_NOVARM_ID:
            strAlarmName = qmlALARM_HW_PS_NOVARM;
            break;
        case AlarmIndexEnum.ALARM_HW_START_SWITCH_TIME_ID:
            strAlarmName = qmlALARM_HW_START_SWITCH_TIME;
            break;
        case AlarmIndexEnum.ALARM_HW_MEM_FULL_ID:
            strAlarmName = qmlALARM_HW_MEM_FULL;
            break;
        case AlarmIndexEnum.ALARM_HW_INTERNAL_STORAGE_FAIL_ID:
            strAlarmName = qmlALARM_HW_INTERNAL_STORAGE_FAIL;
            break;
        case AlarmIndexEnum.ALARM_HW_RECALIBRATE_ACT_ID:
            strAlarmName = qmlALARM_HW_RECALIBRATE_ACT;
            break;
        case AlarmIndexEnum.ALARM_HW_ACT_CLR_FUN_ID:
            strAlarmName = qmlALARM_HW_ACT_CLR_FUN;
            break;
        case AlarmIndexEnum.ALARM_HW_EXTRA_TOOLING_ACTIVE_ID:
            strAlarmName = qmlALARM_HW_EXTRA_TOOLING_ACTIVE;
            break;
        case AlarmIndexEnum.ALARM_HW_ACT_TYPE_CHANGED_ID:
            strAlarmName = qmlALARM_HW_ACT_TYPE_CHANGED;
            break;
        case AlarmIndexEnum.ALARM_HW_SYS_PRESSURE_INCORRECT_ID:
            strAlarmName = qmlALARM_HW_SYS_PRESSURE_INCORRECT;
            break;
        case AlarmIndexEnum.ALARM_HW_SYS_PART_PRESENT_ACTIVE_ID:
            strAlarmName = qmlALARM_HW_SYS_PART_PRESENT_ACTIVE;
            break;
        case AlarmIndexEnum.ALARM_HW_USB_MEM_LOST_ID:
            strAlarmName = qmlALARM_HW_USB_MEM_LOST;
            break;
        case AlarmIndexEnum.ALARM_INTERNAL_COMM_ENET:
            strAlarmName = qmlALARM_CONNECTION_LOST;
            break;
        case AlarmIndexEnum.ALARM_HW_ETH_LINK_LOST_ID:
            strAlarmName = qmlALARM_HW_ETH_LINK_LOST;
            break;
        case AlarmIndexEnum.ALARM_HW_CABLE_FAIL_ID:
            strAlarmName = qmlALARM_HW_CABLE_FAIL;
            break;
        case AlarmIndexEnum.ALARM_HW_PROFINET_OR_IP_NOT_ID:
            strAlarmName = qmlALARM_HW_PROFINET_OR_IP_NOT;
            break;
        case AlarmIndexEnum.ALARM_HW_AC_LINE_LOST_ID:
            strAlarmName = qmlALARM_HW_AC_LINE_LOST;
            break;
        case AlarmIndexEnum.ALARM_HW_TRIGGER_ACTIVE_READY_ID:
            strAlarmName = qmlALARM_HW_TRIGGER_ACTIVE_READY;
            break;
        case AlarmIndexEnum.ALARM_HW_INTERNAL_COMM_FAIL_ID:
            strAlarmName = qmlALARM_HW_INTERNAL_COMM_FAIL;
            break;
        case AlarmIndexEnum.ALARM_HW_SC_COMPONENT_FAIL_ID:
            strAlarmName = qmlALARM_HW_SC_COMPONENT_FAIL;
            break;
        case AlarmIndexEnum.ALARM_HW_RTC_LOW_BATT_ID:
            strAlarmName = qmlALARM_HW_SC_COMPONENT_FAIL;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_GROUND_DETECT_ABORT_ID:
            strAlarmName = qmlALARM_CYCLE_GROUND_DETECT_ABORT;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_MAXTIMEOUT_ID:
            strAlarmName = qmlALARM_CYCLE_MAXTIMEOUT;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_NOFORCESTEP_ID:
            strAlarmName = qmlALARM_CYCLE_NOFORCESTEP;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_TRIGGER_GREATER_ENDFORCE_ID:
            strAlarmName = qmlALARM_CYCLE_TRIGGER_GREATER_ENDFORCE;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_LL_NOT_REACHED_ID:
            strAlarmName = qmlALARM_CYCLE_LL_NOT_REACHED;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_PEAKPOWER_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_PEAKPOWER_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_ABSOLUTE_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_ABSOLUTE_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_COLLAPSE_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_COLLAPSE_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_ULTRASONICS_DISABLED_ID:
            strAlarmName = qmlALARM_CYCLE_ULTRASONICS_DISABLED;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_CUSTOM1_CUTOFF_ID:		// Not in E1
            strAlarmName = qmlALARM_CYCLE_CUSTOM1_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_CUSTOM2_CUTOFF_ID:		// Not in E1
            strAlarmName = qmlALARM_CYCLE_CUSTOM2_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_FREQLOW_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_FREQLOW_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_FREQHIGH_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_FREQHIGH_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_CUST_DIGITAL_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_CUST_DIGITAL_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_ENERGY_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_ENERGY_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_GD_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_GD_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_TIME_CUTOFF_ID:
            strAlarmName = qmlALARM_CYCLE_TIME_CUTOFF;
            break;
        case AlarmIndexEnum.ALARM_CYCLE_NO_PRESSURE_STEP_ID:
            strAlarmName = qmlALARM_CYCLE_NO_PRESSURE_STEP;
            break;
        case AlarmIndexEnum.ALARM_ENERGY_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_ENERGY_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_ENERGY_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_ENERGY_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_POWER_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_POWER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_POWER_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_POWER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_COLLAPSE_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_COLLAPSE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_COLLAPSE_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_COLLAPSE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_ABSOLUTE_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_ABSOLUTE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_ABSOLUTE_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_ABSOLUTE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TRIGGER_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_TRIGGER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TRIGGER_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_TRIGGER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_WELD_FORCE_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_WELD_FORCE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_WELD_FORCE_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_WELD_FORCE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TIME_SLLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_TIME_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TIME_SHLIMIT_ID:
            strAlarmName = qmlALARM_SUSPECT_TIME_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_VELOCITY_SLLIMITS_ID:
            strAlarmName = qmlALARM_SUSPECT_VELOCITY_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_VELOCITY_SHLIMITS_ID:
            strAlarmName = qmlALARM_SUSPECT_VELOCITY_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_FREQ_SLLIMITS_ID:
            strAlarmName = qmlALARM_SUSPECT_FREQ_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_FREQ_SHLIMITS_ID:
            strAlarmName = qmlALARM_SUSPECT_FREQ_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_ENERGY_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_ENERGY_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_ENERGY_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_ENERGY_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_POWER_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_POWER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_POWER_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_POWER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_COLLAPSE_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_COLLAPSE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_COLLAPSE_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_COLLAPSE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_ABSOLUTE_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_ABSOLUTE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_ABSOLUTE_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_ABSOLUTE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TRIGGER_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_TRIGGER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TRIGGER_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_TRIGGER_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_WELD_FORCE_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_WELD_FORCE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_WELD_FORCE_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_WELD_FORCE_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TIME_RLLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_TIME_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_TIME_RHLIMIT_ID:
            strAlarmName = qmlALARM_REJECT_TIME_LIMIT;
            break;
        case AlarmIndexEnum.ALARM_FREQ_RLLIMITS_ID:
            strAlarmName = qmlALARM_REJECT_FREQ_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_FREQ_RHLIMITS_ID:
            strAlarmName = qmlALARM_REJECT_FREQ_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_POWER_MATCH_CURVE_RLLIMITS_ID:
            strAlarmName = qmlALARM_POWER_MATCH_CURVE_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_POWER_MATCH_CURVE_RHLIMITS_ID:
            strAlarmName = qmlALARM_POWER_MATCH_CURVE_LIMITS;
            break;
        case AlarmIndexEnum.ALARM_WARNING_TRIGGERLOST_ID:
            strAlarmName = qmlALARM_WARNING_TRIGGERLOST;
            break;
        case AlarmIndexEnum.ALARM_WARNING_ACTUATOR_CLR_NOT_RCHD_ID:
            strAlarmName = qmlALARM_WARNING_ACTUATOR_CLR_NOT_RCHD;
            break;
        case AlarmIndexEnum.ALARM_WARNING_ACTU_RECAL_ID:
            strAlarmName = qmlALARM_WARNING_ACTU_RECAL;
            break;
        case AlarmIndexEnum.ALARM_WARNING_USBMEMORY_ID:
            strAlarmName = qmlALARM_WARNING_USBMEMORY;
            break;
        case AlarmIndexEnum.ALARM_WARNING_DISK_MEMORY_ID:
            strAlarmName = qmlALARM_WARNING_DISK_MEMORY;
            break;
        case AlarmIndexEnum.ALARM_WARNING_ALARM_LOG_ID:
            strAlarmName = qmlALARM_WARNING_ALARM_LOG;
            break;
        case AlarmIndexEnum.ALARM_WARNING_EVENT_LOG_ID:
            strAlarmName = qmlALARM_WARNING_EVENT_LOG;
            break;
        case AlarmIndexEnum.ALARM_WARNING_WELD_RESULT_ID:
            strAlarmName = qmlALARM_WARNING_WELD_RESULT;
            break;
        case AlarmIndexEnum.ALARM_WARNING_WELD_GRAPH_ID:
            strAlarmName = qmlALARM_WARNING_WELD_GRAPH;
            break;
        case AlarmIndexEnum.ALARM_WARNING_HORN_SCAN_ID:
            strAlarmName = qmlALARM_WARNING_HORN_SCAN;
            break;
        case AlarmIndexEnum.ALARM_WARNING_EEPROM_CORRUPT_ID:
            strAlarmName = qmlALARM_WARNING_EEPROM_CORRUPT; //**warning
            break;
        case AlarmIndexEnum.ALARM_PHASE_OVERLOAD_ID:					//** Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_CURR_OVERLOAD_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_FREQ_OVERLOAD_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POWER_OVERLOAD_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_VOLT_OVERLOAD_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEMP_OVERLOAD_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_EB_PHASE_OVERLOAD_ID:					//** Energy Brake Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_EB_CURR_OVERLOAD_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_EB_FREQ_OVERLOAD_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_EB_POWER_OVERLOAD_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_EB_VOLT_OVERLOAD_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_EB_TEMP_OVERLOAD_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_AB_PHASE_OVERLOAD_ID:					//** Afterburst Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_AB_CURR_OVERLOAD_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_AB_FREQ_OVERLOAD_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_AB_POWER_OVERLOAD_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_AB_VOLT_OVERLOAD_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_AB_TEMP_OVERLOAD_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POST_SEEK_PHASE_OVERLOAD_ID:					//** Post Weld Seek Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POST_SEEK_CURR_OVERLOAD_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POST_SEEK_FREQ_OVERLOAD_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POST_SEEK_POWER_OVERLOAD_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POST_SEEK_VOLT_OVERLOAD_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_POST_SEEK_TEMP_OVERLOAD_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_PHASE_ID:					//** Seek Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_CURRENT_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_FREQUENCY_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_POWER_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_VOLTAGE_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_SEEK_OVERLOAD_TEMPERATURE_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEST_OVERLOAD_PHASE_ID:					//** Test Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEST_OVERLOAD_CURRENT_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEST_OVERLOAD_FREQUENCY_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEST_OVERLOAD_POWER_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEST_OVERLOAD_VOLTAGE_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_TEST_OVERLOAD_TEMPERATURE_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_PHASE_ID:					//** Pretrigger Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_CURRENT_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_FREQUENCY_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_POWER_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_VOLTAGE_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRETRIGGER_OVERLOAD_TEMPERATURE_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRE_SEEK_PHASE_OVERLOAD_ID:					//** Pre Weld Seek Overloads
            strAlarmName = qmlALARM_PHASE_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRE_SEEK_CURR_OVERLOAD_ID:
            strAlarmName = qmlALARM_CURR_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRE_SEEK_FREQ_OVERLOAD_ID:
            strAlarmName = qmlALARM_FREQ_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRE_SEEK_POWER_OVERLOAD_ID:
            strAlarmName = qmlALARM_POWER_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRE_SEEK_VOLT_OVERLOAD_ID:
            strAlarmName = qmlALARM_VOLT_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_PRE_SEEK_TEMP_OVERLOAD_ID:
            strAlarmName = qmlALARM_TEMP_OVERLOAD;
            break;
        case AlarmIndexEnum.ALARM_MULTIPLE_FAULTS_ID:
            strAlarmName = qmlALARM_MULTIPLE_FAULTS;
            break;
        case AlarmIndexEnum.ALARM_PALM_BUTTON_FAULT_ID:
            strAlarmName = qmlALARM_PALM_BUTTON_FAULT;
            break;
        case AlarmIndexEnum.ALARM_24V_FAULT_ID:
            strAlarmName = qmlALARM_24V_FAULT;
            break;
        case AlarmIndexEnum.ALARM_ESTOP_FAULT_ID:
            strAlarmName = qmlALARM_ESTOP_FAULT;
            break;
        case AlarmIndexEnum.ALARM_LINEAR_ENCODER_FAULT_ID:
            strAlarmName = qmlALARM_LINEAR_ENCODER_FAULT;
            break;
        case AlarmIndexEnum.ALARM_S_BEAM_FAULT_ID:
            strAlarmName = qmlALARM_S_BEAM_FAULT;
            break;
        case AlarmIndexEnum.ALARM_TRIGGER_SWITCH_FAULT_ID:
            strAlarmName = qmlALARM_TRIGGER_SWITCH_FAULT;
            break;
        case AlarmIndexEnum.ALARM_DRIVE_FAULT_ID:
            strAlarmName = qmlALARM_DRIVE_FAULT;
            break;
        case AlarmIndexEnum.ALARM_CROSS_MONITORING_FAULT_ID:
            strAlarmName = qmlALARM_CROSS_MONITORING_FAULT;
            break;
        case AlarmIndexEnum.ALARM_LOGIC_FAULT_ID:
            strAlarmName = qmlALARM_LOGIC_FAULT;
            break;
        case AlarmIndexEnum.ALARM_SONICS_ENABLE_FAULT_ID:
            strAlarmName = qmlALARM_SONICS_ENABLE_FAULT;
            break;
        default:
            strAlarmName = qmlALARM_UNKNOW_ALARM;
            break;
        }
        return strAlarmName;
    }


    Component.onCompleted:
    {
        updateLanguage()
    }

    QtObject {
        id: textGeneralEnum
        readonly property int textErrorDescriptionIdx:  0
        readonly property int textResetIdx:             1
        readonly property int textHideIdx:              2
    }

}
