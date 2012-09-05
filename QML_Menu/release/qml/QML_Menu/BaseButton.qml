// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import Qt 4.7
//import QtQuick 1.1

Rectangle {
    id:button
    property alias text: textItem.text
    signal clicked

    width: 30; height: 30
    border.width: 1
    radius: 3
    smooth: true

    gradient: Gradient {
        GradientStop { position: 0.0; color: "darkGray" }
        GradientStop { position: 0.5; color: "black" }
        GradientStop { position: 1.0; color: "darkGray" }
    }

    Text {
        id: textItem
        anchors.centerIn: parent
        font.pointSize: 20
        color: "white"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
//            doOp(operation)
            button.clicked()
    }
    }
}
