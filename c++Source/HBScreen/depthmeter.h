#ifndef DEPTHMETER_H
#define DEPTHMETER_H

#include <QObject>

class DepthMeter : public QObject
{
    Q_OBJECT

    //深度预设
    Q_PROPERTY(int DepthPreset READ DepthPreset WRITE setDepthPreset NOTIFY DepthPresetChanged)

   //当前深度
    Q_PROPERTY(int CurrentDepth READ CurrentDepth WRITE setCurrentDepth NOTIFY CurrentDepthChanged)

public:

    static DepthMeter* getInstance();

    Q_INVOKABLE int DepthPreset() const;

    Q_INVOKABLE void setDepthPreset(int newDepthPreset);

    Q_INVOKABLE int CurrentDepth() const;

    Q_INVOKABLE void setCurrentDepth(int newDepthPreset);

private:
     explicit DepthMeter(QObject *parent = nullptr);

    DepthMeter(const DepthMeter&) = delete;
    DepthMeter& operator=(const DepthMeter&) = delete;
    static DepthMeter* m_depthMeter;

signals:

    void DepthPresetChanged();

    void CurrentDepthChanged();



private:

    int m_depthPreset;
    int m_currentDepth;
};

#endif // DEPTHMETER_H
