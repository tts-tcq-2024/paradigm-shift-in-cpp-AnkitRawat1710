### README.md

---

# Paradigm Shift: Battery Management System


## Approach

### 1. **Modularization**
The primary goal of this refactor was to organize the code into distinct, logical components by separating the implementation into multiple files. This modular approach enhances maintainability, readability, and scalability.

- **BatteryStatus.h**: Contains all the constants and the `BatteryStatus` structure, which is used across the application to represent the status of the battery.
- **BatteryWarning.h**: Contains function declarations for checking battery parameters (temperature, SoC, and charge rate) and helper functions. This header is responsible for exposing the API for checking battery health.
- **BatteryWarning.cpp**: Implements the functions declared in `BatteryWarning.h`. It handles the actual logic of checking if the battery parameters are within acceptable limits or near warning zones.
- **main.cpp**: Contains the main logic of the application, including test cases to validate the correctness of the battery-checking functionality.

### 2. **Separation of Concerns**
Each component of the code has a specific responsibility:

- **BatteryStatus.h**: Focuses on defining the structure for battery status and constants for warning thresholds.
- **BatteryWarning.cpp/.h**: Handles the detailed logic of checking individual battery parameters (temperature, state of charge, and charge rate) and generating warning messages.
- **main.cpp**: Isolates the application’s entry point and test cases to validate the functionality without cluttering it with logic from other parts of the system.

This structure makes it easy to maintain and extend functionality in the future. If new parameters or features need to be added, they can be incorporated without altering the core logic of other components.

### 3. **Early Warning Mechanism**
The core feature of the program is to check battery parameters and provide early warnings when the values approach critical thresholds (5% tolerance). The application also generates critical warnings when values fall outside of acceptable limits, helping monitor battery health and issue alerts before any failures.


## Challenges

### 1. **Managing Multiple Files**
One of the challenges with modularizing the code is ensuring that all necessary files are correctly included and that there are no circular dependencies. Care was taken to ensure that the headers are only included where required, and the `#include` guards (or `#pragma once`) prevent multiple inclusions.

### 2. **Maintaining Readability Across Components**
When splitting code into multiple files, maintaining readability and ensuring that the code remains easy to follow is essential. Too many file splits could lead to fragmentation, where it becomes difficult to trace the flow of the program. In this case, the files are divided logically, so each component of the code is clearly responsible for a specific function.

### 3. **Testing Across Multiple Files**
With the logic spread across different files, debugging and testing can become more challenging. To mitigate this, test cases were centralized in `main.cpp` to ensure the behavior of the program is validated after the refactor. Additionally, special care was taken to ensure that each function in `BatteryWarning.cpp` operates correctly when integrated with the other components.

### 4. **Consistency of Warning System**
Another challenge was ensuring the consistency of the warning system. We had to ensure that warnings for temperature, SoC, and charge rate adhered to the same pattern for generating messages, so the user experience is uniform across all parameters.

Testing the boundaries of each parameter—temperature, SoC, and charge rate—was crucial. Handling these edge cases (e.g., temperature right at the upper or lower limits) had to be implemented carefully to prevent errors or incorrect warnings. The test cases in `main.cpp` ensure these edge cases are covered.


## Test Coverage

- **Temperature**:
  - Safe: 25°C
  - Low: -20°C
  - High: 100°C
  - Warnings: Between 0-2.25°C (low) and 42.75-45°C (high)
  
- **State of Charge (SOC)**:
  - Safe: 70%
  - Low: 10%
  - High: 100%
  - Warnings: Between 20-24% (low) and 76-80% (high)
  
- **Charge Rate**:
  - Safe: 0.7C
  - High: 1.1C
  - Warnings: Between 0.76-0.8C
