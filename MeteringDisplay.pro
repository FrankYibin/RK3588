QT += quick gui charts serialport serialbus sql multimedia
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
    c++Source/HBData/hbdatabase.cpp \
    c++Source/HBGraph/SensorGraphData.cpp \
    c++Source/HBModbus/hbmodbusclient.cpp \
    c++Source/HBModbus/modbusutils.cpp \
    c++Source/HBScreen/autotestspeed.cpp \
    c++Source/HBScreen/depth.cpp \
    c++Source/HBScreen/depthmeter.cpp \
    c++Source/HBScreen/depthsafe.cpp \
    c++Source/HBScreen/hbhome.cpp \
    c++Source/HBScreen/history.cpp \
    c++Source/HBScreen/network.cpp \
    c++Source/HBScreen/rs232.cpp \
    c++Source/HBScreen/tensiometer.cpp \
    c++Source/HBScreen/tensiometermanager.cpp \
    c++Source/HBScreen/tensionsafe.cpp \
    c++Source/HBScreen/wellparameter.cpp \
#    c++Source/HBVideoCapture/videocaptureitem.cpp \
        c++Source/alarmnotification.cpp \
        c++Source/clientsocket.cpp \
        c++Source/communicationinterface.cpp \
    c++Source/HBVoice/hbvoice.cpp \
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
        c++Source/weldresultmodel.cpp \



HEADERS += \
    c++Source/HBData/hbdatabase.h \
    c++Source/HBDefine.h \
    c++Source/HBGraph/GraphAxisDefineHB.h \
    c++Source/HBGraph/SensorGraphData.h \
    c++Source/HBModbus/hbmodbusclient.h \
    c++Source/HBModbus/modbusutils.h \
    c++Source/HBQmlEnum.h \
    c++Source/HBScreen/autotestspeed.h \
    c++Source/HBScreen/depth.h \
    c++Source/HBScreen/depthmeter.h \
    c++Source/HBScreen/depthsafe.h \
    c++Source/HBScreen/hbhome.h \
    c++Source/HBScreen/history.h \
    c++Source/HBScreen/network.h \
    c++Source/HBScreen/rs232.h \
    c++Source/HBScreen/tensiometer.h \
    c++Source/HBScreen/tensiometermanager.h \
    c++Source/HBScreen/tensionsafe.h \
    c++Source/HBScreen/wellparameter.h \
#    c++Source/HBVideoCapture/videocaptureitem.h \
    c++Source/alarmindexdef.h \
    c++Source/alarmnotification.h \
    c++Source/clientsocket.h \
    c++Source/communicationinterface.h \
    c++Source/definition.h \
    c++Source/graphaxisdef.h \
    c++Source/HBVoice/hbvoice.h \
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
    c++Source/weldresultmodel.h \


RESOURCES += images.qrc \
            data/VirtualKeyboard.qrc \
            fonts.qrc \
            jsonfile.qrc \
            misc.qrc \
            qml.qrc \
            voice.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


contains(DEFINES, RK3588){
#    QMAKE_LFLAGS += -Wl,-rpath, -L$$PWD/../opencv_arm/
#    LIBS += -L$$PWD/../opencv_arm/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lc
#    LIBS += -L$$PWD/../opencv_arm/ -lz -ltbb -lgtk-3 -lgdk-3 -lcairo -lgdk_pixbuf-2.0
#    LIBS += -L$$PWD/../opencv_arm/ -lgobject-2.0 -lopencv_imgcodecs -ldc1394 -lgstbase-1.0 -lgstreamer-1.0 -lgstapp-1.0 -lgstriff-1.0 -lgstpbutils-1.0
#    LIBS += -L$$PWD/../opencv_arm/ -lavcodec -lavformat -lavutil -lswscale -lgphoto2 -lgphoto2_port -lgmodule-2.0 -lpangocairo-1.0 -lXi -lXfixes -lcairo-gobject
#    LIBS += -L$$PWD/../opencv_arm/ -latk-1.0 -latk-bridge-2.0 -lepoxy -lfribidi -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lharfbuzz -lfontconfig -lfreetype
#    LIBS += -L$$PWD/../opencv_arm/ -lXinerama -lXrandr -lXcursor -lXcomposite -lXdamage -lwayland-cursor -lwayland-egl -lwayland-client -lXext
#    LIBS += -L$$PWD/../opencv_arm/ -lrt -lpixman-1 -lpng16 -lxcb-shm -lxcb-render -lXrender -ljpeg
#    LIBS += -L$$PWD/../opencv_arm/ -lgstvideo-1.0 -lgstaudio-1.0 -lgsttag-1.0
#    LIBS += -L$$PWD/../opencv_arm/  -lavcodec  -ltiff
#    LIBS += -L$$PWD/../opencv_arm/   -lavformat -lavutil -lswscale -lgdcmMSFF -lIlmImf-2_5 -lgdcmDSED
#    INCLUDEPATH += $$PWD/../opencv_arm/
#    DEPENDPATH += $$PWD/../opencv_arm
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libc.so.6
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libc_nonshared.a
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libopencv_core.a
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libopencv_imgproc.a
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libopencv_imgcodecs.a
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libopencv_highgui.a
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libopencv_videoio.a
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libz.so.1
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libtbb.so.2
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgtk-3.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgdk-3.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libcairo.so.2
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgdk_pixbuf-2.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgobject-2.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgstbase-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgstreamer-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgstapp-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgstpbutils-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgstvideo-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgstaudio-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libgsttag-1.0.so.0
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/librt.so.1
#    PRE_TARGETDEPS += $$PWD/../opencv_arm/libwebp.so.6

}
else
{
#    LIBS += -L$$PWD/../opencv/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio
#    INCLUDEPATH += $$PWD/../opencv/
#    DEPENDPATH += $$PWD/../opencv
#    PRE_TARGETDEPS += $$PWD/../opencv/libopencv_core.so
#    PRE_TARGETDEPS += $$PWD/../opencv/libopencv_imgproc.so
#    PRE_TARGETDEPS += $$PWD/../opencv/libopencv_highgui.so
#    PRE_TARGETDEPS += $$PWD/../opencv/libopencv_videoio.so
}




