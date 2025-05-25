import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import HB.Modbus 1.0

Item{
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_SETTING
    signal signalCreateTensometer()
    signal signalViewTensometer()
    signal signalScaleTensometer()


    //    function deleteAllTensiometers(index) {
    //        if (index < 0) {
    //            tensionMeterTable.currentRow = -1
    //            return
    //        }

    //        console.log("Deleting row:", index)
    //        tensiometerManager.removeTensiometer(index)

    //        Qt.callLater(function() {
    //            deleteAllTensiometers(index - 1)
    //        })
    //    }

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

    HBTableView {
        id: tensionMeterTable
        property var tensionsTypeModel: []
        property var sensorRangeModel: []
        property var analogRangeModel: []
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
        model: tensiometerManager
        // selectionMode: SelectionMode.SingleSelection
        isMouseMoving: false
        rowDelegate: Rectangle{
            height: tensionMeterTable.rowHeight
            color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor

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
                    //                    text: styleData.value +1
                    text: styleData.row + 1
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
                    Component.onCompleted: console.log("SensorNumber cell:", styleData.value)

                }
                MouseArea {
                    anchors.fill: parent
                    property int previousX: 0
                    property int previousY: 0
                    onClicked: {
                        tensionMeterTable.currentRow = styleData.row // Update the current row
                        //                        tensionMeterTable.currentRow = model.index
                        console.debug("Selected Row: ", tensionMeterTable.currentRow)
                    }

                    onPressed: {
                        // previousX = mouseX
                        previousY = mouseY
                    }
                    onMouseXChanged: {
                        var moveToX = tensionMeterTable.flickableItem.contentX - (mouseX - previousX)
                        if(moveToX >= 0 && moveToX <= tensionMeterTable.flickableItem.contentWidth - tensionMeterTable.flickableItem.width)
                            tensionMeterTable.flickableItem.contentX = moveToX
                        previousX = mouseX
                    }

                    // onMouseYChanged: {
                    //     var moveToY = tensionMeterTable.flickableItem.contentY - (mouseY - previousY)
                    //     if(moveToY >= -tensionMeterTable.headerHeight && moveToY <= tensionMeterTable.flickableItem.contentHeight - tensionMeterTable.flickableItem.height - tensionMeterTable.headerHeight)
                    //         tensionMeterTable.flickableItem.contentY = moveToY
                    //     previousY = mouseY
                    // }
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
                    //                    text: styleData.value
                    text: tensionsTypeModel[styleData.value] !== undefined
                          ? tensionsTypeModel[styleData.value]
                          : ""
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
                    //                    text: styleData.value
                    text: sensorRangeModel[styleData.value] !== undefined
                          ? sensorRangeModel[styleData.value]
                          : ""
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
                    //                    text: styleData.value
                    text: analogRangeModel[styleData.value] !== undefined
                          ? analogRangeModel[styleData.value]
                          : ""
                    font.family: "宋体"
                    font.pixelSize: tensionMeterTable.fontSize
                }
            }
        }
        TableViewColumn {
            title: qsTr("操作")
            width: Math.round(270 * Style.scaleHint)

            delegate: Rectangle {

                color: (styleData.row === tensionMeterTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                height: Math.round(40 * Style.scaleHint)
                width: parent.width

                Row {
                    spacing: Math.round(10 * Style.scaleHint)
                    anchors.centerIn: parent

                    HBPrimaryButton {
                        text: qsTr("查看")
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: tensionMeterTable.fontSize
                        onClicked: {
                            tensionMeterTable.currentRow = styleData.row
                            signalViewTensometer()
                        }
                    }

                    HBPrimaryButton {
                        text: qsTr("刻度")
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: tensionMeterTable.fontSize
                        onClicked: {
                            tensionMeterTable.currentRow = styleData.row
                            signalScaleTensometer()
                        }
                    }

                    HBPrimaryButton {
                        text: qsTr("删除")
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: tensionMeterTable.fontSize
                        onClicked: {

                            //                            console.log("Delete clicked at delegate row:", styleData.row);
                            //                            console.log("tensionMeterTable currentRow:", tensionMeterTable.currentRow);
                            //                            console.log("tensiometerManager rowCount:", tensiometerManager.count)
                            //                            const row = styleData.row
                            //                            console.log("Row to delete:", row)
                            //                            if (row >= 0) {
                            //                                tensionMeterTable.currentRow = -1
                            //                                Qt.callLater(() => {
                            //                                                 tensiometerManager.removeTensiometer(row)
                            //                                             })
                            //                            } else {
                            //                                console.warn("Invalid row for deletion:", row)
                            //                            }
                            //                            const index = styleData.row;
                            //                             console.log("Request delete at index:", index);
                            //                             if (index >= 0 && index < tensiometerManager.count) {
                            //                                 tensionMeterTable.currentRow = -1;
                            //                                 tensiometerManager.removeTensiometer(index);
                            //                                 Qt.callLater(() => {
                            //                                     if (tensiometerManager.count > 0) {
                            //                                         tensionMeterTable.currentRow = Math.min(index, tensiometerManager.count - 1);
                            //                                     } else {
                            //                                         tensionMeterTable.currentRow = -1;
                            //                                     }
                            //                                 });
                            //                             } else {
                            //                                 console.warn("Invalid index for deletion:", index);
                            //                             }
                            //                            }
                            const index = styleData.row;
                            if (index >= 0 && index < tensiometerManager.count) {
                                tensionMeterTable.currentRow = -1;
                                tensiometerManager.removeTensiometer(index);
                                Qt.callLater(() => {
                                                 if (tensiometerManager.count > 0) {
                                                     tensionMeterTable.currentRow = Math.min(index, tensiometerManager.count - 1);
                                                 } else {
                                                     tensionMeterTable.currentRow = -1;
                                                 }
                                             });
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


