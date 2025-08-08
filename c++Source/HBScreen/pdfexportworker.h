#ifndef PDFEXPORTWORKER_H
#define PDFEXPORTWORKER_H

#include <QObject>
#include "exportworker.h"
class PDFExportWorker : public ExportWorker
{
    Q_OBJECT
private:
    bool ExportToPDF();
public:
    explicit PDFExportWorker(const QStringList &localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // PDFEXPORTWORKER_H
