import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import Style 1.0

Item {
    id: dateTimeSetting
    property alias hoursIndex: timeView.currentIndex
    property alias minutesIndex: mint.currentIndex
    property alias secondsIndex: second.currentIndex

    function getDateString()
    {
        return Qt.formatDateTime(calendar.selectedDate, "yyyy-MM-dd")
    }
    function getTimeString()
    {
        return hourText.text + ":" + minuteText.text + ":" + secondText.text
    }
    function getDateTimeString()
    {
        return Qt.formatDateTime(calendar.selectedDate, "yyyy-MM-dd") + " " + hourText.text + ":" + minuteText.text + ":" + secondText.text
    }



    width: 750
    height: 400
    HBCalendar
    {
        id: calendar
        width: 450
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
    }

    Item
    {
        width: 250
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        Item {
            anchors.top: parent.top
            anchors.right: parent.right
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            Row {
                anchors.right: parent.right
                anchors.rightMargin: Math.round(10 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                spacing: 15
                Text {
                    width: 59
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: qsTr("小时")
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor /*"white"*/

                }
                Text {
                    width: 59
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: qsTr("分钟")
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor /*"white"*/

                }
                Text {
                    width: 59
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: qsTr("秒")
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor /*"white"*/
                }
            }
        }

        HBTextField{
            id: hourText
            width: 59
            height: 59
            anchors.bottom: timeView.top
            anchors.right: timeView.right
            anchors.bottomMargin: 15
            horizontalAlignment: Qt.AlignHCenter
            enabled: false
            font.pixelSize: 26
        }
        PathView {
            id: timeView
            model: 24
            width: 59
            height: 280
            anchors.bottom: parent.bottom
            anchors.right: mint.left
            anchors.rightMargin: 15
            highlightRangeMode: ListView.StrictlyEnforceRange;
            preferredHighlightBegin: 0.5;
            preferredHighlightEnd: 0.5;
            clip: true;
            pathItemCount: 7;
            Rectangle{
                anchors.fill: parent
                color: "#00000000"
                border.width: 1
                border.color: "#D0DFE5"
                Rectangle{
                    width: parent.width
                    height: 2
                    color: "#D0DFE5"
                    anchors.centerIn: parent
                }
            }

            path: Path {
                startY: 0
                startX: 30
                PathLine { y: second.height; x: 30 }
            }

            delegate: Item {
                height: 33
                width: timeView.width
                Text {
                    id: modelRect
                    anchors.centerIn: parent
                    text: index

                    color: timeView.currentIndex == index ? Style.hbButtonBackgroundColor /*"blue"*/ : Style.whiteFontColor /*"white"*/;
                    font.pointSize: 20
                }
            }

            onCurrentIndexChanged: {
                if(currentIndex < 10)
                {
                    hourText.text = "0"+currentIndex
                }
                else
                {
                    hourText.text = currentIndex
                }
            }

        }
        Text {
            text: ":"
            color: "#002552" /*"white"*/
            anchors.right: minuteText.left
            anchors.verticalCenter: minuteText.verticalCenter
            font.pointSize: 20
        }
        HBTextField {
            id: minuteText
            width: 59
            height: 59
            anchors.bottom: mint.top
            anchors.right: mint.right
            anchors.bottomMargin: 15
            horizontalAlignment: Qt.AlignHCenter
            enabled: false
            font.pixelSize: 26
        }
        PathView {
            id: mint
            model: 60
            width: 59
            height: 280
            anchors.bottom: timeView.bottom
            anchors.right: second.left
            anchors.rightMargin: 15
            highlightRangeMode: ListView.StrictlyEnforceRange;
            preferredHighlightBegin: 0.5;
            preferredHighlightEnd: 0.5;
            clip: true;
            pathItemCount: 7;
            Rectangle{
                anchors.fill: parent
                color: "#00000000"
                border.width: 1
                border.color: "#D0DFE5"
                Rectangle{
                    width: parent.width
                    height: 2
                    color: "#D0DFE5"
                    anchors.centerIn: parent
                }
            }

            path: Path {
                startY: 0
                startX: 30
                PathLine { y: second.height; x: 30 }
            }
            delegate: Item {
                height: 33
                width: timeView.width
                Text {
                    id: modelRect2
                    anchors.centerIn: parent
                    text: index

                    color: mint.currentIndex == index ? Style.hbButtonBackgroundColor /*"blue"*/ : Style.whiteFontColor /*"white"*/;
                    font.pointSize: 20
                }
            }
            onCurrentIndexChanged: {
                if(currentIndex < 10)
                {
                    minuteText.text = "0"+currentIndex
                }
                else
                {
                    minuteText.text = currentIndex
                }
            }
        }
        Text {
            text: ":"
            color: "#002552" /*"white"*/
            anchors.right: secondText.left
            anchors.verticalCenter: secondText.verticalCenter
            font.pointSize: 20
        }
        HBTextField {
            id: secondText
            width: 59
            height: 59
            anchors.bottom: second.top
            anchors.right: second.right
            anchors.bottomMargin: 15
            horizontalAlignment: Qt.AlignHCenter
            enabled: false
            font.pixelSize: 26
        }
        PathView {
            id: second
            model: 60
            width: 59
            height: 280
            anchors.bottom: mint.bottom
            anchors.right: parent.right
            anchors.rightMargin: 15
            highlightRangeMode: ListView.StrictlyEnforceRange;
            preferredHighlightBegin: 0.5 //height / 2.5;
            preferredHighlightEnd: 0.5 //height / 2.5;
            clip: true;
            pathItemCount: 7;
            Rectangle{
                anchors.fill: parent
                color: "#00000000"
                border.width: 1
                border.color: "#D0DFE5"
                Rectangle{
                    width: parent.width
                    height: 2
                    color: "#D0DFE5"
                    anchors.centerIn: parent
                }
            }

            path: Path {
                startY: 0
                startX: 30 //0//pathMargin
                PathLine { y: second.height; x: 30 }
            }
            delegate: Item {
                height: 33
                width: timeView.width
                Text {
                    id: modelRect3
                    anchors.centerIn: parent
                    text: index

                    color: second.currentIndex == index ? Style.hbButtonBackgroundColor /*"blue"*/ : Style.whiteFontColor /*"white"*/;
                    font.pointSize: 20
                }
            }
            onCurrentIndexChanged: {
                if (currentIndex < 10) {
                    secondText.text = "0"+currentIndex
                } else {
                    secondText.text = currentIndex
                }
            }
        }

        Component.onCompleted:
        {
            var currentDate = new Date()
            var str = Qt.formatDateTime(currentDate, "yyyy-MM-dd hh:mm:ss")
            var dateTimeParts = str.split(" ")
            var timePart = dateTimeParts[1]
            var timeComponents = timePart.split(":")
            var hours = timeComponents[0]
            var minutes = timeComponents[1]
            var seconds = timeComponents[2]
            hoursIndex = parseInt(hours)
            minutesIndex = parseInt(minutes)
            secondsIndex = parseInt(seconds)
        }
    }

}
