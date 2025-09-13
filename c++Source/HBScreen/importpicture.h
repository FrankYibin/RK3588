#ifndef IMPORTPICTURE_H
#define IMPORTPICTURE_H

#include <QObject>

class ImportPicture : public QObject
{
    Q_OBJECT
private:
    QString m_PictureFile;
    QString m_USBDirectory;
public:
    explicit ImportPicture(QObject *parent = nullptr);
    ImportPicture(QString pictureFile, QString directory);

signals:

public slots:
    void importToFile();
};

#endif // IMPORTPICTURE_H
