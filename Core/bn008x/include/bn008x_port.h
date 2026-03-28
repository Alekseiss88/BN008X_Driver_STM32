#ifndef BN008X_PORT_H
#define BN008X_PORT_H

#include <stdint.h>

// HAL-функции, которые должен предоставить пользователь
typedef struct {
    // Запись по I2C
    int32_t (*i2c_write)(uint8_t dev_addr, const uint8_t *data, uint16_t len, uint32_t timeout);
    
    // Чтение по I2C
    int32_t (*i2c_read)(uint8_t dev_addr, uint8_t *data, uint16_t len, uint32_t timeout);
    
    // Задержка в мс
    void (*delay_ms)(uint32_t ms);
    
    // Получить текущее время в мс
    uint32_t (*get_tick_ms)(void);
} bn008x_hal_t;

void bn008x_hal_init_stm32(bn008x_hal_t *hal);
#endif
