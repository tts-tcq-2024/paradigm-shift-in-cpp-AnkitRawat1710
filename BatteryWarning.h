#ifndef BATTERY_WARNING_H
#define BATTERY_WARNING_H

#include <string>
#include "BatteryStatus.h"

// Define the BatteryStatus structure
struct BatteryStatus {
    bool All_Ok;               // Flag to indicate if the battery status is okay
    std::string Warning_message; // Warning message if any conditions are not met
};

// Helper function to generate a warning message
std::string generateWarningMessage(const std::string& parameter, const std::string& limitType);

// Helper function to check if a value is in a specific range
bool isInRange(float value, float lowerLimit, float upperLimit);

// Helper function to check for early warning based on specific ranges
BatteryStatus checkEarlyWarning(float value, float lowerLimit, float upperLimit, float tolerance, const std::string& parameter);

// Function to check temperature and issue warnings
BatteryStatus checkTemperature(float temperature);

// Function to check State of Charge (SoC) and issue warnings
BatteryStatus checkSoC(float soc);

// Function to check charge rate and issue warnings
BatteryStatus checkChargeRate(float chargeRate);

// Helper function to check and report the battery status
bool checkAndReport(const BatteryStatus& status);

// Function to check the battery status for temperature, SoC, and charge rate
bool batteryIsOk(float temperature, float soc, float chargeRate);

#endif // BATTERY_WARNING_H
