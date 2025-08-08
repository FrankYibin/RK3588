#ifndef CSVEXPORTWORKER_H
#define CSVEXPORTWORKER_H

#include <QObject>
#include "exportworker.h"
class CSVExportWorker : public ExportWorker
{
    Q_OBJECT
public:
    explicit CSVExportWorker(const QStringList& localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // CSVEXPORTWORKER_H
