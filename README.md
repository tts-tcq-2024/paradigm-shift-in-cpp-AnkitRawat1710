### README.md

---

# Paradigm Shift: Battery Management System


### Extensions Implemented

1. **Early Warning System**:
   - Introduced a warning system for temperature, SOC, and charge rate with a 5% tolerance before reaching critical limits.
   - The system provides early warnings like "Approaching charge-peak" or "Approaching discharge" to alert users before actual alarms are triggered.

   #### Example:
   - **State of Charge (SOC)**:
     - Safe range: 20% to 80%
     - Early warning:
       - **20% to 24%**: "Warning: Approaching discharge"
       - **76% to 80%**: "Warning: Approaching charge-peak"

2. **Maintainable and Extensible Code**:
   - Refactored the code to simplify the logic and reduce Cyclomatic Complexity Number(CCN) to less than 3.
   - Introduced modular, reusable functions for checking parameter limits and warning ranges.
   - Easy adaptation for future requirements or customer feedback (e.g., disabling warnings for specific parameters).

3. **Generalized Warning System**:
   - The warning and limit checks are now driven by configuration structures for each parameter (temperature, SOC, charge rate), making it easy to adjust warning thresholds and upper/lower limits as needed.

---

## Purpose

The goal is to safeguard the battery by detecting and alerting users to abnormal conditions during the charging process. The system can be applied across various EV battery applications, including:
- **Home Charging**
- **Public Charging Stations**
- **Vehicle Regenerative Braking**

---

## Key Features

- **Modular Design**: The system is designed to be easily extended for additional parameters or future functionalities.
- **Early Warning for Action**: Users are notified before critical limits are breached, allowing preventive action.
- **Configurable Limits**: Each parameter (temperature, SOC, charge rate) has configurable limits and tolerance values to support different use cases or battery specifications.
  
---

## Approach

1. **Clean Code Principles**:
   - **Refactoring**: The code is refactored to reduce complexity and ensure that each function has a single responsibility, making the system maintainable and easy to extend.
   - **Separation of Concerns**: Pure functions handle the checks, while I/O operations (like printing messages) are separated, ensuring testability and clarity.

2. **Handling Future Changes**:
   - The system is designed to adapt to future research and evolving technology. Limits can be adjusted easily without rewriting the entire codebase.

---

## Code Structure

- **Threshold Configuration**: Each parameter (temperature, SOC, charge rate) has a structure defining its upper and lower limits along with the early warning tolerance.
- **Modular Check Functions**: Separate functions handle checks for low, high, and warning conditions, and their results are combined using helper functions to ensure a clean structure.
- **Test Cases**: A comprehensive set of test cases covers normal, warning, and abnormal conditions for each parameter.

---

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

---

## Future Improvements

- **Customizable Warnings**: Feedback from customers could enable turning on/off specific warnings (e.g., temperature warnings only).
- **Sensor Accuracy**: Allow flexibility for integrating sensors from different vendors with varying accuracy levels.

---

## Conclusion

The refactored system ensures a clean, maintainable codebase with a flexible and extensible design. Early warnings provide actionable insights, enhancing the safety of EV batteries before reaching critical conditions.
