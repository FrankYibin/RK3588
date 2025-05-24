#include "videocaptureitem.h"
#include <QPainter>
#include <QDebug>
QTimer* VideoCaptureItem::_timer = nullptr;
VideoCaptureItem::VideoCaptureItem(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_videoWidth(640), m_videoHeight(480)
{
    // 打开摄像头
    capture.open(0);  // 0 为默认摄像头
    if (!capture.isOpened())
    {
        qWarning("无法打开摄像头");
        return;
    }
    // 设置定时器以更新图像
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &VideoCaptureItem::updateFrame);
    _timer->start(1000);  // 每30ms更新一次画面
}

void VideoCaptureItem::paint(QPainter *painter)
{
    if (!currentFrame.isNull()) {
        painter->drawImage(boundingRect(), currentFrame);
    }
}

void VideoCaptureItem::stopCapture()
{
    if (capture.isOpened()) {
        capture.release();  // 释放摄像头资源
        qDebug("摄像头已释放");
    }
}

void VideoCaptureItem::updateFrame()
{
    cv::Mat frame;
    if (capture.read(frame)) {  // 获取视频帧
        // 旋转图像 90 度
        cv::rotate(frame, frame, cv::ROTATE_90_CLOCKWISE);

        // 将视频帧缩放到标签大小
        cv::resize(frame, frame, cv::Size(m_videoWidth, m_videoHeight));

        // 将帧转换为 RGB 格式
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        // 将 Mat 转为 QImage
        currentFrame = QImage(frame.data, frame.cols, frame.rows, frame.step[0], QImage::Format_RGB888);
        update();  // 触发重绘
    }
}

int VideoCaptureItem::videoWidth() const
{
    return m_videoWidth;
}

void VideoCaptureItem::setVideoWidth(const int width)
{
    if (m_videoWidth != width) {
        m_videoWidth = width;
        emit videoWidthChanged();
    }
}

int VideoCaptureItem::videoHeight() const
{
    return m_videoHeight;
}

void VideoCaptureItem::setVideoHeight(const int height)
{
    if (m_videoHeight != height) {
        m_videoHeight = height;
        emit videoHeightChanged();
    }
}
