import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    property int qmlscreenIndicator:  UIScreenEnum.HB_HISTORY_DATA

    Component.onCompleted:
    {
        historyDataModel.resetModel()
    }

    QtObject {
        id: historyScreenIndex
        readonly property int graph:   0
        readonly property int table:   1
        readonly property int records:  2
    }

    function updateTabBar(index)
    {
        screenLoader.source = ""
        switch(index)
        {
        case historyScreenIndex.graph:
            screenLoader.source = "qrc:/qmlSource/HistoryGraphWindow.qml"
            break;
        case historyScreenIndex.table:
            screenLoader.source = "qrc:/qmlSource/HistoryTableWindow.qml"
            break;
        case historyScreenIndex.records:
            screenLoader.source = "qrc:/qmlSource/HistoryRecordsWindow.qml"
            break;
        default:
            break;
        }
    }

    ListModel {
        id: historyDataModel
        function resetModel()
        {
            historyDataModel.clear()
            historyDataModel.append({"Title":      "历史数据图",
                                     "Width":      100,
                                     "Index":      historyScreenIndex.graph})
            historyDataModel.append({"Title":      "历史数据表",
                                     "Width":      100,
                                     "Index":      historyScreenIndex.table})
            historyDataModel.append({"Title":      "操作记录",
                                     "Width":      100,
                                     "Index":      historyScreenIndex.records})

        }
    }


    TabBar {
        id: historyTabBar
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: Math.round(30 * Style.scaleHint)
        spacing: 20
        background: Image {
            source: "qrc:/images/bg1.png"
            anchors.fill: parent
            smooth: true
        }

        Repeater {
            id: tabbtn
            model: historyDataModel
            delegate: HBTabButton {
                anchors.top: parent.top
                width: Math.round(model.Width * Style.scaleHint)
                height: parent.height
                tabbtnText: model.Title
                onClicked: {
                    updateTabBar(model.Index)
                }
            }
        }
    }

    Loader{
        id: screenLoader
        width: parent.width
        anchors.top: historyTabBar.bottom
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        source:  "qrc:/qmlSource/HistoryGraphWindow.qml"
    }
}


