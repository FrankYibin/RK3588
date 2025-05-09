import QtQuick.Controls 1.4
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
Item{
    readonly property int textWidth: 100
    readonly property int comboBoxWidth: 150
    readonly property int buttonWidth: 150
    readonly property int rowSpacing: 20
    readonly property int componentHeight: 30

    Component.onCompleted:
    {
        headerModel.resetModel()
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

        Item {
            id: buttonArray
            width: parent.width
            height: parent.height / 2
            anchors.top: parent.top
            anchors.left: parent.left
            Row
            {
                id: argumentLayout
                spacing: Math.round(30 * Style.scaleHint)
                width: Math.round((buttonWidth * 3 ) * Style.scaleHint) + argumentLayout.columnSpacing * 2
                height: Math.round((componentHeight * 2) * Style.scaleHint) + argumentLayout.rowSpacing
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.top: parent.top
                anchors.topMargin: Math.round(20 * Style.scaleHint)

                HBPrimaryButton
                {
                    id: buttonInquiresSetting
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("设置查询条件")
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
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
                    }
                }

                HBPrimaryButton
                {
                    id: buttonExport
                    width: Math.round(buttonWidth * Style.scaleHint)
                    height: Math.round(componentHeight * Style.scaleHint)
                    text: qsTr("导出选中")
                    onClicked:
                    {
                        // controlLimitNumpad.visible = false
                    }
                }


            }
        }

        Item {
            id: textContent
            width: parent.width
            height: parent.height / 2
            anchors.top: buttonArray.bottom
            anchors.left: parent.left
            Text {
                id: titleStartTimeStamp
                anchors.left: parent.left
                anchors.leftMargin: Math.round(20 * Style.scaleHint)
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: Math.round(componentHeight * Style.scaleHint)
                text: qsTr("查询方式") + ":"
                font.family: "宋体"
                font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                color: Style.whiteFontColor
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
            headerModel.append({"role": "Date",                 "title": qsTr("日期"),      "headerWidth": 100})
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
    ListModel
    {
        id: dataModel
        function resetModel()
        {
            dataModel.clear()
            dataModel.append({"Index": 0,               "WellNumber": "陕30H-3",    "Date": "2025-4-22",
                              "OperateType": "射孔",    "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 1,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 2,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 3,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 4,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 5,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 6,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 7,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 8,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 9,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 10,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 11,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 12,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 13,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 14,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})
            dataModel.append({"Index": 15,               "WellNumber": "陕30H-3",     "Date": "2025-4-22",
                              "OperateType": "射孔",      "Operater": "1",              "Depth": 100.0,
                              "Velocity": 100.0,        "VelocityUnit": "m/min",    "Tensions": 50.0,
                              "TensionIncreament": 1.0, "TensionUnit": "kg",        "MaxTension": 255.0,
                              "HarnessTension": 101.0,  "SafetyTension": 100.0,     "Exception": "无"})

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
        model: dataModel

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


