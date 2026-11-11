# EXP

CAT 10

# DATE

05/10/2026

# NAME OF EXP

STM32-Wemos Wi-Fi Modem Interface Using AT Commands

# HARDWARE SETUP / PLATFORM

**Tasks 1, 2 and 3:**

- Development Board: STM32 Blue Pill
- Microcontroller: STM32F103C8T6
- Processor Core: ARM Cortex-M3
- Wi-Fi Module: Wemos D1 (ESP8266)
- Communication: UART using STM32 HAL libraries
- PC Interface: Arduino IDE Serial Monitor

**UART Configuration used in the supplied programs:**

- USART1: STM32–Wemos communication.
- USART2: STM32–PC communication.
- Baud rate: 115200
- Word length: 8 bits
- Stop bits: 1
- Parity: None
- Hardware flow control: None

# TASK NO

- Task 1 – Basic AT Command Communication
- Task 2 – Wi-Fi Configuration and Connection
- Task 3 – TCP Server Configuration

# CIRCUIT DIAGRAM

The circuit diagrams are provided separately in the respective task folders.

- Tasks 1–3: STM32 Blue Pill with Wemos D1.

# CORE LOGIC

The experiment progressively develops UART-based communication between an STM32 microcontroller and an ESP8266 Wi-Fi module.

1. Establish UART communication between STM32 and Wemos using AT commands.
2. Receive responses from Wemos and forward them to the PC serial terminal.
3. Configure the ESP8266 in station mode and connect it to a Wi-Fi access point.
4. Retrieve the network IP information.
5. Enable multiple TCP connections and configure the ESP8266 as a TCP server on port 80.

# TASK 1 – BASIC UART COMMUNICATION

## Core Logic

- Initialize HAL, system clock, GPIO, USART1 and USART2.
- Send the `AT` command to the ESP8266 through USART1.
- Receive the ESP8266 response one byte at a time.
- Forward each received byte to the PC through USART2.
- Wait for the response collection timeout before proceeding.

## Pseudocode

1. Initialize HAL.
2. Configure the system clock.
3. Initialize GPIO, USART1 and USART2.
4. Declare the AT command `AT\r\n`.
5. Transmit the AT command through USART1.
6. Start receiving bytes from USART1.
7. For every successfully received byte, transmit it through USART2.
8. Continue receiving until the configured timeout expires.
9. Wait for a short delay.
10. Keep the microcontroller running.

## Code Base

- `HAL_UART_Transmit()` – Sends the AT command.
- `HAL_UART_Receive()` – Receives the ESP8266 response.
- USART1 – STM32–Wemos communication.
- USART2 – STM32–PC communication.

# TASK 2 – WI-FI CONFIGURATION AND CONNECTION

## Core Logic

- Initialize the STM32 peripherals.
- Send AT commands to configure the ESP8266 as a Wi-Fi station.
- Enable DHCP for station mode.
- Send the Wi-Fi credentials to connect to the access point.
- Wait for the `WIFI GOT IP` and `OK` responses.
- Retrieve the IP information using `AT+CIFSR`.
- Forward the received responses to the PC terminal.

## Pseudocode

1. Initialize HAL, system clock, GPIO, USART1 and USART2.
2. Declare the required AT commands:

   - `AT`
   - `AT+CWMODE=1`
   - `AT+CWDHCP=1,1`
   - `AT+CWJAP`
   - `AT+CIFSR`

3. Transmit `AT` and collect the response.
4. Transmit `AT+CWMODE=1` and collect the response.
5. Transmit `AT+CWDHCP=1,1` and collect the response.
6. Transmit the Wi-Fi connection command.
7. Receive the response for up to 5000 ms.
8. Check the received data for:

   - `WIFI GOT IP`
   - `OK`
   - `FAIL` or `ERROR`

9. Stop waiting when both successful connection indications are received, an error occurs, or the timeout expires.
10. Forward the collected response to the PC.
11. Transmit `AT+CIFSR` and collect the IP information.
12. Keep the microcontroller running.

## Code Base

- `HAL_UART_Transmit()` – Sends AT commands.
- `HAL_UART_Receive()` – Receives ESP8266 responses.
- `HAL_GetTick()` – Measures elapsed time.
- `strstr()` – Searches for connection status messages.
- `HAL_UART_Transmit()` through USART2 – Displays responses on the PC.

# TASK 3 – TCP SERVER CONFIGURATION

## Core Logic

- Perform the initialization and Wi-Fi connection steps from Task 2.
- Enable multiple TCP connections using `AT+CIPMUX=1`.
- Start a TCP server on port 80 using `AT+CIPSERVER=1,80`.
- Collect and forward the ESP8266 responses to the PC.
- Keep the microcontroller running after server configuration.

## Pseudocode

1. Initialize HAL, system clock, GPIO, USART1 and USART2.
2. Declare the AT commands for:

   - Communication check: `AT`
   - Station mode: `AT+CWMODE=1`
   - DHCP configuration: `AT+CWDHCP=1,1`
   - Wi-Fi connection: `AT+CWJAP`
   - IP information: `AT+CIFSR`
   - Multiple connections: `AT+CIPMUX=1`
   - TCP server: `AT+CIPSERVER=1,80`

3. Send each command through USART1.
4. Receive the ESP8266 response until the configured timeout expires.
5. Forward each collected response to the PC through USART2.
6. Wait for the required delay between commands.
7. After connecting to Wi-Fi and retrieving IP information, send `AT+CIPMUX=1`.
8. Send `AT+CIPSERVER=1,80`.
9. Display the collected responses on the PC.
10. Keep the microcontroller running.

## Code Base

- `HAL_UART_Transmit()` – Sends ESP8266 AT commands.
- `HAL_UART_Receive()` – Collects ESP8266 responses.
- `HAL_Delay()` – Provides delays between commands.
- `HAL_GetTick()` – Supports timeout handling.

# INFERENCE

The experiment demonstrates the progressive development of an STM32-based Wi-Fi communication system using the ESP8266 module.

Tasks 1–3 establish UART communication, configure Wi-Fi connectivity and start a TCP server.

The experiment demonstrates UART communication, ESP8266 AT command control, Wi-Fi station configuration and TCP server operation.