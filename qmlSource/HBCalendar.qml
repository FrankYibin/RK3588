import QtQuick 2.0
import Style 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Item
{
    id: hbCalendar
    property date selectedDate: new Date()
    width: parent.width
    height: parent.height
    readonly property int buttonWidth: 100
    readonly property int componentHeight: 30
    signal signalConfirmed(bool isConfirmed)
    SystemPalette {
        id: systemPalette
    }

    Calendar {
        id: calendar
        // Convert the timestamp to QDateTime
        property date todayDate: new Date()
        width: parent.width
        height: parent.height - Math.round(50 * Style.scaleHint)
        // height: parent.height
        frameVisible: false
        // weekNumbersVisible: true
        selectedDate: todayDate
        focus: true
        onClicked:{
            hbCalendar.selectedDate = date
        }

        style: CalendarStyle {
            background: Rectangle
            {
                anchors.fill: parent
                color: Style.hbButtonBackgroundColor
            }
            navigationBar: Item {
                readonly property var strMonths: [qsTr("一月"), qsTr("二月"), qsTr("三月"),
                    qsTr("四月"), qsTr("五月"), qsTr("六月"),
                    qsTr("七月"), qsTr("八月"), qsTr("九月"),
                    qsTr("十月"), qsTr("十一月"), qsTr("十二月")]
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                Rectangle
                {
                    anchors.fill: parent
                    color: Style.backgroundDeepColor
                }
                HBPrimaryButton {
                    text: "<"
                    width: Math.round(25 * Style.scaleHint)
                    height: width
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        calendar.showPreviousMonth()
                    }
                }

                HBPrimaryButton {
                    text: ">"
                    onClicked: calendar.showNextMonth()
                    width: Math.round(25 * Style.scaleHint)
                    height: width
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }

                // Current month and year label
                Label {
                    height: parent.height
                    width: Math.round(50 * Style.scaleHint)
                    anchors.centerIn: parent
                     text: qsTr("%1  %2").arg(strMonths[calendar.visibleMonth]).arg(calendar.visibleYear)
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

            }

            dayOfWeekDelegate: Item {
                readonly property var strWeekDays: [qsTr("周日"), qsTr("周一"), qsTr("周二"),
                    qsTr("周三"), qsTr("周四"), qsTr("周五"), qsTr("周六")]
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                Label {
                    anchors.centerIn: parent
                    text: strWeekDays[styleData.dayOfWeek]
                    color: styleData.dayOfWeek === 0 || styleData.dayOfWeek === 6 ? Style.redFontColor : Style.whiteFontColor
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    font.family: "宋体"
                    font.bold: true
                }
            }
            dayDelegate: Item {
                readonly property color sameMonthDateTextColor: Style.whiteFontColor
                readonly property color selectedDateColor: Qt.platform.os === "osx" ? Style.hbButtonBackgroundColor : systemPalette.highlight
                readonly property color selectedDateTextColor: Style.blackFontColor
                readonly property color differentMonthDateTextColor: "#bbb"
                readonly property color invalidDatecolor: "#dddddd"

                Rectangle {
                    anchors.fill: parent
                    border.color: "transparent"
                    color: styleData.date !== undefined && styleData.selected ? selectedDateColor : Style.hbButtonBackgroundColor
                    anchors.margins: styleData.selected ? -1 : 0
                }

                Label {
                    id: dayDelegateText
                    text: styleData.date.getDate()
                    font.pixelSize: Math.round(Style.style3 * Style.scaleHint)
                    anchors.centerIn: parent
                    color: {
                        var color = invalidDatecolor;
                        if (styleData.valid) {
                            // Date is within the valid range.
                            if(styleData.visibleMonth === true)
                            {
                                color = sameMonthDateTextColor;
                                if(styleData.date.getDay() === 0 || styleData.date.getDay() === 6)
                                    color = Style.redFontColor
                            }
                            else
                                color = differentMonthDateTextColor;
                            if (styleData.selected) {
                                color = selectedDateTextColor;
                            }
                        }
                        return color;
                    }
                }
            }
        }
    }

    Rectangle {
        color: Style.backgroundDeepColor
        width: parent.width
        height: Math.round(50 * Style.scaleHint)
        anchors.top: calendar.bottom
        Row {
            spacing: Math.round(30 * Style.scaleHint)
            anchors.centerIn: parent

            HBPrimaryButton {
                text: qsTr("确定")
                width: Math.round(buttonWidth * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                onClicked: {
                    hbCalendar.visible = false
                    signalConfirmed(true)
                }
            }

            HBPrimaryButton {
                text: qsTr("取消")
                width: Math.round(buttonWidth * Style.scaleHint)
                height: Math.round(componentHeight * Style.scaleHint)
                onClicked: {
                    hbCalendar.visible = false
                    signalConfirmed(false)
                }
            }
        }
    }



}


