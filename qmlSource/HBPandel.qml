import QtQuick 2.15
import Style 1.0
import QtQuick.Controls 2.15
Item
{
    width: 240
    height: 240
    property real angle: 0.0


    onAngleChanged:
    {
        if(angle < 60)
            angle = 60;
        if(angle > 300)
            angle = 300
        pointer.pointerAngle = (angle * Math.PI) / 180 // 转换为弧度
        pointer.requestPaint(); // 强制重新绘制
    }

    // 表盘背景
    Rectangle {
        id: background
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height)
        height: width
        radius: width/2
        gradient: Gradient {
            GradientStop { position: 0.0; color: Style.hbPandelBackgroundDeepColor }
            GradientStop { position: 1.0; color: Style.hbPandelBackgroundLightColor }
        }

        transform: Rotation
        {
            angle: 315
            origin.x: width / 2
            origin.y: width / 2
        }
    }

    Rectangle {
        id: pandelFace
        anchors.centerIn: parent
        width: background.width - 20
        height: width
        radius: width/2
        color: Style.hbPandelCentralBackgroundColor

        Canvas {
            id: pandelScale
            anchors.fill: parent
            property int bigScaleLength: 13
            property int smallScaleLength: 8
            property int bigScaleLineWidth: 2
            property int smallScaleLineWidth: 1
            onPaint: {
                const ctx = getContext("2d")
                ctx.reset()

                // 绘制次刻度
                drawScale(ctx, {
                    lineWidth: bigScaleLineWidth,
                    length: bigScaleLength,
                    count: 120,
                    color: "white"
                })
            }

            function drawScale(ctx, config) {
                const center = width/2
                const radius = center - 30
                const angleStep = 240 / config.count
                var length = config.length

                for(let i = 0; i <= config.count; i++)
                {
                    const angle = i * angleStep + 150
                    const rad = angle * Math.PI / 180
                    ctx.beginPath()
                    ctx.lineWidth = (i % 10 === 0) ? bigScaleLineWidth : smallScaleLineWidth
                    if(i < (config.count * 0.8))
                        ctx.strokeStyle = "white"
                    else
                        ctx.strokeStyle = "red"
                    length = (i % 10 === 0) ? bigScaleLength : smallScaleLength
                    ctx.moveTo(
                        center + (radius - length) * Math.cos(rad),
                        center + (radius - length) * Math.sin(rad)
                    )
                    ctx.lineTo(
                        center + radius * Math.cos(rad),
                        center + radius * Math.sin(rad)
                    )

                    ctx.stroke()
                    if(i % 10 === 0)
                    {
                        ctx.font = Math.round(Style.style1 * Style.scaleHint) + "px sans-serif";
                        ctx.fillStyle = "white"
                        ctx.textAlign = "center"
                        ctx.textBaseline = "middle"
                        ctx.fillText(i / 10, center + (radius + 15) * Math.cos(rad), center + (radius + 15) * Math.sin(rad))
                    }
                }

            }
        }

        Canvas {
            id: pointer
            width: parent.width
            height: width
            anchors.centerIn: parent

            property real pointerAngle: (60 * Math.PI) / 180 // 初始指针角度
            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);

                ctx.save();
                ctx.translate(width / 2, height / 2); // 移动到中心
                ctx.rotate(pointerAngle); // 旋转指针

                // 创建指针形状
                ctx.beginPath()
                ctx.moveTo(-5, 0); // 左下角
                ctx.lineTo(5, 0); // 右下角
                ctx.lineTo(0, width / 2 * 0.5); // 尖端
                ctx.closePath();

                // 创建指针渐变填充
                var halogd = ctx.createRadialGradient(0, 0, 0, 0, 0, 60);
                halogd.addColorStop(0, "rgba(255, 69, 0, 1)"); // 中心橙色
                halogd.addColorStop(1, "rgba(255, 140, 0, 1)"); // 尖端黄色

                ctx.fillStyle = halogd;
                ctx.strokeStyle = "white"; // 白色边框
                ctx.lineWidth = 2;

                // 绘制指针
                ctx.fill();
                ctx.stroke();
                ctx.restore();

                // 绘制中心点
                ctx.save();
                var radGradient = ctx.createRadialGradient(0, 0, 0, 0, 0, 5);
                radGradient.addColorStop(0, "rgba(169, 169, 169, 1)"); // 深灰色
                radGradient.addColorStop(0.5, "rgba(255, 255, 255, 1)"); // 白色
                radGradient.addColorStop(1, "rgba(169, 169, 169, 1)"); // 深灰色

                ctx.fillStyle = radGradient;
                ctx.translate(width / 2, height / 2); // 移动到中心
                ctx.beginPath();
                ctx.arc(0, 0, 6, 0, 2 * Math.PI); // 圆心直径为 10
                ctx.fill();
                ctx.restore();
            } // 动态更新指针角度

            // 动态更新指针角度
            // Slider {
            //     anchors.bottom: parent.bottom
            //     anchors.horizontalCenter: parent.horizontalCenter
            //     from: 60
            //     to: 300
            //     value: 0
            //     onValueChanged:
            //     {

            //         pointer.pointerAngle = (value * Math.PI) / 180 // 转换为弧度
            //         pointer.requestPaint(); // 强制重新绘制
            //     }
            // }

        }

        Text{
            id: scale
            text: "X 100"
            font.pixelSize: Math.round(Style.style4 * Style.scaleHint)
            font.family: "Arial"
            color: "white"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
