#ifndef HBHOME_H
#define HBHOME_H

#include <QObject>

class HBHome : public QObject
{
    Q_OBJECT

    //depth        深度
    Q_PROPERTY(QString DepthCurrent READ DepthCurrent WRITE setDepthCurrent NOTIFY DepthCurrentChanged)

    //speed        速度
    Q_PROPERTY(QString VelocityCurrent READ VelocityCurrent WRITE setVelocityCurrent NOTIFY VelocityCurrentChanged)

    //tension      张力
    Q_PROPERTY(QString TensionCurrent READ TensionCurrent WRITE setTensionCurrent NOTIFY TensionCurrentChanged)

    //tensionIncrement  张力增量
    Q_PROPERTY(QString TensionCurrentDelta READ TensionCurrentDelta WRITE setTensionCurrentDelta NOTIFY TensionCurrentDeltaChanged)

    //pulse count  脉冲数
    Q_PROPERTY(QString PulseCount READ PulseCount WRITE setPulseCount NOTIFY PulseCountChanged)

    //MaxTension 极限张力
    Q_PROPERTY(QString TensionLimited READ TensionLimited WRITE setTensionLimited NOTIFY TensionLimitedChanged)

    //TargetDepth   目的深度
    Q_PROPERTY(QString DepthTargetLayer READ DepthTargetLayer WRITE setDepthTargetLayer NOTIFY DepthTargetLayerChanged)

    //MaxSpeed    极限速度
    Q_PROPERTY(QString VelocityLimited READ VelocityLimited WRITE setVelocityLimited NOTIFY VelocityLimitedChanged)

    //MaxTensionIncrement  极限张力增量
    Q_PROPERTY(QString TensionLimitedDelta READ TensionLimitedDelta WRITE setTensionLimitedDelta NOTIFY TensionLimitedDeltaChanged )

    //K_Value           k值
    Q_PROPERTY(QString KValue READ KValue WRITE setKValue NOTIFY KValueChanged )

    //HarnessTension  缆头张力
    Q_PROPERTY(QString TensionCableHead READ TensionCableHead WRITE setTensionCableHead NOTIFY TensionCableHeadChanged )

    //MaxParameterStatus  极限参数状态
    Q_PROPERTY(int StatusLimitedPara READ StatusLimitedPara WRITE setStatusLimitedPara NOTIFY StatusLimitedParaChanged)

    //NetworkStatus   网络状态
    Q_PROPERTY(int StatusNetwork READ StatusNetwork WRITE setStatusNetwork NOTIFY StatusNetworkChanged)

public:

    static HBHome* GetInstance();

    Q_INVOKABLE QString DepthCurrent() const;
    Q_INVOKABLE void setDepthCurrent(const QString value);

    Q_INVOKABLE QString VelocityCurrent() const;
    Q_INVOKABLE void setVelocityCurrent(const QString value);

    Q_INVOKABLE QString TensionCurrent() const;
    Q_INVOKABLE void setTensionCurrent(const QString value);

    Q_INVOKABLE QString TensionCurrentDelta() const;
    Q_INVOKABLE void setTensionCurrentDelta(const QString value);

    Q_INVOKABLE QString PulseCount() const;
    Q_INVOKABLE void setPulseCount(const QString value);

    Q_INVOKABLE QString TensionLimited() const;
    Q_INVOKABLE void setTensionLimited(const QString value);

    Q_INVOKABLE QString DepthTargetLayer() const;
    Q_INVOKABLE void setDepthTargetLayer(const QString value);

    Q_INVOKABLE QString VelocityLimited() const;
    Q_INVOKABLE void setVelocityLimited(const QString value);

    Q_INVOKABLE QString TensionLimitedDelta() const;
    Q_INVOKABLE void setTensionLimitedDelta(const QString value);

    Q_INVOKABLE QString KValue() const;
    Q_INVOKABLE void setKValue(const QString value);

    Q_INVOKABLE QString TensionCableHead() const;
    Q_INVOKABLE void setTensionCableHead(const QString value);

    Q_INVOKABLE int StatusLimitedPara() const;
    Q_INVOKABLE void setStatusLimitedPara(const int status);

    Q_INVOKABLE int StatusNetwork() const;
    Q_INVOKABLE void setStatusNetwork(const int status);



signals:

    void DepthCurrentChanged();

    void VelocityCurrentChanged();

    void TensionCurrentChanged();

    void TensionCurrentDeltaChanged();

    void PulseCountChanged();

    void TensionLimitedChanged();

    void DepthTargetLayerChanged();

    void VelocityLimitedChanged();

    void TensionLimitedDeltaChanged();

    void KValueChanged();

    void TensionCableHeadChanged();

    void StatusLimitedParaChanged();

    void StatusNetworkChanged();

private:
    explicit HBHome(QObject *parent = nullptr);

    HBHome(const HBHome&) = delete;
    HBHome& operator=(const HBHome&) = delete;
    static HBHome* _ptrHome;

private:

    QString m_DepthCurrent;
    QString m_VelocityCurrent;
    QString m_TensionCurrent;
    QString m_TensionCurrentDelta;
    QString m_PulseCount;
    QString m_TensionLimited;
    QString m_DepthTargetLayer;
    QString m_VelocityLimited;
    QString m_TensionLimitedDelta;
    QString m_KValue;
    QString m_TensionCableHead;
    int m_StatusLimitedPara;
    int m_StatusNetwork;

};

#endif // HBHOME_H
