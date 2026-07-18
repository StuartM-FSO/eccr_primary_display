#include "system_state.h"

typedef enum{
  INIT_OK,
  INIT_SYSTEM_STATE_FAILED,
  INIT_UNINITIALISED
} init_state_t;

void setup() {
  bool proceed = true;
  init_state_t init_failure_cause = INIT_UNINITIALISED;

  debug_serial_init();
  

  if((system_init() != STATE_OK) && proceed){
    init_failure_cause = INIT_SYSTEM_STATE_FAILED;
    proceed = false;
  }

  if(!proceed){
    if(system_set_fsm(FSM_UNINITIALISED) != STATE_OK){
      
    }
  }

}

void loop() {
  fsm_state_t current_fsm_state;

  if(system_get_fsm(&current_fsm_state) != STATE_OK){
    debug_handle_error("loop read fsm state");
    current_fsm_state = FSM_HARD_FAILURE;
  }

  switch (current_fsm_state) {
    case FSM_START:
      fsm_start();
      break;
    case FSM_READY:
      fsm_ready();
      break;
    case FSM_HARD_FAILURE:
      fsm_hard_failure();
      break;
    case FSM_UNINITIALISED:
      fsm_uninitialised();
      break;
    default:
      fsm_uninitialised();
      break;
  }

}

// 1 - FSM Handlers

void fsm_start(){

}

void fsm_ready(){

}

void fsm_hard_failure(){

}

void fsm_uninitialised(){

}





// DEBUG

void debug_serial_init(){
  Serial.begin(115200);
  while(!Serial){
    delay(1);
  }
  Serial.println("Starting...");
  Serial.println();
}

void debug_handle_error(char * error_text){
  Serial.println(error_text);
  system_set_fsm(FSM_HARD_FAILURE);
}