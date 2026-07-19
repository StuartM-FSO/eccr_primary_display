#include <sys/_stdint.h>
#ifndef CELL_MODULE_H
#define CELL_MODULE_H

#include <Arduino.h>
#include <stdint.h>

void cellmod_get_reading(uint16_t cells[], const uint8_t error_cell);

#endif