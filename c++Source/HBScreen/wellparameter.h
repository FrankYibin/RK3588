#ifndef WELLPARAMETER_H
#define WELLPARAMETER_H

#include <QObject>
#include <QString>
#include <QList>

//well condition parameter
class WellParameter : public QObject
{
    Q_OBJECT
    //well number        井号
    Q_PROPERTY(QString WellNumber READ WellNumber WRITE setWellNumber NOTIFY WellNumberChanged) //database modbus

    //area block         区块
    Q_PROPERTY(QString AreaBlock READ AreaBlock WRITE setAreaBlock NOTIFY AreaBlockChanged) //database

    //WellType           油气井类型
    Q_PROPERTY(int WellType READ WellType WRITE setWellType NOTIFY WellTypeChanged) //database modbus

    //WellDepth          井深（作业井深度）
    Q_PROPERTY(QString DepthWell READ DepthWell WRITE setDepthWell NOTIFY DepthWellChanged)

    //HarnessWeight      电缆每千米重量
    Q_PROPERTY(QString WeightEachKilometerCable READ WeightEachKilometerCable WRITE setWeightEachKilometerCable NOTIFY WeightEachKilometerCableChanged)

    //SensorWeight       仪器串重量
    Q_PROPERTY(QString WeightInstrumentString READ WeightInstrumentString WRITE setWeightInstrumentString NOTIFY WeightInstrumentStringChanged FINAL)

    //HarnessType        电缆规格
    Q_PROPERTY(int CableSpec READ CableSpec WRITE setCableSpec NOTIFY CableSpecChanged)

    //HarnessForce       电缆拉断力
    // Q_PROPERTY(QString HarnessForce READ HarnessForce WRITE setHarnessForce NOTIFY HarnessForceChanged)
    Q_PROPERTY(QString BreakingForceCable READ BreakingForceCable WRITE setBreakingForceCable NOTIFY BreakingForceCableChanged)

    //TensionUnit        拉力磅吨位
    // Q_PROPERTY(int TensionUnit READ TensionUnit WRITE setTensionUnit NOTIFY TensionUnitChanged)
    Q_PROPERTY(QString TonnageTensionStick READ TonnageTensionStick WRITE setTonnageTensionStick NOTIFY TonnageTensionStickChanged FINAL)

    //WorkType           作业类型
    Q_PROPERTY(int WorkType READ WorkType WRITE setWorkType NOTIFY WorkTypeChanged)

    //UserName           操作员姓名
    Q_PROPERTY(QString UserName READ UserName WRITE setUserName NOTIFY UserNameChanged)

    //OperatorType       操作员工种
    Q_PROPERTY(QString OperatorType READ OperatorType WRITE setOperatorType NOTIFY OperatorTypeChanged)
    //大斜度井斜度设置
    Q_PROPERTY(QString SlopeAngleWellSetting READ SlopeAngleWellSetting WRITE setSlopeAngleWellSetting NOTIFY SlopeAngleWellSettingChanged)
public:
    enum OIL_WELL_TYPE
    {
        VERTICAL = 0,
        SLOPE,
        HORIZONTAL
    };

    enum WORK_TYPE
    {
        PERFORATION = 0, //qsTr("射孔")
        LOGGING //qsTr("测井")
    };

    enum CABLE_SPEC
    {
        MILIMETER_5_6 = 0,  //5.6mm
        MILIMETER_11_8      //11.8mm
    };

public:
    static WellParameter* GetInstance();

    Q_INVOKABLE QString WeightEachKilometerCable() const;
    Q_INVOKABLE void setWeightEachKilometerCable(const QString weight);

    Q_INVOKABLE QString WeightInstrumentString() const;
    Q_INVOKABLE void setWeightInstrumentString(const QString weight);

    Q_INVOKABLE int CableSpec() const;
    Q_INVOKABLE void setCableSpec(const int spec);

    Q_INVOKABLE QString BreakingForceCable() const;
    Q_INVOKABLE void setBreakingForceCable(const QString value);

    Q_INVOKABLE QString TonnageTensionStick() const;
    Q_INVOKABLE void setTonnageTensionStick(const QString value);

    Q_INVOKABLE QString UserName() const;
    Q_INVOKABLE void setUserName(const QString &value);

    Q_INVOKABLE QString OperatorType() const;
    Q_INVOKABLE void setOperatorType(const QString &value);

    Q_INVOKABLE QString WellNumber() const;
    Q_INVOKABLE void setWellNumber(const QString &value);

    Q_INVOKABLE QString AreaBlock() const;
    Q_INVOKABLE void setAreaBlock(const QString &value);

    Q_INVOKABLE QString DepthWell() const;
    Q_INVOKABLE void setDepthWell(const QString &value);

    Q_INVOKABLE int WorkType() const;
    Q_INVOKABLE void setWorkType(const int type);

    Q_INVOKABLE int WellType() const;
    Q_INVOKABLE void setWellType(const int type);

    Q_INVOKABLE QString SlopeAngleWellSetting() const;
    Q_INVOKABLE void setSlopeAngleWellSetting(const QString angle);




    // CSV methods
//    QString toCSVLine() const;
//    static QString csvHeader();
//    Q_INVOKABLE static WellParameter* fromCSVLine(const QString &line, QObject *parent = nullptr);
//    static QList<WellParameter*> loadFromCSV(const QString &filePath, QObject *parent = nullptr);
//    Q_INVOKABLE static bool saveToCSV(const QString &filePath, const QList<WellParameter*> &list);

signals:
    void WellNumberChanged();
    void AreaBlockChanged();
    void WeightInstrumentStringChanged();
    void CableSpecChanged();
    void BreakingForceCableChanged();
    void TonnageTensionStickChanged();
    void UserNameChanged();
    void OperatorTypeChanged();
    void WorkTypeChanged();
    void WellTypeChanged();
    void DepthWellChanged();
    void SlopeAngleWellSettingChanged();
    void WeightEachKilometerCableChanged();
private:
    explicit WellParameter(QObject *parent = nullptr);

    WellParameter(const WellParameter&) = delete;              // 禁止拷贝
    WellParameter& operator=(const WellParameter&) = delete;   // 禁止赋值
    static WellParameter* _ptrWellParameter;

private:
    QString m_wellNumber;
    QString m_areaBlock;
    QString m_WeightEachKilometerCable;
    QString m_WeightInstrumentString;
    int m_CableSpec;
    QString m_BreakingForceCable;
    QString m_TonnageTensionStick;
    QString m_userName = "";
    QString m_operatorType = "";
    int m_workType;
    int m_wellType;
    QString m_DepthWell;
    QString m_SlopeAngleWellSetting;
};

#endif // WELLPARAMETER_H
