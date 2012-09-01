 //import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
//import QtQuick 1.1
import Qt 4.7

Rectangle {
    id: screen
    width: 500; height: 500
    property int partition: height/3
    border { width: 1; color: "#DCDCCC"}
    state: "DRAWER_CLOSED"



    MenuBar {
        id:menuBar
        height: screen.partition; width: screen.width
        z: 1
    }

    //Item 2: The editable text area
    Rectangle {
        id:textArea
        width :400; height:400
       // property color fontColor: "white"
        //property alias textContent: textEdit.text
        Flickable {
            id: flickArea
            width: parent.width; height: parent.height
            anchors.fill:parent
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.HorizontalFlick
            interactive: true
            function ensureVisible(r) {
                if (contentX >= r.x)
                contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;
                if (contentY >= r.y)
                contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;
            }

            TextEdit {
                id: textEdit
                x: 0
                y: 0
                anchors.fill:parent
                width:parent.width; height:parent.height
                //color:fontColor
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                focus: true
                wrapMode: TextEdit.Wrap
                font.pointSize:10
                onCursorRectangleChanged: flickArea.ensureVisible(cursorRectangle)
                selectByMouse: true
            }
        }
    }

    //Item 3: The drawer handle
    Rectangle {
        id: drawer
        height: 15; width: parent.width
        border { color : "#6A6D6A"; width: 1 }
        z: 1
        gradient: Gradient {
                GradientStop { position: 0.0; color: "#8C8F8C" }
                GradientStop { position: 0.17; color: "#6A6D6A" }
                GradientStop { position: 0.77; color: "#3F3F3F" }
                GradientStop { position: 1.0; color: "#6A6D6A" }
            }
        Image {
            id: arrowIcon
            source: "./images/arrow.png"
            anchors.horizontalCenter: parent.horizontalCenter
            Behavior{ NumberAnimation { property: "rotation"; easing.type: Easing.OutExpo } }
        }

        MouseArea {
            id: drawerMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: parent.border.color = Qt.lighter("#6A6D6A")
            onExited:  parent.border.color = "#6A6D6A"
            onClicked: {
                if (screen.state == "DRAWER_CLOSED") {
                    screen.state = "DRAWER_OPEN"
                }
                else if (screen.state == "DRAWER_OPEN"){
                    screen.state = "DRAWER_CLOSED"
                }
            }
        }
    }
//! [states]
    states:[
        State {
            name: "DRAWER_OPEN"
            PropertyChanges { target: menuBar; y: 0}
            PropertyChanges { target: textArea; y: partition + drawer.height}
            PropertyChanges { target: drawer; y: partition}
            PropertyChanges { target: arrowIcon; rotation: 180}

            PropertyChanges {
                target: buttonopenword
                x: 360
                opacity: 1
            }

            PropertyChanges {
                target: openwordimage
                x: 0
                y: 0
                width: 30
                height: 30
                source: "images/win/fileopen.png"
                sourceSize.height: 32
                sourceSize.width: 32
                opacity: 1
            }
        },
        State {
            name: "DRAWER_CLOSED"
            PropertyChanges { target: menuBar; y:-height; }
            PropertyChanges { target: textArea; x: 0; y: drawer.height; width: 500; height: screen.height - drawer.height }
            PropertyChanges { target: drawer; y: 0 }
            PropertyChanges { target: arrowIcon; rotation: 0 }

            PropertyChanges {
                target: flickArea
                x: 0
                y: 63
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 63
                anchors.rightMargin: 0
            }

            PropertyChanges {
                target: row1
                x: 29
                y: 45
                width: 442
                height: 39
                anchors.horizontalCenterOffset: 0
            }

            PropertyChanges {
                target: openwordimage
                x: 0
                y: 0
                width: 30
                height: 30
                opacity: 1
                sourceSize.height: 32
                sourceSize.width: 32
                source: "images/mac/fileopen.png"
            }

            PropertyChanges {
                target: buttonopenword
                opacity: 1
            }
        }
    ]
//! [states]

//! [transitions]
    transitions: [
        Transition {
            to: "*"
            NumberAnimation { target: textArea; properties: "y, height"; duration: 100; easing.type:Easing.OutExpo }
            NumberAnimation { target: menuBar; properties: "y"; duration: 100; easing.type: Easing.OutExpo }
            NumberAnimation { target: drawer; properties: "y"; duration: 100; easing.type: Easing.OutExpo }
        }
    ]
//! [transitions]


        Row
         {
             id: row1
             x: 75
             y: 46
             width: 470
             height: 39
             anchors.horizontalCenterOffset: 0
             anchors.horizontalCenter: parent.horizontalCenter
             spacing: 10
             BaseButton {
                 id: buttonNew
                 //text: "New"
                 onClicked:  {
                     textEdit.text = "";
                 }
                 Image {
                     anchors.fill: parent
                     id: newImage
                     source: "./images/mac/filenew.png"
                 }
             }
             BaseButton {
                 id: buttonOpen
                //text: "Open"
                 Image {
                     anchors.fill: parent
                     id: openImage
                     source: "./images/mac/fileopen.png"
                 }
                 onClicked:
                 {
                     textEdit.text = textclass.fileOpen();
                 }
                 }

             BaseButton {
                 id: buttonSave
                // text: "Save"

                 Image {
                     anchors.fill: parent
                     id: saveImage
                     source: "./images/mac/filesave.png"
                 }
                 onClicked:
                 {
                     textclass.fileSaveAs(textEdit.text);
                 }
             }
              BaseButton {
                 id: buttonPrint
                // text: "Print"

                 Image {
                     anchors.fill: parent
                     id: printImage
                     source: "./images/mac/fileprint.png"
                 }
                 onClicked:
                 {
                     textclass.filePrint(textEdit.text);
                 }
             }
//              BaseButton {
//                 id: buttonRedo
//                // text: "Redo"
//                 Image {
//                     anchors.fill: parent
//                     id: redoImage
//                     source: "./images/mac/editredo.png"
//                 }
//             }

//              BaseButton {
//                 id: buttonUndo
//                 //text: "Undo"
//                 Image {
//                     anchors.fill: parent
//                     id: undoImage
//                     source: "./images/mac/editundo.png"
//                 }
//                 onClicked:
//                 {

//                 }
//             }

             BaseButton {
                 id: buttonLeft
                 //text: "Left"
                 Image {
                     anchors.fill: parent
                     id: leftImage
                     source: "./images/mac/textleft.png"
                 }
                 onClicked:
                 {
                     textEdit.horizontalAlignment = TextEdit.AlignLeft;
                 }
             }
              BaseButton {
                         id: buttonCenter
                        // text: "Center"
                         Image {
                             anchors.fill: parent
                             id: centerImage
                             source: "./images/mac/textcenter.png"
                         }
                         onClicked:
                         {
                             textEdit.horizontalAlignment = TextEdit.AlignHCenter;
                         }
                     }
              BaseButton {
                 id: buttonRigth
                 //text: "Rigth"
                 Image {
                     anchors.fill: parent
                     id: rigthImage
                     source: "./images/mac/textright.png"
                 }
                 onClicked:
                 {
                     textEdit.horizontalAlignment = TextEdit.AlignRight;
                 }
             }
             BaseButton {
                 id: buttonBold
                 //text: "Rigth"
                 onClicked:
                 {
                     var b = textEdit.selectionStart;
                     var e = textEdit.selectionEnd;
                     textEdit.text =  textEdit.text.substring(0,b)+ "<b>"+textEdit.selectedText+"</b>"+textEdit.text.substring(e,textEdit.text.length);

                 }
                 Image {
                     anchors.fill: parent
                     id: boldImage
                     source: "./images/mac/textbold.png"
                 }
             }
             BaseButton {
                 id: buttonItalic
                 //text: "Rigth"
                 Image {
                     anchors.fill: parent
                     id: italicImage
                     source: "./images/mac/textitalic.png"
                 }
                 onClicked:
                 {
                     var b = textEdit.selectionStart;
                     var e = textEdit.selectionEnd;
                     textEdit.text =  textEdit.text.substring(0,b)+ "<i>"+textEdit.selectedText+"</i>"+textEdit.text.substring(e,textEdit.text.length);

                 }
             }
              BaseButton {
                 id: buttonUnder
                 //text: "Rigth"
                 Image {
                     anchors.fill: parent
                     id: underImage
                     source: "./images/mac/textunder.png"
                 }
                 onClicked:
                 {
                     var b = textEdit.selectionStart;
                     var e = textEdit.selectionEnd;
                     textEdit.text =  textEdit.text.substring(0,b)+ "<u>"+textEdit.selectedText+"</u>"+textEdit.text.substring(e,textEdit.text.length);

                 }
             }

             BaseButton {
                 id: buttonopenword
                 x: 396
                 y: 0
                 opacity: 0

                 Image {
                     anchors.fill: parent
                     id: openwordImage
                     source: "./images/mac/fileopen.png"
                 }
                 onClicked:
                 {
                    textclass.openWord(textEdit.text);
                 }
             }
         }

}
