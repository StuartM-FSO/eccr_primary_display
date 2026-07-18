#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <Arduino.h>
#include <stdint.h>

typedef enum{
  STATE_OK,
  STATE_INVALID_PARAMETER,
  STATE_UNINITIALISED
} system_state_t;

system_state_t system_init();

#endif