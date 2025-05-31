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
    Q_PROPERTY(QString WellNumber READ WellNumber WRITE setWellNumber NOTIFY WellNumberChanged)

    //area block         区块
    Q_PROPERTY(QString AreaBlock READ AreaBlock WRITE setAreaBlock NOTIFY AreaBlockChanged)

    //WellType           油气井类型
    Q_PROPERTY(int WellType READ WellType WRITE setWellType NOTIFY WellTypeChanged)

    //WellDepth          井深（作业井深度）
    Q_PROPERTY(QString WellDepth READ WellDepth WRITE setWellDepth NOTIFY WellDepthChanged)

    //HarnessWeight      电缆自重
    Q_PROPERTY(QString HarnessWeight READ HarnessWeight WRITE setHarnessWeight NOTIFY HarnessWeightChanged)

    //SensorWeight       仪器串重量
    Q_PROPERTY(QString SensorWeight READ SensorWeight WRITE setSensorWeight NOTIFY SensorWeightChanged)

    //HarnessType        电缆规格
    Q_PROPERTY(int HarnessType READ HarnessType WRITE setHarnessType NOTIFY HarnessTypeChanged)

    //HarnessForce       电缆拉断力
    Q_PROPERTY(QString HarnessForce READ HarnessForce WRITE setHarnessForce NOTIFY HarnessForceChanged)

    //TensionUnit        拉力磅吨位
    Q_PROPERTY(int TensionUnit READ TensionUnit WRITE setTensionUnit NOTIFY TensionUnitChanged)

    //WorkType           作业类型
    Q_PROPERTY(int WorkType READ WorkType WRITE setWorkType NOTIFY WorkTypeChanged)

    //UserName           操作员姓名
    Q_PROPERTY(QString UserName READ UserName WRITE setUserName NOTIFY UserNameChanged)

    //OperatorType       操作员工种
    Q_PROPERTY(QString OperatorType READ OperatorType WRITE setOperatorType NOTIFY OperatorTypeChanged)
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
public:
    static WellParameter* getInstance();

    Q_INVOKABLE QString WellNumber() const;
    Q_INVOKABLE void setWellNumber(const QString &value);

    Q_INVOKABLE QString AreaBlock() const;
    Q_INVOKABLE void setAreaBlock(const QString &value);

    Q_INVOKABLE QString WellDepth() const;
    Q_INVOKABLE void setWellDepth(const QString &value);

    Q_INVOKABLE QString HarnessWeight() const;
    Q_INVOKABLE void setHarnessWeight(const QString &value);

    Q_INVOKABLE QString SensorWeight() const;
    Q_INVOKABLE void setSensorWeight(const QString &value);

    Q_INVOKABLE int HarnessType() const;
    Q_INVOKABLE void setHarnessType(const int newHarnessTYpe);

    Q_INVOKABLE QString HarnessForce() const;
    Q_INVOKABLE void setHarnessForce(const QString &value);

    Q_INVOKABLE int TensionUnit() const;
    Q_INVOKABLE void setTensionUnit(const int newTensionUnit);

    Q_INVOKABLE QString UserName() const;
    Q_INVOKABLE void setUserName(const QString &value);

    Q_INVOKABLE QString OperatorType() const;
    Q_INVOKABLE void setOperatorType(const QString &value);

    Q_INVOKABLE int WorkType() const;
    Q_INVOKABLE int WellType() const;
    Q_INVOKABLE void setWorkType(const int type);
    Q_INVOKABLE void setWellType(const int type);

    // CSV methods
//    QString toCSVLine() const;
//    static QString csvHeader();
//    Q_INVOKABLE static WellParameter* fromCSVLine(const QString &line, QObject *parent = nullptr);
//    static QList<WellParameter*> loadFromCSV(const QString &filePath, QObject *parent = nullptr);
//    Q_INVOKABLE static bool saveToCSV(const QString &filePath, const QList<WellParameter*> &list);

signals:

    void WellNumberChanged();

    void AreaBlockChanged();

    void WellDepthChanged();

    void HarnessWeightChanged();

    void SensorWeightChanged();

    void HarnessTypeChanged();

    void HarnessForceChanged();

    void TensionUnitChanged();
    void UserNameChanged();

    void OperatorTypeChanged();

    void WorkTypeChanged();
    void WellTypeChanged();

private:
    explicit WellParameter(QObject *parent = nullptr);

    WellParameter(const WellParameter&) = delete;              // 禁止拷贝
    WellParameter& operator=(const WellParameter&) = delete;   // 禁止赋值
    static WellParameter* m_wellParameter;

private:

    QString m_wellNumber;
    QString m_areaBlock;

    QString m_wellDepth = 0;
    QString m_harnessWeight = 0;
    QString m_sensorWeight = 0;
    int m_harnessType = 0;
    QString m_harnessForce;
    int m_tensionUnit = 0;
    QString m_userName = "";
    QString m_operatorType = "";
    int m_workType;
    int m_wellType;
};

#endif // WELLPARAMETER_H
