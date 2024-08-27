#include <iostream>
#include <assert.h>
using namespace std;

// Structure hold the status of battery (checks with an OK flag and a warning message)
struct BatteryStatus {
    bool All_Ok;
    string Warning_message;
};

// To Checks if the temperature is within the safe range (0°C to 45°C)
BatteryStatus checkTemperature(float temperature) {
    if (temperature < 0) {
        return {false, "Warning: Temperature is low\n"};
        
    }
    else if (temperature > 45) {
        return {false, "Warning: Temperature is high\n"};
        
    }
    return {true, ""};
}

// To check if the State of Charge (SOC) is within the safe range (20% to 80%)
BatteryStatus checkSoC(float soc) {
    if (soc < 20) {
        return {false, "Warning: State of Charge is low\n"};
    } 
    else if (soc > 80) {
        return {false, "Warning: State of Charge is high\n"};
    }
    return {true, ""};
}

// To check if the charge rate is within the safe limit (0 to 0.8C)
BatteryStatus checkChargeRate(float chargeRate) {
    if (chargeRate > 0.8) {
        return {false, "Warning: Charge Rate is high\n"};
    }
    return {true, ""};
}

//Function to check if the battery is Ok (checks for temperature, SOC and charge rate)
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    BatteryStatus checks[] = {
        checkTemperature(temperature),
        checkSoc(soc),
        checkChargeRate(chargeRate)
    };

    for (const auto& status : checks) {
        if (!status.All_Ok) {
            cout << status.Warning_message;
            return false;
        }
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

// Main function
int main() {
    runTestCases();
    cout << "\nAll the test cases have passed\n";
}


