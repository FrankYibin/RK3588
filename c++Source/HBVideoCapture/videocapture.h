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
    QImage m_CurrentFrame;
    static VideoCapture* _ptrVideoCapture;
public:
    static VideoCapture* GetInstance();
    Q_INVOKABLE void saveLoginImage(const QString &imageSource);
protected:
    explicit VideoCapture(QQuickItem *parent = nullptr);
signals:

private slots:

};

#endif // VIDEOCAPTURE_H
