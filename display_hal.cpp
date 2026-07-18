#include <sys/_intsup.h>
#include "display_hal.h"

typedef struct{
  bool initialised;
} internal_state_t;

static internal_state_t state = {};

// Public API

display_state_t display_init(){
  if(state.initialised){
    return DISPLAY_OK;
  }
  state.initialised = true;
  return DISPLAY_OK;
}