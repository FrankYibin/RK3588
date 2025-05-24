#ifndef VIDEOCAPTUREITEM_H
#define VIDEOCAPTUREITEM_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QTimer>
#include <opencv2/opencv.hpp>

class VideoCaptureItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int videoWidth READ videoWidth WRITE setVideoWidth NOTIFY videoWidthChanged)
    Q_PROPERTY(int videoHeight READ videoHeight WRITE setVideoHeight NOTIFY videoHeightChanged)
private:
    cv::VideoCapture capture;
    QImage currentFrame;
    static QTimer *_timer;
    int m_videoWidth;
    int m_videoHeight;
public:
    explicit VideoCaptureItem(QQuickItem *parent = nullptr);
    virtual void paint(QPainter *painter) override;
    void stopCapture();
signals:
    void videoWidthChanged();
    void videoHeightChanged();
private slots:
    void updateFrame();
    int videoWidth() const;
    void setVideoWidth(const int width);
    int videoHeight() const;
    void setVideoHeight(const int height);

};

#endif // VIDEOCAPTUREITEM_H
