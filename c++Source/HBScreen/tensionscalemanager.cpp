#include "tensionscalemanager.h"
#include "c++Source/HBScreen/tensiometer.h"
#include "c++Source/HBData/hbdatabase.h"
#include "c++Source/HBUtility/hbutilityclass.h"
#include "tensiometermanager.h"
#include "tensionsetting.h"
#include <QDebug>

QList<TensionScaleManager::SCALE_DATA> TensionScaleManager::m_ScaleList;  // 存储刻度点数据
QList<TensionScaleManager::SCALE_RAW_DATA> TensionScaleManager::m_ScaleRawList;
TensionScaleManager* TensionScaleManager::_ptrScaleManager = nullptr;
QVector<QPointF> TensionScaleManager::m_ScalePoint;
QList<qreal> TensionScaleManager::m_axisMinParameters;
QList<qreal> TensionScaleManager::m_axisMaxParameters;
TensionScaleManager::TensionScaleManager(QObject *parent)
    : QAbstractListModel(parent)
{
    m_TensiometerNumber = "";
    setTensiometerNumber("0000000");
    m_QuantityOfCalibration = "0";
    setQuantityOfCalibration("2");
    resetModel();
    connect(this, &TensionScaleManager::TensiometerChanged, TensiometerManager::GetInstance(), &TensiometerManager::UpdateTensiometer);
}

void TensionScaleManager::LoadGraphPoint()
{
    QList<qreal> axisMinValues;
    QList<qreal> axisMaxValues;
    m_ScalePoint.clear();
    float f_Scale, f_Tension;
    for(int i = 0; i < 2; i++)
    {
        axisMinValues.append(0);
        axisMaxValues.append(100);
    }

    axisMinValues.replace(0, 9999999);
    axisMinValues.replace(1, 9999999);
    axisMaxValues.replace(0, 0);
    axisMaxValues.replace(1, 0);

    for(int i = 0; i < m_ScaleList.size(); i++)
    {
        f_Scale = m_ScaleList[i].ScaleValue.toFloat();
        HBUtilityClass::GetInstance()->CalculateLargest(axisMaxValues[0], f_Scale);
        HBUtilityClass::GetInstance()->CalculateSmallest(axisMinValues[0], f_Scale);

        f_Tension = m_ScaleList[i].TensionValue.toFloat();
        HBUtilityClass::GetInstance()->CalculateLargest(axisMaxValues[1], f_Tension);
        HBUtilityClass::GetInstance()->CalculateSmallest(axisMinValues[1], f_Tension);

        m_ScalePoint.append(QPointF(f_Scale, f_Tension));
        setAxisMaxParameters(axisMaxValues);
        setAxisMinParameters(axisMinValues);
    }
    emit signalGraphDataReady();
}

TensionScaleManager *TensionScaleManager::GetInstance()
{
    if (!_ptrScaleManager)
    {
        _ptrScaleManager = new TensionScaleManager();
    }
    return _ptrScaleManager;
}

int TensionScaleManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ScaleList.count();
}

QVariant TensionScaleManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    SCALE_DATA scale = m_ScaleList.at(index.row());


    switch (role)
    {
    case IndexRole:
        return index.row();
    case ScaleValueRole:
        return scale.ScaleValue;
    case TensionValueRole:
        return scale.TensionValue;
    default:
        return QVariant();
    }
}

void TensionScaleManager::resetModel()
{
    beginResetModel();
    m_ScaleList.clear();
    endResetModel();
}

void TensionScaleManager::initModel(int quantity)
{

    SCALE_DATA scale;
    // Tow Records for the default setting.
    beginResetModel();
    m_ScaleList.clear();
    for(int i = 0; i < quantity; i++)
    {
        scale.ScaleValue = QString::number(i * 10);
        scale.TensionValue = "0.00";
        m_ScaleList.append(scale);
    }
    endResetModel();
}

void TensionScaleManager::loadModel()
{
    bool ok = false;
    int number = m_TensiometerNumber.toInt(&ok);
    QString str = "";
    TensionSetting::FORCE_UNIT unit = static_cast<TensionSetting::FORCE_UNIT>(TensionSetting::GetInstance()->TensionUnit());
    if(HBDatabase::GetInstance().LoadScales(number, str) == true)
    {
        beginResetModel();
        m_ScaleList.clear();
        m_ScaleRawList.clear();
        if(HBUtilityClass::GetInstance()->StringJsonToList(str, &m_ScaleRawList) == true)
        {
            SCALE_DATA scale;
            for(int i = 0; i < m_ScaleRawList.size(); i++)
            {
                scale.ScaleValue = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2INTEGER, m_ScaleRawList[i].ScaleRaw);
                switch(unit)
                {
                case TensionSetting::LB:
                    scale.TensionValue = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, m_ScaleRawList[i].TensionRaw);
                    break;
                case TensionSetting::KG:
                    scale.TensionValue = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILOGRAM, m_ScaleRawList[i].TensionRaw);
                    break;
                case TensionSetting::KN:
                    scale.TensionValue = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2KILONEWTON, m_ScaleRawList[i].TensionRaw);
                    break;
                default:
                    scale.TensionValue = HBUtilityClass::GetInstance()->FormatedDataToString(HBUtilityClass::HEX2POUND, m_ScaleRawList[i].TensionRaw);
                    break;
                }
                m_ScaleList.append(scale);
            }
            LoadGraphPoint();
        }
        endResetModel();
    }
}

void TensionScaleManager::setTensionValue(const int index, const QString tension)
{
    if (index >= 0 && index < m_ScaleList.size())
    {
        m_ScaleList[index].TensionValue = tension;
        QModelIndex modelIndex = createIndex(index, 0);
        emit dataChanged(modelIndex, modelIndex, {TensionValueRole});
    }
}

void TensionScaleManager::getScaleCurrent(const int index)
{
    if (index >= 0 && index < m_ScaleList.size())
    {
        m_ScaleList[index].ScaleValue = Tensiometer::GetInstance()->ScaleCurrent();
        QModelIndex modelIndex = createIndex(index, 0);
        emit dataChanged(modelIndex, modelIndex, {ScaleValueRole});
    }
}

void TensionScaleManager::SetTensiometerIndex(const int index)
{
    m_TensiometerIndex = index;
}

void TensionScaleManager::saveModel()
{
    QString str = "";
    bool ok = false;
    m_ScaleRawList.clear();
    for(int i = 0; i < m_ScaleList.size(); i++)
    {
        SCALE_RAW_DATA raw;
        raw.ScaleRaw = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2INTEGER, m_ScaleList[i].ScaleValue);
        TensionSetting::FORCE_UNIT unit = static_cast<TensionSetting::FORCE_UNIT>(TensionSetting::GetInstance()->TensionUnit());
        switch(unit)
        {
        case TensionSetting::LB:
            raw.TensionRaw = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2POUND, m_ScaleList[i].TensionValue);
            break;
        case TensionSetting::KG:
            raw.TensionRaw = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2KILOGRAM, m_ScaleList[i].TensionValue);
            break;
        case TensionSetting::KN:
            raw.TensionRaw = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2KILONEWTON, m_ScaleList[i].TensionValue);
            break;
        default:
            raw.TensionRaw = HBUtilityClass::GetInstance()->StringToFormatedData(HBUtilityClass::HEX2POUND, m_ScaleList[i].TensionValue);
            break;
        }
        m_ScaleRawList.append(raw);
    }
    if(HBUtilityClass::GetInstance()->ListJsonToString(&m_ScaleRawList, str) == true)
    {
        int number = m_TensiometerNumber.toInt(&ok);
        if(ok == true)
        {
            HBDatabase::GetInstance().updateScaleJson(number, str);
            emit TensiometerChanged(m_TensiometerIndex, str);
        }
    }
}

QString TensionScaleManager::TensiometerNumber() const
{
    return m_TensiometerNumber;
}

void TensionScaleManager::setTensiometerNumber(const QString number)
{
    if(m_TensiometerNumber != number)
    {
        m_TensiometerNumber = number;
        emit TensiometerNumberChanged();
    }
}

QString TensionScaleManager::QuantityOfCalibration() const
{
    return m_QuantityOfCalibration;
}

void TensionScaleManager::setQuantityOfCalibration(const QString quantity)
{
    if(m_QuantityOfCalibration != quantity)
    {
        m_QuantityOfCalibration = quantity;
        emit QuantityOfCalibrationChanged();
    }
}

void TensionScaleManager::setAxisMinParameters(const QList<qreal> &a_axisVal)
{
    m_axisMinParameters.clear();
    m_axisMinParameters.append(a_axisVal);
}

void TensionScaleManager::setAxisMaxParameters(const QList<qreal> &a_axisVal)
{
    m_axisMaxParameters.clear();
    m_axisMaxParameters.append(a_axisVal);
}

QList<qreal> TensionScaleManager::getAxisMinParameters()
{
    return m_axisMinParameters;
}

QList<qreal> TensionScaleManager::getAxisMaxParameters()
{
    return m_axisMaxParameters;
}

int TensionScaleManager::appendSamples(QAbstractSeries *a_series, quint8 a_type)
{
    Q_UNUSED(a_type);
    QXYSeries *xySeries = static_cast<QXYSeries*>(a_series);
    xySeries->replace(m_ScalePoint);
    int length = m_ScalePoint.count();
    return length;
}

QHash<int, QByteArray> TensionScaleManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IndexRole] = "index";
    roles[ScaleValueRole] = "scaleValue";
    roles[TensionValueRole] = "tensionValue";
    return roles;
}
