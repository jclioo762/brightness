#include "brightnessplugin.h"
#include "brightnesswidget.h"
#include <QtCore/QVariant>
#include <DDBusSender>

/**
 * 构造函数
 * @param parent
 */
BrightnessPlugin::BrightnessPlugin(QObject *parent)
    : QObject(parent),
      m_brightnessWidget(new BrightnessWidget),
      m_tipsWidget(new QLabel),
      m_brightnessApplet(new BrightnessApplet),
      m_settings( "deepin")
    {
//    QObject::connect(m_brightnessWidget, SIGNAL(wheelEventTriggered(const int)),
//                     m_brightnessApplet, SLOT(setBackLight(const int)));
//    QObject::connect(m_brightnessWidget, SIGNAL(wheelEventTip()),
//                     this, SLOT(handleEventTip()));
    }

/**
 * 插件名称
 * @return
 */
const QString BrightnessPlugin::pluginName() const
{
    return QString("brightness");
}

/**
 * 插件显示名称,用于在界面上显示
 * @return
 */
const QString BrightnessPlugin::pluginDisplayName() const
{
    return QStringLiteral("亮度插件-Brightness");
}

/**
 * 初始化
 * @param proxyInter
 */
void BrightnessPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

/**
 * 主控件，用于显示在 dde-dock 面板上
 * @param itemKey
 * @return
 */
QWidget *BrightnessPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_brightnessWidget;
}

/**
 * 鼠标悬浮在插件主控件上时显示的提示框控件
 * @param itemKey
 * @return
 */
QWidget *BrightnessPlugin::itemTipsWidget(const QString &itemKey)
{
    BackLightInfo brightnessInfo = m_brightnessApplet->getCurBackLight();
    m_tipsWidget->setText(QString(" 当前亮度 %1% ").arg((brightnessInfo.curBrightness * 100 /  brightnessInfo.maxBrightness) + 1));
    return m_tipsWidget;
}
/**
 * 滚轮出发的槽函数 用来调节显示lable
 */
void BrightnessPlugin::handleEventTip() {
    itemTipsWidget(nullptr);
}

/**
 * 左键点击插件主控件后弹出的控件
 * @param itemKey
 * @return
 */
QWidget *BrightnessPlugin::itemPopupApplet(const QString &itemKey)
{
    m_brightnessApplet->setBackLightInfo();
    return m_brightnessApplet;
}

bool BrightnessPlugin::pluginIsAllowDisable()
{
    // 告诉 dde-dock 本插件允许禁用
    return true;
}

bool BrightnessPlugin::pluginIsDisable()
{
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void BrightnessPlugin::pluginStateSwitched()
{
    // 获取当前禁用状态的反值作为新的状态值
    const bool disabledNew = !pluginIsDisable();
    // 存储新的状态值
    m_proxyInter->saveValue(this, "disabled", disabledNew);

    // 根据新的禁用状态值处理主控件的加载和卸载
    if (disabledNew) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

const QString BrightnessPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(1);

    QMap<QString, QVariant> setting;
    setting["itemId"] = "setting";
    setting["itemText"] = "亮度设置";
    setting["isActive"] = true;
    items.push_back(setting);


    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void BrightnessPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    // 根据上面接口设置的 id 执行不同的操作
    if (menuId == "setting") {
        DDBusSender()
                .service("com.deepin.dde.ControlCenter")
                .interface("com.deepin.dde.ControlCenter")
                .path("/com/deepin/dde/ControlCenter")
                .method(QString("ShowModule"))
                .arg(QString("display"))
                .call();
    }
}

int BrightnessPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    const QString key = QString("pos_%1").arg(displayMode());
    return m_settings.value(key, 0).toInt();
}

void BrightnessPlugin::setSortKey(const QString &itemKey, const int order)
{
    Q_UNUSED(itemKey);

    const QString key = QString("pos_%1").arg(displayMode());
    m_settings.setValue(key, order);
}