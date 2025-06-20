#ifndef DATETIME_H
#define DATETIME_H

#include <QObject>

class DateTime : public QObject
{
    Q_OBJECT
public:
    static DateTime* GetInstance();
    Q_INVOKABLE void setSystemDateTime(QString datetime) const;
protected:
    explicit DateTime(QObject *parent = nullptr);
private:
    static DateTime* _ptrDateTime;
signals:
};

#endif // DATETIME_H
