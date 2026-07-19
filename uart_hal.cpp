#include <sys/_stdint.h>
#include "api/Common.h"
#include "uart_hal.h"
#include "cell_module.h"

constexpr uint8_t THREE_CELLS = 3U;

constexpr uint8_t CELLMOD_ALL_AGREE = 4U;

static change_t random_choice(const int16_t ppo2);

// Public API

typedef struct{
  bool initialised;
  uint16_t cells[THREE_CELLS];
} uart_internal_state_t;

static uart_internal_state_t state;

uart_state_t uart_hal_init(){
  if(state.initialised){
    return UART_OK;
  }
  randomSeed(analogRead(0));
  for(uint8_t channel = 0U; channel < THREE_CELLS; channel++){
    state.cells[channel] = 1000u;
  }
  return UART_OK;
}

uart_state_t uart_hal_controller_connected(void){
  if(!state.initialised){
    return UART_UNINITIALISED;
  }
  return UART_OK;
}

uart_state_t uart_hal_read_cells(uint16_t cells[]){
  uint16_t simulated_ppo2_X1000[THREE_CELLS];

  cellmod_get_reading(simulated_ppo2_X1000, CELLMOD_ALL_AGREE);
  for(uint8_t channel = 0U; channel < THREE_CELLS; channel++){
    cells[channel] = simulated_ppo2_X1000[channel];
  }
  return UART_OK;
}

uart_state_t x_uart_hal_read_cells(uint16_t cells[]){
  uint16_t current_ppo2 = 0U;
  change_t random_outcome;
  for(uint8_t channel = 0U; channel < THREE_CELLS; channel++){
    current_ppo2 = state.cells[channel];
    if(current_ppo2 < 50U){
      current_ppo2 = 50U;
    }
    if(current_ppo2 > 2000){
      current_ppo2 = 2000U;
    }
    random_outcome = random_choice(current_ppo2);

    switch (random_outcome){
      case PPO2_UP:
        current_ppo2 += 50;
        break;
      case PPO2_DOWN:
        current_ppo2 -= 50;
        break;
      case PPO2_UNCHANGED:
        break;
      default:
        break;
    }

    state.cells[channel] = current_ppo2;
    cells[channel] = current_ppo2;
  }
  return UART_OK;
}

// Private functions

static change_t random_choice(const int16_t ppo2){
  uint8_t r = random(0, 100);  // gives an integer from 0 to 99
  uint8_t weighted_nothing = 0U;
  uint8_t weighted_down = 0U;

  if(ppo2 < 900){
    weighted_nothing = 25;
    weighted_down = 60;
  } else if(ppo2 > 1100){
    weighted_nothing = 25;
    weighted_down = 75;
  } else {
    weighted_nothing = 70;
    weighted_down = 85;
  }

  if (r < weighted_nothing) {
    return PPO2_UNCHANGED;          // 0–69   → 70% chance
  } else if (r < weighted_down) {
    return PPO2_DOWN;            // 70–84  → 15% chance
  } else {
    return PPO2_UP;          // 85–99  → 15% chance
  }
}