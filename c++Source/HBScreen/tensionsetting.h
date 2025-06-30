#ifndef TENSIONSETTING_H
#define TENSIONSETTING_H

#include <QObject>

class TensionSetting : public QObject
{
    Q_OBJECT
    //Tension Units  张力单位
    Q_PROPERTY(int TensionUnit READ TensionUnit WRITE setTensionUnit NOTIFY TensionUnitChanged)
    //K_Value           k值
    Q_PROPERTY(QString KValue READ KValue WRITE setKValue NOTIFY KValueChanged)

    //MaxTension 极限张力
    Q_PROPERTY(QString TensionLimited READ TensionLimited WRITE setTensionLimited NOTIFY TensionLimitedChanged)

    //MaxTensionIncrement  极限张力增量
    Q_PROPERTY(QString TensionLimitedDelta READ TensionLimitedDelta WRITE setTensionLimitedDelta NOTIFY TensionLimitedDeltaChanged )


public:
    enum FORCE_UNIT
    {
        LB = 0,
        KG,
        KN
    };
public:
    static TensionSetting* GetInstance();
    virtual ~TensionSetting();

    Q_INVOKABLE int TensionUnit() const;
    Q_INVOKABLE void setTensionUnit(int unit);
    Q_INVOKABLE QString KValue() const;
    Q_INVOKABLE void setKValue(const QString &value);
    Q_INVOKABLE QString TensionLimited() const;
    Q_INVOKABLE void setTensionLimited(const QString &value);
    Q_INVOKABLE QString TensionLimitedDelta() const;
    Q_INVOKABLE void setTensionLimitedDelta(const QString &value);
private:
    int m_TensionUnit;
    QString m_KValue;
    QString m_TensionLimited;
    QString m_TensionLimitedDelta;
private:
    static TensionSetting* _ptrTensionSetting;
    explicit TensionSetting(QObject *parent = nullptr);

signals:
    void TensionUnitChanged(int Unit);
    void KValueChanged();
    void TensionLimitedChanged();
    void TensionLimitedDeltaChanged();
};

#endif // TENSIONSETTING_H
