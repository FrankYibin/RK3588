import Style 1.0
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TableView{
    id: modelView

    property bool chooseRow: true
    property bool mousePressed: false

    property int headHeight: Math.round(30 * Style.scaleHint)
    property int rowHeight: Math.round(30 * Style.scaleHint)
    property int handleWidth: 15
    property int loaderHeight: Math.round(30 * Style.scaleHint)

    property int currentPage: 1
    property int totalPage: 1

    property int slidHeight: 3

    signal loadPreviousPage()
    signal loadNextPage()

    signal rowClicked(int row, int xValue)

    onVisibleChanged: {
        if(visible)
        {
            flickableItem.contentY = -modelView.headHeight
        }
    }

    MouseArea{
        id: controlArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: modelView.headHeight
        width: modelView.contentItem.width
        height: modelView.contentItem.height - modelView.headHeight

        property bool previousVisible: false
        property bool nextVisible: false

        property int presedIndex: 0
        property int releasedIndex: 0
        property int clickedIndex: 0

        property int previousX: 0
        property int previousY: 0

        property double prevoiusMaxY: 20000
        property double nextMinY: 20000

        onPressed: {
            mousePressed = true
            previousX = mouseX
            previousY = mouseY
        }
        onMouseXChanged: {
            var moveToX = modelView.flickableItem.contentX - (mouseX - previousX)
            if(moveToX >= 0 && moveToX <= modelView.flickableItem.contentWidth - modelView.flickableItem.width)
            {
                modelView.flickableItem.contentX = moveToX
            }
            previousX = mouseX
        }
        onMouseYChanged: {
            var moveToY = modelView.flickableItem.contentY - (mouseY - previousY)
            if(moveToY >= -modelView.headHeight
                    && moveToY <= modelView.flickableItem.contentHeight - modelView.flickableItem.height - modelView.headHeight)
            {
                modelView.flickableItem.contentY = moveToY
            }

            if(currentPage > 1 && !controlArea.previousVisible
                    && mouseY - previousY > slidHeight
                    && modelView.flickableItem.contentY === -modelView.headHeight)
            {
                controlArea.previousVisible = true
                prevoiusMaxY = mouseY
            }
            else if(mouseY - previousY < -slidHeight)
            {
                controlArea.previousVisible = false
                prevoiusMaxY = 20000
            }
            else if(prevoiusMaxY != 20000 && prevoiusMaxY - mouseY >= modelView.loaderHeight)
            {
                controlArea.previousVisible = true
                prevoiusMaxY = 20000
            }
            else if(prevoiusMaxY != 20000 && prevoiusMaxY < mouseY)
            {
                prevoiusMaxY = mouseY
            }

            if(currentPage < totalPage && !controlArea.nextVisible
                    && mouseY - previousY < -slidHeight &&
                    (modelView.flickableItem.height >= modelView.flickableItem.contentHeight
                    || (modelView.flickableItem.height < modelView.flickableItem.contentHeight
                        && modelView.flickableItem.contentY == modelView.flickableItem.contentHeight - modelView.flickableItem.height - modelView.headHeight)))
            {
                controlArea.nextVisible = true
                nextMinY = mouseY
            }
            else if(mouseY - previousY > slidHeight)
            {
                controlArea.nextVisible = false
                nextMinY = 20000
            }
            else if(nextMinY != 20000 && mouseY - nextMinY >= modelView.loaderHeight)
            {
                controlArea.nextVisible = false
                nextMinY = 20000
            }
            else if(nextMinY != 20000 && mouseY < nextMinY)
            {
                nextMinY = mouseY
            }

            previousY = mouseY
        }
        onReleased: {
            mousePressed = false

            if(controlArea.previousVisible)
            {
                modelView.loadPreviousPage()
                controlArea.previousVisible = false
            }
            else if(controlArea.nextVisible)
            {
                modelView.loadNextPage()
                controlArea.nextVisible = false
            }
        }
        onClicked: {
            if(chooseRow)
            {
                modelView.currentRow = rowAt(mouseX, mouseY + modelView.headHeight)
            }
            rowClicked(modelView.currentRow, mouseX)
        }
    }

    style: TableViewStyle{
        alternateBackgroundColor : "#E5F0F5"
        backgroundColor : "#e8e8e8"
        frame: Rectangle{
            anchors.fill: parent
            color: "#000000"
        }
        corner: Rectangle{
            color: "#E5F0F5"
        }
        scrollBarBackground: Rectangle{
            implicitWidth: modelView.handleWidth
            implicitHeight: modelView.handleWidth
            color: "#A5CEDE"
        }
        decrementControl: Item{
            width: modelView.handleWidth
            height: styleData.horizontal ? modelView.handleWidth : (modelView.handleWidth + modelView.headHeight)
            Rectangle{
                width: modelView.handleWidth
                height: modelView.headHeight
                color: "#E5F0F5"
                visible: !styleData.horizontal
            }
            Rectangle{
                width: modelView.handleWidth
                height: modelView.handleWidth
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                color: "#A5CEDE"
                Image{
                    anchors.fill: parent
                    anchors.margins: 3
                    source: styleData.horizontal ? "qrc:/images/left.png" : "qrc:/images/up.png"
                }
            }
        }
        incrementControl: Rectangle{
            width: modelView.handleWidth
            height: modelView.handleWidth
            color: "#A5CEDE"
            Image{
                anchors.fill: parent
                anchors.margins: 3
                source: styleData.horizontal ? "qrc:/images/right.png" : "qrc:/images/down.png"
            }
        }
        handle: Item{
            implicitWidth: modelView.handleWidth
            implicitHeight: modelView.handleWidth
            Rectangle{
                anchors.fill: parent
                anchors.margins: 2
                color: "#E5F0F5"
            }
        }
    }

    rowDelegate: Rectangle{
        height: modelView.rowHeight
        color: modelView.currentRow === styleData.row ? "#002339" : (styleData.row % 2 === 0) ? "#053654" : "#044063"
        // Rectangle{
        //     width: parent.width
        //     height: modelView.currentRow === styleData.row ? 1 : 0
        //     color: "#F0F0F0"
        //     anchors.top: parent.top
        //     clip: true
        // }
        // Rectangle{
        //     width: parent.width
        //     height: modelView.currentRow === styleData.row ? 1 : 0
        //     color: "#F0F0F0"
        //     anchors.bottom: parent.bottom
        //     clip: true
        // }
    }

    headerDelegate: Rectangle{
        implicitHeight: controlArea.previousVisible ? previousLoad.height + modelView.headHeight : modelView.headHeight
        border.width: 1
        color: Style.backgroundLightColor
        border.color: Style.hbFrameBorderColor
        Text{
            anchors.top: parent.top
            anchors.topMargin: (modelView.headHeight - height)/2
            anchors.horizontalCenter: parent.horizontalCenter
            color: Style.whiteFontColor
            font.bold: true
            font.family: "宋体"
            font.pixelSize: Math.round(Style.style1 * Style.scaleHint)
            text: styleData.value
        }
    }

    Rectangle{
        id: previousLoad
        width: parent.width
        height: controlArea.previousVisible ? modelView.loaderHeight : 0
        anchors.top: parent.top
        anchors.topMargin: modelView.headHeight
        color: "#A5CEDE"
        clip: true
        AnimatedImage{
            anchors.centerIn: parent
            source: "qrc:/images/loading.gif"
            playing: controlArea.previousVisible
        }
    }

    contentFooter: Item{
        width: modelView.width
        height: controlArea.nextVisible? modelView.loaderHeight : 0
        clip: true
        AnimatedImage{
            anchors.centerIn: parent
            source: "qrc:/images/loading.gif"
            playing: controlArea.nextVisible
        }
    }
}
