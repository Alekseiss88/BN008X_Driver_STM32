#include "bn008x_port.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
// Внешние переменные из кода CubeMX
extern I2C_HandleTypeDef hi2c1;  // или hi2c2
// ===== Реализация функций =====

static int32_t stm32_i2c_write(uint8_t dev_addr, const uint8_t *data, uint16_t len, uint32_t timeout) {
    // В STM32 адрес надо сдвинуть влево на 1 бит
    uint16_t addr = dev_addr << 1;
    
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, addr, (uint8_t*)data, len, timeout);
    
    return (status == HAL_OK) ? 0 : -1;
}

static int32_t stm32_i2c_read(uint8_t dev_addr, uint8_t *data, uint16_t len, uint32_t timeout) {
    uint16_t addr = dev_addr << 1;
    
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive(&hi2c1, addr, data, len, timeout);
    
    return (status == HAL_OK) ? 0 : -1;
}

static void stm32_delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

static uint32_t stm32_get_tick_ms(void) {
    return HAL_GetTick();
}

// Инициализация HAL структуры

void bn008x_hal_init_stm32(bn008x_hal_t *hal) {
    if (hal == NULL) return;
    
    hal->i2c_write = stm32_i2c_write;
    hal->i2c_read = stm32_i2c_read;
    hal->delay_ms = stm32_delay_ms;
    hal->get_tick_ms = stm32_get_tick_ms;
}
