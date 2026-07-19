#include <sys/_stdint.h>
#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <Arduino.h>
#include <stdint.h>

typedef enum{
  STATE_OK,
  STATE_INVALID_PARAMETER,
  STATE_UNINITIALISED
} system_state_t;

typedef enum{
  FSM_ZERO_COUNT = 0,     // Do not add states before here
  FSM_START,
  FSM_READY,
  FSM_UNINITIALISED,
  FSM_HARD_FAILURE,
  FSM_END_COUNT           // Do not add states past here
} fsm_state_t;

system_state_t system_init();
system_state_t system_set_fsm(const fsm_state_t fsm_state);
system_state_t system_get_fsm(fsm_state_t * const fsm_state);

system_state_t system_set_main_loop_timer(const uint32_t main_loop_timer);
system_state_t system_get_main_loop_timer(uint32_t * const main_loop_timer);



#endif