#ifndef BATTERY_STATUS_H
#define BATTERY_STATUS_H

#include <string>

// Structure to hold the status of the battery
struct batteryStatus {
    bool All_Ok;
    std::string Warning_message;
};

// Specific warning tolerance values for each parameter
const float temperatureWarningLower = 0.05 * 45;  // 5% of upper limit (45°C)
const float socWarningLower = 4;                  // 5% of upper limit (80%) for SoC
const float chargeRateWarningLower = 0.04;        // 5% of upper limit (0.8C)

#endif // BATTERY_STATUS_H
