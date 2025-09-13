import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Qt.labs.folderlistmodel 2.1
Item {

    property string imgDir: "C:/Users/jerryw.wang/Documents/MeteringDisplay/RK3588" // 修改为你的图片目录
    property alias currentIndex: pictureList.currentIndex
    signal fileSelected(string fileName) // <-- 声明信号
    Rectangle
    {
        id: background
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        focus: true
        gradient: Gradient {
            GradientStop { position: 0.0; color: Style.backgroundLightColor }
            GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }

    FolderListModel {
        id: folderModel
        folder: "file:///" + imgDir.replace(/\\/g, "/")
        nameFilters: ["*.jpg", "*.jpeg", "*.png", "*.bmp", "*.gif", "*.tif", "*.tiff"]
        showDirs: false
    }

    ScrollView {
        id: pictureScrollView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(50 * Style.scaleHint)
        // 显示滚动条并加宽
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.width: 24
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded
        ScrollBar.horizontal.width: 24

        ListView {
            id: pictureList
            width: parent.width
            height: parent.height
            model: folderModel
            // 支持鼠标点击选中
            delegate: Rectangle {
                width: parent.width
                height: 120
                color: ListView.isCurrentItem ? Style.backgroundLightColor : (index % 2 === 0 ? "#222" : "#333")
                radius: 8
                Row {
                    spacing: 20
                    anchors.verticalCenter: parent.verticalCenter

                    Image {
                        id: img
                        source: fileURL
                        width: 100
                        height: 100
                        fillMode: Image.PreserveAspectFit
                        onStatusChanged: {
                            if (status === Image.Ready) {
                                // 触发属性绑定
                            }
                        }
                    }
                    Column {
                        spacing: 5
                        Text { text: "文件名: " + fileName; color: "white" }
                        Text { text: "路径: " + fileURL; color: "white"; font.pixelSize: 10 }
                        Text { text: "大小: " + Math.round(fileSize/1024) + " KB"; color: "white" }
                        Text { text: "分辨率: " + img.width + " x " + img.height; color: "white" }
                        Text { text: "格式: " + fileName.split('.').pop().toUpperCase(); color: "white" }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: pictureList.currentIndex = index
                }
            }
        }
    }

    Item {
        anchors.top: pictureScrollView.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        HBPrimaryButton
        {
            id: buttonOK
            anchors.centerIn: parent
            width: Math.round(100 * Style.scaleHint)
            height: Math.round(30 * Style.scaleHint)
            text: qsTr("确认")
            onClicked:
            {
                if (pictureList.currentIndex >= 0 && pictureList.currentIndex < folderModel.count) {
                    fileSelected(folderModel.get(currentIndex, "fileName"))
                }
                mainWindow.showPictureList(false)
            }
        }
    }

}
