# EXP
CAT12

# DATE
14/10/2026

# NAME OF EXP
STM32F401RE Cortex-M4: GPIO and User Input Programming

# HARDWARE SETUP / PLATFORM
- **Development Board:** NUCLEO-F401RE
- **Microcontroller:** STM32F401RET6
- **Processor Core:** ARM Cortex-M4
- **On-board LED:** LD2 connected to GPIO PA5
- **On-board User Push Button:** B1 connected to GPIO PC13
- **Development Tools:** STM32CubeMX and Keil MDK
- **Software Library:** STM32 HAL

### Clock Configuration
The system clock is configured using the external high-speed clock (HSE) in bypass mode and the PLL.

The supplied configuration uses:
- HSE mode: Bypass
- PLL source: HSE
- PLLM: 25
- PLLN: 168
- PLLP: 2
- PLLQ: 4
- AHB prescaler: 1
- APB1 prescaler: 2
- APB2 prescaler: 1

The actual system clock frequency depends on the external clock frequency supplied to the HSE input.

# TASK NO
- **Task 1:** On-board LED Bring-Up
- **Task 2:** On-board Switch Control with State Remembrance
- **Task 3:** Short-Press and Long-Press Detection

# Circuit Diagram

The experiments use the on-board peripherals of the NUCLEO-F401RE development board.

- LD2 (on-board LED) is connected to PA5.
- B1 (on-board user push button) is connected to PC13.

![Circuit Diagram](circuit.jpeg)

Separate circuit diagrams are maintained in the respective task folders where applicable. No external LED or push button is required for these tasks.

# CORE LOGIC / PSEUDOCODE / CODE BASE

## Task 1 – On-board LED Bring-Up

### Core Logic
GPIO pin PA5 is configured as a push-pull output. The program continuously toggles the output state with a 100 ms delay between consecutive toggles.

### Pseudocode

```text
START

Initialize HAL
Configure system clock
Initialize GPIO

WHILE TRUE
    Toggle LED on PA5
    Wait for 100 milliseconds
END WHILE

END
```

## Task 2 – On-board Switch Control with State Remembrance

### Core Logic
GPIO pin PC13 is configured as an input with an internal pull-up, while PA5 is configured as an output. The program continuously reads the button state and controls the LED based on the input level.

### Pseudocode

```text
START

Initialize HAL
Configure system clock
Initialize GPIO

Configure PC13 as input with pull-up
Configure PA5 as output

WHILE TRUE

    Read button state from PC13

    IF button is pressed THEN
        Turn ON LED
    ELSE
        Turn OFF LED
    END IF

END WHILE

END
```

**Implementation note:** The supplied code performs level-based LED control. The LED remains ON while the button is pressed and turns OFF when released. It does not implement the press-event toggle and state remembrance described in the task requirement.

## Task 3 – Short-Press and Long-Press Detection

### Core Logic
The program measures button press duration using `HAL_GetTick()`.

- A press duration below 250 ms is treated as a short press.
- A press duration of 250 ms or more is treated as a long press.
- A short press toggles the LED when blinking is inactive.
- A short press during blinking stops blinking and turns the LED OFF.
- A long press starts continuous blinking if blinking is inactive.
- The LED toggles every 100 ms while blinking is active.

### Pseudocode

```text
START

Initialize HAL
Configure system clock
Initialize GPIO

pressed = 0
isBlinking = 0

WHILE TRUE

    Read button state from PC13

    IF button is pressed THEN

        IF pressed == 0 THEN
            pressed = 1
            Store current tick as press_start
        END IF

    ELSE

        IF pressed == 1 THEN

            pressed = 0
            duration = current tick - press_start

            IF duration < 250 milliseconds THEN

                IF isBlinking == 0 THEN
                    Toggle LED
                ELSE
                    Turn OFF LED
                    Stop blinking
                END IF

            ELSE

                IF isBlinking == 0 THEN
                    Turn ON LED
                    Start blinking
                    Store current tick as blink_start
                END IF

            END IF

        END IF

    END IF

    IF isBlinking == 1 THEN

        IF current tick - blink_start >= 100 milliseconds THEN
            Toggle LED
            Update blink_start
        END IF

    END IF

END WHILE

END
```

## Code Base
Each task folder contains its respective `main.c`, `main.h` and STM32CubeMX-generated project files.

- **Task1:** GPIO output configuration and periodic LED blinking.
- **Task2:** GPIO input reading and button-controlled LED operation.
- **Task3:** Short-press and long-press detection using the HAL tick counter and timed LED blinking.

# INFERENCE
The experiments demonstrated GPIO output control, digital input reading and time-based user input detection using the NUCLEO-F401RE development board.

Task 1 verified the on-board LED operation through GPIO output toggling. Task 2 demonstrated button-based LED control using GPIO input polling. Task 3 extended the application by measuring button press duration using the HAL tick counter and performing different LED operations based on short and long presses.

These experiments provided practical understanding of GPIO configuration, on-board peripheral interfacing, polling-based input detection and non-blocking time measurement using STM32 HAL.