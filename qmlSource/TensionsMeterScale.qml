import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    id: newTensionMeter
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_VIEW
    property int totalScales: 0
    signal signalSaveTensometerScale()
    Component.onCompleted:
    {
        dataModel.resetModel()

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

    ListModel
    {
        id: dataModel
        function resetModel()
        {
            dataModel.clear()
            dataModel.append({"Checked": true,  "Index": 1,   "ScaleValue": 10,   "TensionValue": 0.5})
            dataModel.append({"Checked": true,  "Index": 2,   "ScaleValue": 20,   "TensionValue": 1.0})
            dataModel.append({"Checked": false, "Index": 3,   "ScaleValue": 30,   "TensionValue": 1.5})
            dataModel.append({"Checked": false, "Index": 4,   "ScaleValue": 40,   "TensionValue": 2.0})
            dataModel.append({"Checked": false, "Index": 5,   "ScaleValue": 50,   "TensionValue": 2.5})
            dataModel.append({"Checked": true,  "Index": 6,   "ScaleValue": 60,   "TensionValue": 3.0})
            dataModel.append({"Checked": true,  "Index": 7,   "ScaleValue": 70,   "TensionValue": 0.5})
            dataModel.append({"Checked": true,  "Index": 8,   "ScaleValue": 80,   "TensionValue": 1.0})
            dataModel.append({"Checked": false, "Index": 9,   "ScaleValue": 90,   "TensionValue": 1.5})
            dataModel.append({"Checked": false, "Index": 10,   "ScaleValue": 100,   "TensionValue": 2.0})
            dataModel.append({"Checked": false, "Index": 11,   "ScaleValue": 110,   "TensionValue": 2.5})
            dataModel.append({"Checked": true,  "Index": 12,   "ScaleValue": 120,   "TensionValue": 3.0})
        }
    }


    Item {
        id: tensionScaleFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width / 2
        HBTableView {
            id: tensionScaleTable
            width: Math.round(300 * Style.scaleHint)
            height: Math.round(280 * Style.scaleHint)
            anchors.centerIn: parent
            headerHeight: Math.round(40 * Style.scaleHint)
            rowHeight: Math.round(35 * Style.scaleHint)
            fontSize: Math.round(Style.style2 * Style.scaleHint)
            model: dataModel
            // model: tensiometerModel
            isMouseMoving: false

            rowDelegate: Rectangle{
                height: tensionScaleTable.rowHeight
            }

            TableViewColumn {
                role: "Checked";      title: "";                width: Math.round(30 * Style.scaleHint)
                delegate: Rectangle {
                    height: tensionScaleTable.rowHeight
                    width: styleData.columnWidth
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    HBRadioButton
                    {
                        height: Math.round(20 * Style.scaleHint)
                        width: parent.width/2
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: Math.round(5 * Style.scaleHint)
                        circleSize: height
                        checked: styleData.value
                        borderWidth: Math.round(2 * Style.scaleHint)
                        onClicked:
                        {

                        }
                    }
                }
            }
            TableViewColumn {
                role: "Index";         title: qsTr("刻度点");     width: Math.round(90 * Style.scaleHint)
                delegate: Rectangle {
                    height: tensionScaleTable.rowHeight
                    width: styleData.columnWidth
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    Text {
                        anchors.centerIn: parent
                        color: Style.whiteFontColor
                        text: styleData.value
                        font.family: Style.regular.name
                        font.pixelSize: tensionScaleTable.fontSize
                    }

                    MouseArea {
                        anchors.fill: parent
                        property int previousY: 0
                        onClicked: {
                            tensionScaleTable.currentRow = styleData.row // Update the current row
                            console.debug("Selected Row: ", tensionScaleTable.currentRow)
                        }
                        onPressed: {
                            previousY = mouseY
                        }
                        onMouseYChanged: {
                            var moveToY = tensionScaleTable.flickableItem.contentY - (mouseY - previousY)
                            if(moveToY >= -tensionScaleTable.headerHeight && moveToY <= tensionScaleTable.flickableItem.contentHeight - tensionScaleTable.flickableItem.height - tensionScaleTable.headerHeight)
                                tensionScaleTable.flickableItem.contentY = moveToY
                            previousY = mouseY
                        }
                    }
                }

            }
            TableViewColumn {
                role: "ScaleValue";    title: qsTr("刻度值");     width: Math.round(90 * Style.scaleHint)
                delegate: Rectangle {
                    height: tensionScaleTable.rowHeight
                    width: styleData.columnWidth
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    Text {
                        anchors.centerIn: parent
                        color: Style.whiteFontColor
                        text: styleData.value
                        font.family: Style.regular.name
                        font.pixelSize: tensionScaleTable.fontSize
                    }
                }
            }
            TableViewColumn {
                role: "TensionValue";  title: qsTr("张力值(kN)"); width: Math.round(90 * Style.scaleHint)
                delegate: Rectangle {
                    height: tensionScaleTable.rowHeight
                    width: styleData.columnWidth
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    HBTextField
                    {
                        text: styleData.value
                        width: parent.width
                        height: parent.height
                        backgroundColor: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                        fontSize: tensionScaleTable.fontSize
                        onlyForNumpad: true
                        onSignalClickedEvent: {
                            mainWindow.showPrimaryNumpad("Time Scale Setting", "s", 3, 0, 5, "0.123")
                        }
                    }
                }
            }
        }
    }

    Item {
        id: graphView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width / 2
        HBScalesChartView {
            id: tensionScaleChart
            width: Math.round(300 * Style.scaleHint)
            height: Math.round(280 * Style.scaleHint)
            anchors.centerIn: parent
        }
    }

    Item {
        id: itemTensiometer
        anchors.left: parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        anchors.top: parent.top
        height: Math.round(60 * Style.scaleHint)
        width: parent.width
        Row{
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(10 * Style.scaleHint)
            Text
            {
                id: titleTensiometer
                text: qsTr("张力计编号") + ":"
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                font.family: "宋体"
                color: Style.whiteFontColor
                verticalAlignment: Text.AlignVCenter
                height: Math.round(40 * Style.scaleHint)
            }

            Text
            {
                id: numberTensiometer
                text: qsTr("2412001")
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
                verticalAlignment: Text.AlignVCenter
                height: Math.round(40 * Style.scaleHint)
            }
        }
    }

    Item {
        id: itemInfo
        anchors.left: parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        anchors.bottom: parent.bottom
        height: Math.round(60 * Style.scaleHint)
        width: parent.width

        Text
        {
            id: infoMessage
            text: qsTr("您已经选择了") + totalScales + qsTr("个刻度点")
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: "宋体"
            color: Style.whiteFontColor
            verticalAlignment: Text.AlignVCenter
            height: Math.round(40 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    HBPrimaryButton
    {
        id: btnSave
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        width: Math.round(120 * Style.scaleHint)
        height: Math.round(30 * Style.scaleHint)
        text: qsTr("保存")
        fontSize: Math.round(Style.style5 * Style.scaleHint)
        onClicked:
        {
            signalSaveTensometerScale()
        }
    }


}


