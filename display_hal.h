#include <sys/_stdint.h>
#ifndef DISPLAY_HAL_H
#define DISPLAY_HAL_H

#include <Arduino.h>
#include <stdint.h>

const uint8_t DISPLAY_ROW_STATUS = 0U;
const uint8_t DISPLAY_ROW_PPO2 = 1U;


typedef enum{
  DISPLAY_OK,
  DISPLAY_UNINITIALISED,
  DISPLAY_INVALID_PARAMETER
} display_state_t;

display_state_t display_init();
display_state_t display_print_ppo2(uint16_t ppo2_x1000[], const bool connected);
display_state_t display_print_status(const bool connected);
display_state_t display_print_pulse_symbol(void);
display_state_t display_blank_line(const uint8_t row);

#endif