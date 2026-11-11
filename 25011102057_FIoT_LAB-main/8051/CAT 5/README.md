# CAT5 – Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

## EXP
CAT5

## DATE
10/08/2026

## NAME OF EXP
Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

## HARDWARE SETUP / PLATFORM

- **Development Board:** 8051 Development Board
- **Microcontroller:** AT89S52 (8051 family)
- **CPU Core:** 8051-compatible 8-bit microcontroller core
- **Crystal Frequency:** 11.0592 MHz
- **Timer Used:** Timer 0
- **Timer Modes:** Mode 1 (16-bit timer mode)
- **Programming Environment:** Keil µVision with Keil C51 compiler
- **Programming Language:** Embedded C
- **Implementation Constraint:** No Arduino APIs, HAL libraries or RTOS services.

## TASKS

This experiment consists of three tasks involving hardware timer configuration, timing generation, LED control and stepper motor operation.

### Task 1 – Timer 0 Configuration and LED Toggling

- Configure Timer 0 in Mode 1 (16-bit timer mode).
- Use the preload value `FC66H` to generate an approximately 1 ms overflow interval.
- Monitor the Timer 0 overflow flag (`TF0`) using polling.
- Use a software counter to count 1000 timer overflows.
- Toggle the LED connected to P2.0 after the required number of overflows.

**Timing mechanism:** Timer 0 overflow flag polling.

[View Task 1 README](TASK1/README.md)

### Task 2 – LED Fading Using Software PWM

- Configure Timer 0 in Mode 1 using the preload value `FFA4H`.
- Generate an approximately 100 µs timer overflow interval.
- Divide each PWM cycle into 10 steps.
- Vary the LED duty cycle from 0% to 100% and back to 0%.
- Control the LED brightness through software-generated PWM on P2.0.

**Timing mechanism:** Timer 0 overflow flag polling.

[View Task 2 README](TASK2/README.md)

### Task 3 – Stepper Motor Speed and Direction Control (Optional)

- Configure Timer 0 in Mode 1 and enable Timer 0 interrupts.
- Generate periodic interrupts at approximately 1 ms intervals.
- Use the four-step excitation sequence to control the stepper motor through an L298N motor driver.
- Select the motor stepping speed using three buttons.
- Implement slow, medium and fast stepping modes.

**Timing mechanism:** Timer 0 interrupt service routine.

**Implemented stepping speeds:**
- Slow: 100 ms per step
- Medium: 50 ms per step
- Fast: 10 ms per step

The implemented sequence provides forward stepping. Reverse-direction control is not included.

[View Task 3 README](TASK3/README.md)

## KEY CONCEPTS DEMONSTRATED

- 8051 Timer 0 configuration
- 16-bit timer operation (Mode 1)
- Timer preload calculation
- Timer overflow and overflow flag (`TF0`)
- Polling-based timer control
- Timer interrupt service routines
- Software time-base generation
- Software Pulse Width Modulation (PWM)
- PWM duty-cycle variation
- LED brightness control
- GPIO output control
- Stepper motor excitation sequence
- Motor speed selection using button inputs
- Interfacing a stepper motor through the L298N motor driver

## INFERENCE

The experiment demonstrates the use of Timer 0 in the AT89S52 microcontroller for generating precise timing intervals and controlling external devices.

Task 1 demonstrates timer overflow polling and software counter-based LED toggling. Task 2 demonstrates software PWM generation and LED brightness control through duty-cycle variation. Task 3 demonstrates interrupt-based timing and stepper motor speed control using an L298N motor driver.

Together, these tasks provide practical experience with hardware timer configuration, polling, interrupts, PWM generation, GPIO control and peripheral interfacing using Embedded C.