#include "Arduino.h"
#include "Setting.h"


static int verticalWarningRange=5;
static int horizontalWarningRange=40;
static int vibrationStrength=100;
static struct DisabledAxis disabledAxis;

int Setting::getHorizontalWarningRange()
{
  return horizontalWarningRange;
}
void Setting::setHorizontalWarningRange(int distance)
{
  horizontalWarningRange = distance;
}

int Setting::getVerticalWarningRange()
{
  return verticalWarningRange;
}
void Setting::setVerticalWarningRange(int distance)
{
  verticalWarningRange = distance;
}

int Setting::getVibrationStrength()
{
  return vibrationStrength;
}
void Setting::setVibrationStrength(int percentage)
{
  vibrationStrength = percentage;
}

DisabledAxis Setting::getDisabledAxis()
{
  return disabledAxis;
}
void Setting::setDisabledAxis(bool horizontal,bool vertical)
{
  disabledAxis.horizontal = horizontal;
  disabledAxis.vertical = vertical;
}
