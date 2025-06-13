#ifndef TENSIOMETER_H
#define TENSIOMETER_H

#include <QObject>

class Tensiometer : public QObject
{
    Q_OBJECT

    //Tensiometer number
    Q_PROPERTY(QString TensiometerNumber READ TensiometerNumber WRITE setTensiometerNumber NOTIFY TensiometerNumberChanged)

    //Tensiometer Type
    Q_PROPERTY(int TensiometerEncoder READ TensiometerEncoder WRITE setTensiometerEncoder NOTIFY TensiometerEncoderChanged)

    //Tesiometer range
    Q_PROPERTY(int TensiometerRange READ TensiometerRange WRITE setTensiometerRange NOTIFY TensiometerRangeChanged)

    //Tension output signal
    Q_PROPERTY(int TensiometerAnalog READ TensiometerAnalog WRITE setTensiometerAnalog NOTIFY TensiometerAnalogChanged)

    //Scale
    Q_PROPERTY(QString ScaleCurrent READ ScaleCurrent WRITE setScaleCurrent NOTIFY ScaleCurrentChanged)
    Q_PROPERTY(QString Point1Scale READ Point1Scale WRITE setPoint1Scale NOTIFY Point1ScaleChanged)
    Q_PROPERTY(QString Point2Scale READ Point2Scale WRITE setPoint2Scale NOTIFY Point2ScaleChanged)
    Q_PROPERTY(QString Point3Scale READ Point3Scale WRITE setPoint3Scale NOTIFY Point3ScaleChanged)
    Q_PROPERTY(QString Point4Scale READ Point4Scale WRITE setPoint4Scale NOTIFY Point4ScaleChanged)
    Q_PROPERTY(QString Point5Scale READ Point5Scale WRITE setPoint5Scale NOTIFY Point5ScaleChanged)
    //Tension
    Q_PROPERTY(QString Point1Tension READ Point1Tension WRITE setPoint1Tension NOTIFY Point1TensionChanged)
    Q_PROPERTY(QString Point2Tension READ Point2Tension WRITE setPoint2Tension NOTIFY Point2TensionChanged)
    Q_PROPERTY(QString Point3Tension READ Point3Tension WRITE setPoint3Tension NOTIFY Point3TensionChanged)
    Q_PROPERTY(QString Point4Tension READ Point4Tension WRITE setPoint4Tension NOTIFY Point4TensionChanged)
    Q_PROPERTY(QString Point5Tension READ Point5Tension WRITE setPoint5Tension NOTIFY Point5TensionChanged)

public:
    struct TENSIONMETER
    {
        int Number;
        int Encoder;           //0 数字无线  1 数字有线   2 模拟有线
        int Range;          //0 10T      1 15T       2 20T           3  30T
        int Analog;         //0 无       1 30mV      2 0-1.5V 3      3 0-5V
        QString Scale;      //Json format
    };

    static Tensiometer* GetInstance();
    Q_INVOKABLE QString TensiometerNumber() const;
    Q_INVOKABLE void setTensiometerNumber(const QString number);
    Q_INVOKABLE int TensiometerEncoder() const;
    Q_INVOKABLE void setTensiometerEncoder(const int encoder);
    Q_INVOKABLE int TensiometerRange() const;
    Q_INVOKABLE void setTensiometerRange(const int range);
    Q_INVOKABLE int TensiometerAnalog() const;
    Q_INVOKABLE void setTensiometerAnalog(const int analog);

    //Scale
    Q_INVOKABLE QString ScaleCurrent() const;
    Q_INVOKABLE void setScaleCurrent(const QString scale);
    Q_INVOKABLE QString Point1Scale() const;
    Q_INVOKABLE void setPoint1Scale(const QString scale);
    Q_INVOKABLE QString Point2Scale() const;
    Q_INVOKABLE void setPoint2Scale(const QString scale);
    Q_INVOKABLE QString Point3Scale() const;
    Q_INVOKABLE void setPoint3Scale(const QString scale);
    Q_INVOKABLE QString Point4Scale() const;
    Q_INVOKABLE void setPoint4Scale(const QString scale);
    Q_INVOKABLE QString Point5Scale() const;
    Q_INVOKABLE void setPoint5Scale(const QString scale);
    Q_INVOKABLE QString Point1Tension() const;
    Q_INVOKABLE void setPoint1Tension(const QString tension);
    Q_INVOKABLE QString Point2Tension() const;
    Q_INVOKABLE void setPoint2Tension(const QString tension);
    Q_INVOKABLE QString Point3Tension() const;
    Q_INVOKABLE void setPoint3Tension(const QString tension);
    Q_INVOKABLE QString Point4Tension() const;
    Q_INVOKABLE void setPoint4Tension(const QString tension);
    Q_INVOKABLE QString Point5Tension() const;
    Q_INVOKABLE void setPoint5Tension(const QString tension);


signals:
    void TensiometerNumberChanged();
    void TensiometerEncoderChanged();
    void TensiometerRangeChanged();
    void TensiometerAnalogChanged();

    void ScaleCurrentChanged();
    void Point1ScaleChanged();
    void Point2ScaleChanged();
    void Point3ScaleChanged();
    void Point4ScaleChanged();
    void Point5ScaleChanged();

    void Point1TensionChanged();
    void Point2TensionChanged();
    void Point3TensionChanged();
    void Point4TensionChanged();
    void Point5TensionChanged();

private:
    explicit Tensiometer(QObject *parent = nullptr);
    Tensiometer(const Tensiometer&) = delete;              // 禁止拷贝
    Tensiometer& operator=(const Tensiometer&) = delete;   // 禁止赋值
    static Tensiometer* _ptrTensiometer;

private:
    QString m_TensiometerNumber;
    int m_TensiometerEncoder;
    int m_TensiometerRange;
    int m_TensiometerAnalog;

    QString m_Point1Tension;
    QString m_Point2Tension;
    QString m_Point3Tension;
    QString m_Point4Tension;
    QString m_Point5Tension;
    QString m_ScaleCurrent;
    QString m_Point1Scale;
    QString m_Point2Scale;
    QString m_Point3Scale;
    QString m_Point4Scale;
    QString m_Point5Scale;
};

#endif // TENSIOMETER_H
