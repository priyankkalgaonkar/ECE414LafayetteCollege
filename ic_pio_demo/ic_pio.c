/* 
 * ic - simple interrupt-drive input capture for Raspberry Pi Pico
 * ECE 414 July 2023
 * J. Nestor
 *
 */

#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "timer.h"
#include "ic.h"

// include file generated by PIOASM
#include "ic_pio.PIO.h"

    static PIO pio = pio1;
    static uint sm = 0;
    static uint32_t capture, last_capture, capture_period;
    
    // Configure Interrupt on IC_PIN
    void ic_init() {
        gpio_init(IC_PIN);  // is this necessary?  Hunter doesn't do this
        // load the program
        uint offset = pio_add_program(pio, &capture_program);
        capture_program_init(pio, sm, offset, IC_PIN);
        pio_sm_set_clkdiv (pio, sm, 1.0) ;
        pio_sm_clear_fifos (pio, sm);      // drain the transmit fifo
        // and turn on the state machine
        pio_sm_set_enabled(pio, sm, true);
        capture = 0;
        last_capture = 0;
        capture_period = NO_CAPTURE_READY;
    }    
    
    // return the measured period in IC state machine count
    uint32_t ic_getperiod() { 
        // read all values out of FIFO, discarding all except the last
        uint level = pio_sm_get_rx_fifo_level(pio, sm);
        //printf("level=%d\n", level);
        if (level == 0) return NO_CAPTURE_READY;  // indicate no samples since last call
        for (int i = 0; i < level; i++) {
            last_capture = capture;
            capture = pio_sm_get(pio, sm);
            //printf("capture=%x\n", capture);
        }   
        capture_period = last_capture - capture;  // PIO counter counts down!
        last_capture = capture;
        return capture_period;
    }
    
    static const uint32_t USPERSEC = 1000000;

    // input capture PIO counts one "tick" per 2 clock cycles
    // since clock is 125MHz, count rate is 62.5MHz
    static const uint32_t IC_TICKS_PER_SEC = 62500000;
    static uint32_t ic_rpm;

    // convert timer ticks to RPM
    // note use of rounding idiom (add ticks/2) in the division 
    uint32_t ic_ticks2rpm(uint32_t ticks) {
        ic_rpm = ((IC_TICKS_PER_SEC * 60) + (ticks/2)) / ticks;
        return ic_rpm;
    }

    // return the estimated RPM of the input capture
    // if called more before another capture edge arrives,
    // keep track of the time elapsed since the last
    // capture using the system timer.  If we have no
    // capture for MIN_RPM_TIMEOUT_US, then return 0
    // as we assume the fan is not turning.  Otherwise
    // return NO_CAPTURE_READY 

    uint32_t ic_getrpm(){
         static uint32_t last_capture_time, capture_time;
         uint32_t period = ic_getperiod();
         capture_time = time_us_32();
         if (period == NO_CAPTURE_READY) {
            if ((capture_time - last_capture_time) > MIN_RPM_TIMEOUT_US) {
                return 0;
            } else {
                return NO_CAPTURE_READY;
            }
         } else {
            last_capture_time = capture_time;
            return( ic_ticks2rpm(period));
         }
    }
