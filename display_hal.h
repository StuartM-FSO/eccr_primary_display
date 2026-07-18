#ifndef DISPLAY_HAL_H
#define DISPLAY_HAL_H

#include <Arduino.h>
#include <stdint.h>

typedef enum{
  DISPLAY_OK,
  DISPLAY_UNINITIALISED,
  DISPLAY_INVALID_PARAMETER
} display_state_t;

display_state_t display_init();

#endif