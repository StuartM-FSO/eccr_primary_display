#include "system_state.h"

typedef enum{
  INIT_OK,
  INIT_SYSTEM_STATE_FAILED,
  INIT_UNINITIALISED
} init_state_t;

void setup() {
  bool proceed = true;
  init_state_t init_failure_cause = INIT_UNINITIALISED;

  if((system_init() != STATE_OK) && proceed){
    init_failure_cause = INIT_SYSTEM_STATE_FAILED;
    proceed = false;
  }


}

void loop() {

}
