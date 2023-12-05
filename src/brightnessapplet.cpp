#include "brightnessapplet.h"
#include <QVBoxLayout>
#include "components/horizontalseperator.h"
#include <DFontSizeManager>
#include <QDir>
#include "common/common.h"
#include "common/brightnessutil.h"

#define TITLE_HEIGHT 46
#define TITLE_TEXT "亮度"
// 滑块高
#define SLIDER_HIGHT 70
// QWidget itemPopupApplet 宽度
#define WIDGETFIXEDWIDTH 260
// 当前设备下标 （暂时不实现多设备，懒）
#define CURDEVICEINDEX 0

BrightnessApplet::BrightnessApplet(QWidget *parent)
    : QWidget(parent),
      central_layout(new QVBoxLayout(this)),
      m_infoLabel(new QLabel(this)),
      m_titleLabel(new QLabel(this)),
      slider(new LightSlider(this)),
      m_seperator(new HorizontalSeperator(this)),
      m_backLightInfoList(new QList<BackLightInfo>)
{
    initUI();
    this->setFixedWidth(WIDGETFIXEDWIDTH);
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setBackLight(int)));
}
/**
 * 初始化 UI
 */
void BrightnessApplet::initUI()
{
    setBackLightInfo();
    // 标题 Label
    m_titleLabel->setText(tr(TITLE_TEXT));
    m_titleLabel->setFixedHeight(TITLE_HEIGHT);
    m_titleLabel->setForegroundRole(QPalette::BrightText);
    Dtk::Widget::DFontSizeManager::instance()->bind(m_titleLabel, Dtk::Widget::DFontSizeManager::T4, QFont::Medium);
    // 亮度 Label
    m_infoLabel->setText(QString("%1%").arg(0));
    m_infoLabel->setFixedHeight(TITLE_HEIGHT);
    m_infoLabel->setForegroundRole(QPalette::BrightText);
    Dtk::Widget::DFontSizeManager::instance()->bind(m_infoLabel, Dtk::Widget::DFontSizeManager::T8, QFont::Medium);

    // 标题布局
    QHBoxLayout *deviceLayout = new QHBoxLayout;
    deviceLayout->setSpacing(0);
    deviceLayout->setMargin(0);
    deviceLayout->setContentsMargins(10, 0, 10, 0);
    deviceLayout->addWidget(m_titleLabel, 0, Qt::AlignLeft);
    deviceLayout->addWidget(m_infoLabel, 0, Qt::AlignRight);
    central_layout->addLayout(deviceLayout);

    // 分割线
    QVBoxLayout *seperator_layout = new QVBoxLayout;
    seperator_layout->addWidget(m_seperator);
    central_layout->addLayout(seperator_layout);

    // 滑块
    slider->setMaximum(100);
    slider->setMinimum(1);
    // slider->setPageStep(5);
    slider->setFixedHeight(SLIDER_HIGHT);

//    slider->setValue(m_backLightInfoList->value(CURDEVICEINDEX).curBrightness * 100 / m_backLightInfoList->value(CURDEVICEINDEX).maxBrightness);
    slider->setValue(BrightnessUtil::getBackLightPercentage());
    m_infoLabel->setText(QString::number(slider->value()) + " %");

    QHBoxLayout *sliderLayout = new QHBoxLayout;
    sliderLayout->setSpacing(0);
    sliderLayout->setMargin(0);
    sliderLayout->setContentsMargins(0, 0, 0, 0);

    // 添加最小亮度图标
    // sliderLayout->addWidget(m_volumeIconMin);

    sliderLayout->addWidget(slider);

    // 添加最大亮度图标
    // sliderLayout->addWidget(m_volumeIconMax);

    central_layout->addLayout(sliderLayout);
    setLayout(central_layout);
}
/**
 * 给设备信息列表赋值
 */
void BrightnessApplet::setBackLightInfo() {
    QList<BackLightInfo> backLightInfo = BrightnessUtil::getBackLightInfo();
    if (!backLightInfo.isEmpty()) {
        *m_backLightInfoList = backLightInfo;
    } else {
        BackLightInfo tmplightInfo = *new BackLightInfo();
        tmplightInfo.maxBrightness = 100;
        tmplightInfo.curBrightness = 80;
        tmplightInfo.name = "emptyEquipment";
        m_backLightInfoList->append(tmplightInfo);
        qWarning() << "BackLightInfo is empty!!";
    }
}
/**
 * 槽函数 滑块事件函数
 * @param value
 */
void BrightnessApplet::setBackLight(const int &value) {
//    qInfo() << "::getBackLightPercentage::" <<BrightnessUtil::getBackLightPercentage();
    BackLightInfo curBackLightInfo = m_backLightInfoList->value(CURDEVICEINDEX);
//    slider->setValue(BrightnessUtil::getBackLightPercentage());
//    m_infoLabel->setText(QString::number(BrightnessUtil::getBackLightPercentage()) + " %");
    m_infoLabel->setText(QString::number(slider->value()) + " %");
    curBackLightInfo.curBrightness = value * curBackLightInfo.maxBrightness / 100;
    BrightnessUtil::setBrightness(curBackLightInfo.name.toStdString(), curBackLightInfo.curBrightness);
    m_backLightInfoList->replace(CURDEVICEINDEX, curBackLightInfo);
}
/**
 * 返回当前设备信息
 * @return
 */
BackLightInfo BrightnessApplet::getCurBackLight() {
    BackLightInfo curBackLightInfo = m_backLightInfoList->value(CURDEVICEINDEX);
    return curBackLightInfo;
}

LightSlider *BrightnessApplet::getSlider() {
    return slider;
}

