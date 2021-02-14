#include "Arduino.h"

struct DisabledAxis
{
  bool horizontal;
  bool vertical;
};
  
class Setting
{
  private:
  
  public:
  static int getHorizontalWarningRange();
  static void setHorizontalWarningRange(int distance);
  static int getVerticalWarningRange();
  static void setVerticalWarningRange(int distance);
  static int getVibrationStrength();
  static void setVibrationStrength(int percentage);
  static struct DisabledAxis getDisabledAxis();
  static void setDisabledAxis(bool horizontal,bool vertical);
  
};
