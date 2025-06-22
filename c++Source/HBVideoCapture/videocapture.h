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
    QString m_ImagePath;
    static VideoCapture* _ptrVideoCapture;
public:
    static VideoCapture* GetInstance();
    Q_INVOKABLE bool    detectFaceImage();
    Q_INVOKABLE bool    generateFaceEigenValue();
    Q_INVOKABLE QString getImageDirectory();
protected:
    explicit VideoCapture(QQuickItem *parent = nullptr);
signals:

private slots:

};

#endif // VIDEOCAPTURE_H
