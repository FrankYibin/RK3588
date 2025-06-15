#include "usermanual.h"
  #include <QCoreApplication>
UserManual* UserManual::_ptrUserManual = nullptr;
UserManual::UserManual(QObject *parent)
    : QObject{parent}
{}

UserManual *UserManual::GetInstance()
{
    if(_ptrUserManual == nullptr)
    {
        _ptrUserManual = new UserManual();
    }
    return _ptrUserManual;
}

QString UserManual::getUserManualByPDFJS()
{
    QString installPath = QCoreApplication::applicationDirPath();
    QString viewerPath = "file:///" + installPath + "/usermanual/pdfjs/web/viewer.html";
    QString filePath = "file:///" + installPath + "/usermanual/manual.pdf";
    QString path = viewerPath + "?file=" + filePath;
    return path;
}
