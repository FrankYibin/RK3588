import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    signal signalCreateTensometer()
    signal signalViewTensometer()
    signal signalScaleTensometer()
    Component.onCompleted:
    {
        dataModel.resetModel()
        operateModel.resetModel()
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
        id: operateModel
        function resetModel()
        {
            operateModel.clear()
            operateModel.append({"Index": 0, "Name": qsTr("查看")})
            operateModel.append({"Index": 1, "Name": qsTr("刻度")})
            operateModel.append({"Index": 2, "Name": qsTr("删除")})
        }
    }

    ListModel
    {
        id: dataModel
        function resetModel()
        {
            dataModel.clear()
            dataModel.append({"Index": 0,               "SensorNumber": 2412001,   "SensorType": qsTr("数字无线"),
                              "SensorRange": "10T",      "AnalogRange": qsTr("无"),         "Operating": ""})
            dataModel.append({"Index": 1,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 2,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 3,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 4,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 5,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 6,               "SensorNumber": 2412001,   "SensorType": qsTr("数字无线"),
                              "SensorRange": "10T",      "AnalogRange": qsTr("无"),         "Operating": ""})
            dataModel.append({"Index": 7,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 8,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 9,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 10,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
            dataModel.append({"Index": 11,               "SensorNumber": 2412002,   "SensorType": qsTr("模拟有线"),
                              "SensorRange": "30T",      "AnalogRange": "0-5V",         "Operating": ""})
        }

    }

    HBTableView {
        id: tensionMeterTable
        property int selectedRow: -1
        anchors.left: parent.left
        anchors.leftMargin: Math.round(10 * Style.scaleHint)
        anchors.right: parent.right
        anchors.rightMargin: Math.round(10 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(50 * Style.scaleHint)
        headerHeight: Math.round(40 * Style.scaleHint)
        rowHeight: Math.round(35 * Style.scaleHint)
        fontSize: Math.round(Style.style2 * Style.scaleHint)
        model: dataModel
        // selectionMode: SelectionMode.SingleSelection
        isMouseMoving: false
        rowDelegate: Rectangle{
            height: tensionMeterTable.rowHeight
        }

        TableViewColumn {
            role: "Index";              title: qsTr("");                width: 30;
            delegate: Rectangle {
                height: tensionMeterTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.value
                    font.family: Style.regular.name
                    font.pixelSize: tensionMeterTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "SensorNumber";         title: qsTr("张力计编号");        width: 150
            delegate: Rectangle {
                height: tensionMeterTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.value
                    font.family: Style.regular.name
                    font.pixelSize: tensionMeterTable.fontSize
                }
                MouseArea {
                    anchors.fill: parent
                    property int previousX: 0
                    property int previousY: 0
                    onClicked: {
                        tensionMeterTable.currentRow = styleData.row // Update the current row
                        console.debug("Selected Row: ", tensionMeterTable.currentRow)
                    }

                    onPressed: {
                        // previousX = mouseX
                        previousY = mouseY
                    }
                    // onMouseXChanged: {
                    //     var moveToX = tensionMeterTable.flickableItem.contentX - (mouseX - previousX)
                    //     if(moveToX >= 0 && moveToX <= tensionMeterTable.flickableItem.contentWidth - tensionMeterTable.flickableItem.width)
                    //         tensionMeterTable.flickableItem.contentX = moveToX
                    //     previousX = mouseX
                    // }

                    onMouseYChanged: {
                        var moveToY = tensionMeterTable.flickableItem.contentY - (mouseY - previousY)
                        if(moveToY >= -tensionMeterTable.headerHeight && moveToY <= tensionMeterTable.flickableItem.contentHeight - tensionMeterTable.flickableItem.height - tensionMeterTable.headerHeight)
                            tensionMeterTable.flickableItem.contentY = moveToY
                        previousY = mouseY
                    }
                }
            }
        }
        TableViewColumn {
            role: "SensorType";           title: qsTr("张力计类型");        width: 150
            delegate: Rectangle {
                height: tensionMeterTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.value
                    font.family: "宋体"
                    font.pixelSize: tensionMeterTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "SensorRange";          title: qsTr("张力计量程");        width: 150
            delegate: Rectangle {
                height: tensionMeterTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.value
                    font.family: Style.regular.name
                    font.pixelSize: tensionMeterTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "AnalogRange";          title: qsTr("张力输出信号");      width: 150
            delegate: Rectangle {
                height: tensionMeterTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    color: Style.whiteFontColor
                    text: styleData.value
                    font.family: "宋体"
                    font.pixelSize: tensionMeterTable.fontSize
                }
            }
        }
        TableViewColumn {
            role: "Operating";            title: qsTr("操作");             width: 430
            delegate: Rectangle {
                height: tensionMeterTable.rowHeight
                width: styleData.columnWidth
                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Row{
                    anchors.centerIn: parent
                    spacing: Math.round(10 * Style.scaleHint)
                    Repeater
                    {
                        model: operateModel
                        HBPrimaryButton
                        {
                            width: Math.round(80 * Style.scaleHint)
                            height: Math.round(25 * Style.scaleHint)
                            text: model.Name
                            fontSize: tensionMeterTable.fontSize
                            onClicked:
                            {
                                switch(model.Index)
                                {
                                case 0:
                                    signalViewTensometer()
                                    break;
                                case 1:
                                    signalScaleTensometer()
                                    break;
                                case 2:
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Item{
        anchors.top: tensionMeterTable.bottom
        anchors.bottom: parent.bottom
        anchors.left: tensionMeterTable.left
        anchors.right: tensionMeterTable.right
        Item{
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            height: Math.round(30 * Style.scaleHint)
            width: Math.round((120 * 2 + 20) * Style.scaleHint)
            Row{
                spacing: Math.round(20 * Style.scaleHint)
                anchors.fill: parent
                HBPrimaryButton
                {
                    id: newSensor
                    width: Math.round(120 * Style.scaleHint)
                    height: Math.round(30 * Style.scaleHint)
                    text: qsTr("新建张力计")
                    fontSize: Math.round(Style.style5 * Style.scaleHint)
                    onClicked:
                    {
                        signalCreateTensometer()
                    }
                }

                HBPrimaryButton
                {
                    id: defaultSetting
                    width: Math.round(120 * Style.scaleHint)
                    height: Math.round(30 * Style.scaleHint)
                    text: qsTr("默认刻度")
                    fontSize: Math.round(Style.style5 * Style.scaleHint)
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
                    }
                }
            }
        }
    }
}


