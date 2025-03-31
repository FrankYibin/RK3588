/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtGraphicalEffects 1.15
import Style 1.0
import Com.Branson.RecipeEnum 1.0
Item {
    readonly property color titleBackgroundColor: "#E1EAEA"
    readonly property int iconSize: 25
    readonly property int bigIconSize: 35
    readonly property int creatingIconSize: 44
    property bool isActive: false
    property bool isNewCard: false
    property string qmltextAction:      "Actions"
    property string qmltextNewCard:     "New Recipe"
    property string numberAssigned: "7" //for the recipe or sequence numbers
    property string nameAssigned: "Speakerbox" // for the recipe or sequence names
    property string weldCountTitle: "Cycle Count"
    property string weldCountValue: "10"
    property alias actionModel: actionButton.model
    property alias strDataModel: cardDetailsInfo.model

    signal signalActionEvent(var actionIndex)

    RectangularGlow {
        id: existingGlowEffective
        anchors.fill: existingCardFront
        glowRadius: 3
        spread: 0.2
        opacity: 0.2
        color: "#80000000"
        cornerRadius: existingCardFront.radius + glowRadius
        visible: isNewCard === true ? false : true
    }

    Rectangle {
        id: existingCardFront
        width: parent.width
        height: parent.height
        clip: true
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: isActive === true ? Style.activeFrameBorderColor: Style.frameBorderColor
        visible: isNewCard === true ? false : true
        Rectangle {
            id: cardTitle
            anchors.top: parent.top
            anchors.topMargin: parent.border.width
            anchors.left: parent.left
            anchors.leftMargin: parent.border.width
            height: (parent.height - 2 * parent.border.width)/2
            width: parent.width - 2 * parent.border.width
            color: isActive === true ? titleBackgroundColor : "#FFFFFF"
            Text {
                id: cardName
                anchors.centerIn: parent
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: numberAssigned + " : " + nameAssigned
                font.family: Style.regular.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                font.bold: true
                color: isActive === true ? Style.blueFontColor : Style.blackFontColor
            }
        }
        Rectangle {
            id: cardDetails
            anchors.top: cardTitle.bottom
            anchors.left: cardTitle.left
            height: cardTitle.height
            width: cardTitle.width
            color: isActive === true ? titleBackgroundColor : "#FFFFFF"
            Column {
                anchors.centerIn: parent
                Repeater {
                    id: cardDetailsInfo
                    delegate: Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        wrapMode: Text.NoWrap
                        elide: Text.ElideRight
                        text: model.TitleNum + ": " + model.TitleDetails
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                        color: isActive === true ? Style.blueFontColor : Style.blackFontColor
                    }
                }

                Text {
                    id: separator
                    anchors.horizontalCenter: parent.horizontalCenter
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: "..."
                    height: cycleCount.height
                    font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                    color: {
                        if(cardDetailsInfo.count > 2)
                        {
                            if(isActive === true)
                                return Style.blueFontColor
                            else
                                return Style.blackFontColor
                        }
                        else
                            return "transparent"
                    }
                }

                Text {
                    id: cycleCount
                    anchors.horizontalCenter: parent.horizontalCenter
                    wrapMode: Text.NoWrap
                    elide: Text.ElideRight
                    text: weldCountTitle + " : " + weldCountValue
                    font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                    color: isActive === true ? Style.blueFontColor : Style.blackFontColor
                }
            }
        }

        MouseArea {
            id: frontRectangleMouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onReleased: {
                actionAnimation.restart()
                frontRectangleMouseArea.visible = false
            }
        }

        Rectangle {
            id: existingCardBack
            width: parent.width
            height: parent.height
            x: 0
            y: parent.height
            clip: true
            border.width: Style.scaleHint === 1.0 ? 1 : 3
            border.color: isActive === true ? Style.activeFrameBorderColor: Style.frameBorderColor
            Rectangle {
                id: actionHeader
                anchors.top: parent.top
                anchors.topMargin: existingCardBack.border.width
                anchors.left: parent.left
                anchors.leftMargin: existingCardBack.border.width
                width: parent.width - 2 * existingCardBack.border.width
                height: Math.round(40 * Style.scaleHint)
                color: titleBackgroundColor

                Image {
                    id: deleteIcon
                    anchors.left: parent.left
                    anchors.leftMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/Trash.svg"
                    height: Math.round(bigIconSize * Style.scaleHint)
                    width: Math.round(bigIconSize * Style.scaleHint)
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: deleteIcon.width
                    sourceSize.height: deleteIcon.height
                    smooth: true
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            signalActionEvent(RecipeEnum.DELETE_IDX)
                            reverseActionAnimation.restart()
                            frontRectangleMouseArea.visible = true
                        }
                    }
                }

                Image {
                    id: infoIcon
                    anchors.right: parent.right
                    anchors.rightMargin: Math.round(5 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/Info.svg"
                    height: Math.round(iconSize * Style.scaleHint)
                    width: Math.round(iconSize * Style.scaleHint)
                    sourceSize.width: infoIcon.width
                    sourceSize.height: infoIcon.height
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            signalActionEvent(RecipeEnum.INFORMATION_IDX)
                        }
                    }
                }

                Image {
                    id: copyIcon
                    anchors.right: infoIcon.left
                    anchors.rightMargin: Math.round(40 * Style.scaleHint)
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/Copy.svg"
                    height: Math.round(iconSize * Style.scaleHint)
                    width: Math.round(iconSize * Style.scaleHint)
                    sourceSize.width: copyIcon.width
                    sourceSize.height: copyIcon.height
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            signalActionEvent(RecipeEnum.COPY_IDX)
                            reverseActionAnimation.restart()
                            frontRectangleMouseArea.visible = true
                        }
                    }
                }

                Row {
                    id: actionArea
                    anchors.centerIn: parent
                    spacing: Math.round(10 * Style.scaleHint)
                    Image {
                        id: actionIcon
                        source: "qrc:/images/Chevron.svg"
                        height: Math.round(iconSize * Style.scaleHint)
                        width: Math.round(iconSize * Style.scaleHint)
                        fillMode: Image.PreserveAspectFit
                        anchors.bottom: actionTitle.bottom
                        sourceSize.width: actionIcon.width
                        sourceSize.height: actionIcon.height
                        smooth: true
                    }
                    Text {
                        id: actionTitle
                        wrapMode: Text.NoWrap
                        elide: Text.ElideRight
                        text: qmltextAction
                        verticalAlignment: Text.AlignVCenter
                        font.family: Style.semibold.name
                        font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                        color: Style.blackFontColor
                    }
                }
                MouseArea {
                    id: backRectangleMouseArea
                    anchors.fill: actionArea
                    cursorShape: Qt.PointingHandCursor
                    onReleased: {
                        reverseActionAnimation.restart()
                        frontRectangleMouseArea.visible = true
                    }
                }
            }

            Rectangle {
                id: actionButtonArray
                anchors.top: actionHeader.bottom
                anchors.bottom: parent.bottom
                anchors.bottomMargin: existingCardBack.border.width
                anchors.left: actionHeader.left
                width: actionHeader.width
                Grid {
                    anchors.centerIn: parent
                    rows: 2
                    columns: 2
                    rowSpacing: Math.round(10 * Style.scaleHint)
                    columnSpacing: Math.round(8 * Style.scaleHint)
                    Repeater {
                        id: actionButton
                        delegate: BransonChildButton
                        {
                            text: model.ActionName
                            width: Math.round(175 * Style.scaleHint)
                            height: Math.round(50 * Style.scaleHint)
                            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
                            onChildButtonClicked: {
                                signalActionEvent(model.ActionIndex)
                                reverseActionAnimation.restart()
                                frontRectangleMouseArea.visible = true
                            }
                        }
                    }
                }
            }
        }
    }

    NumberAnimation {
        id: actionAnimation
        target: existingCardBack
        property: "y"
        to: 0
        duration: 250
    }

    NumberAnimation {
        id: reverseActionAnimation
        target: existingCardBack
        property: "y"
        to: existingCardBack.height
        duration: 250
    }

    RectangularGlow {
        id: creatingGlowEffective
        anchors.fill: creatingCard
        glowRadius: 3
        spread: 0.2
        opacity: 0.2
        color: "#80000000"
        cornerRadius: creatingCard.radius + glowRadius
        visible: isNewCard === true ? true : false
    }

    Rectangle {
        id: creatingCard
        width: parent.width
        height: parent.height
        clip: true
        border.width: Style.scaleHint === 1.0 ? 1 : 3
        border.color: Style.frameBorderColor
        visible: isNewCard === true ? true : false
        Column{
            id: newCardMouseArea
            anchors.centerIn: parent
            spacing: 12
            Image {
                id: creatingImage
                source: "qrc:/images/Add.svg"
                height: Math.round(creatingIconSize * Style.scaleHint)
                width: Math.round(creatingIconSize * Style.scaleHint)
                fillMode: Image.PreserveAspectFit
                sourceSize.width: creatingImage.width
                sourceSize.height: creatingImage.height
                smooth: true
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: newCardTitle
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                text: qmltextNewCard
                font.family: Style.semibold.name
                font.pixelSize: Math.round(Style.style6 * Style.scaleHint)
                color: Style.blackFontColor
            }
        }
        MouseArea {
            anchors.fill: newCardMouseArea
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                signalActionEvent(RecipeEnum.CREATE_NEW_IDX)
            }
        }
    }
}
