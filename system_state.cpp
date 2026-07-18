#include <sys/_stdint.h>
#include <cstddef>
#include "system_state.h"

typedef struct{
  bool initialised;
  fsm_state_t current_fsm_state;
  uint32_t main_loop_timer;
} loop_state_t;

static loop_state_t state = {};

system_state_t system_init(){
  if(state.initialised){
    return STATE_OK;
  }
  state.main_loop_timer = 0U;
  state.current_fsm_state = FSM_START;
  state.initialised = true;
  return STATE_OK;
}

system_state_t system_set_fsm(const fsm_state_t fsm_state){
  if(!state.initialised){
    return STATE_UNINITIALISED;
  }
  if(fsm_state <= FSM_ZERO_COUNT || fsm_state >= FSM_END_COUNT){
    return STATE_INVALID_PARAMETER;
  }
  state.current_fsm_state = fsm_state;
  return STATE_OK;
}

system_state_t system_get_fsm(fsm_state_t * const fsm_state){
  if(!state.initialised){
    return STATE_UNINITIALISED;
  }
  if(fsm_state == NULL){
    return STATE_INVALID_PARAMETER;
  }
  *fsm_state = state.current_fsm_state;
  return STATE_OK;
}

system_state_t system_set_main_loop_timer(const uint32_t main_loop_timer){
  if(!state.initialised){
    return STATE_UNINITIALISED;
  }
  state.main_loop_timer = main_loop_timer;
  return STATE_OK;
}

system_state_t system_get_main_loop_timer(uint32_t * const main_loop_timer){
  if(!state.initialised){
    return STATE_UNINITIALISED;
  }
  if(main_loop_timer == NULL){
    return STATE_INVALID_PARAMETER;
  }
  *main_loop_timer = state.main_loop_timer;
  return STATE_OK;
}
