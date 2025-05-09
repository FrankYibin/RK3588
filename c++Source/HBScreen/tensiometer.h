#ifndef TENSIOMETER_H
#define TENSIOMETER_H

#include <QObject>

class Tensiometer : public QObject
{
    Q_OBJECT

    //Tensiometer number
    Q_PROPERTY(QString TensiometerNumber READ TensiometerNumber WRITE setTensiometerNumber NOTIFY TensiometerNumberChanged);

    //Tensiometer Type
    Q_PROPERTY(int TensiometerType READ TensiometerType WRITE setTensiometerType NOTIFY TensiometerTypeChanged);

    //Tesiometer range
    Q_PROPERTY(int TensiometerRange READ TensiometerRange WRITE setTensiometerRange NOTIFY TensiometerRangeChanged);

    //Tension output signal
    Q_PROPERTY(int TensionSignal READ TensionSignal WRITE setTensionSignal NOTIFY TensionSignalChanged);


    //Tension Unit
    Q_PROPERTY(int TensionUnit READ TensionUnit WRITE setTensionUnit NOTIFY TensionUnitChanged);


public:
    static Tensiometer* getInstance();


    Q_INVOKABLE QString TensiometerNumber() const;
    Q_INVOKABLE void setTensiometerNumber(const QString &number);

    Q_INVOKABLE int TensiometerType() const;
    Q_INVOKABLE void setTensiometerType(int type);

    Q_INVOKABLE int TensiometerRange() const;
    Q_INVOKABLE void setTensiometerRange(int range);

    Q_INVOKABLE int TensionSignal() const;
    Q_INVOKABLE void setTensionSignal(int signal);


    Q_INVOKABLE int TensionUnit() const;
    Q_INVOKABLE void setTensionUnit(int signal);


signals:

    void TensiometerNumberChanged();
    void TensiometerTypeChanged();
    void TensiometerRangeChanged();
    void TensionSignalChanged();
    void TensionUnitChanged();

private:
    explicit Tensiometer(QObject *parent = nullptr);

    Tensiometer(const Tensiometer&) = delete;              // 禁止拷贝
    Tensiometer& operator=(const Tensiometer&) = delete;   // 禁止赋值
    static Tensiometer* m_tensiometer;



private:

    QString m_tensiometerNumber;
    int m_tensiometerType;
    int m_tensiometerRange;
    int m_tensionSignal;

    int m_tensionUnit;
};

#endif // TENSIOMETER_H
