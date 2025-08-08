#ifndef EXCELEXPORTWORKER_H
#define EXCELEXPORTWORKER_H

#include "exportworker.h"
#include <QObject>

class ExcelExportWorker : public ExportWorker
{
    Q_OBJECT
private:
    bool ExportToXLSX();
public:
    explicit ExcelExportWorker(const QStringList &localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // EXCELEXPORTWORKER_H
