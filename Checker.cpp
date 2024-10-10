#include <iostream>
#include <assert.h>
using namespace std;

// Structure to hold the status of the battery
struct BatteryStatus {
    bool All_Ok;
    string Warning_message;
};

// Tolerance percentages for early warnings
const float temperatureWarningTolerance = 0.05 * 45;  // 5% of the upper limit (45°C)
const float socWarningTolerance = 0.05 * 80;          // 5% of the upper limit (80% SoC)
const float chargeRateWarningTolerance = 0.05 * 0.8;  // 5% of the upper limit (0.8C)

// Helper function to generate a warning message
string generateWarningMessage(const string& parameter, const string& limitType) {
    return "Warning: " + parameter + " is " + limitType + "\n";
}

// Helper function to check if a value is in a specific range
bool isInRange(float value, float lowerLimit, float upperLimit) {
    return value >= lowerLimit && value <= upperLimit;
}

// Helper function to check for early warning based on tolerance
BatteryStatus checkEarlyWarning(float value, float lowerLimit, float upperLimit, float tolerance, const string& parameter) {
    if (isInRange(value, lowerLimit, lowerLimit + tolerance)) {
        return {true, generateWarningMessage(parameter, "approaching low limit")};
    }
    if (isInRange(value, upperLimit - tolerance, upperLimit)) {
        return {true, generateWarningMessage(parameter, "approaching high limit")};
    }
    return {true, ""};
}

// Function to check temperature and issue warnings
BatteryStatus checkTemperature(float temperature) {
    if (temperature < 0) {
        return {false, generateWarningMessage("Temperature", "low")};
    }
    if (temperature > 45) {
        return {false, generateWarningMessage("Temperature", "high")};
    }
    return checkEarlyWarning(temperature, 0, 45, temperatureWarningTolerance, "Temperature");
}

// Function to check State of Charge (SoC) and issue warnings
BatteryStatus checkSoC(float soc) {
    if (soc < 20) {
        return {false, generateWarningMessage("State of Charge", "low")};
    }
    if (soc > 80) {
        return {false, generateWarningMessage("State of Charge", "high")};
    }
    return checkEarlyWarning(soc, 20, 80, socWarningTolerance, "State of Charge");
}

// Function to check charge rate and issue warnings
BatteryStatus checkChargeRate(float chargeRate) {
    if (chargeRate > 0.8) {
        return {false, generateWarningMessage("Charge Rate", "high")};
    }
    return checkEarlyWarning(chargeRate, 0, 0.8, chargeRateWarningTolerance, "Charge Rate");
}

// Helper function to check and report the battery status
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

// Function to check the battery status for temperature, SoC, and charge rate
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkAndReport(checkTemperature(temperature)) &&
           checkAndReport(checkSoC(soc)) &&
           checkAndReport(checkChargeRate(chargeRate));
}

// Test cases
void runTestCases() {
    // Normal conditions
    assert(batteryIsOk(25, 70, 0.7) == true);

    // Temperature edge cases
    assert(batteryIsOk(-20, 70, 0.6) == false);  // Low temperature
    assert(batteryIsOk(100, 70, 0.6) == false);  // High temperature
    assert(batteryIsOk(2, 70, 0.6) == true);     // Approaching low temperature limit
    assert(batteryIsOk(43, 70, 0.6) == true);    // Approaching high temperature limit

    // SoC edge cases
    assert(batteryIsOk(25, 10, 0.6) == false);  // Low SOC
    assert(batteryIsOk(25, 100, 0.6) == false);  // High SOC
    assert(batteryIsOk(25, 22, 0.6) == true);    // Approaching discharge limit
    assert(batteryIsOk(25, 78, 0.6) == true);    // Approaching charge-peak

    // Charge rate edge cases
    assert(batteryIsOk(25, 70, 1.1) == false);   // High charge rate
    assert(batteryIsOk(25, 70, 0.76) == true);   // Approaching charge rate limit
}

int main() {
    runTestCases();
    cout << "\nAll the test cases have passed\n";
}
