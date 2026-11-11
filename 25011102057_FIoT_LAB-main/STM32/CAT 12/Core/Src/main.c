
#include "main.h"
#include "bme280.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

struct bme280_settings settings;
struct bme280_dev dev;
struct bme280_data comp_data;

int8_t rslt;

float temperature;
float pressure;
float humidity;

static uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

char msg[150];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr);

void user_delay_us(uint32_t period, void *intf_ptr);


int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    // Configure BME280 interface
    dev.intf_ptr = &dev_addr;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    // Initialize BME280
    rslt = bme280_init(&dev);

    if(rslt != BME280_OK)
    {
        snprintf(msg, sizeof(msg),
                 "BME280 Initialization Failed!\r\n");

        HAL_UART_Transmit(&huart1,
                          (uint8_t *)msg,
                          strlen(msg),
                          HAL_MAX_DELAY);

        while(1);
    }

    // Sensor settings
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_1X;
    settings.osr_t = BME280_OVERSAMPLING_1X;
    settings.filter = BME280_FILTER_COEFF_OFF;

    rslt = bme280_set_sensor_settings(
        BME280_SEL_OSR_PRESS |
        BME280_SEL_OSR_TEMP |
        BME280_SEL_OSR_HUM |
        BME280_SEL_FILTER,
        &settings,
        &dev
    );

    if(rslt != BME280_OK)
    {
        while(1);
    }

    // Set normal mode
    rslt = bme280_set_sensor_mode(
        BME280_POWERMODE_NORMAL,
        &dev
    );

    if(rslt != BME280_OK)
    {
        while(1);
    }

    HAL_UART_Transmit(&huart1,
                      (uint8_t *)"BME280 Ready!\r\n",
                      strlen("BME280 Ready!\r\n"),
                      HAL_MAX_DELAY);

    while(1)
    {
        rslt = bme280_get_sensor_data(
            BME280_ALL,
            &comp_data,
            &dev
        );

        if(rslt == BME280_OK)
        {
            temperature = comp_data.temperature;
            pressure = comp_data.pressure / 100.0f;
            humidity = comp_data.humidity;

            int32_t t100 = (int32_t)(temperature * 100);
            int32_t p100 = (int32_t)(pressure * 100);
            int32_t h100 = (int32_t)(humidity * 100);

            snprintf(msg, sizeof(msg),
                     "Temperature: %ld.%02ld C\r\n"
                     "Pressure: %ld.%02ld hPa\r\n"
                     "Humidity: %ld.%02ld %%RH\r\n"
                     "-------------------------\r\n",
                     (long)(t100 / 100),
                     (long)(t100 < 0 ? -(t100 % 100) : t100 % 100),
                     (long)(p100 / 100),
                     (long)(p100 % 100),
                     (long)(h100 / 100),
                     (long)(h100 % 100));

            HAL_UART_Transmit(&huart1,
                              (uint8_t *)msg,
                              strlen(msg),
                              HAL_MAX_DELAY);
        }
       else
			{
					snprintf(msg, sizeof(msg),
									 "Sensor Read Error! Code: %d\r\n", rslt);

					HAL_UART_Transmit(&huart1,
														(uint8_t *)msg,
														strlen(msg),
														HAL_MAX_DELAY);
			}
        HAL_Delay(1000);
    }
}


// I2C Read Function
int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr)
{
    uint8_t address = *(uint8_t *)intf_ptr;

    if(HAL_I2C_Mem_Read(&hi2c1,
                        address << 1,
                        reg_addr,
                        I2C_MEMADD_SIZE_8BIT,
                        reg_data,
                        len,
                        HAL_MAX_DELAY) == HAL_OK)
    {
        return BME280_OK;
    }

    return BME280_E_COMM_FAIL;
}


// I2C Write Function
int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr)
{
    uint8_t address = *(uint8_t *)intf_ptr;

    if(HAL_I2C_Mem_Write(&hi2c1,
                         address << 1,
                         reg_addr,
                         I2C_MEMADD_SIZE_8BIT,
                         (uint8_t *)reg_data,
                         len,
                         HAL_MAX_DELAY) == HAL_OK)
    {
        return BME280_OK;
    }

    return BME280_E_COMM_FAIL;
}


// Delay Function
void user_delay_us(uint32_t period, void *intf_ptr)
{
    HAL_Delay((period / 1000) + 1);
}


// System Clock Configuration
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(
        PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue =
        RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 84;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;

    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        Error_Handler();

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                           FLASH_LATENCY_2) != HAL_OK)
        Error_Handler();
}


// I2C1 Initialization
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if(HAL_I2C_Init(&hi2c1) != HAL_OK)
        Error_Handler();
}


// USART1 Initialization
static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if(HAL_UART_Init(&huart1) != HAL_OK)
        Error_Handler();
}


// GPIO Initialization
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}


// Error Handler
void Error_Handler(void)
{
    __disable_irq();

    while(1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
