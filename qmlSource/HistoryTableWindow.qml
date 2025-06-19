import QtQuick.Controls 1.4
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.HistoryDataTable 1.0
import HB.Database 1.0

Item{
    readonly property int textWidth: 100
    readonly property int comboBoxWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 20
    readonly property int componentHeight: 30

    HBCalendar{
        id: calendarDate
        anchors.centerIn: parent
        width: Math.round(400 * Style.scaleHint)
        height: Math.round(250 * Style.scaleHint)
        z: 5
        visible: false
        onSelectedDateChanged: {
            console.debug("selected Date: ", selectedDate)
        }
    }

    DataTableModel {
        id: historyDataModel
    }

    Component.onCompleted:
    {
        headerModel.resetModel()

        var startStamp = comboBoxStartTimeStamp.text + "T00:00:00"
        var endStamp   = comboBoxFinishTimeStamp.text + "T23:59:59"
        historyDataModel.loadFromDatabase(startStamp, endStamp)
    }

    Rectangle
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
    HBGroupBox
    {
        id: info
        title: qsTr("信息")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 3 - Math.round(40 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor
        Grid
        {
            id: argumentLayout
            columns: 2
            rows: 2
            columnSpacing: Math.round(80 * Style.scaleHint)
            rowSpacing: Math.round(10 * Style.scaleHint)
            width: Math.round((textWidth + rowSpacing + comboBoxWidth) * 2 * Style.scaleHint) + argumentLayout.columnSpacing
            height: Math.round((componentHeight * 2) * Style.scaleHint) + argumentLayout.rowSpacing
            anchors.left: parent.left
            anchors.leftMargin: Math.round(20 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((textWidth + rowSpacing + comboBoxWidth) * Style.scaleHint)
                Text {
                    id: titleStartTimeStamp
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("开始时间") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBoxCalendar
                {
                    id: comboBoxStartTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    text: {
                        var now = new Date()
                        var yesterday = new Date(now.getTime() - 24 * 60 * 60 * 1000)
                        return Qt.formatDate(yesterday, "yyyy-MM-dd")
                    }

                    onSignalPopUp:
                    {
                        if(isShow === true)
                            calendarDate.visible = true
                        else
                        {
                            calendarDate.visible = false
                            comboBoxStartTimeStamp.text = Qt.formatDate(calendarDate.selectedDate, "yyyy-MM-dd")
                        }
                    }
                }
            }

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((textWidth + rowSpacing + comboBoxWidth) * Style.scaleHint)
                Text {
                    id: titleFinishTimeStamp
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("结束时间") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }

                HBComboBoxCalendar
                {
                    id: comboBoxFinishTimeStamp
                    width: Math.round(comboBoxWidth * Style.scaleHint)
                    height: parent.height
                    text: {
                        var now = new Date()
                        return Qt.formatDate(now, "yyyy-MM-dd")
                    }
                    onSignalPopUp:
                    {
                        if(isShow === true)
                            calendarDate.visible = true
                        else
                        {
                            calendarDate.visible = false
                            comboBoxFinishTimeStamp.text = Qt.formatDate(calendarDate.selectedDate, "yyyy-MM-dd")
                        }
                    }
                }
            }

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((buttonWidth + rowSpacing + buttonWidth) * Style.scaleHint)
                HBPrimaryButton
                {
                    id: buttonInquire
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("查询")
                    onClicked:
                    {
                        var startStamp = comboBoxStartTimeStamp.text + "T00:00:00"
                        var endStamp   = comboBoxFinishTimeStamp.text + "T23:59:59"
                        historyDataModel.loadFromDatabase(startStamp, endStamp)
                        console.log("startStamp: ", startStamp,"endStamp: ", endStamp)
                    }
                }

                HBPrimaryButton
                {
                    id: buttonExport
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("导出")
                    onClicked:
                    {
                        historyDataModel.exportData()
                    }
                }
            }
        }
    }

    ListModel
    {
        id: headerModel
        function resetModel()
        {
            headerModel.clear()
            headerModel.append({"role": "Index",                "title": qsTr("序号"),      "headerWidth": 50})
            headerModel.append({"role": "WellNumber",           "title": qsTr("井号"),      "headerWidth": 100})
            headerModel.append({"role": "Date",                 "title": qsTr("日期"),      "headerWidth": 200})
            headerModel.append({"role": "OperateType",          "title": qsTr("操作类型"),  "headerWidth": 100})
            headerModel.append({"role": "Operater",             "title": qsTr("操作员"),    "headerWidth": 100})
            headerModel.append({"role": "Depth",                "title": qsTr("深度"),      "headerWidth": 100})
            headerModel.append({"role": "Velocity",             "title": qsTr("速度"),      "headerWidth": 100})
            headerModel.append({"role": "VelocityUnit",         "title": qsTr("速度单位"),  "headerWidth": 100})
            headerModel.append({"role": "Tensions",             "title": qsTr("张力"),      "headerWidth": 100})
            headerModel.append({"role": "TensionIncreament",    "title": qsTr("张力增量"),  "headerWidth": 100})
            headerModel.append({"role": "TensionUnit",          "title": qsTr("张力单位"),  "headerWidth": 100})
            headerModel.append({"role": "MaxTension",           "title": qsTr("最大张力"),  "headerWidth": 100})
            headerModel.append({"role": "HarnessTension",       "title": qsTr("缆头张力"),  "headerWidth": 100})
            headerModel.append({"role": "SafetyTension",        "title": qsTr("安全张力"),  "headerWidth": 100})


        }

    }

    HBTableView {
        id: gridParentFrame
        anchors.left: info.left
        anchors.right: info.right
        anchors.top: info.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        model: historyDataModel

        fontSize: Math.round(Style.style0 * Style.scaleHint)
        rowHeight: Math.round(25 * Style.scaleHint)
        itemDelegate: Rectangle {
            height: gridParentFrame.rowHeight
            width: styleData.columnWidth
            color: styleData.column === 0 ? Style.backgroundLightColor : "0x000000"
            border.color: Style.hbFrameBorderColor
            Text {
                anchors.centerIn: parent
                color: Style.whiteFontColor
                //                text: styleData.value
                text: styleData.column === 0 ? (styleData.row + 1) : styleData.value
                font.family: "宋体"
                font.pixelSize: gridParentFrame.fontSize
            }
        }
        rowDelegate: Rectangle{
            height: gridParentFrame.rowHeight
        }

        TableViewColumn { role: "Index";                title: qsTr("");            width: 30}
        TableViewColumn { role: "WellNumber";           title: qsTr("井号");        width: 100}
        TableViewColumn { role: "Date";                 title: qsTr("日期");        width: 100}
        TableViewColumn { role: "OperateType";          title: qsTr("操作类型");    width: 80}
        TableViewColumn { role: "Operater";             title: qsTr("操作员");      width: 80}
        TableViewColumn { role: "Depth";                title: qsTr("深度");        width: 80}
        TableViewColumn { role: "Velocity";             title: qsTr("速度");        width: 80}
        TableViewColumn { role: "VelocityUnit";         title: qsTr("速度单位");    width: 80}
        TableViewColumn { role: "Tensions";             title: qsTr("张力");        width: 80}
        TableViewColumn { role: "TensionIncreament";    title: qsTr("张力增量");    width: 80}
        TableViewColumn { role: "TensionUnit";          title: qsTr("张力单位");    width: 80}
        TableViewColumn { role: "MaxTension";           title: qsTr("最大张力");    width: 80}
        TableViewColumn { role: "HarnessTension";       title: qsTr("缆头张力");    width: 80}
        TableViewColumn { role: "SafetyTension";        title: qsTr("安全张力");    width: 80}
        TableViewColumn { role: "Exception";            title: qsTr("异常数据标识");  width: 100}
    }
}


