#ifndef BRIGHTNESS_WIDGET_H
#define BRIGHTNESS_WIDGET_H

#include <QWidget>
#include "brightnessapplet.h"


class BrightnessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BrightnessWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);

signals:
    void wheelEventTriggered(const int  &value);
    void wheelEventTip();

private:
    void initUI();

private:
//    QScopedPointer<BrightnessApplet> m_applet;
    QPixmap m_iconPixmap;
};

#endif
