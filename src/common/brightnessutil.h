#ifndef BRIGHTNESSUTIL_H
#define BRIGHTNESSUTIL_H

#include <QString>
#include "common.h"

class BrightnessUtil {
public:
    static QList<BackLightInfo> getBackLightInfo();
    static int getBackLightPercentage();
    static bool setBrightness(const std::string &backlight, int value);
};
#endif // BRIGHTNESSUTIL_H
