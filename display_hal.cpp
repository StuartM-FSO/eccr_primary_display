// NOTES
//  1. Cell values to be sent as char arrays in format:
//     const char *cells[] = {"1.02", "1.0*", "1.04"};

#include <cstddef>
#include <sys/_stdint.h>
#include "display_hal.h"
#include "Waveshare_LCD1602.h"
#include <Wire.h>
#include "format_for_print.h"

static constexpr uint8_t ROWS = 2U;
static constexpr uint8_t COLUMNS = 16U;
static constexpr uint8_t COLUMN_CELL_0 = 0U;
static constexpr uint8_t COLUMN_CELL_INCREMENT = 5U;
static constexpr uint8_t COLUMN_OK_SYMBOL = 15U;
static constexpr char BLANK_LINE[] = "                ";
static constexpr char SYMBOL_PULSE[] = "+";
static constexpr char SPACE[] = " ";

typedef struct{
  bool initialised;
  bool pulse_on;
  Waveshare_LCD1602 lcd{COLUMNS, ROWS};
} internal_state_t;

static internal_state_t state;

// Public API

display_state_t display_init(){
  if(state.initialised){
    return DISPLAY_OK;
  }
  Wire.begin();
  state.lcd.init();
  state.initialised = true;
  state.pulse_on = true;
  return DISPLAY_OK;
}

display_state_t display_print_ppo2(uint16_t ppo2_x1000[]){   // See Note 1
  if(!state.initialised){
    return DISPLAY_UNINITIALISED;
  }
  if(ppo2_x1000 == NULL){
    return DISPLAY_INVALID_PARAMETER;
  }
  for(uint8_t channel = 0U; channel < 3; channel++){
    char buffer[FORMATTING_PPO2_STR_LEN];
    uint8_t column = COLUMN_CELL_0 + COLUMN_CELL_INCREMENT * channel;

    format_ppo2_to_text(ppo2_x1000[channel], buffer);
    state.lcd.setCursor(column, DISPLAY_ROW_PPO2);
    state.lcd.send_string(buffer);
  }
  return DISPLAY_OK;
}

display_state_t display_print_pulse_symbol(void){
  if(!state.initialised){
    return DISPLAY_UNINITIALISED;
  }
  state.lcd.setCursor(COLUMN_OK_SYMBOL, DISPLAY_ROW_PPO2);
  if(state.pulse_on){
    state.lcd.send_string(SYMBOL_PULSE);
  } else {
    state.lcd.send_string(SPACE);
  }
  state.pulse_on = !state.pulse_on;
  return DISPLAY_OK;
}

display_state_t display_blank_line(const uint8_t row){
  if(!state.initialised){
    return DISPLAY_UNINITIALISED;
  }
  if((row != DISPLAY_ROW_PPO2) && (row != DISPLAY_ROW_STATUS)){
    return DISPLAY_INVALID_PARAMETER;
  }
  state.lcd.setCursor(0, row);
  state.lcd.send_string(BLANK_LINE);
  return DISPLAY_OK;
}
