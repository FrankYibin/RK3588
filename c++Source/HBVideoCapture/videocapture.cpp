#include "videocapture.h"
#include <QPainter>
#include <QDir>
#include <QDebug>
VideoCapture* VideoCapture::_ptrVideoCapture = nullptr;
VideoCapture *VideoCapture::GetInstance()
{
    if(_ptrVideoCapture == nullptr)
        _ptrVideoCapture = new VideoCapture();
    return _ptrVideoCapture;
}

void VideoCapture::saveLoginImage(const QString &imageSource)
{
    // QString filePath = QDir::homePath() + "/" + "tmp.jpg"; // 保存到用户主目录
    // 如果是 image:// 类型，处理相应的逻辑
    if (imageSource.startsWith("image://")) {
        // 这里可以根据你的应用程序逻辑处理 image:// 类型
        // 例如，调用 QQuickImageProvider 来获取图像
        // 但通常 image:// 资源是实时的，不能直接保存

        // 你可能需要将图像转换为 QImage
        // 这通常需要一个 QQuickImageProvider
        qWarning() << "无法直接从 image:// 源保存图片";
        return;
    }

    // 将 QUrl 转换为文件路径
    QUrl url(imageSource);
    QString filePath = url.toLocalFile(); // 获取本地文件路径

    // 加载图片
    QImage image(filePath);
    if (image.isNull()) {
        qWarning() << "无法加载图片:" << filePath;
        return;
    }

    // 保存为 JPEG 格式
    QString savePath = "saved_image.jpg"; // 你想要保存的路径
    if (image.save(savePath, "JPEG")) {
        qDebug() << "图片已保存为:" << savePath;
    } else {
        qWarning() << "保存图片失败";
    }
}

VideoCapture::VideoCapture(QQuickItem *parent)
    : QObject(parent)
{

}
