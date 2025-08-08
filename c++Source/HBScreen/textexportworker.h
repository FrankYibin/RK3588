#ifndef TEXTEXPORTWORKER_H
#define TEXTEXPORTWORKER_H

#include <QObject>
#include "exportworker.h"
class TextExportWorker : public ExportWorker
{
    Q_OBJECT
public:
    explicit TextExportWorker(const QStringList &localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // TEXTEXPORTWORKER_H
