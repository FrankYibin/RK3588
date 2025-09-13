#ifndef TEXTEXPORTWORKER_H
#define TEXTEXPORTWORKER_H

#include <QObject>
#include "exportworker.h"
class TextExportWorker : public ExportWorker
{
    Q_OBJECT
private:
    bool ExportToTxt(const QString localDirectory, const QString targetDirectory);
public:
    explicit TextExportWorker(const QStringList &localfiles, const QString USBDirectory);
public slots:
    virtual void exportToFile() override;
};

#endif // TEXTEXPORTWORKER_H
