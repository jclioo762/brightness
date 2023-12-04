#include "brightnesswidget.h"
#include "common/imageutil.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include "common/brightnessutil.h"

#define PLUGIN_ICON_MAX_SIZE 32

BrightnessWidget::BrightnessWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void BrightnessWidget::initUI()
{
    int iconSize = PLUGIN_ICON_MAX_SIZE;
    const auto ratio = devicePixelRatioF();
    QString iconString = "brightness.svg";
    m_iconPixmap = ImageUtil::loadSvg(iconString, ":/", iconSize, ratio);
}

void BrightnessWidget::paintEvent(QPaintEvent *e)
{
    // 调用父类的paintEvent函数
    QWidget::paintEvent(e);

    // 绘制图标
    QPainter painter(this);
    const QRectF &rf = QRectF(rect());
    const QRectF &rfp = QRectF(m_iconPixmap.rect());
    painter.drawPixmap(rf.center() - rfp.center() / m_iconPixmap.devicePixelRatioF(), m_iconPixmap);
}

/**
 * 鼠标滚轮事件
 * @param e
 */
//int lightNum = 1;
void BrightnessWidget::wheelEvent(QWheelEvent *e)
{
//    int wheelNum = e->angleDelta().y();
//    if (wheelNum > 0) {
//        if (lightNum > 99) {
//            return;
//        }
//        lightNum = BrightnessUtil::getBackLightPercentage() + 3;
//    } else {
//        if (lightNum < 2)  {
//            return;
//        }
//        lightNum = BrightnessUtil::getBackLightPercentage() - 3;
//    }
//    emit wheelEventTip();
//    emit wheelEventTriggered(lightNum);

//    QWheelEvent *event = new QWheelEvent(e->pos(), e->delta(), e->buttons(), e->modifiers());
//    qApp->postEvent(m_applet->getSlider(), event);
    e->accept();
}