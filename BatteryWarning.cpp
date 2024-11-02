#include "BatteryWarning.h"
#include <iostream>

using namespace std;

std::string generateWarningMessage(const std::string& parameter, const std::string& limitType) {
    return "Warning: " + parameter + " is " + limitType + "\n";
}

bool isInRange(float value, float lowerLimit, float upperLimit) {
    return value >= lowerLimit && value <= upperLimit;
}

BatteryStatus checkEarlyWarning(float value, float lowerLimit, float upperLimit, float tolerance, const std::string& parameter) {
    if (isInRange(value, lowerLimit, lowerLimit + tolerance)) {
        return {true, generateWarningMessage(parameter, "approaching low limit")};
    }
    if (isInRange(value, upperLimit - tolerance, upperLimit)) {
        return {true, generateWarningMessage(parameter, "approaching high limit")};
    }
    return {true, ""};
}

// Separate functions to handle specific checks
BatteryStatus checkTemperatureBounds(float temperature) {
    if (temperature < 0) {
        return {false, generateWarningMessage("Temperature", "low")};
    }
    if (temperature > 45) {
        return {false, generateWarningMessage("Temperature", "high")};
    }
    return {true, ""}; // No error
}

BatteryStatus checkSoCBounds(float soc) {
    if (soc < 20) {
        return {false, generateWarningMessage("State of Charge", "low")};
    }
    if (soc > 80) {
        return {false, generateWarningMessage("State of Charge", "high")};
    }
    return {true, ""}; // No error
}

BatteryStatus checkChargeRateBounds(float chargeRate) {
    if (chargeRate > 0.8) {
        return {false, generateWarningMessage("Charge Rate", "high")};
    }
    return {true, ""}; // No error
}

BatteryStatus checkTemperature(float temperature) {
    BatteryStatus boundsStatus = checkTemperatureBounds(temperature);
    if (!boundsStatus.All_Ok) {
        return boundsStatus;
    }
    return checkEarlyWarning(temperature, 0, 45, temperatureWarningLower, "Temperature");
}

BatteryStatus checkSoC(float soc) {
    BatteryStatus boundsStatus = checkSoCBounds(soc);
    if (!boundsStatus.All_Ok) {
        return boundsStatus;
    }
    return checkEarlyWarning(soc, 20, 80, socWarningLower, "State of Charge");
}

BatteryStatus checkChargeRate(float chargeRate) {
    BatteryStatus boundsStatus = checkChargeRateBounds(chargeRate);
    if (!boundsStatus.All_Ok) {
        return boundsStatus;
    }
    return checkEarlyWarning(chargeRate, 0, 0.8, chargeRateWarningLower, "Charge Rate");
}

bool checkAndReport(const BatteryStatus& status) {
    if (!status.All_Ok) {
        cout << status.Warning_message;
        return false;
    }
    if (!status.Warning_message.empty()) {
        cout << status.Warning_message;
    }
    return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkAndReport(checkTemperature(temperature)) &&
           checkAndReport(checkSoC(soc)) &&
           checkAndReport(checkChargeRate(chargeRate));
}
