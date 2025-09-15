#include "wellparameter.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QDebug>
#include <QDir>

WellParameter* WellParameter::_ptrWellParameter = nullptr;
QThread *WellParameter::m_ptrImportThread = nullptr;
ImportPicture *WellParameter::m_ptrImportPicture = nullptr;
WellParameter::WellParameter(QObject *parent)
    : QObject(parent),m_settings(QCoreApplication::applicationDirPath() + "/wellsettings.ini", QSettings::IniFormat)
{
    ensureWellSettingsFileExists();

    m_settings.setIniCodec("UTF-8");
    m_WellNumber = "";
    m_AreaBlock = "";
    m_WeightEachKilometerCable = "";
    m_WeightInstrumentString = "";
    m_CableSpec = -1;
    m_BreakingForceCable = "";
    m_TonnageTensionStick = "";
    m_UserName = "";
    m_OperatorType = "";
    m_WorkType = -1;
    m_WellType = -1;
    m_DepthWell = "";
    m_SlopeAngleWellSetting = "";
    m_WellOfficalType = "";
    m_WellModel = "";
    m_CompleteWellDepth = "";
    m_SurfaceCasingDepth = "";
    m_ProductionCasingDepth = "";
    m_HorizontalLength = "";
    m_VerticalLength = "";
    m_KickOffPoint = "";

    setWellNumber(m_settings.value("wellParameter/number", "陕50H-30").toString());
    setAreaBlock(m_settings.value("wellParameter/area", "---").toString());
    setWeightEachKilometerCable("20000");
    setWeightInstrumentString("300");
    setCableSpec(MILIMETER_5_6);
    setBreakingForceCable("40000");
    setTonnageTensionStick("10.00");
    setUserName(m_settings.value("wellParameter/userName", "张强").toString());
    setOperatorType(m_settings.value("wellParameter/operatorType", "11111111").toString());
    setWellType(VERTICAL);
    setWorkType(PERFORATION);
    setDepthWell("99999.99");
    setSlopeAngleWellSetting("0.00");
    QString OcrAiPath = QCoreApplication::applicationDirPath() + "/OcrAi";
    QString RapidOcrTablePath = QCoreApplication::applicationDirPath() + "/rapid_ocr_table.py";
    QString RunOcrShellPath = QCoreApplication::applicationDirPath() + "/run_ocr.sh";
    if(!QFile::exists(OcrAiPath))
    {
        if(!QFile::copy(":/misc/OcrAi", OcrAiPath))
        {
            qWarning() << "Failed to copy OcrAi from resources to" << OcrAiPath;
            return;
        }
    }
    if(!QFile::exists(RapidOcrTablePath))
    {
        if(!QFile::copy(":/misc/rapid_ocr_table.py", RapidOcrTablePath))
        {
            qWarning() << "Failed to copy rapid_ocr_table.py from resources to" << RapidOcrTablePath;
            return;
        }
    }
    if(!QFile::exists(RunOcrShellPath))
    {
        if(!QFile::copy(":/misc/run_ocr.sh", RunOcrShellPath))
        {
            qWarning() << "Failed to copy :/misc/run_ocr.sh from resources to" << RunOcrShellPath;
            return;
        }
    }
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
    return m_WellNumber;
}

void WellParameter::setWellNumber(const QString &value)
{
    if (m_WellNumber != value) {
        m_WellNumber = value;
        emit WellNumberChanged();
    }
}

QString WellParameter::AreaBlock() const
{
    return m_AreaBlock;
}

void WellParameter::setAreaBlock(const QString &value)
{
    if (m_AreaBlock != value) {
        m_AreaBlock = value;
        emit AreaBlockChanged();
    }

}

int WellParameter::WellType() const
{
    return m_WellType;
}

QString WellParameter::SlopeAngleWellSetting() const
{
    return m_SlopeAngleWellSetting;
}

void WellParameter::setWellType(const int type)
{
    if (m_WellType != type)
    {
        m_WellType = type;
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
    return m_WorkType;
}

void WellParameter::setWorkType(const int type)
{
    if (m_WorkType != type)
    {
        m_WorkType = type;
        emit WorkTypeChanged();
    }

}

QString WellParameter::UserName() const
{
    return m_UserName;
}

void WellParameter::setUserName(const QString &value)
{
    if (m_UserName != value) {
        m_UserName = value;
        emit UserNameChanged();
    }

}

QString WellParameter::OperatorType() const
{
    return m_OperatorType;
}

void WellParameter::setOperatorType(const QString &value)
{
    if (m_OperatorType != value) {
        m_OperatorType = value;
        emit OperatorTypeChanged();
    }
}

QString WellParameter::getWellOfficalType() const
{
    return m_WellOfficalType;
}
void WellParameter::setWellOfficalType(const QString &value)
{
    if (m_WellOfficalType != value) 
    {
        m_WellOfficalType = value;
        emit notifyWellOfficalTypeChanged();
    }
}

QString WellParameter::getWellModel() const
{
    return m_WellModel;
}
void WellParameter::setWellModel(const QString &value)
{
    if (m_WellModel != value) 
    {
        m_WellModel = value;
        emit notifyWellModelChanged();
    }
}

QString WellParameter::getDesignWellDepth() const
{
    return m_DesignWellDepth;
}
void WellParameter::setDesignWellDepth(const QString &value)
{
    if (m_DesignWellDepth != value) 
    {
        m_DesignWellDepth = value;
        emit notifyDesignWellDepthChanged();
    }
}

QString WellParameter::getCompleteWellDepth() const
{
    return m_CompleteWellDepth;
}
void WellParameter::setCompleteWellDepth(const QString &value)
{
    if (m_CompleteWellDepth != value) 
    {
        m_CompleteWellDepth = value;
        emit notifyCompleteWellDepthChanged();
    }
}
QString WellParameter::getSurfaceCasingDepth() const
{
    return m_SurfaceCasingDepth;
}
void WellParameter::setSurfaceCasingDepth(const QString &value)
{
    if (m_SurfaceCasingDepth != value) 
    {
        m_SurfaceCasingDepth = value;
        emit notifySurfaceCasingDepthChanged();
    }
}
QString WellParameter::getProductionCasingDepth() const
{
    return m_ProductionCasingDepth;
}
void WellParameter::setProductionCasingDepth(const QString &value)
{
    if (m_ProductionCasingDepth != value) 
    {
        m_ProductionCasingDepth = value;
        emit notifyProductionCasingDepthChanged();
    }
}
QString WellParameter::getHorizontalLength() const
{
    return m_HorizontalLength;
}
void WellParameter::setHorizontalLength(const QString &value)
{
    if (m_HorizontalLength != value) 
    {
        m_HorizontalLength = value;
        emit notifyHorizontalLengthChanged();
    }
}
QString WellParameter::getVerticalLength() const
{
    return m_VerticalLength;
}
void WellParameter::setVerticalLength(const QString &value)
{
    if (m_VerticalLength != value) 
    {
        m_VerticalLength = value;
        emit notifyVerticalLengthChanged();
    }
}
QString WellParameter::getKickOffPoint() const
{
    return m_KickOffPoint;
}
void WellParameter::setKickOffPoint(const QString &value)
{
    if (m_KickOffPoint != value) 
    {
        m_KickOffPoint = value;
        emit notifyKickOffPointChanged();
    }
}



void WellParameter::importFromIniFile()
{
#ifdef RK3588
    QString filePath = findWellSettingsPath();
    if (filePath.isEmpty())
        return;
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    setWellNumber(settings.value("wellParameter/number", "陕50H-30").toString());
    setAreaBlock(settings.value("wellParameter/area", "---").toString());
    setUserName(settings.value("wellParameter/userName", "张强").toString());
    setOperatorType(settings.value("wellParameter/operatorType", "操作员").toString());
#endif
}

bool WellParameter::importDataFromPicture(QString directory, QString localfile)
{

    QThread *thread = new QThread(this);
    ImportPicture *worker = new ImportPicture(localfile, directory);

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &ImportPicture::importToFile);

    // 转发进度和结果
    connect(worker, &ImportPicture::importPrograss,this, &WellParameter::signalImportPrograss);

    connect(worker, &ImportPicture::importFinished, this, [=](bool ok, QString err) {

        emit signalImportCompleted(ok, err);
        thread->quit();  // 任务完成 -> 退出线程
    });

    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);


    thread->start();
    return true;
}


void WellParameter::saveToIniFile()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/wellsettings.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("wellParameter/number", m_WellNumber);
    settings.setValue("wellParameter/area", m_AreaBlock);
    settings.setValue("wellParameter/userName", m_UserName);
    settings.setValue("wellParameter/operatorType", m_OperatorType);
}


QString WellParameter::findWellSettingsPath()
{
    QDir mediaDir("/run/media");
    QStringList subDirs = mediaDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subDir : subDirs)
    {
        QString filePath = "/run/media/" + subDir + "/wellsettings.ini";
        if (QFile::exists(filePath))
        {
            qDebug() << "Found wellsettings.ini at:" << filePath;
            return filePath;
        }
    }
    return QString();
}


void WellParameter::ensureWellSettingsFileExists()
{
    QString wellsettingPath = QCoreApplication::applicationDirPath() + "/wellsettings.ini";

    if (!QFile::exists(wellsettingPath)) {
        if (!QFile::copy(":/misc/wellsettings.ini", wellsettingPath)) {
            qDebug() << "Failed to copy wellsettings.ini from resources!";
        } else {
            qDebug() << "wellsettings.ini copied from resources to " << wellsettingPath;
        }
    }
}
