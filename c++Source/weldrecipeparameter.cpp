#include "weldrecipeparameter.h"
/**************************************************************************//**
*
* \brief
*
* \param
*
* \return
*
******************************************************************************/
WeldRecipeParameter::WeldRecipeParameter()
{
    m_CurrentSystemFreq = SYSTEM_TYPE_20KHZ;
    m_MapRecipeParams.clear();
    createRecipeParameterStructure();
}

/**************************************************************************//**
*
* \brief WeldRecipeParameter::addNewParmToMap : This function used to map default values according to KZ
*
* \param strMetricUnit, strImperialUnit, str20KDefaultValue, str20KMinValue, str20KMaxValue,
* str30KDefaultValue, str30KMinValue, str30KMaxValue,
* str40KDefaultValue, str40KMinValue, str40KMaxValue
*
* \return none
*
******************************************************************************/
void WeldRecipeParameter::addNewParmToMap(QString strMetricUnit, QString strImperialUnit,
                                          QString str20KDefaultValue, QString str20KMinValue, QString str20KMaxValue,
                                          QString str30KDefaultValue, QString str30KMinValue, QString str30KMaxValue,
                                          QString str40KDefaultValue, QString str40KMinValue, QString str40KMaxValue,
                                          int paramIndex)
{
    stRecipeParmInfo stTempParam;
    stTempParam.paramIndexInStructure                   = paramIndex;
    stTempParam.ParamUnit[UNIT_SI]                      = strMetricUnit;
    stTempParam.ParamUnit[UNIT_SAE]                     = strImperialUnit;
    stTempParam.ParamDefaultValue[SYSTEM_TYPE_20KHZ]    = str20KDefaultValue;
    stTempParam.ParamMinValue[SYSTEM_TYPE_20KHZ]        = str20KMinValue;
    stTempParam.ParamMaxValue[SYSTEM_TYPE_20KHZ]        = str20KMaxValue;
    stTempParam.ParamDefaultValue[SYSTEM_TYPE_30KHZ]    = str30KDefaultValue;
    stTempParam.ParamMinValue[SYSTEM_TYPE_30KHZ]        = str30KMinValue;
    stTempParam.ParamMaxValue[SYSTEM_TYPE_30KHZ]        = str30KMaxValue;
    stTempParam.ParamDefaultValue[SYSTEM_TYPE_40KHZ]    = str40KDefaultValue;
    stTempParam.ParamMinValue[SYSTEM_TYPE_40KHZ]        = str40KMinValue;
    stTempParam.ParamMaxValue[SYSTEM_TYPE_40KHZ]        = str40KMaxValue;
    m_MapRecipeParams.insert(paramIndex, stTempParam);
}

/**************************************************************************//**
*
* \brief To save all recipe minimum, maximum and default values
*
* \param none
*
* \return none
*
******************************************************************************/
void WeldRecipeParameter::createRecipeParameterStructure()
{
    //              SIUnit  SAEUnit 20_DEF  20_Min  20_MAX  30_DEF  30_MIN  30_MAX  40_DEF  40_MIN  40_MAX  Index
    //SC Structure
    addNewParmToMap("",     "",     "0",    "1",    "1000", "0",    "1",    "1000", "0",    "1",    "1000", SC_RECIPE_NUMBER);
    addNewParmToMap("",     "",     "0",    "1",    "1000", "0",    "1",    "1000", "0",    "1",    "1000", SC_RECIPE_VER_NUMBER);
    addNewParmToMap("",     "",     "1",    "1",    "6",    "1",    "1",    "6",    "1",    "1",    "6",    SC_WELD_MODE);
    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_MODE_VALUE);
    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_MODE_VALUE_TIME);
    addNewParmToMap("J",    "J",    "1",    "1",    "120000","1",   "1",    "45000","1",    "1",    "24000",SC_MODE_VALUE_ENERGY);
    addNewParmToMap("W",    "W",    "400",  "1",    "4000", "150",  "1",    "1500", "80",   "1",    "800",  SC_MODE_VALUE_POWER);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_MODE_VALUE_AD);
    addNewParmToMap("mm",   "in",   "0.01", "0.01", "25",   "0.01", "0.01", "25",   "0.01", "0.01", "25",   SC_MODE_VALUE_CD);
    addNewParmToMap("s",    "s",    "0.001","0.001","0.5",  "0.001","0.001","0.5",  "0.001","0.001","0.5",  SC_MODE_VALUE_ST);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_SCRUB_AMPLITUDE);
    addNewParmToMap("s",    "s",    "0.001","0.001","0.5",  "0.001","0.001","0.5",  "0.001","0.001","0.5",  SC_MODE_VALUE_GD);
    addNewParmToMap("%",    "%",    "0",    "0",    "100",  "0",    "0",    "100",  "0",    "0",    "100",  SC_MODE_VALUE_DY);
    addNewParmToMap("%",    "%",    "0",    "0",    "100",  "0",    "0",    "100",  "0",    "0",    "100",  SC_MODE_VALUE_DENSITY);
    addNewParmToMap("%",    "%",    "100",  "0",    "100",  "100",  "0",    "100",  "100",  "0",    "100",  SC_REACTIVITY);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_FORCE_LEVEL_ENABLED);
    addNewParmToMap("%",    "%",    "100",  "0",    "100",  "100",  "0",    "100",  "100",  "0",    "100",  SC_FORCE_LEVEL);
    addNewParmToMap("s",    "s",    "0",    "0",    "0.3",  "0",    "0",    "0.3",  "0",    "0",    "0.3",  SC_FORCE_LEVEL_TIME);

    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_HOLD_TIME);
    addNewParmToMap("N",    "lbs",  "25",   "5",    "2500", "25",   "5",    "2500", "25",   "5",   "2500",  SC_TRIGGER_FORCE);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_TRIGGER_DISTANCE);
    addNewParmToMap("s",    "s",    "6",    "0.05", "30",   "6",    "0.05", "30",   "6",    "0.05", "30",   SC_MAX_WELD_TIMEOUT);
    addNewParmToMap("",     "",     "1",    "1",    "10",   "1",    "1",    "10",   "1",    "1",    "10",   SC_NUM_AMPLITUDE_STEPS);
    addNewParmToMap("",     "",     "1",    "1",    "7",    "1",    "1",    "7",    "1",    "1",    "7",    SC_AMPLITUDE_STEP_AT);
    addNewParmToMap("",     "",     "1",    "1",    "10",   "1",    "1",    "10",   "1",    "1",    "10",   SC_NUM_FORCE_STEPS);
    addNewParmToMap("",     "",     "1",    "1",    "7",    "1",    "1",    "7",    "1",    "1",    "7",    SC_FORCE_STEP_AT);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE1);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE2);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE3);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE4);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE5);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE6);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE7);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE8);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE9);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_FORCE_STEP_VALUE10);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE1);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE2);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE3);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE4);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE5);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE6);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE7);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE8);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE9);
    addNewParmToMap("",     "",     "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_AMPLITUDE_STEP_VALUE10);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP1);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP2);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP3);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP4);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP5);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP6);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP7);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP8);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP9);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AMPLITUDE_STEP10);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_COOLING_VALVE);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_GLOBAL_SUSPECT);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_GLOBAL_REJECT);
    addNewParmToMap("",     "",     "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    "0",    SC_CONTROL_LIMIT);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_PEAKPOWER_CUTOFF);
    addNewParmToMap("W",    "W",    "400",  "1",    "4000", "150",  "1",    "1500", "80",   "1",    "800",  SC_CL_PEAKPOWER_CUTOFF_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_ABSOLUTE_CUTOFF);
    addNewParmToMap("mm",   "in",   "125",  "3",    "125",  "125",  "3",    "125",  "125",  "3",    "125",  SC_CL_ABSOLUTE_CUTOFF_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_COLLAPSE_CUTOFF);
    addNewParmToMap("mm",   "in",   "25",   "0.01", "25",   "25",   "0.01", "25",   "25",   "0.01", "25",   SC_CL_COLLAPSE_CUTOFF_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_TIME_CUTOFF);
    addNewParmToMap("s",    "s",    "30",   "0.010","30",   "30",   "0.010","30",   "30",   "0.010","30",   SC_CL_TIME_CUTOFF_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_FREQ_LOW);
    addNewParmToMap("Hz",   "Hz",   "500",  "1",    "500",  "750",  "1",    "750",  "1000", "1",    "1000", SC_CL_FREQ_LOW_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_FREQ_HIGH);
    addNewParmToMap("Hz",   "Hz",   "500",  "1",    "500",  "750",  "1",    "750",  "1000", "1",    "1000", SC_CL_FREQ_HIGH_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_ENERGY_CUTOFF);
    addNewParmToMap("J",    "J",    "120000","1",   "120000","45000","1",   "45000","24000","1",    "24000",SC_CL_ENERGY_CUTOFF_VAL);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_CL_GROUND_DETECT_CUTOFF);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_PRETRIGGER);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_AUTO_PRETRIGGER);
    addNewParmToMap("",     "",     "1",    "0",    "1",    "1",    "0",    "1",    "1",    "0",    "1",    SC_DISTANCE_PRETRIGGER);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_PRETRIGGER_DISTANCE);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_PRETRIGGER_AMPLITUDE);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_AFTER_BURST);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  SC_AB_AMPLITUDE);
    addNewParmToMap("s",    "s",    "0.1",  "0.050","2",    "0.1",  "0.050","2",    "0.1",  "0.050","2",    SC_AB_DELAY);
    addNewParmToMap("s",    "s",    "0.1",  "0.1",  "2",    "0.1",  "0.1",  "2",    "0.1",  "0.1",  "2",    SC_AB_TIME);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_ENERGY_BRAKE);
    addNewParmToMap("%",    "%",    "3",    "1",    "100",  "3",    "1",    "100",  "3",    "1",    "100",  SC_ENERGY_BRAKE_AMPLITUDE);
    addNewParmToMap("s",    "s",    "0.02", "0.01", "1",    "0.02", "0.01", "1",    "0.02", "0.01", "1",    SC_ENERGY_BRAKE_TIME);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_TIME_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_TIME_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_TIME_HIGH_ENABLED);
    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_SUSPECT_TIME_LOW);
    addNewParmToMap("s",    "s",    "30",   "0.010","30",   "30",   "0.010","30",   "30",   "0.010","30",   SC_SUSPECT_TIME_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_ENERGY_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_ENERGY_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_ENERGY_HIGH_ENABLED);
    addNewParmToMap("J",    "J",    "1",    "1",    "120000","1",   "1",    "45000","1",    "1",    "24000",SC_SUSPECT_ENERGY_LOW);
    addNewParmToMap("J",    "J",    "120000","1",   "120000","45000","1",   "45000","24000","1",    "24000",SC_SUSPECT_ENERGY_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_POWER_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_POWER_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_POWER_HIGH_ENABLED);
    addNewParmToMap("W",    "W",    "1",    "1",    "4000", "1",    "1",    "1500", "1",    "1",    "800",  SC_SUSPECT_POWER_LOW);
    addNewParmToMap("W",    "W",    "4000", "1",    "4000", "1500", "1",    "1500", "800",  "1",    "800",  SC_SUSPECT_POWER_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_CD_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_CD_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_CD_HIGH_ENABLED);
    addNewParmToMap("mm",   "in",   "0.01", "0.01", "25",   "0.01", "0.01", "25",   "0.01", "0.01", "25",   SC_SUSPECT_CD_LOW);
    addNewParmToMap("mm",   "in",   "25",   "0.01", "25",   "25",   "0.01", "25",   "25",   "0.01", "25",   SC_SUSPECT_CD_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_AD_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_AD_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_AD_HIGH_ENABLED);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_SUSPECT_AD_LOW);
    addNewParmToMap("mm",   "in",   "125",  "3",    "125",  "125",  "3",    "125",  "125",  "3",    "125",  SC_SUSPECT_AD_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_TD_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_TD_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_TD_HIGH_ENABLED);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_SUSPECT_TD_LOW);
    addNewParmToMap("mm",   "in",   "125",  "3",    "125",  "125",  "3",    "125",  "125",  "3",    "125",  SC_SUSPECT_TD_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_END_FORCE_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_END_FORCE_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_END_FORCE_HIGH_ENABLED);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", SC_SUSPECT_END_FORCE_LOW);
    addNewParmToMap("N",    "lbs",  "2500", "25",   "2500", "2500", "25",   "2500", "2500", "25",   "2500", SC_SUSPECT_END_FORCE_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_FREQ_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_FREQ_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_SUSPECT_FREQ_HIGH_ENABLED);
    addNewParmToMap("Hz",   "Hz",   "1",    "1",    "500",  "1",    "1",    "750",  "1",    "1",    "1000", SC_SUSPECT_FREQ_LOW);
    addNewParmToMap("Hz",   "Hz",   "500",  "1",    "500",  "750",  "1",    "750",  "1000", "1",    "1000", SC_SUSPECT_FREQ_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_TIME_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_TIME_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_TIME_HIGH_ENABLED);
    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   SC_REJECT_TIME_LOW);
    addNewParmToMap("s",    "s",    "30",   "0.010","30",   "30",   "0.010","30",   "30",   "0.010","30",   SC_REJECT_TIME_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_ENERGY_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_ENERGY_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_ENERGY_HIGH_ENABLED);
    addNewParmToMap("J",    "J",    "1",    "1",    "120000","1",   "1",    "45000","1",    "1",    "24000",SC_REJECT_ENERGY_LOW);
    addNewParmToMap("J",    "J",    "120000","1",   "120000","45000","1",   "45000","24000","1",    "24000",SC_REJECT_ENERGY_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_POWER_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_POWER_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_POWER_HIGH_ENABLED);
    addNewParmToMap("W",    "W",    "1",    "1",    "4000", "1",    "1",    "1500", "1",    "1",    "800",  SC_REJECT_POWER_LOW);
    addNewParmToMap("W",    "W",    "4000", "1",    "4000", "1500", "1",    "1500", "800",  "1",    "800",  SC_REJECT_POWER_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_CD_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_CD_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_CD_HIGH_ENABLED);
    addNewParmToMap("mm",   "in",   "0.01", "0.01", "25",   "0.01", "0.01", "25",   "0.01", "0.01", "25",   SC_REJECT_CD_LOW);
    addNewParmToMap("mm",   "in",   "25",   "0.01", "25",   "25",   "0.01", "25",   "25",   "0.01", "25",   SC_REJECT_CD_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_AD_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_AD_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_AD_HIGH_ENABLED);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_REJECT_AD_LOW);
    addNewParmToMap("mm",   "in",   "125",  "3",    "125",  "125",  "3",    "125",  "125",  "3",    "125",  SC_REJECT_AD_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_TD_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_TD_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_TD_HIGH_ENABLED);
    addNewParmToMap("mm",   "in",   "3",    "3",    "125",  "3",    "3",    "125",  "3",    "3",    "125",  SC_REJECT_TD_LOW);
    addNewParmToMap("mm",   "in",   "125",  "3",    "125",  "125",  "3",    "125",  "125",  "3",    "125",  SC_REJECT_TD_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_END_FORCE_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_END_FORCE_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_END_FORCE_HIGH_ENABLED);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", SC_REJECT_END_FORCE_LOW);
    addNewParmToMap("N",    "lbs",  "2500", "25",   "2500", "2500", "25",   "2500", "2500", "25",   "2500", SC_REJECT_END_FORCE_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_FREQ_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_FREQ_LOW_ENABLED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_REJECT_FREQ_HIGH_ENABLED);
    addNewParmToMap("Hz",   "Hz",   "1",    "1",    "500",  "1",    "1",    "750",  "1",    "1",    "1000", SC_REJECT_FREQ_LOW);
    addNewParmToMap("Hz",   "Hz",   "500",  "1",    "500",  "750",  "1",    "750",  "1000", "1",    "1000", SC_REJECT_FREQ_HIGH);
    addNewParmToMap("",     "",     "",     "",     "",     "",     "",     "",     "",     "",     "",     SC_USER);
    addNewParmToMap("",     "",     "",     "",     "",     "",     "",     "",     "",     "",     "",     SC_STACK_SERIAL_NO);
    addNewParmToMap("",     "",     "",     "",     "",     "",     "",     "",     "",     "",     "",     UI_RECIPE_NAME);
    addNewParmToMap("min",  "min",  "1",    "1",    "59",   "1",    "1",    "59",   "1",    "1",    "59",   SC_TIMED_SEEK_PERIOD);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_TIMED_SEEK);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_PRE_WELD_SEEK);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    SC_POST_WELD_SEEK);
    // PC Structure
    addNewParmToMap("KHz",  "KHz",  "100",  "1",    "20000","205",  "1",    "20000","205",  "1",    "20000",PC_AMPLITUDE_LOOPC1);
    addNewParmToMap("KHz",  "KHz",  "300",  "1",    "20000","370",  "1",    "20000","370",  "1",    "20000",PC_AMPLITUDE_LOOPC2);
    addNewParmToMap("KHz",  "KHz",  "450",  "50",   "500",  "100",  "50",   "500",  "60",   "50",   "500",  PC_PHASE_LOOP);
    addNewParmToMap("KHz",  "KHz",  "450",  "50",   "500",  "200",  "50",   "500",  "200",  "50",   "500",  PC_PHASE_LOOPCF);
    addNewParmToMap("Hz",   "Hz",   "500",  "19450",  "20450",  "750",  "29250",   "30750",  "1000", "38950", "40950", PC_FREQUENCY_LOW);
    addNewParmToMap("Hz",   "Hz",   "500",  "19450",  "20450",  "750",  "29250",   "30750",  "1000", "38950", "40950", PC_FREQUENCY_HIGH);
    addNewParmToMap("s",    "s",    "0.5",  "0.001","20",   "0.5",  "0.001","20",   "0.5",  "0.001","20",   PC_PHASE_LIMIT_TIME);
    addNewParmToMap("",     "",     "1000", "4",    "9765", "1000", "4",    "9765", "1000", "4",    "9765", PC_PHASE_LIMIT);
    addNewParmToMap("",     "",     "",     "",     "",     "",     "",     "",     "",     "",     "",     PC_CONTROL_MODE);
    addNewParmToMap("",     "",     "0",    "0",    "1000", "0",    "0",    "1000", "0",    "0",    "1000", PC_BLIND_TIME_SEEK);
    addNewParmToMap("",     "",     "0",    "0",    "1000", "0",    "0",    "1000", "0",    "0",    "1000", PC_BLIND_TIME_WELD);
    addNewParmToMap("",     "",     "500",  "0",    "1000", "200",  "0",    "1000", "200",  "0",    "1000", PC_DDS_SWITCH_TIME);
    addNewParmToMap("",     "",     "800",  "0",    "10000","1200", "0",    "10000","0",    "0",    "10000",PC_PARAMETER7);
    addNewParmToMap("",     "",     "1000", "0",    "10000","1000", "0",    "10000","0",    "0",    "10000",PC_PARAMETER8);
    addNewParmToMap("",     "",     "200",  "0",    "10000","200",  "0",    "10000","0",    "0",    "10000",PC_PARAMETER9);
    addNewParmToMap("",     "",     "5",    "0",    "10000","5",    "0",    "10000","0",    "0",    "10000",PC_PARAMETER10);
    addNewParmToMap("",     "",     "0",    "0",    "10000","0",    "0",    "10000","0",    "0",    "10000",PC_PARAMETER11);
    addNewParmToMap("",     "",     "0",    "0",    "10000","0",    "0",    "10000","0",    "0",    "10000",PC_PARAMETER12);
    addNewParmToMap("",     "",     "20000","0",   "100000","20000","0",   "100000","20000","0",   "100000",PC_PARAMETER13);
    addNewParmToMap("",     "",     "20000","0",   "100000","20000","0",   "100000","20000","0",   "100000",PC_PARAMETER14);
    addNewParmToMap("",     "",     "20000","0",   "100000","20000","0",   "100000","20000","0",   "100000",PC_PARAMETER15);
    addNewParmToMap("s",    "s",    "1",    "0",    "1",    "1",    "0",    "1",    "1",    "0",    "1",    PC_F_LIMIT_TIME);
    addNewParmToMap("KHz",  "KHz",  "100",  "1",    "500",  "205",  "1",    "500",  "205",  "1",    "500",  PC_AMP_PROPORTIONAL_GAIN);
    addNewParmToMap("KHz",  "KHz",  "5",    "1",    "500",  "5",    "1",    "500",  "5",    "1",    "500",  PC_AMP_INTEGRAL_GAIN);
    addNewParmToMap("KHz",  "KHz",  "22",   "1",    "500",  "25",   "1",    "500",  "41",   "1",    "500",  PC_PHASE_INTEGRAL_GAIN);
    addNewParmToMap("KHz",  "KHz",  "5",    "1",    "500",  "5",    "1",    "500",  "5",    "1",    "500",  PC_PHASE_PROPORTIONAL_GAIN);
    addNewParmToMap("",     "",     "100",  "1",    "500",  "100",  "1",    "500",  "100",  "1",    "500",  PC_FREQUENCY_WINDOW_SIZE);
    addNewParmToMap("KHz",  "KHz",  "450",  "1",    "500",  "200",  "1",    "500",  "200",  "1",    "500",  PC_PF_OF_PHASE_CONTROL_LOOP);
    addNewParmToMap("KHz",  "KHz",  "500",  "1",    "500",  "750",  "1",    "750",  "1000", "1",    "1000", PC_PI_FREQUENCY_LOW);
    addNewParmToMap("KHz",  "KHz",  "500",  "1",    "500",  "750",  "1",    "750",  "1000", "1",    "1000", PC_PI_FREQUENCY_HIGH);
    addNewParmToMap("s",    "s",    "0.5",  "0.001","20",   "0.5",  "0.001","20",   "0.5",  "0.001","20",   PC_PI_PHASE_LIMIT_TIME);
    addNewParmToMap("",     "",     "1000", "4",    "9765", "1000", "4",    "9765", "1000", "4",    "9765", PC_PI_PHASE_LIMIT);
    addNewParmToMap("s",    "s",    "0.08", "0.01", "1",    "0.08", "0.01", "1",    "0.08", "0.01", "1",    PC_WELD_RAMP_TIME);
    addNewParmToMap("Hz",   "Hz",   "19950","19450","20450","30000","29250","30750","39900","39100","40700",PC_START_FREQUENCY);
    addNewParmToMap("",     "",     "0",    "0",    "10000","0",    "0",    "10000","0",    "0",    "10000",PC_MEMORY_OFFSET);
    addNewParmToMap("Hz",   "Hz",   "19950","19450","20450","30000","29250","30750","39900","39100","40700",PC_DIGITAL_TUNE);
    addNewParmToMap("Hz",   "Hz",   "19950","19450","20450","30000","29250","30750","39900","39100","40700",PC_FREQUENCY_OFFSET);
    //AC Structure
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_WELD_FORCE);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_RAMP_TIME);
    addNewParmToMap("",     "",     "",     "",     "",     "",     "",     "",     "",     "",     "",     AC_HOLD_MODE);
    addNewParmToMap("mm",   "in",   "0",    "0",    "50",   "0",    "0",    "50",   "0",    "0",    "50",   AC_TOTAL_COLLAPSE_TARGET);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_HOLD_FORCE);
    addNewParmToMap("s",    "s",    "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    AC_HOLD_FORCE_RAMP_TIME);
    addNewParmToMap("mm",   "in",   "0",    "0",    "125",  "0",    "0",    "125",  "0",    "0",    "125",  AC_EXPECTED_PART_CONTACT_POSITION);
    addNewParmToMap("mm",   "in",   "5",    "5",    "120",  "5",    "5",    "120",  "5",    "5",    "120",  AC_READY_POSITION);
    addNewParmToMap("mm/s2","in/s2","500",  "1",    "10000","500",  "1",    "10000","500",  "1",    "10000",AC_DOWN_ACCELERATION);
    addNewParmToMap("mm/s2","in/s2","500",  "1",    "10000","500",  "1",    "10000","500",  "1",    "10000",AC_DOWN_DECELERATION);
    addNewParmToMap("mm/s", "in/s", "50",   "5",    "150",  "50",   "5",    "150",  "50",   "5",    "150",  AC_DOWN_MAX_VELOCITY);
    addNewParmToMap("mm/s2","in/s2","500",  "1",    "10000","500",  "1",    "10000","500",  "1",    "10000",AC_RETURN_ACCELERATION);
    addNewParmToMap("mm/s2","in/s2","500",  "1",    "10000","500",  "1",    "10000","500",  "1",    "10000",AC_RETURN_DECELERATION);
    addNewParmToMap("mm/s", "in/s", "50",   "5",    "150",  "50",   "5",    "150",  "50",   "5",    "150",  AC_RETURN_MAX_VELOCITY);
    addNewParmToMap("mm",   "in",   "0.01", "0.01", "5",    "0.01", "0.01", "5",    "0.01", "0.01", "5",    AC_PART_CONTANCT_OFFSET);
    addNewParmToMap("mm",   "in",   "2",    "0.01", "10",   "2",    "0.01", "10",   "2",    "0.01", "10",   AC_PART_CONTANCT_WINDOW_MINUS);
    addNewParmToMap("mm",   "in",   "2",    "0.01", "10",   "2",    "0.01", "10",   "2",    "0.01", "10",   AC_PART_CONTANCT_WINDOW_PLUS);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE1);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE2);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE3);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE4);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE5);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE6);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE7);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE8);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE9);
    addNewParmToMap("s",    "s",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    "0.1",  "0",    "1",    AC_FORCE_STEP_RAMP_VALUE10);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP1);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP2);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP3);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP4);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP5);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP6);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP7);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP8);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP9);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", AC_FORCE_STEP10);
    addNewParmToMap("",     "",     "1",    "0",    "1",    "1",    "0",    "1",    "1",    "0",    "1",    AC_READY_POSITION_TOGGLE);
    addNewParmToMap("",     "",     "3",    "1",    "3",    "3",    "1",    "3",    "3",    "1",    "3",    AC_WELD_FORCE_CONTROL);

    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_GLOBAL_SETUP);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_SETUP_WELD_MODE_STATUS);
    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   UI_SETUP_WELD_MODE_LOW);
    addNewParmToMap("s",    "s",    "30",   "0.010","30",   "30",   "0.010","30",   "30",   "0.010","30",   UI_SETUP_WELD_MODE_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_WELD_AMP_STATUS);
    addNewParmToMap("%",    "%",    "10",   "10",   "100",  "10",   "10",   "100",  "10",   "10",   "100",  UI_WELD_AMP_LOW);
    addNewParmToMap("%",    "%",    "100",  "10",   "100",  "100",  "10",   "100",  "100",  "10",   "100",  UI_WELD_AMP_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_WELD_FORCE_STATUS);
    addNewParmToMap("N",    "lbs",  "50",   "25",   "2500", "50",   "25",   "2500", "50",   "25",   "2500", UI_WELD_FORCE_LOW);
    addNewParmToMap("N",    "lbs",  "2500", "25",   "2500", "2500", "25",   "2500", "2500", "25",   "2500", UI_WELD_FORCE_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_TRIGGER_FORCE_STATUS);
    addNewParmToMap("N",    "lbs",  "25",   "5",    "2500", "25",   "5",    "2500", "25",   "5",    "2500", UI_TRIGGER_FORCE_LOW);
    addNewParmToMap("N",    "lbs",  "2500", "5",    "2500", "2500", "5",    "2500", "2500", "5",    "2500", UI_TRIGGER_FORCE_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_HOLD_FORCE_STATUS);
    addNewParmToMap("N",    "lbs",  "25",   "25",   "2500", "25",   "25",   "2500", "25",   "25",   "2500", UI_HOLD_FORCE_LOW);
    addNewParmToMap("N",    "lbs",  "2500", "25",   "2500", "2500", "15",   "2500", "2500", "25",   "2500", UI_HOLD_FORCE_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_HOLD_TIME_STATUS);
    addNewParmToMap("s",    "s",    "0.010","0.010","30",   "0.010","0.010","30",   "0.010","0.010","30",   UI_HOLD_TIME_LOW);
    addNewParmToMap("s",    "s",    "30",   "0.010","30",   "30",   "0.010","30",   "30",   "0.010","30",   UI_HOLD_TIME_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_SCRUB_AMP_STATUS);
    addNewParmToMap("%",    "%",    "1",    "1",    "100",  "1",    "1",    "100",  "1",    "1",    "100",  UI_SCRUB_AMP_LOW);
    addNewParmToMap("%",    "%",    "100",  "1",    "100",  "100",  "1",    "100",  "100",  "1",    "100",  UI_SCRUB_AMP_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_SCRUB_TIME_STATUS);
    addNewParmToMap("s",    "s",    "0.001","0.001","0.5",  "0.001","0.001","0.5",  "0.001","0.001","0.5",  UI_SCRUB_TIME_LOW);
    addNewParmToMap("s",    "s",    "0.5",  "0.001","0.5",  "0.5",  "0.001","0.5",  "0.5",  "0.001","0.5",  UI_SCRUB_TIME_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_REACTIVITY_STATUS);
    addNewParmToMap("%",    "%",    "0",    "0",    "100",  "0",    "0",    "100",  "0",    "0",    "100",  UI_REACTIVITY_LOW);
    addNewParmToMap("%",    "%",    "100",  "0",    "100",  "100",  "0",    "100",  "100",  "0",    "100",  UI_REACTIVITY_HIGH);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_FORCE_LEVEL_STATUS);
    addNewParmToMap("%",    "%",    "0",    "0",    "100",  "0",    "0",    "100",  "0",    "0",    "100",  UI_FORCE_LEVEL_LOW);
    addNewParmToMap("%",    "%",    "100",  "0",    "100",  "100",  "0",    "100",  "100",  "0",    "100",  UI_FORCE_LEVEL_HIGH);

    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_IS_MODIFIED);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_ISNEW_RECIPE);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_ISVALID);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_ISLOCK);
    addNewParmToMap("",     "",     "0",    "0",    "1",    "0",    "0",    "1",    "0",    "0",    "1",    UI_ISACTIVE);
}

/**************************************************************************//**
*
* \brief Convert seconds to milliseconds
*
* \param dbTime
*
* \return millisecond time value
*
******************************************************************************/
double WeldRecipeParameter::convertSecToMsec(double dbTime)
{
    double tmp;
    tmp = dbTime * (double)1000;
    return tmp;
}

/**************************************************************************//**
*
* \brief Convert Milliseconds to seconds
*
* \param dbTime
*
* \return second time value
*
******************************************************************************/
double WeldRecipeParameter::convertMsecToSec(double dbTime)
{
    double tmp;
    tmp = dbTime / (double)1000;
    return tmp;
}

/**************************************************************************//**
*
* \brief Convert Micrometre to Millimetre
*
* \param dbLength
*
* \return millimetre length value
*
******************************************************************************/
double WeldRecipeParameter::convertMicrometreToMillimetre(double dbLength)
{
    double tmp;
    tmp = dbLength / (double)1000;
    return tmp;
}

/**************************************************************************//**
*
* \brief convert Millimetre to Micrometre
*
* \param dbLength
*
* \return micrometre length value
*
******************************************************************************/
double WeldRecipeParameter::convertMillimetreToMicrometre(double dbLength)
{
    double tmp;
    tmp = dbLength * (double)1000;
    return tmp;
}

/**************************************************************************//**
*
* \brief Convert Inches to Micrometre
*
* \param dbInches
*
* \return Micrometre length value
*
******************************************************************************/
double WeldRecipeParameter::convertInchToMicrometre(double dbInches)
{
    double dbMicrometre;
    dbMicrometre = dbInches * (double)25400;
    return dbMicrometre;
}

/**************************************************************************//**
*
* \brief Convert Inches to Millimetre
*
* \param dbInches
*
* \return Millimetre length value
*
******************************************************************************/
double WeldRecipeParameter::convertInchToMillimetre(double dbInches)
{
    double dbMillimetre;
    dbMillimetre = dbInches * (double)25.4;
    return dbMillimetre;
}

/**************************************************************************//**
*
* \brief Convert Micrometre to Inches
*
* \param dbMicrometres
*
* \return Inches length value
*
******************************************************************************/
double WeldRecipeParameter::convertMicrometreToInch(double dbMicrometres)
{
    double dbInches;
    dbInches = dbMicrometres / (double)25400;
    return dbInches;
}

/**************************************************************************//**
*
* \brief Convert Millimetre to Inches
*
* \param dbMillimetres
*
* \return Inches length value
*
******************************************************************************/
double WeldRecipeParameter::convertMillimetreToInch(double dbMillimetres)
{
    double dbInches;
    dbInches = dbMillimetres / (double)25.4;
    return dbInches;
}

/**************************************************************************//**
*
* \brief Convert Newtons to Pounds
*
* \param dbNewtons
*
* \return Pounds value
*
******************************************************************************/
double WeldRecipeParameter::convertNewtonToLB(double dbNewtons)
{
    double dbPounds;
    dbPounds = dbNewtons / (double)4.44822;
    return dbPounds;
}

/**************************************************************************//**
*
* \brief Convert Pounds to NewTons
*
* \param dbPounds
*
* \return Newtons value
*
******************************************************************************/
double WeldRecipeParameter::convertLBToNewton(double dbPounds)
{
    double dbNewtons;
    dbNewtons = dbPounds * (double)4.44822;
    return dbNewtons;
}

/**************************************************************************//**
*
* \brief GetDefaultValue and assign to the Particular Values and Unit
*
* \param parameter index
*
* \return default value of the specific parameter under the current system frequency.
*
******************************************************************************/
QString WeldRecipeParameter::getDefaultValue(int dwParamIndex)
{
    return m_MapRecipeParams[dwParamIndex].ParamDefaultValue[m_CurrentSystemFreq];
}

/**************************************************************************//**
*
* \brief To get minimum value of the specific parameter under the current system frequency
*
* \param parameter index
*
* \return minimum value
*
******************************************************************************/
QString WeldRecipeParameter::getMinValue(int dwParamIndex)
{
    return m_MapRecipeParams[dwParamIndex].ParamMinValue[m_CurrentSystemFreq];
}

/**************************************************************************//**
*
* \brief To get maximum value of the specific parameter under the current system frequency
*
* \param parameter index
*
* \return maximum value
*
******************************************************************************/
QString WeldRecipeParameter::getMaxValue(int dwParamIndex)
{
    return m_MapRecipeParams[dwParamIndex].ParamMaxValue[m_CurrentSystemFreq];
}

/**************************************************************************//**
*
* \brief To set Maximum value of the specific parameter under the current system frequency
*
* \param parameter index, parameter value
*
* \return none
*
******************************************************************************/
void WeldRecipeParameter::setMaxValue(int dwParamIndex, int dwParamVal)
{
    if(m_MapRecipeParams.contains(dwParamIndex) == true)
    {
        m_MapRecipeParams[dwParamIndex].ParamMaxValue[m_CurrentSystemFreq] = QString::number(dwParamVal);
    }
}
