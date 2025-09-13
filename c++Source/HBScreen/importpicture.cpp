#include "importpicture.h"

ImportPicture::ImportPicture(QObject *parent)
    : QObject{parent}
{}

ImportPicture::ImportPicture(QString pictureFile, QString directory)
{
    m_PictureFile = pictureFile;
    m_USBDirectory = directory;
}

void ImportPicture::importToFile()
{
    // Implementation of the import logic goes here
}
