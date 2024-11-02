#ifndef BATTERY_WARNING_H
#define BATTERY_WARNING_H

#include <string>
#include "BatteryStatus.h"


struct BatteryStatus {
    bool All_Ok;               // Flag to indicate if the battery status is okay
    std::string Warning_message; // Warning message if any conditions are not met
};

std::string generateWarningMessage(const std::string& parameter, const std::string& limitType);

bool isInRange(float value, float lowerLimit, float upperLimit);

BatteryStatus checkEarlyWarning(float value, float lowerLimit, float upperLimit, float tolerance, const std::string& parameter);

BatteryStatus checkTemperature(float temperature);

BatteryStatus checkSoC(float soc);

BatteryStatus checkChargeRate(float chargeRate);

bool checkAndReport(const BatteryStatus& status);

bool batteryIsOk(float temperature, float soc, float chargeRate);

#endif // BATTERY_WARNING_H
