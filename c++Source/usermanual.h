#ifndef USERMANUAL_H
#define USERMANUAL_H

#include <QObject>

class UserManual : public QObject
{
    Q_OBJECT
private:
    explicit UserManual(QObject *parent = nullptr);
    static UserManual* _ptrUserManual;

public:
    static UserManual* GetInstance();
    Q_INVOKABLE QString getUserManualByPDFJS();

signals:
};

#endif // USERMANUAL_H
