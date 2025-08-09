#ifndef EXPORTWORKER_H
#define EXPORTWORKER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QProcess>
class ExportWorker : public QObject
{
    Q_OBJECT
protected:
    QStringList m_LocalFiles;
    QString m_USBDirectory;
    bool GetTargetDirectory(const QString localDirectory, QString& targetDirectory);
    bool DeleteLocalCSVFiles();
public:
    explicit ExportWorker(QObject *parent = nullptr);
public slots:
    virtual void exportToFile() = 0;

signals:
    void exportFinished(bool success, const QString &message);
    void exportPrograss(int current, int total);
};

#endif // EXPORTWORKER_H
