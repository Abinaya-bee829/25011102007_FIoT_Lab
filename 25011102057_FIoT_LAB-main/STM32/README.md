# Fundamentals of Internet of Things (IoT) – Laboratory

**Course:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**University:** Shiv Nadar University Chennai  
**Repository:** `25011102003_FIoT_Lab`

---

## About This Repository

This repository contains the laboratory experiments, implementations, source code, and documentation completed as part of the **Fundamentals of Internet of Things (IoT)** course.

The experiments focus on understanding microcontroller-based embedded systems, peripheral interfacing, hardware programming, and communication protocols used in IoT applications.

The repository is organized into two major sections based on the microcontroller platforms used:

- **8051 Microcontroller**
- **STM32 Microcontroller**

Each experiment has its own documentation, including its objective, hardware setup, circuit diagram, implementation logic, and observations or inference. Experiments containing multiple tasks are further organized into individual task folders wherever applicable.

## Repository Structure

```text
25011102003_FIoT_Lab/
│
├── 8051/
│   ├── CAT1/
│   ├── CAT2/
│   ├── CAT3/
│   ├── CAT4/
│   ├── CAT5/
│   ├── CAT6/
│   ├── CAT7/
│   └── README.md
│
├── STM32/
│   ├── CAT8/
│   ├── CAT9/
│   ├── CAT10/
│   ├── CAT11/
│   ├── CAT12/
│   ├── CAT13/
│   ├── CAT14/
│   └── README.md
│
├── .gitignore
└── README.md
```

*The folders under each platform contain the corresponding experiment documentation, circuit diagrams, source code, and supporting project files.*

## Platforms and Hardware

### 1. 8051 Microcontroller

The 8051 section focuses on bare-metal programming and peripheral interfacing using the **AT89S52 microcontroller**.

Topics covered include:

- Development environment and toolchain setup
- GPIO programming and LED control
- Timers and interrupt handling
- Matrix keypad interfacing
- Seven-segment display interfacing
- UART communication and serial debugging
- 16×2 LCD interfacing and display control
- Stepper motor control and software PWM

### 2. STM32 Microcontroller

The STM32 section explores embedded programming using STM32 development boards and the STM32 Hardware Abstraction Layer (HAL).

The experiments use different STM32 platforms depending on the task, including:

- **STM32F103C8T6 – Blue Pill**
- **STM32F410RBT6 – NUCLEO-F410RB**
- **STM32F410RET6 - NUCLEO-F401RE**

Topics covered include:

- GPIO configuration and switch-controlled LED applications
- Timer-based operations and button handling
- UART communication and command-based control
- ESP8266 Wi-Fi module interfacing using AT commands
- HTTP server implementation using an ESP8266 Wi-Fi modem
- BME280 environmental sensor interfacing using I²C
- MQTT communication using a custom-built ESP8266 API

## Software and Development Tools

The experiments use platform-specific development tools and software libraries, including:

- **Keil µVision / Keil MDK** – Embedded C development and debugging
- **STM32CubeMX** – STM32 peripheral configuration and code generation
- **STM32 HAL** – Hardware abstraction layer for STM32 peripherals
- **Arduino IDE Serial Monitor** – Serial communication and debugging
- **Bosch BME280 Sensor API** – Environmental sensor interfacing
- **Custom ESP8266 API** – Wi-Fi and MQTT communication

The exact tools and libraries used are documented in the respective experiment folders.

## Documentation Format

Each experiment README follows a consistent documentation structure:

1. **Experiment Number and Date**
2. **Name of the Experiment**
3. **Hardware Setup / Platform**
4. **Task Number**
5. **Circuit Diagram**
6. **Core Logic / Pseudocode / Code Base**
7. **Inference**

For experiments with multiple tasks, each task is documented separately, along with its corresponding circuit diagram and implementation details.

## How to Navigate This Repository

- Start with the [`8051`](./8051/) folder to explore experiments involving the AT89S52 microcontroller.
- Visit the [`STM32`](./STM32/) folder to explore experiments involving STM32 development boards.
- Open the README inside an experiment folder for its detailed documentation.
- For experiments with multiple tasks, navigate into the respective task folder to find its source code, circuit diagram, and explanation.

## Learning Outcomes

Through these laboratory experiments, the repository demonstrates practical understanding of:

- Microcontroller architecture and embedded C programming
- GPIO, timers, interrupts, and peripheral configuration
- Interfacing external hardware components and sensors
- Serial communication using UART
- Inter-device communication using Wi-Fi
- IoT communication protocols such as MQTT
- Sensor data acquisition and transmission
- Development, testing, and debugging of embedded applications

---

**Note:** This repository documents the laboratory work carried out as part of the course. The implementation details, hardware connections, and observations are specific to the experiments performed.