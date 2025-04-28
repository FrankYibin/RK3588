import Style 1.0
import QtQuick 2.15
import QtQuick.Controls 1.4
Rectangle {
    id: gridParentFrame
    property alias dataModel: tableView.model
    ListModel {
        id: dataModel
        ListElement { column1: qsTr("Row 2, Col 1"); column2: qsTr("Row 2, Col 2"); column3: qsTr("Row 2, Col 3") }
        ListElement { column1: qsTr("Row 3, Col 1"); column2: qsTr("Row 3, Col 2"); column3: qsTr("Row 3, Col 3") }
    }

    // ScrollView {
    //     id: scrollView
    //     anchors.fill: parent
    //     clip: true
    //     contentItem: TableView {
        TableView {
            id: tableView
            anchors.fill: parent
            frameVisible: true
            model: dataModel
            headerDelegate: Rectangle {
                height: Math.round(30 * Style.scaleHint)
                width: styleData.columnWidth
                color: Style.backgroundLightColor
                border.color: Style.hbFrameBorderColor
                Text {
                    anchors.centerIn: parent
                    text: styleData.value
                    color: Style.whiteFontColor
                    font.bold: true
                    font.family: "宋体"
                }
            }

            rowDelegate: Rectangle {
                height: 30
                width: styleData.columnWidth
                color: styleData.row % 2 === 0 ? "white" : "lightblue"
                border.color: "black"
                Text {
                    anchors.centerIn: parent
                    text: styleData.value
                    Component.onCompleted: console.log("Row value:", styleData.value);
                }
            }

            TableViewColumn {
                role: "column1"
                title: "Column 1"
                width: tableView.width / 3
            }

            TableViewColumn {
                role: "column2"
                title: "Column 2"
                width: tableView.width / 3
            }

            TableViewColumn {
                role: "column3"
                title: "Column 3"
                width: tableView.width / 3
            }
        }
}
