import QtQuick 2.0
import Style 1.0
Item
{
    Rectangle{
        id: background
        width: parent.width
        height: parent.height
        gradient: Gradient {
        GradientStop { position: 0.0; color: Style.backgroundLightColor }
        GradientStop { position: 1.0; color: Style.backgroundDeepColor }
        }
    }
}
