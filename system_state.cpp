#include <cstddef>
#include "system_state.h"

typedef struct{
  bool initialised;
} loop_state_t;

static loop_state_t state = {};

system_state_t system_init(){
  if(state.initialised){
    return STATE_OK;
  }
  state.initialised = true;
}

