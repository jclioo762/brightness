#ifndef BRIGHTNESSPLUGIN_H
#define BRIGHTNESSPLUGIN_H

#include <QLabel>
#include <dde-dock/pluginsiteminterface.h>
#include "brightnesswidget.h"
#include "brightnessapplet.h"

class BrightnessPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "brightness.json")

public:
    explicit BrightnessPlugin(QObject *parent = nullptr);

    const QString pluginName() const override;
    const QString pluginDisplayName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    /// 返回插件的itemWidget
    QWidget *itemWidget(const QString &itemKey) override;
    /// 返回插件的itemTipsWidget
    QWidget *itemTipsWidget(const QString &itemKey) override;
    /// 返回插件的itemPopupApplet
    QWidget *itemPopupApplet(const QString &itemKey) override;


    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

    int itemSortKey(const QString &itemKey);
    void setSortKey(const QString &itemKey, const int order);

    const QString itemContextMenu(const QString &itemKey) override;
    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;

public slots:
    void handleEventTip();

private:
    BrightnessApplet  *m_brightnessApplet;
    BrightnessWidget *m_brightnessWidget;
    QLabel *m_tipsWidget;
    QSettings m_settings;
};

#endif
