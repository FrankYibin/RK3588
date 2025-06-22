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

bool VideoCapture::detectFaceImage()
{
    return false;
}

bool VideoCapture::generateFaceEigenValue()
{
    return false;
}

QString VideoCapture::getImageDirectory()
{
    return m_ImagePath;
}

VideoCapture::VideoCapture(QQuickItem *parent)
    : QObject(parent)
{
    QString str = QDir::currentPath();
    QDir dir(str);
    if(!dir.exists("image"))
    {
        if(dir.mkdir("image"))
        {
            qDebug() << "image has been created";
        }
        else
        {
            qDebug() << "No way to create image folder";
        }
    }
    else
        qDebug() << "image folde is exist in current path";
    m_ImagePath = str + "/image";
}
