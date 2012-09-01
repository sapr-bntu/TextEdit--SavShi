import Qt 4.7
//import QtQuick 1.0

Rectangle {
    id: editMenu
    height: 480; width:1000
    color: "powderblue"
    property color buttonBorderColor: "#7A8182"
    property color buttonFillColor: "#61BDCACD"
    property string menuName:"Edit"
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#6A7570" }
        GradientStop { position: 1.0; color: Qt.darker("#6A7570") }
    }

    Rectangle {
        id:actionContainer
         color:"transparent"
        anchors.centerIn: parent
        width: parent.width; height: parent.height / 5
        Row {
            anchors.centerIn: parent
            spacing: parent.width/9
            Button {
                id: cutButton
                buttonColor: buttonFillColor
                label: "Cut"
                labelSize: 16
                borderColor: buttonBorderColor
                height: actionContainer.height; width: actionContainer.width/6

                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                    GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                }
                onButtonClick:
                {
                    textEdit.cut();
                }
            }
            Button {
                id: copyButton
                height: actionContainer.height; width: actionContainer.width/6
                buttonColor: buttonFillColor
                label: "Copy"
                borderColor: buttonBorderColor
                labelSize: 16


                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                    GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                }
                onButtonClick:
                {
                    textEdit.copy();
                }
            }
            Button {
                id: pasteButton
                label: "Paste"
                height: actionContainer.height; width: actionContainer.width/6
                labelSize: 16
                buttonColor: buttonFillColor
                borderColor:buttonBorderColor

                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                    GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                }
                onButtonClick:
                {
                    textEdit.paste();
                }
            }
            Button {
                id: selectButton
                label: "Select All"
                height: actionContainer.height; width: actionContainer.width/6
                labelSize: 16
                buttonColor: buttonFillColor
                borderColor:buttonBorderColor
                onButtonClick:
                {
                    textEdit.selectAll();
                }

                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                    GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                }
            }
        }
    }
}
