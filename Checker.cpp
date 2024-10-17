#include <iostream>
#include <assert.h>
#include "BatteryWarning.h"

using namespace std;

// Test cases
void runTestCases() {
    // Normal conditions
    assert(batteryIsOk(25, 70, 0.7) == true);

    // Temperature edge cases
    assert(batteryIsOk(-20, 70, 0.6) == false);  // Low temperature
    assert(batteryIsOk(100, 70, 0.6) == false);  // High temperature
    assert(batteryIsOk(1, 70, 0.6) == true);     // Approaching low temperature limit
    assert(batteryIsOk(44, 70, 0.6) == true);    // Approaching high temperature limit

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
    return 0;
}
