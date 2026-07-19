#include "system_state.h"
#include "display_hal.h"
#include "uart_hal.h"
#include "time_helpers.h"
#include "format_for_print.h"

constexpr uint32_t FREQUENCY_MAIN_LOOP_MS = 1000U;
constexpr uint8_t THREE_CELLS = 3U;

typedef enum{
  INIT_OK,
  INIT_SYSTEM_STATE_FAILED,
  INIT_DISPLAY_FAILED,
  INIT_UART_FAILED,
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
  if((display_init() != DISPLAY_OK) && proceed){
    init_failure_cause = INIT_DISPLAY_FAILED;
    proceed = false; 
  }
  if(uart_hal_init() != UART_OK && proceed){
    init_failure_cause = INIT_UART_FAILED;
    proceed = false;
  }

  if(!proceed){
    if(system_set_fsm(FSM_UNINITIALISED) != STATE_OK){
      debug_handle_error("Failed at init");
    }
  }
  if(system_set_fsm(FSM_START) != STATE_OK){
    debug_handle_error("setup assign fsm_start");
  }
  display_blank_line(DISPLAY_ROW_STATUS);
  display_blank_line(DISPLAY_ROW_PPO2);
}

void loop() {
  fsm_state_t current_fsm_state;
  uint32_t now = millis();

  if(system_get_fsm(&current_fsm_state) != STATE_OK){
    debug_handle_error("loop read fsm state");
    current_fsm_state = FSM_HARD_FAILURE;
  }

  switch (current_fsm_state) {
    case FSM_START:
      fsm_start();
      break;
    case FSM_READY:
      fsm_ready(now);
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
  display_print_status("STARTING");
  delay(1000);
  system_set_fsm(FSM_READY);
  display_blank_line(DISPLAY_ROW_STATUS);
}

void fsm_ready(uint32_t now){
  uint32_t last_cell_read_ms = 0U;
  uint16_t ppo2_from_uart_x1000[3] = {0U};
  char cell_buffers[THREE_CELLS][FORMATTING_PPO2_STR_LEN];
  const char *cells[THREE_CELLS];

  if(system_get_main_loop_timer(&last_cell_read_ms) != STATE_OK){
    debug_handle_error("FSM Ready get timer");
  }
  if(has_timer_elapsed(now, last_cell_read_ms, FREQUENCY_MAIN_LOOP_MS)){
    uart_hal_read_cells(ppo2_from_uart_x1000);
    display_print_ppo2(ppo2_from_uart_x1000);
    system_set_main_loop_timer(now);
  }
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