#include <sys/_stdint.h>
#ifndef UART_HAL_H
#define UART_HAL_H

#include <Arduino.h>
#include <stdint.h>

typedef enum{
  PPO2_UP = 0,
  PPO2_DOWN,
  PPO2_UNCHANGED
} change_t;

typedef enum{
  UART_OK,
  UART_UNINITIALISED,
  UART_INVALID_PARAMETER
} uart_state_t;

uart_state_t uart_hal_init();
uart_state_t uart_hal_controller_connected(void);
uart_state_t uart_hal_read_cells(uint16_t cells[]);

#endif