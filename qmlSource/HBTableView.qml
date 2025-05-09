import Style 1.0
import QtQuick 2.15
import QtQuick.Controls 1.4
TableView {
    id: tableView
    height: parent.height
    width: parent.width
    frameVisible: true
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    // backgroundVisible: true
    property int headerHeight: Math.round(25 * Style.scaleHint)
    property int rowHeight: Math.round(25 * Style.scaleHint)

    model: dataModel
    selectionMode: SelectionMode.NoSelection
    headerDelegate: Rectangle {
        id: headerTabelView
        height: headerHeight
        width: styleData.columnWidth
        color: Style.backgroundLightColor
        border.color: Style.hbFrameBorderColor
        Text {
            anchors.centerIn: parent
            text: styleData.value
            color: Style.whiteFontColor
            font.bold: true
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
        }
    }

    itemDelegate: Rectangle {
        height: rowHeight
        width: styleData.columnWidth
        color: styleData.column === 0 ? Style.backgroundLightColor : "0x000000"
        border.color: Style.hbFrameBorderColor
        Text {
            anchors.centerIn: parent
            color: Style.whiteFontColor
            text: styleData.value
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style0 * Style.scaleHint)
        }
    }

    rowDelegate: Rectangle{
        height: rowHeight
    }

    MouseArea{
        id: controlArea
        anchors.fill: parent

        property int previousX: 0
        property int previousY: 0

        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }

        onMouseXChanged: {
            var moveToX = tableView.flickableItem.contentX - (mouseX - previousX)
            if(moveToX >= 0 && moveToX <= tableView.flickableItem.contentWidth - tableView.flickableItem.width)
                tableView.flickableItem.contentX = moveToX
            previousX = mouseX
        }

        onMouseYChanged: {
            var moveToY = tableView.flickableItem.contentY - (mouseY - previousY)
            if(moveToY >= -tableView.headerHeight && moveToY <= tableView.flickableItem.contentHeight - tableView.flickableItem.height - tableView.headerHeight)
                tableView.flickableItem.contentY = moveToY
            previousY = mouseY
        }
    }
}
