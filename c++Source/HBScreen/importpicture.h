#ifndef IMPORTPICTURE_H
#define IMPORTPICTURE_H

#include <QObject>
#include <QMap>

class ImportPicture : public QObject
{
    Q_OBJECT
private:
    QString m_PictureFile;
    QString m_USBDirectory;
    QMap<QString, QString> m_WellInfoList;
    bool parseJson(const QString message, QMap<QString, QString>* _list);
public:
    explicit ImportPicture(QObject *parent = nullptr);
    ImportPicture(QString pictureFile, QString directory);

signals:
    void importFinished(bool success, const QString &message);
    void importPrograss(int current, int total);
public slots:
    void importToFile();
};

#endif // IMPORTPICTURE_H
