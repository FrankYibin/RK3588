#ifndef CSVEXPORTWORKER_H
#define CSVEXPORTWORKER_H

#include <QObject>
#include "exportworker.h"
class CSVExportWorker : public ExportWorker
{
    Q_OBJECT
private:
    bool ExportToCSV(const QString localDirectory, const QString targetDirectory);
public:
    explicit CSVExportWorker(const QStringList& localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // CSVEXPORTWORKER_H
