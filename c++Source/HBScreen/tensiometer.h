#ifndef TENSIOMETER_H
#define TENSIOMETER_H

#include <QObject>

class Tensiometer : public QObject
{
    Q_OBJECT

    //Tensiometer number
    Q_PROPERTY(QString TensiometerNumber READ TensiometerNumber WRITE setTensiometerNumber NOTIFY TensiometerNumberChanged)

    //Tensiometer Type
    Q_PROPERTY(int TensiometerType READ TensiometerType WRITE setTensiometerType NOTIFY TensiometerTypeChanged)

    //Tesiometer range
    Q_PROPERTY(int TensiometerRange READ TensiometerRange WRITE setTensiometerRange NOTIFY TensiometerRangeChanged)

    //Tension output signal
    Q_PROPERTY(int TensiometerSignal READ TensiometerSignal WRITE setTensiometerSignal NOTIFY TensiometerSignalChanged)


    //Tension Units  张力单位
    Q_PROPERTY(int TensionUnits READ TensionUnits WRITE setTensionUnits NOTIFY TensionUnitsChanged)


public:
    static Tensiometer* getInstance();


    Q_INVOKABLE QString TensiometerNumber() const;
    Q_INVOKABLE void setTensiometerNumber(const QString &number);

    Q_INVOKABLE int TensiometerType() const;
    Q_INVOKABLE void setTensiometerType(int newTensiometerType);

    Q_INVOKABLE int TensiometerRange() const;
    Q_INVOKABLE void setTensiometerRange(int newTensiometerRange);

    Q_INVOKABLE int TensiometerSignal() const;
    Q_INVOKABLE void setTensiometerSignal(int TensiometerSignal);


    Q_INVOKABLE int TensionUnits() const;
    Q_INVOKABLE void setTensionUnits(int newTensionUnits);


signals:

    void TensiometerNumberChanged();
    void TensiometerTypeChanged();
    void TensiometerRangeChanged();
    void TensiometerSignalChanged();
    void TensionUnitsChanged();

private:
    explicit Tensiometer(QObject *parent = nullptr);

    Tensiometer(const Tensiometer&) = delete;              // 禁止拷贝
    Tensiometer& operator=(const Tensiometer&) = delete;   // 禁止赋值
    static Tensiometer* m_tensiometer;



private:

    QString m_tensiometerNumber;
    int m_tensiometerType;
    int m_tensiometerRange;
    int m_tensiometerSignal;

    int m_tensionUnits = 0;
};

#endif // TENSIOMETER_H
