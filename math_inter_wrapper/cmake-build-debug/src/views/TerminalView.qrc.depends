import QtQuick
import QtQuick.Controls 2.15
import UntitledProject3

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "ui"


    Item {
        id: terminalView
        width: 800
        height: 600

        property alias command: commandInput.text

        Rectangle {
            anchors.fill: parent
            color: "#282c34"
            border.color: "#61afef"
            radius: 8

            Column {
                anchors.fill: parent
                spacing: 4

                TextArea {
                    id: outputArea
                    anchors.fill: parent
                    wrapMode: Text.Wrap
                    font.pixelSize: 16
                    readOnly: true
                    color: "white"
                    text: terminalViewModel.output.join("\n")
                }

                Row {
                    spacing: 8
                    TextField {
                        id: commandInput
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width * 0.9
                        placeholderText: "Enter command..."
                        font.pixelSize: 16
                        color: "#abb2bf"
                        background: Rectangle {
                            color: "#2c323c"
                            radius: 5
                        }
                    }

                    Button {
                        text: "Run"
                        onClicked: terminalViewModel.submitCommand()
                    }
                }
            }
        }
    }

}

