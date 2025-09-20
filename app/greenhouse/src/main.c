// Greenhouse demo application for Seeeduino XIAO used for demonstrations
// Author: Lenka Koskova Triskova, lenka@koskova.cz
// License: MIT
#include "./gh_definitions.h"

#include <zephyr/kernel.h>

#define USE_SEEDUINO 1

#ifdef USE_SEEDUINO
#define Serial Serial1
#define GH_BAUD 115200
#else
#define Serial Serial
#define GH_BAUD 9600
#endif

static int gh_state = GH_STATE_INIT;
static int gh_err_code = GH_ERR_NOERR;
static int gh_debug = GH_DEBUG_ON;

static int gh_loop_count = 0;

static int gh_process_error()
{
  const char *to_print = "";
  int ret_code = 0;  
  //Returns 1 if restart is needed.
  switch(gh_err_code) {
    case GH_ERR_NOINIT:
      to_print=GH_ERR_NOINIT_STR;      
      gh_state=GH_STATE_CLOSING;
      ret_code = 1;
      break;
    case GH_ERR_UNKNOWN_STATE: 
      to_print = GH_ERR_UNKNOWN_STATE_STR;
;            
      gh_state=GH_STATE_CLOSING;
      ret_code=1;
      break;
    case GH_ERR_MAX_COUNT:
      to_print = GH_ERR_MAX_COUNT_STR;
      gh_state=GH_STATE_CLOSING;
      ret_code=1;
      break;
    default:
      to_print = GH_ERR_NOERR_STR;
      gh_state=GH_STATE_ON;
      ret_code = 0;
      break;
  }
  printf("%s", to_print);
  return ret_code;
}

static void print_debug(const char *to_print)
{
  if (gh_debug == GH_DEBUG_ON)
  {
    printf("%s%s", GH_DEBUG_STRING, to_print);
  }
}

static void gh_check_loop()
{
  printf("GH main loop nr: %d\n", gh_loop_count);
  gh_loop_count++;
  if (gh_loop_count > GH_MAX_LOOP)
  {
    gh_state = GH_STATE_ERROR;
    gh_err_code = GH_ERR_MAX_COUNT;
  }
}

static void gh_do_init()
{
}

static void gh_do_normal_operation()
{
  // Nothing yet, just enering the sleep:
  print_debug("State: Normal operation\n");
  gh_state = GH_STATE_SLEEP;
}

static void gh_do_sleep()
{
  // No real sleep yet, just delay and back to normal
  print_debug("State: Sleeping\n");
  k_msleep(GH_DELAY_SLEEP);
  gh_state = GH_STATE_ON;
}

static void gh_do_ui()
{
  print_debug("State: User interaction\n");
  //No UI yet, delay and back to normal operation:
  k_msleep(GH_DELAY_SHORT);
  gh_state=GH_STATE_ON;
}

static void gh_do_closing()
{
  print_debug("State: The device is swiching off.\n");
        // Code to close what is open here:
  k_msleep(GH_DELAY_SHORT);
  NVIC_SystemReset();        //Reset device
}

static void loop()
{

  while (true) { //Main while loop:
    gh_check_loop();

    // The main loop code:
    // Case state of the device:
    switch(gh_state) {
      case GH_STATE_ON:        
        gh_do_normal_operation();
        break;

      case(GH_STATE_SLEEP):        
        gh_do_sleep();
        break;

      case (GH_STATE_UI):        
        gh_do_ui();
        break;

      case (GH_STATE_CLOSING):
        gh_do_closing();        
        break;

      case (GH_STATE_ERROR):
        print_debug("State: The device is in error state.\n");
        
        //Process the error and if returns 1, restart the device:
        if (gh_process_error()) {
          NVIC_SystemReset();
        }
        break;

      default:
        print_debug("Unknown state - entering error\n");
        gh_state = GH_STATE_ERROR;
        gh_err_code = GH_ERR_UNKNOWN_STATE;
        break;
      }
      k_msleep(GH_DELAY_LONG);
  }
}

int main(void)
{
  // Serial line initialization:
  if (gh_state == GH_STATE_INIT)
  {

    printf("-------------------------\n");
    printf("Greenhouse is starting.\n");
    gh_do_init();
    printf("Initialization done.\n");
    printf("-------------------------\n");

    gh_state = GH_STATE_ON;
  }
  else
  {
    gh_state = GH_STATE_ERROR;
    gh_err_code = GH_ERR_NOINIT;
  }

  loop();
}
