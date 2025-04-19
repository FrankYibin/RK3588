import QtQuick 2.0
import Style 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle
{
    width: parent.width
    height: parent.height
    SystemPalette {
        id: systemPalette
    }

    Calendar {
        id: calendar
        // Convert the timestamp to QDateTime
        property date todayDate: new Date()
        width: parent.width
        height: parent.height
        frameVisible: false
        // weekNumbersVisible: true
        selectedDate: todayDate
        focus: true

        style: CalendarStyle {
            dayOfWeekDelegate: Item {
                readonly property var strWeekDays: [qsTr("周日"), qsTr("周一"), qsTr("周二"), qsTr("周三"), qsTr("周四"), qsTr("周五"), qsTr("周六")]
                width: parent.width
                height: Math.round(30 * Style.scaleHint)
                Rectangle
                {
                    anchors.fill: parent
                    color: Style.hbButtonBackgroundColor
                // anchors.margins: -1
                // border.color: Style.hbButtonBackgroundColor
                }
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
}


