#include "wellparameter.h"
#include <QFile>
#include <QTextStream>

WellParameter* WellParameter::_ptrWellParameter = nullptr;

WellParameter::WellParameter(QObject *parent)
    : QObject{parent}
{
    m_workType = -1;
    m_wellType = -1;
    m_DepthWell = "";
    m_SlopeAngleWellSetting = "";
    m_WeightEachKilometerCable = "";
    m_CableSpec = -1;
    m_BreakingForceCable = "";
    m_TonnageTensionStick = "";
    setWellType(VERTICAL);
    setWorkType(PERFORATION);
    setSlopeAngleWellSetting("0.00");
    setDepthWell("99999.99");
    setWeightEachKilometerCable("20000");
    setCableSpec(MILIMETER_5_6);
    setBreakingForceCable("40000");
    setTonnageTensionStick("10.00");
}

WellParameter *WellParameter::GetInstance()
{
    if (!_ptrWellParameter) {
        _ptrWellParameter = new WellParameter();
    }
    return _ptrWellParameter;

}

QString WellParameter::WellNumber() const
{
    return m_wellNumber;
}

void WellParameter::setWellNumber(const QString &value)
{
    if (m_wellNumber != value) {
        m_wellNumber = value;
        emit WellNumberChanged();
    }
}

QString WellParameter::AreaBlock() const
{
    return m_areaBlock;
}

void WellParameter::setAreaBlock(const QString &value)
{
    if (m_areaBlock != value) {
        m_areaBlock = value;
        emit AreaBlockChanged();
    }

}

int WellParameter::WellType() const
{
    return m_wellType;
}

QString WellParameter::SlopeAngleWellSetting() const
{
    return m_SlopeAngleWellSetting;
}

void WellParameter::setWellType(const int type)
{
    if (m_wellType != type)
    {
        m_wellType = type;
        emit WellTypeChanged();
    }
}

void WellParameter::setSlopeAngleWellSetting(const QString angle)
{
    if(m_SlopeAngleWellSetting != angle)
    {
        m_SlopeAngleWellSetting = angle;
        emit SlopeAngleWellSettingChanged();
    }
}

QString WellParameter::DepthWell() const
{
    return m_DepthWell;
}

void WellParameter::setDepthWell(const QString &value)
{
    if (m_DepthWell != value) {
        m_DepthWell = value;
        emit DepthWellChanged();
    }

}

QString WellParameter::WeightEachKilometerCable() const
{
    return m_WeightEachKilometerCable;
}

void WellParameter::setWeightEachKilometerCable(const QString weight)
{
    if (m_WeightEachKilometerCable != weight) {
        m_WeightEachKilometerCable = weight;
        emit WeightEachKilometerCableChanged();
    }

}

QString WellParameter::WeightInstrumentString() const
{
    return m_WeightInstrumentString;
}

void WellParameter::setWeightInstrumentString(const QString weight)
{
    if (m_WeightInstrumentString != weight) {
        m_WeightInstrumentString = weight;
        emit WeightInstrumentStringChanged();
    }

}

int WellParameter::CableSpec() const
{
    return m_CableSpec;
}

void WellParameter::setCableSpec(const int spec)
{
    if (m_CableSpec != spec) {
        m_CableSpec = spec;
        emit CableSpecChanged();
    }

}

QString WellParameter::BreakingForceCable() const
{
    return m_BreakingForceCable;
}

void WellParameter::setBreakingForceCable(const QString value)
{    if (m_BreakingForceCable != value) {
        m_BreakingForceCable = value;
        emit BreakingForceCableChanged();
    }
}

QString WellParameter::TonnageTensionStick() const
{
    return m_TonnageTensionStick;
}

void WellParameter::setTonnageTensionStick(const QString value)
{
    if (m_TonnageTensionStick != value)
    {
        m_TonnageTensionStick = value;
        emit TonnageTensionStickChanged();
    }

}

int WellParameter::WorkType() const
{
    return m_workType;
}

void WellParameter::setWorkType(const int type)
{
    if (m_workType != type)
    {
        m_workType = type;
        emit WorkTypeChanged();
    }

}

QString WellParameter::UserName() const
{
    return m_userName;
}

void WellParameter::setUserName(const QString &value)
{
    if (m_userName != value) {
        m_userName = value;
        emit UserNameChanged();
    }

}

QString WellParameter::OperatorType() const
{
    return m_operatorType;
}

void WellParameter::setOperatorType(const QString &value)
{
    if (m_operatorType != value) {
        m_operatorType = value;
        emit OperatorTypeChanged();
    }

}

//QString WellParameter::csvHeader()
//{
//    return "WellNumber,AreaBlock,WellType,WellDepth,HarnessWeight,SensorWeight,HarnessType,HarnessForce,TensionUnit,WorkType,UserName,OperatorType";
//}



//QString WellParameter::toCSVLine() const
//{
//    QStringList fields = {
//        m_wellNumber,
//        m_areaBlock,
//        m_wellType,
//        m_wellDepth,
//        m_harnessWeight,
//        m_sensorWeight,
//        m_harnessType,
//        m_harnessForce,
//        m_tensionUnit,
//        m_workType,
//        m_userName,
//        m_operatorType
//    };

//    for(QString &field : fields){
//        field.replace("\"","\"\""); //escape quotes
//        if(field.contains(',') || field.contains('"') || field.contains('\n')){
//            field = "\"" + field + "\"";
//        }
//    }

//    return fields.join(',');
//}


//CSV Import
//WellParameter *WellParameter::fromCSVLine(const QString &line, QObject *parent)
//{
//    QStringList fields;
//    QString field;
//    bool inQuotes = false;

//    for(int i = 0; i< line.length(); ++i){
//        QChar c = line[i];

//        if (c == '"'){
//            if(inQuotes && i +1 < line.length() && line[i + 1] == '"'){
//                field += '"';
//                ++i;
//            }else{
//                inQuotes = !inQuotes;
//            }
//        }else if (c == ',' && !inQuotes){
//            fields << field;
//            field.clear();
//        }else{
//            field +=c;
//        }
//    }

//    fields << field;

//    if (fields.size() != 12)
//        return nullptr;

//    WellParameter * param = new WellParameter(parent);

//    param->setWellNumber(fields[0]);
//    param->setAreaBlock(fields[1]);
//    param->setWellType(fields[2]);
//    param->setWellDepth(fields[3]);
//    param->setHarnessWeight(fields[4]);
//    param->setSensorWeight(fields[5]);
//    param->setHarnessType(fields[6]);
//    param->setHarnessForce(fields[7]);
//    param->setTensionUnit(fields[8]);
//    param->setWorkType(fields[9]);
//    param->setUserName(fields[10]);
//    param->setOperatorType(fields[11]);

//    return param;
//}

//QList<WellParameter *> WellParameter::loadFromCSV(const QString &filePath, QObject *parent)
//{
//    QList<WellParameter*> list;
//    QFile file(filePath);
//    if (!file.open(QIODevice :: ReadOnly | QIODevice :: Text))
//        return list;


//    QTextStream in(&file);
//    in.setCodec("UTF-8");

//    if(!in.atEnd())
//        in.readLine(); //skip header

//    while(!in.atEnd()){
//        QString line = in.readLine().trimmed();
//        if(line.isEmpty()) continue;


//        WellParameter *param = fromCSVLine(line,parent);
//        if(param)
//            list.append(param);
//    }

//    file.close();
//    return list;
//}

////save list to csv
//bool WellParameter::saveToCSV(const QString &filePath, const QList<WellParameter *> &list)
//{
//    QFile file(filePath);
//    if (!file.open(QIODevice::WriteOnly | QIODevice :: Text))
//        return false;

//    QTextStream out(&file);
//    out.setCodec("UTF-8");
//    out << csvHeader() << "\n";

//    for (WellParameter *param : list){
//        out << param->toCSVLine() << "\n";

//    }

//    file.close();
//    return true;
//}

