import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.HistoryOperationModel 1.0
Item{
    readonly property int textWidth: 70
    readonly property int comboBoxWidth: 150
    readonly property int editTextWidth: 100
    readonly property int buttonWidth: 100
    readonly property int rowSpacing: 10
    readonly property int componentHeight: 30

    HBCalendar{
        id: calendarDate
        anchors.centerIn: parent
        width: Math.round(400 * Style.scaleHint)
        height: Math.round(250 * Style.scaleHint)
        z: 5
        visible: false
        onSelectedDateChanged: {
            console.debug("3333333333333: ", selectedDate)
        }
    }

    HistoryOperationModel{
        id: historyOperationModel
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
        title: qsTr("作业信息")
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.left: parent.left
        anchors.leftMargin: Math.round(5 * Style.scaleHint)
        width: parent.width - Math.round(10 * Style.scaleHint)
        height: parent.height / 3 - Math.round(40 * Style.scaleHint)
        backgroundColor: Style.backgroundLightColor
        //        Item {
        //            id: argumentLayout
        //            width: parent.width
        //            height: parent.height / 2
        //            anchors.left: parent.left
        //            anchors.top: parent.top
        //            Row
        //            {
        //                height: Math.round(componentHeight * Style.scaleHint)
        //                width: parent.width
        //                anchors.left: parent.left
        //                anchors.leftMargin: Math.round(20 * Style.scaleHint)
        //                anchors.top: parent.top
        //                anchors.topMargin: Math.round(20 * Style.scaleHint)
        //                spacing: Math.round(30 * Style.scaleHint)

        //                Row{
        //                    spacing: Math.round(rowSpacing * Style.scaleHint)
        //                    height: parent.height
        //                    width: Math.round((textWidth + rowSpacing + editTextWidth) * Style.scaleHint)
        //                    Text {
        //                        id: titleFirstNumber
        //                        width: Math.round(textWidth * Style.scaleHint)
        //                        height: parent.height
        //                        text: qsTr("队别") + ":"
        //                        font.family: "宋体"
        //                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        //                        verticalAlignment: Text.AlignVCenter
        //                        color: Style.whiteFontColor
        //                    }
        //                    HBLineEdit {
        //                        id: textFirstNumber
        //                        width: Math.round(editTextWidth * Style.scaleHint)
        //                        height: parent.height
        //                        text: "01"
        //                    }
        //                }

        //                Row{
        //                    spacing: Math.round(rowSpacing * Style.scaleHint)
        //                    height: parent.height
        //                    width: Math.round((textWidth + rowSpacing + editTextWidth) * Style.scaleHint)
        //                    Text {
        //                        id: titleAreaNumber
        //                        width: Math.round(textWidth * Style.scaleHint)
        //                        height: parent.height
        //                        text: qsTr("区域") + ":"
        //                        font.family: "宋体"
        //                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        //                        verticalAlignment: Text.AlignVCenter
        //                        color: Style.whiteFontColor
        //                    }
        //                    HBLineEdit {
        //                        id: textAreaNumber
        //                        width: Math.round(editTextWidth * Style.scaleHint)
        //                        height: parent.height
        //                        text: "01"
        //                    }
        //                }

        //                Row{
        //                    spacing: Math.round(rowSpacing * Style.scaleHint)
        //                    height: parent.height
        //                    width: Math.round((textWidth + rowSpacing + editTextWidth) * Style.scaleHint)
        //                    Text {
        //                        id: titleWellNumber
        //                        width: Math.round(textWidth * Style.scaleHint)
        //                        height: parent.height
        //                        text: qsTr("井名") + ":"
        //                        font.family: "宋体"
        //                        font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
        //                        verticalAlignment: Text.AlignVCenter
        //                        color: Style.whiteFontColor
        //                    }
        //                    HBLineEdit {
        //                        id: textWellNumber
        //                        width: Math.round(editTextWidth * Style.scaleHint)
        //                        height: parent.height
        //                        text: "01"
        //                    }
        //                }
        //            }

        //        }

        Item{
            id: timeScopeLayout
            width: parent.width
            height: parent.height / 2
            //            anchors.top: argumentLayout.bottom
            anchors.left: parent.left
            Row{
                width: parent.width
                height: Math.round(componentHeight * Style.scaleHint)
                spacing: Math.round(20 * Style.scaleHint)
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                Row{
                    spacing: Math.round(rowSpacing * Style.scaleHint)
                    height: parent.height
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
                    //                    HBComboBox
                    //                    {
                    //                        id:comboBoxStartTimeStamp
                    //                        width: Math.round(comboBoxWidth * Style.scaleHint)
                    //                        height: parent.height
                    //                    }
                    HBComboBoxCalendar
                    {
                        id:comboBoxStartTimeStamp
                        width: Math.round(comboBoxWidth * Style.scaleHint)
                        height: parent.height
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
                    height: parent.height
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
                    //                    HBComboBox
                    //                    {
                    //                        id:comboBoxFinishTimeStamp
                    //                        width: Math.round(comboBoxWidth * Style.scaleHint)
                    //                        height: parent.height
                    //                    }
                    HBComboBoxCalendar
                    {
                        id:comboBoxFinishTimeStamp
                        width: Math.round(comboBoxWidth * Style.scaleHint)
                        height: parent.height
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

                HBPrimaryButton
                {
                    id: buttonInquire
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("查询")
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
                        var startIso = comboBoxStartTimeStamp.text + "T00:00:00"
                        var endIso   = comboBoxFinishTimeStamp.text + "T23:59:59"
                        historyOperationModel.setRange(startIso, endIso)
                    }
                }
            }
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
        model: historyOperationModel

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
                text: styleData.value
                font.family: "宋体"
                font.pixelSize: gridParentFrame.fontSize
            }
        }
        rowDelegate: Rectangle{
            height: gridParentFrame.rowHeight
        }

        TableViewColumn { role: "Index";                title: qsTr("");            width: 30}
        TableViewColumn { role: "WellNumber";           title: qsTr("井号");        width: 100}
        TableViewColumn { role: "OperateType";          title: qsTr("操作类型");    width: 80}
        TableViewColumn { role: "Operater";             title: qsTr("操作员");      width: 80}
        TableViewColumn { role: "Date";                 title: qsTr("日期");        width: 200}
        TableViewColumn { role: "Description";          title: qsTr("操作");        width: 600}
    }
}


