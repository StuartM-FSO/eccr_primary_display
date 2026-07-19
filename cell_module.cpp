#include "api/Common.h"
#include <sys/_stdint.h>
#include "cell_module.h"

static constexpr pin_size_t POTENTIOMETER = D0;

void cellmod_get_reading(uint16_t cells[], const uint8_t error_cell){
  uint16_t pot_reading = analogRead(POTENTIOMETER);
  for(uint8_t i = 0U; i < 3; i++){
    cells[i] = pot_reading * 2U;
    if(error_cell == i){
      cells[i] += 300;
    }
  }
}

// Private
