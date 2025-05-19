#include "wellparameter.h"
#include <QFile>
#include <QTextStream>

WellParameter* WellParameter::m_wellParameter = nullptr;

WellParameter::WellParameter(QObject *parent)
    : QObject{parent}
{}

WellParameter *WellParameter::getInstance()
{
    if (!m_wellParameter) {
        m_wellParameter = new WellParameter();
    }
    return m_wellParameter;

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

void WellParameter::setWellType(const int newWellType)
{
    if (m_wellType != newWellType) {
        m_wellType = newWellType;
        emit WellTypeChanged();
    }
}

QString WellParameter::WellDepth() const
{
    return m_wellDepth;
}

void WellParameter::setWellDepth(const QString &value)
{
    if (m_wellDepth != value) {
        m_wellDepth = value;
        emit WellDepthChanged();
    }

}

QString WellParameter::HarnessWeight() const
{
    return m_harnessWeight;
}

void WellParameter::setHarnessWeight(const QString &value)
{
    if (m_harnessWeight != value) {
        m_harnessWeight = value;
        emit HarnessWeightChanged();
    }

}

QString WellParameter::SensorWeight() const
{
    return m_sensorWeight;
}

void WellParameter::setSensorWeight(const QString &value)
{
    if (m_sensorWeight != value) {
        m_sensorWeight = value;
        emit SensorWeightChanged();
    }

}

int WellParameter::HarnessType() const
{
    return m_harnessType;
}

void WellParameter::setHarnessType(const int newHarnessType)
{
    if (m_harnessType != newHarnessType) {
        m_harnessType = newHarnessType;
        emit HarnessTypeChanged();
    }

}

QString WellParameter::HarnessForce() const
{
    return m_harnessForce;
}

void WellParameter::setHarnessForce(const QString &value)
{    if (m_harnessForce != value) {
        m_harnessForce = value;
        emit HarnessForceChanged();
    }

}

int WellParameter::TensionUnit() const
{
    return m_tensionUnit;
}

void WellParameter::setTensionUnit(const int newTensionUnit)
{
    if (m_tensionUnit != newTensionUnit) {
        m_tensionUnit = newTensionUnit;
        emit TensionUnitChanged();
    }

}

int WellParameter::WorkType() const
{
    return m_workType;
}

void WellParameter::setWorkType(const int newWorkType)
{
    if (m_workType != newWorkType) {
        m_workType = newWorkType;
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

