#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QTimer>

class VideoCapture : public QObject
{
    Q_OBJECT
private:
    struct COMPARE_RESULT
    {
        int Errno;
        QString Msg;
        QString FaceToken;
        int ComparedUserCount;
        QString GroupID;
        double Score;
        QString UserID;
    };
    QString m_ImagePath;
    COMPARE_RESULT m_ComparedResult;
    QStringList m_UserIDList;
    static VideoCapture* _ptrVideoCapture;

    bool ParseComparedLog(const QString &log);
    bool ParseUserListLog(const QString &log);
    void RunCommand(const QString cmd, const QStringList arguments);
public:
    static VideoCapture* GetInstance();
    Q_INVOKABLE bool    detectFaceImage();
    Q_INVOKABLE bool    generateFaceEigenValue(QString username_password);
    Q_INVOKABLE bool    deleteFaceRecord(QString username_password);
    Q_INVOKABLE bool    getUsersList();
    Q_INVOKABLE QString getImageDirectory();

protected:
    explicit VideoCapture(QQuickItem *parent = nullptr);
signals:

private slots:

};

#endif // VIDEOCAPTURE_H
