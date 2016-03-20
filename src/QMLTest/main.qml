import QtQuick 2.3
import QtQuick.Window 2.2

//Window {
//    visible: true

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            Qt.quit();
//        }
//    }

//    Text {
//        text: qsTr("Hello World")
//        anchors.centerIn: parent
//    }
//}

//import QtQuick 2.0
import OpenGLUnderQML 1.0
import QtQuick.Controls 1.1

Window {
    visible: true
    width: 512
    height: 512

        Squircle {
            SequentialAnimation on t {
                NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
                NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
                loops: Animation.Infinite
                running: true
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
//                myMopup.popup()
            }
        }

        Rectangle {
            color: Qt.rgba(1, 1, 1, 0.7)
            radius: 10
            border.width: 1
            border.color: Qt.rgba("white")
            anchors.fill: label
            anchors.margins: -10

//            ColorAnimation on color { to: "white"; duration: 2000 }
        }

        Text {
            id: label
            color: "black"
            wrapMode: Text.WordWrap
            text: "notification"
//            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 20
        }

//        function entryHandle() {
//            console.debug("hellow1")
//        }

//        Menu {
//            id: myMopup
//            MenuItem {
//                text: "Entry"
//                shortcut: "x+x"
//                onTriggered: entryHandle()
//            }
//        }


//    }
}
