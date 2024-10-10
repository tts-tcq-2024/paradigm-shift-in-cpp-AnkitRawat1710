### README.md

---

# Paradigm Shift: Battery Management System


## Approach

1. **Clean Code Principles**:
   - **Refactoring**: The code is refactored to reduce complexity and ensure that each function has a single responsibility, making the system maintainable and easy to extend.
   - **Separation of Concerns**: Pure functions handle the checks, while I/O operations (like printing messages) are separated, ensuring testability and clarity.

2. **Handling Future Changes**:
   - The system is designed to adapt to future research and evolving technology. Limits can be adjusted easily without rewriting the entire codebase.

---

### Extensions Implemented

1. **Early Warning System**:
   - Introduced a warning system for temperature, SOC, and charge rate with a 5% tolerance before reaching critical limits.
   - The system provides early warnings to alert users before actual alarms are triggered.

   #### Example:
   - **State of Charge (SOC)**:
     - Safe range: 20% to 80%
     - Early warning:
       - **20% to 24%**: "Warning: Temperature is approaching low limit"
       - **76% to 80%**: "Warning: Temperature is approaching high limit"

2. **Maintainable and Extensible Code**:
   - Refactored the code to simplify the logic and reduce Cyclomatic Complexity Number(CCN) to less than 3.
   - Introduced modular, reusable functions for checking parameter limits and warning ranges.
   - Easy adaptation for future requirements or customer feedback (e.g., disabling warnings for specific parameters or change the threshold warning levels).

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
