import QtQuick.Controls 1.4
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Database 1.0
import HistoryGlobalDefine 1.0

Item{
    readonly property int textWidth: 80
    readonly property int comboBoxWidth: 150
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 10
    readonly property int componentHeight: 30
    property bool isUSBAvailable: false

    Connections {
        target: HistoryDataTable
        function signalExportCompleted(success, message)
        {
            if(success === true)
                mainWindow.showDialogScreen(qsTr("导出数据已完成"), Dialog.Ok, null)
            else
                mainWindow.showDialogScreen(qsTr("没有找到可以使用的U盘或尝试再次导出"), Dialog.Ok, null)
        }
    }

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

    Component.onCompleted:
    {
        headerModel.resetModel()

        var startStamp = comboBoxStartTimeStamp.text + "T00:00:00"
        var endStamp   = comboBoxFinishTimeStamp.text + "T23:59:59"
//        HistoryDataTable.loadFromDatabase(startStamp, endStamp)
        HistoryDataTable.setRange(startStamp,endStamp)
        timer.start()
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

    Timer
    {
        id: timer
        interval: 2000  // 设置间隔为 1000 毫秒 (1 秒)
        repeat: true    // 设置为重复计时器
        onTriggered:
        {
            isUSBAvailable = HistoryDataTable.isAvailaleDiskUSB()
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
            columnSpacing: Math.round(50 * Style.scaleHint)
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
                width: Math.round((textWidth + rowSpacing + 2 * buttonWidth) * Style.scaleHint)
                Text {
                    id: inquireCondition
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("查询条件") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                }
                HBComboBox
                {
                    id: alarmType
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    currentIndex: 0
                    model: HistoryGlobalDefine.exceptionType
                }
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

                        var UserCurrentUserName = UserModel.CurrentUser
                        HistoryDataTable.loadFromDatabase(startStamp, endStamp, UserCurrentUserName, alarmType.currentIndex)
                        console.log("startStamp: ", startStamp, "endStamp: ", endStamp)
                        console.log("selectedValue111111111111111111111111",selectedValue)

                    }
                }
            }

            Row{
                spacing: Math.round(rowSpacing * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                width: Math.round((textWidth + rowSpacing + 2 * buttonWidth) * Style.scaleHint)
                Text {
                    id: fileTitle
                    width: Math.round(textWidth * Style.scaleHint)
                    height: parent.height
                    text: qsTr("文件格式") + ":"
                    font.family: "宋体"
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    verticalAlignment: Text.AlignVCenter
                    color: Style.whiteFontColor
                    visible: (UserModel.GroupIndex > 0) ? false : true
                }
                HBComboBox
                {
                    id: fileFormat
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    currentIndex: 0
                    model: HistoryGlobalDefine.fileType
                    visible: (UserModel.GroupIndex > 0) ? false : true
                }

                HBPrimaryButton
                {
                    id: buttonExport
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("导出")
                    enabled: isUSBAvailable
                    visible: (UserModel.GroupIndex > 0) ? false : true
                    onClicked:
                    {
                        mainWindow.showLoading(true)
                        HistoryDataTable.exportData(fileFormat.currentIndex)
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
            headerModel.append({"role": "Date",                 "title": qsTr("时间"),      "headerWidth": 300})
            headerModel.append({"role": "OperateType",          "title": qsTr("工种"),  "headerWidth": 100})
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
        model: HistoryDataTable

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
        TableViewColumn { role: "Date";                 title: qsTr("时间");        width: 200}
        TableViewColumn { role: "OperateType";          title: qsTr("工种");    width: 80}
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

    Item {
        id: txtInfo
        width: Math.round(buttonWidth * Style.scaleHint)
        height: Math.round(componentHeight * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        anchors.bottomMargin: Math.round(-20 * Style.scaleHint)
        anchors.top: gridParentFrame.bottom
        Text {
            id: name
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("U盘未插入")
            visible: !isUSBAvailable
            color: Style.whiteFontColor
            font{
                family: "宋体"
                pixelSize: Math.round(Style.style4 * Style.scaleHint)
            }
        }
    }
}


