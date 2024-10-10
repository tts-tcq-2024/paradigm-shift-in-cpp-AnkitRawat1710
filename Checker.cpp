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

// Generic function to check parameters and generate warnings
BatteryStatus checkParameter(float value, const BatteryThresholds& thresholds, string low_warning, string high_warning) {
    float warning_low = thresholds.lower_limit + thresholds.warning_tolerance;
    float warning_high = thresholds.upper_limit - thresholds.warning_tolerance;

    if (value < thresholds.lower_limit) {
        return {false, low_warning + " is low\n"};
    } else if (value > thresholds.upper_limit) {
        return {false, high_warning + " is high\n"};
    } else if (value <= warning_low) {
        return {true, "Warning: Approaching " + low_warning + "\n"};
    } else if (value >= warning_high) {
        return {true, "Warning: Approaching " + high_warning + "\n"};
    }
    return {true, ""};
}

// Battery limit configurations
BatteryThresholds tempThresholds = {0, 45, 2.25};  // 5% of 45 is 2.25
BatteryThresholds socThresholds = {20, 80, 4};     // 5% of 80 is 4
BatteryThresholds chargeRateThresholds = {0, 0.8, 0.04};  // 5% of 0.8 is 0.04

BatteryStatus checkTemperature(float temperature) {
    return checkParameter(temperature, tempThresholds, "Temperature", "Temperature");
}

BatteryStatus checkSoC(float soc) {
    return checkParameter(soc, socThresholds, "State of Charge", "State of Charge");
}

BatteryStatus checkChargeRate(float chargeRate) {
    return checkParameter(chargeRate, chargeRateThresholds, "Charge Rate", "Charge Rate");
}

// Check and report battery status
bool checkAndReport(const BatteryStatus& status) {
    if (!status.All_Ok || !status.Warning_message.empty()) {
        cout << status.Warning_message;
        return status.All_Ok;
    }
    return true;
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



