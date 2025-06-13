import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import TensionsGlobalDefine 1.0

Item{
    id: newTensionMeter
    readonly property int qmlscreenIndicator:  UIScreenEnum.HB_TENSIONS_VIEW
    property int totalScales: 0
    signal signalSaveTensometerScale()

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

    Item {
        id: tensionScaleFrame
        anchors.top: itemScalePoints.bottom
        anchors.topMargin: Math.round(10 * Style.scaleHint)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        HBTableView {
            id: tensionScaleTable
            width: Math.round(360 * Style.scaleHint)
            height: Math.round(280 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            headerHeight: Math.round(40 * Style.scaleHint)
            rowHeight: Math.round(35 * Style.scaleHint)
            fontSize: Math.round(Style.style2 * Style.scaleHint)
            model: TensiometerScale
            isMouseMoving: false

            rowDelegate: Rectangle{
                height: tensionScaleTable.rowHeight
            }

            TableViewColumn {
                role: "index";         title: qsTr("刻度点");     width: Math.round(90 * Style.scaleHint)
                delegate: Rectangle {
                    height: tensionScaleTable.rowHeight
                    width: styleData.columnWidth
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    Text {
                        anchors.centerIn: parent
                        color: Style.whiteFontColor
                        text: styleData.value + 1
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
                role: "scaleValue";    title: qsTr("刻度值");     width: Math.round(90 * Style.scaleHint)
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
                role: "tensionValue";
                title: qsTr("张力值") + "(" + TensionsGlobalDefine.tensionUnitModel[TensionSetting.TensionUnit] + ")";
                width: Math.round(90 * Style.scaleHint)
                delegate: Rectangle {
                    height: tensionScaleTable.rowHeight
                    width: styleData.columnWidth
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    HBTextField
                    {
                        id:tensionInput
                        text: styleData.value
                        property int row: styleData.row
                        width: parent.width
                        height: parent.height
                        backgroundColor: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                        fontSize: tensionScaleTable.fontSize
                        onlyForNumpad: true
                        onSignalClickedEvent: {
                            mainWindow.showPrimaryNumpad("请输入张力值", " ", 2, 0, 99999, tensionInput.text,tensionInput,function(val){
                                tensionScaleTable.currentRow = row
                                TensiometerScale.setTensionValue(row, val)
                            })
                            tensionInput.focus = true
                        }
                    }
                }
            }
            TableViewColumn {
                title: qsTr("操作")
                width: Math.round(90 * Style.scaleHint)
                delegate: Rectangle {
                    color: (styleData.row === tensionScaleTable.currentRow) ? Style.backgroundDeepColor : Style.backgroundLightColor
                    border.color: Style.hbFrameBorderColor
                    height: Math.round(40 * Style.scaleHint)
                    width: parent.width
                    HBPrimaryButton {
                        text: qsTr("刻度") + (styleData.row + 1)
                        property int row: styleData.row
                        width: Math.round(80 * Style.scaleHint)
                        height: Math.round(25 * Style.scaleHint)
                        fontSize: tensionScaleTable.fontSize
                        anchors.centerIn: parent
                        onClicked: {
                            tensionScaleTable.currentRow = row
                            TensiometerScale.getScaleCurrent(row)
                        }
                    }
                }
            }
        }
    }

    // Item {
    //     id: graphView
    //     anchors.top: parent.top
    //     anchors.bottom: parent.bottom
    //     anchors.right: parent.right
    //     width: parent.width / 2
    //     HBScalesChartView {
    //         id: tensionScaleChart
    //         width: Math.round(300 * Style.scaleHint)
    //         height: Math.round(280 * Style.scaleHint)
    //         anchors.centerIn: parent
    //     }
    // }

    Item {
        id: itemTensiometer
        anchors.left: parent.left
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        anchors.top: parent.top
        anchors.topMargin: Math.round(20 * Style.scaleHint)
        height: Math.round(40 * Style.scaleHint)
        width: parent.width / 3
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
                text: TensiometerScale.TensiometerNumber
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                font.family: Style.regular.name
                color: Style.whiteFontColor
                verticalAlignment: Text.AlignVCenter
                height: Math.round(40 * Style.scaleHint)
            }
        }
    }

    Item {
        id: itemScalePoints
        anchors.left: itemTensiometer.right
        anchors.leftMargin: Math.round(20 * Style.scaleHint)
        anchors.top : itemTensiometer.top
        height: Math.round(40 * Style.scaleHint)
        width: parent.width
        Row
        {
            id: infoWellType
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            anchors.verticalCenter: parent.verticalCenter
            spacing: Math.round(10 * Style.scaleHint)
            Item{
                width: Math.round(100 * Style.scaleHint)
                height: parent.height
                Text
                {
                    id: titleScalePoints
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("刻度点数量") + ":"
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    font.family: "宋体"
                    color: Style.whiteFontColor
                }
            }

            HBComboBox
            {
                id: comboScalePoints
                model: TensionsGlobalDefine.scalePointsModel
                currentIndex: 0
                width: Math.round(100 * Style.scaleHint)
                height: parent.height
                fontFamily: Style.regular.name
                onCurrentIndexChanged: {
                    var str = TensionsGlobalDefine.scalePointsModel[currentIndex]
                    TensiometerScale.QuantityOfCalibration = str;
                    TensiometerScale.resetModel()
                    TensiometerScale.initModel(parseInt(str))
                }
            }
        }


    }



    // Item {
    //     id: itemInfo
    //     anchors.left: parent.left
    //     anchors.leftMargin: Math.round(20 * Style.scaleHint)
    //     anchors.bottom: parent.bottom
    //     height: Math.round(60 * Style.scaleHint)
    //     width: parent.width

    //     Text
    //     {
    //         id: infoMessage
    //         text: qsTr("您已经选择了") + totalScales + qsTr("个刻度点")
    //         font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
    //         font.family: "宋体"
    //         color: Style.whiteFontColor
    //         verticalAlignment: Text.AlignVCenter
    //         height: Math.round(40 * Style.scaleHint)
    //         anchors.verticalCenter: parent.verticalCenter
    //     }
    // }

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
            TensiometerScale.saveModel()
            signalSaveTensometerScale()
        }
    }


}


