#ifndef PDFEXPORTWORKER_H
#define PDFEXPORTWORKER_H

#include <QObject>
#include "exportworker.h"
class PDFExportWorker : public ExportWorker
{
    Q_OBJECT
private:
    bool ExportToPDF(const QString localDirectory, const QString targetDirectory);
public:
    explicit PDFExportWorker(const QStringList &localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // PDFEXPORTWORKER_H
