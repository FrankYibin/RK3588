import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import QtQuick.Controls.Styles 1.4
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    TabView {
        id: tensionMeterFeatures
        anchors.fill: parent
        tabsVisible: false
        style: TabViewStyle {
            frame: Rectangle
            {
                id: background
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                height: parent.height
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Style.backgroundLightColor }
                    GradientStop { position: 1.0; color: Style.backgroundDeepColor }
                }
            }
        }

        Tab{
            TensionsMeterScaleTable {
                anchors.fill: parent
                onSignalCreateTensometer:
                {
                    tensionMeterFeatures.currentIndex = 1
                }
                onSignalViewTensometer:
                {
                    tensionMeterFeatures.currentIndex = 2
                }
                onSignalScaleTensometer:
                {
                    tensionMeterFeatures.currentIndex = 3
                }
            }
        }
        Tab{
            TensionsMeterSettings {
                anchors.fill: parent
                onSignalSaveTensometer:
                {
                    TensiometerManager.addTensiometer();
                    tensionMeterFeatures.currentIndex = 0
                }
            }
        }
        Tab{
            TensionsMeterView {
                anchors.fill: parent
                onSignalReturnTensometer:
                {
                    tensionMeterFeatures.currentIndex = 0
                }
            }
        }
        Tab{
            TensionsMeterScale {
                anchors.fill: parent
                onSignalSaveTensometerScale:
                {
                    tensionMeterFeatures.currentIndex = 0
                }
            }
        }
    }
}


