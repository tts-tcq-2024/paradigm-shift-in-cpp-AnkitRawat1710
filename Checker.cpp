#include <iostream>
#include <assert.h>
using namespace std;

// Structure to hold battery status with warnings
struct BatteryStatus {
    bool All_Ok;
    string Warning_message;
};

// Threshold structure for battery limits
struct BatteryThresholds {
    float lower_limit;
    float upper_limit;
    float warning_tolerance;
};

// General parameter check function
BatteryStatus checkLowLimit(float value, const BatteryThresholds& thresholds, string low_warning) {
    if (value < thresholds.lower_limit) {
        return {false, low_warning + " is low\n"};
    }
    return {true, ""};
}

BatteryStatus checkHighLimit(float value, const BatteryThresholds& thresholds, string high_warning) {
    if (value > thresholds.upper_limit) {
        return {false, high_warning + " is high\n"};
    }
    return {true, ""};
}

BatteryStatus checkWarningLow(float value, const BatteryThresholds& thresholds, string low_warning) {
    if (value <= thresholds.lower_limit + thresholds.warning_tolerance) {
        return {true, "Warning: Approaching " + low_warning + "\n"};
    }
    return {true, ""};
}

BatteryStatus checkWarningHigh(float value, const BatteryThresholds& thresholds, string high_warning) {
    if (value >= thresholds.upper_limit - thresholds.warning_tolerance) {
        return {true, "Warning: Approaching " + high_warning + "\n"};
    }
    return {true, ""};
}

// Battery limit configurations
BatteryThresholds tempThresholds = {0, 45, 2.25};  // 5% of 45 is 2.25
BatteryThresholds socThresholds = {20, 80, 4};     // 5% of 80 is 4
BatteryThresholds chargeRateThresholds = {0, 0.8, 0.04};  // 5% of 0.8 is 0.04

// Helper to combine multiple checks
BatteryStatus combineStatus(BatteryStatus status1, BatteryStatus status2) {
    if (!status1.All_Ok) return status1;
    if (!status2.Warning_message.empty()) return status2;
    return {true, ""};
}

// Individual parameter checks
BatteryStatus checkTemperature(float temperature) {
    auto lowCheck = checkLowLimit(temperature, tempThresholds, "Temperature");
    auto highCheck = checkHighLimit(temperature, tempThresholds, "Temperature");
    auto warningLowCheck = checkWarningLow(temperature, tempThresholds, "Temperature");
    auto warningHighCheck = checkWarningHigh(temperature, tempThresholds, "Temperature");
    return combineStatus(combineStatus(lowCheck, highCheck), combineStatus(warningLowCheck, warningHighCheck));
}

BatteryStatus checkSoC(float soc) {
    auto lowCheck = checkLowLimit(soc, socThresholds, "State of Charge");
    auto highCheck = checkHighLimit(soc, socThresholds, "State of Charge");
    auto warningLowCheck = checkWarningLow(soc, socThresholds, "State of Charge");
    auto warningHighCheck = checkWarningHigh(soc, socThresholds, "State of Charge");
    return combineStatus(combineStatus(lowCheck, highCheck), combineStatus(warningLowCheck, warningHighCheck));
}

BatteryStatus checkChargeRate(float chargeRate) {
    auto highCheck = checkHighLimit(chargeRate, chargeRateThresholds, "Charge Rate");
    auto warningHighCheck = checkWarningHigh(chargeRate, chargeRateThresholds, "Charge Rate");
    return combineStatus(highCheck, warningHighCheck);
}

// Helper function to check and report battery status
bool checkAndReport(const BatteryStatus& status) {
    if (!status.All_Ok || !status.Warning_message.empty()) {
        cout << status.Warning_message;
        return status.All_Ok;
    }
    return true;
}

// Check if battery is OK based on parameters
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool tempStatus = checkAndReport(checkTemperature(temperature));
    bool socStatus = checkAndReport(checkSoC(soc));
    bool chargeRateStatus = checkAndReport(checkChargeRate(chargeRate));
    return tempStatus && socStatus && chargeRateStatus;
}

// Test cases
void runTestCases() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(-20, 70, 0.6) == false);  // Low temperature
    assert(batteryIsOk(100, 70, 0.6) == false);  // High temperature
    assert(batteryIsOk(25, 10, 0.6) == false);  // Low SOC
    assert(batteryIsOk(25, 100, 0.6) == false);  // High SOC
    assert(batteryIsOk(25, 70, 1.1) == false);  // High charge rate
}

int main() {
    runTestCases();
    cout << "\nAll the test cases have passed\n";
}
