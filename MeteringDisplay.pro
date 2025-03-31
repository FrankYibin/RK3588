QT += quick gui charts
CONFIG += c++11
#qtquickcompiler

#CONFIG(debug, debug|release) {
#    BIN_DIR = $$PWD/../build_output/UIController/debug/
#} else {
#    BIN_DIR = $$PWD/../build_output/UIController/release/
#}

#TARGET = UIController
#CONFIG(debug, debug|release) {
#    TARGET = $$member(TARGET, 0)d
#}


DESTDIR = $$BIN_DIR
TEMPLATE = app

static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
        c++Source/alarmnotification.cpp \
        c++Source/clientsocket.cpp \
        c++Source/communicationinterface.cpp \
        c++Source/heartbeatformat.cpp \
        c++Source/jsontreeitem.cpp \
        c++Source/jsontreeitemhash.cpp \
        c++Source/jsontreemodel.cpp \
        c++Source/languageconfig.cpp \
        c++Source/languageitem.cpp \
        c++Source/languagemodel.cpp \
        c++Source/login.cpp \
        c++Source/productionruninterface.cpp \
        c++Source/protocolformat.cpp \
        c++Source/quickcrc32algorithm.cpp \
        c++Source/recipegeneral.cpp \
        c++Source/recipemodel.cpp \
        c++Source/serversocket.cpp \
        c++Source/systemInformationInterface.cpp \
        c++Source/upgradesoftware.cpp \
        c++Source/weldgraphdata.cpp \
        c++Source/weldrecipeparameter.cpp \
        c++Source/weldresultmodel.cpp


HEADERS += \
    c++Source/alarmindexdef.h \
    c++Source/alarmnotification.h \
    c++Source/clientsocket.h \
    c++Source/communicationinterface.h \
    c++Source/definition.h \
    c++Source/graphaxisdef.h \
    c++Source/heartbeatformat.h \
    c++Source/jsontreeitem.h \
    c++Source/jsontreeitemhash.h \
    c++Source/jsontreemodel.h \
    c++Source/languageconfig.h \
    c++Source/languagedef.h \
    c++Source/languageitem.h \
    c++Source/languagemodel.h \
    c++Source/login.h \
    c++Source/logindef.h \
    c++Source/productionruninterface.h \
    c++Source/protocolformat.h \
    c++Source/quickcrc32algorithm.h \
    c++Source/recipedef.h \
    c++Source/recipegeneral.h \
    c++Source/recipemodel.h \
    c++Source/shareDefine.h \
    c++Source/systemInformationInterface.h \
    c++Source/systemTypeDef.h \
    c++Source/serversocket.h \
    c++Source/uiscreendef.h \
    c++Source/upgradesoftware.h \
    c++Source/upgradesoftwaredef.h \
    c++Source/userleveldef.h \
    c++Source/version.h \
    c++Source/weldgraphdata.h \
    c++Source/weldrecipeparameter.h \
    c++Source/weldresultmodel.h

RESOURCES += images.qrc \
            data/VirtualKeyboard.qrc \
            fonts.qrc \
            jsonfile.qrc \
            misc.qrc \
            qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(DEFINES, WIN32){
#    LIBS += -L$$PWD/../Win32Path/ -lxxx
#    INCLUDEPATH += $$PWD/../Win32Path
#    DEPENDPATH += $$PWD/../Win32Path
#    PRE_TARGETDEPS += $$PWD/../Win32Path/libxxx.a
}

contains(DEFINES, linux){
    contains(DEFINES, RASPBERRY){
#       LIBS += -L$$PWD/../RaspberryPath/ -lxxx
#       INCLUDEPATH += $$PWD/../RaspberryPath
#       DEPENDPATH += $$PWD/../RaspberryPath
#       PRE_TARGETDEPS += $$PWD/../RaspberryPath/libxxx.a
    }
    else
    {
#        LIBS += -L$$PWD/../linuxPath/ -lxxx
#        INCLUDEPATH += $$PWD/../linuxPath
#        DEPENDPATH += $$PWD/../linuxPath
#        PRE_TARGETDEPS += $$PWD/../linuxPath/libxxx.a
    }
}

DEFINES += COMMUNICATION_TEST
DEFINES += RASPBERRY
DEFINES += SYSTEMINFODATA

DISTFILES +=




