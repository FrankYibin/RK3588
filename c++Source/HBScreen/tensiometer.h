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
    Q_PROPERTY(int TensionUnits READ TensionUnits WRITE setTensionUnits NOTIFY tensionUnitsChanged)

    //Scale
    Q_PROPERTY(int Scale1 READ Scale1 WRITE setScale1 NOTIFY Scale1Changed)

    Q_PROPERTY(int Scale2 READ Scale2 WRITE setScale2 NOTIFY Scale2Changed)
    Q_PROPERTY(int Scale3 READ Scale3 WRITE setScale3 NOTIFY Scale3Changed)
    Q_PROPERTY(int Scale4 READ Scale4 WRITE setScale4 NOTIFY Scale4Changed)
    Q_PROPERTY(int Scale5 READ Scale5 WRITE setScale5 NOTIFY Scale5Changed)


public:
    enum FORCE_UNIT
    {
        LB = 0,
        KG,
        KN
    };
public:
    static Tensiometer* GetInstance();
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

    //Scale
    Q_INVOKABLE int Scale1() const;
    Q_INVOKABLE void setScale1(int newTensiometerType);
    Q_INVOKABLE int Scale2() const;
    Q_INVOKABLE void setScale2(int newTensiometerType);
    Q_INVOKABLE int Scale3() const;
    Q_INVOKABLE void setScale3(int newTensiometerType);
    Q_INVOKABLE int Scale4() const;
    Q_INVOKABLE void setScale4(int newTensiometerType);
    Q_INVOKABLE int Scale5() const;
    Q_INVOKABLE void setScale5(int newTensiometerType);


signals:
    void TensiometerNumberChanged();
    void TensiometerTypeChanged();
    void TensiometerRangeChanged();
    void TensiometerSignalChanged();
    void tensionUnitsChanged();

    void Scale1Changed();
    void Scale2Changed();
    void Scale3Changed();
    void Scale4Changed();
    void Scale5Changed();


private:
    explicit Tensiometer(QObject *parent = nullptr);
    Tensiometer(const Tensiometer&) = delete;              // 禁止拷贝
    Tensiometer& operator=(const Tensiometer&) = delete;   // 禁止赋值
    static Tensiometer* _ptrTensiometer;



private:
    QString m_tensiometerNumber;
    int m_tensiometerType;
    int m_tensiometerRange;
    int m_tensiometerSignal;
    int m_tensionUnits;
    int m_scale1;
    int m_scale2;
    int m_scale3;
    int m_scale4;
    int m_scale5;
};

#endif // TENSIOMETER_H
