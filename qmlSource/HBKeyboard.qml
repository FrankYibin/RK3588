import QtQuick 2.15
import QtQuick.Controls 2.15
import Style 1.0
Rectangle {
    id: keyboard
    width: Math.round(800 * Style.scaleHint)
    height: Math.round(310 * Style.scaleHint)
    color: "#1E1E1E"

    // property color skinColor: skinIndex === 0 ? "#1E1E1E" : (skinIndex === 1 ? "#D8D8D8" : "#190724")
    // property int skinIndex: 0
    property bool active: false
    property bool upperCase: false
    property bool isChinese: true
    property bool isAlphabet: true

    readonly property int heightSize:           Math.round(50 * Style.scaleHint)
    readonly property int rowWidthSize:         Math.round(55 * Style.scaleHint)
    readonly property int enterRowWidthSize:    Math.round(95 * Style.scaleHint)
    readonly property int abcRowWidthSize:      Math.round(95 * Style.scaleHint)
    readonly property int fontsize: Math.round(Style.style6 * Style.scaleHint)
    signal keyPressed(var key)
    signal backspace()
    signal enter()
    signal space()

    // 拼音输入相关
    property string pinyinBuffer: ""
    property var candidateList: []
    property int candidatePage: 0
    readonly property int candidatesPerPage: 11
    function pagedCandidates() {
        var start = candidatePage * candidatesPerPage;
        var end = start + candidatesPerPage;
        return candidateList.slice(start, end);
    }

    // 主键盘区
    Column {
        id: keyboardLayout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Math.round(10 * Style.scaleHint)
        spacing: Math.round(10 * Style.scaleHint)

        // Row {
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     spacing: Math.round(5 * Style.scaleHint)
        //     Repeater {
        //         model: ["1","2","3","4","5","6","7","8","9","0"]
        //         HBKeyButton {
        //             text: modelData
        //             implicitWidth: rowWidthSize
        //             implicitHeight: heightSize
        //             fontSize: fontsize
        //             onClicked: keyboard.keyPressed(text)
        //         }
        //     }
        // }

        Row {
            id: fristRow
            spacing: Math.round(5 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater {
                model: {
                    if(keyboard.isAlphabet === true)
                    {
                        if(keyboard.upperCase === true)
                            return ["Q","W","E","R","T","Y","U","I","O","P"]
                        else
                            return ["q","w","e","r","t","y","u","i","o","p"]

                    }
                    else
                    {
                        return ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
                    }
                }

                HBKeyButton {
                    text: modelData
                    implicitWidth: rowWidthSize
                    implicitHeight: heightSize
                    fontSize: fontsize
                    onClicked: keyboard.handleLetter(text)
                }
            }
            HBKeyButton {
                text: "Del"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.handleBackspace()
            }
        }

        Row {
            id: secondRow
            spacing: Math.round(5 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater {
                model: {
                    if(keyboard.isAlphabet === true)
                    {
                        if(keyboard.upperCase === true)
                            return ["A","S","D","F","G","H","J","K","L"]
                        else
                            return ["a","s","d","f","g","h","j","k","l"]
                    }
                    else
                    {
                        return ["@", "#", "%", "&", "*", "-", "+", "(", ")"]
                    }
                }
                HBKeyButton {
                    text: modelData
                    implicitWidth: rowWidthSize
                    implicitHeight: heightSize
                    fontSize: fontsize
                    onClicked: keyboard.handleLetter(text)
                }
            }
        }

        Row {
            id: thirdRow
            spacing: Math.round(5 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            HBKeyButton {
                text: keyboard.upperCase ? "A/a" : "A/a"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.upperCase = !keyboard.upperCase
            }
            Repeater {
                model: {
                    if(keyboard.isAlphabet === true)
                    {
                        if(keyboard.upperCase == true)
                            return ["Z", "X", "C", "V", "B", "N", "M"]
                        else
                            return ["z", "x", "c", "v", "b", "n", "m"]
                    }
                    else
                    {
                        return ["!", "\"", "<", ">", "'", ":", ";"]
                    }
                }
                HBKeyButton {
                    text: modelData
                    implicitWidth: rowWidthSize
                    implicitHeight: heightSize
                    fontSize: fontsize
                    onClicked: keyboard.handleLetter(text)
                }
            }
            HBKeyButton {
                text: (keyboard.isAlphabet === true) ? "," : "/"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: {
                    if(keyboard.isAlphabet === true)
                        keyboard.handleLetter(",")
                    else
                        keyboard.handleLetter("/")
                }
            }
            HBKeyButton {
                text: (keyboard.isAlphabet === true) ? "." : "?"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: {
                    if(keyboard.isAlphabet === true)
                        keyboard.handleLetter(".")
                    else
                        keyboard.handleLetter("?")
                }
            }
            HBKeyButton {
                text: keyboard.upperCase ? "A/a" : "A/a"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.upperCase = !keyboard.upperCase
            }

        }
        // 第五排：skin, abc, ,, 空格, ., CH, Enter
        Row {
            id: fourthRow
            spacing: Math.round(5 * Style.scaleHint)
            anchors.horizontalCenter: parent.horizontalCenter
            HBKeyButton {
                text: (keyboard.isAlphabet === true) ? "&123" : "ABC"
                implicitWidth: abcRowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.isAlphabet = !keyboard.isAlphabet
            }

            HBKeyButton {
                text: keyboard.isChinese ? "CH" : "EN"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.isChinese = !keyboard.isChinese
            }

            HBKeyButton {
                text: keyboard.isChinese ? "中文" : "English" // 空格
                implicitWidth: rowWidthSize * 5
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.handleSpace()
            }

            HBKeyButton {
                text: (keyboard.isAlphabet === true) ? "'" : "."
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: {
                    if(keyboard.isAlphabet === true)
                        keyboard.handleLetter("'")
                    else
                        keyboard.handleLetter(".")
                }
            }

            HBKeyButton {
                text: ":-)"
                implicitWidth: rowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.handleLetter(":-)")
            }

            HBKeyButton {
                text: "Enter"
                implicitWidth: enterRowWidthSize
                implicitHeight: heightSize
                fontSize: fontsize
                onClicked: keyboard.handleEnter()
            }

        }
    }
    // 候选词区域
    Item {
        id: chineseLayout
        width: keyboardLayout.width
        height: Math.round(60 * Style.scaleHint)
        anchors.bottom: keyboardLayout.top
        anchors.bottomMargin: Math.round(5 * Style.scaleHint)
        anchors.left: keyboardLayout.left
        Row {
            anchors.fill: parent
            spacing: Math.round(5 * Style.scaleHint)
            // 左翻页按钮
            HBKeyButton {
                visible: keyboard.candidateList.length > keyboard.candidatesPerPage && keyboard.candidatePage > 0
                text: "<"
                implicitHeight: heightSize
                implicitWidth: heightSize
                anchors.verticalCenter: parent.verticalCenter
                buttonColor: "#333333"
                fontFamily: "宋体"
                onClicked: keyboard.candidatePage--
            }
            // 候选词
            Repeater {
                model: keyboard.pagedCandidates()
                HBKeyButton {
                    text: modelData
                    implicitHeight: heightSize
                    implicitWidth: heightSize
                    anchors.verticalCenter: parent.verticalCenter
                    buttonColor: "#333333"
                    fontFamily: "宋体"
                    onClicked: keyboard.selectCandidate(text)
                }
            }
            // 右翻页按钮
            HBKeyButton {
                visible: keyboard.candidateList.length > keyboard.candidatesPerPage && (keyboard.candidatePage + 1) * keyboard.candidatesPerPage < keyboard.candidateList.length
                text: ">"
                implicitHeight: heightSize
                implicitWidth: heightSize
                anchors.verticalCenter: parent.verticalCenter
                buttonColor: "#333333"
                fontFamily: "宋体"
                onClicked: keyboard.candidatePage++
            }
            // 显示拼音缓冲
            Text {
                text: keyboard.pinyinBuffer.length > 0 ? keyboard.pinyinBuffer : ""
                color: "#333333"
                font.pixelSize: Math.round(Style.style5 * Style.scaleHint)
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                visible: keyboard.pinyinBuffer.length > 0
            }
        }
    }
    // 拼音输入处理
    function handleLetter(text)
    {
        if (keyboard.isChinese)
        {
            if (text.match(/[a-zA-Z]/))
            {
                keyboard.pinyinBuffer += text.toLowerCase()
                updateCandidates()
            }
            else
            {
                if (keyboard.pinyinBuffer.length > 0 && keyboard.candidateList.length > 0)
                {
                    // 自动上屏第一个候选
                    keyboard.keyPressed(keyboard.candidateList[0])
                    keyboard.pinyinBuffer = ""
                    keyboard.candidateList = []
                }
                keyboard.keyPressed(text)
            }
        }
        else
        {
            keyboard.keyPressed(text)
        }
    }
    function handleBackspace()
    {
        if (keyboard.isChinese)
        {
            if (keyboard.pinyinBuffer.length > 0)
            {
                keyboard.pinyinBuffer = keyboard.pinyinBuffer.slice(0, -1)
                updateCandidates()
            }
            else
            {
                keyboard.backspace()
            }
        }
        else
        {
            keyboard.backspace()
        }
    }
    function handleSpace()
    {
        if (keyboard.isChinese)
        {
            if (keyboard.pinyinBuffer.length > 0 && keyboard.candidateList.length > 0)
            {
                keyboard.keyPressed(keyboard.candidateList[0])
                keyboard.pinyinBuffer = ""
                keyboard.candidateList = []
            }
            else
            {
                keyboard.space()
            }
        }
        else
        {
            keyboard.space()
        }
    }

    function handleEnter()
    {
        if (keyboard.isChinese)
        {
            if (keyboard.pinyinBuffer.length > 0 && keyboard.candidateList.length > 0)
            {
                keyboard.keyPressed(keyboard.candidateList[0])
                keyboard.pinyinBuffer = ""
                keyboard.candidateList = []
            }
            keyboard.enter()
        }
        else
        {
            keyboard.enter()
        }
    }

    function selectCandidate(text)
    {
        keyboard.keyPressed(text)
        keyboard.pinyinBuffer = ""
        keyboard.candidateList = []
        keyboard.candidatePage = 0
    }
    function updateCandidates()
    {
        if (keyboard.pinyinBuffer.length > 0)
        {
            keyboard.candidateList = PinyinDict.getCandidates(keyboard.pinyinBuffer)
        }
        else
        {
            keyboard.candidateList = []
        }
        keyboard.candidatePage = 0
    }
}
