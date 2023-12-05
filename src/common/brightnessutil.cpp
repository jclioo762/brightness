#include "brightnessutil.h"
#include <QDir>
#include "common.h"
#include <systemd/sd-bus.h>
#include <QtWidgets>
// 当前设备下标 （暂时不实现多设备，懒）
#define CURDEVICEINDEX 0

/**
 * 获取 系统背光信息
 * @return
 */
QList<BackLightInfo> BrightnessUtil::getBackLightInfo() {
    QDir display("/sys/class/backlight");
    QList<BackLightInfo> infos;

    for (auto &item : display.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        BackLightInfo info;
        info.name = item.fileName();
        QFile cf(item.absoluteFilePath() + "/brightness");
        if (cf.open(QFile::ReadOnly)) {
            info.curBrightness = cf.readAll().toInt();
            cf.close();
        } else {
            continue;
        }

        QFile f(item.absoluteFilePath() + "/max_brightness");
        if (f.open(QFile::ReadOnly)) {
            info.maxBrightness = f.readAll().toInt();
            f.close();
        } else {
            continue;
        }
        infos.append(info);
    }
    return infos;
}

/**
 * 设置 背光
 * @param backlight
 * @param value
 * @return
 */
bool BrightnessUtil::setBrightness(const std::string &backlight, int value) {
    sd_bus *bus = nullptr;
    int r = sd_bus_default_system(&bus);
    if (r < 0) {
        qWarning() << "Can't connect to system bus: " << strerror(-r);
        return false;
    }

    sd_bus_message *reply = nullptr;
    r = sd_bus_call_method(
            bus, "org.freedesktop.login1", "/org/freedesktop/login1/session/auto",
            "org.freedesktop.login1.Session", "SetBrightness", nullptr, &reply,
            "ssu", "backlight", backlight.c_str(), value);
    if (r < 0) {
        qWarning() << "Failed to set brightness: " << strerror(-r);
        sd_bus_unref(bus);
        return false;
    }
    sd_bus_message_unref(reply);
    sd_bus_unref(bus);
    return true;
}

/**
 * 获取背光百分比
 * @return
 */
int BrightnessUtil::getBackLightPercentage() {
    QList<BackLightInfo> backLightInfo = getBackLightInfo();
    if (backLightInfo.size() < 1) {
        return -1;
    }

    return (backLightInfo.value(CURDEVICEINDEX).curBrightness * 100 / backLightInfo.value(CURDEVICEINDEX).maxBrightness) + 1;
}
