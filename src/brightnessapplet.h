#ifndef BRIGHTNESS_APPLET_H
#define BRIGHTNESS_APPLET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QtWidgets/QSlider>
#include "components/horizontalseperator.h"
#include "common/common.h"
#include "components/lightslider.h"

class BrightnessApplet : public QWidget
{
    Q_OBJECT

public:
    explicit BrightnessApplet(QWidget *parent = nullptr);
    void setBackLightInfo();
    BackLightInfo getCurBackLight();
    LightSlider *getSlider();

public slots:
    void setBackLight(const int  &value);

private:
    void initUI();

private:
    QVBoxLayout *central_layout;
    QLabel *m_titleLabel;
    QLabel *m_infoLabel;
    LightSlider *slider;
    HorizontalSeperator *m_seperator;
    QList<BackLightInfo>  *m_backLightInfoList;
};

#endif
