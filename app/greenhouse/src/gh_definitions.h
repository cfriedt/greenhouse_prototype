// Greenhouse main internal states
#define GH_STATE_SLEEP 1              //Device in sleep mode to save energy
#define GH_STATE_ON 2                 //Device in normal operation 
#define GH_STATE_UI 3                 //Device interacting with user
#define GH_STATE_INIT 4               //Device is initializing
#define GH_STATE_CLOSING 5            //Device is switching off, closing connections etc. 
#define GH_STATE_ERROR 6              //Device faces some error; restart needed

#define GH_ACT_IN_TEMP 1
#define GH_ACT_IN_HUMIDITY 2
#define GH_ACT_OUT_WATER 3
#define GH_ACT_OUT_DOOR 4
#define GH_ACT_TELEMETRY 5
#define GH_ACT_UI_LOCAL 6
#define GH_ACT_UI_BT 7
#define GH_ACT_UI_NET 8
#define GH_ACT_CLOUD 9

#define GH_DELAY_SHORT 1000
#define GH_DELAY_LONG 3000
#define GH_DELAY_SLEEP 3000             //Device sleep interval

#define GH_MAX_LOOP 5

#define GH_DEBUG_OFF 0 //No debug prints
#define GH_DEBUG_ON 1 // Debug levels
#define GH_DEBUG_STRING "GH DEBUG: "
#define GH_ERR_STRING "GH ERROR: "


#define GH_ERR_NOERR 0 //No error detected, normal operation
#define GH_ERR_NOERR_STR GH_ERR_STRING "No error, normal operation.\n"
#define GH_ERR_NOINIT 1 //Device starting init in wrong state
#define GH_ERR_NOINIT_STR GH_ERR_STRING "Device in wrong state at init, restarting.\n"
#define GH_ERR_UNKNOWN_STATE 2 //Device in undefined state (restart needed).
#define GH_ERR_UNKNOWN_STATE_STR GH_ERR_STRING "Device in undefined state, restarting.\n"
#define GH_ERR_MAX_COUNT 3 // Device reached the max allowed number of cycles. 
#define GH_ERR_MAX_COUNT_STR GH_ERR_STRING "Device reached max allowed number of cycles. Restarting.\n"


