#ifndef COMMON_H
#define COMMON_H

#include <QString>

struct BackLightInfo {
  QString name;
  int curBrightness = 0;
  int maxBrightness = 1;
};
#endif // COMMON_H
