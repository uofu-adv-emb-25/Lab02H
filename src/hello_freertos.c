/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

// FreeRTOS functions
#include "FreeRTOS.h"
#include "task.h"

// pico HAL
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

// start with the LED reset
int count = 0;
bool on = false;

// scheduling parameters
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

// blink the LED
void blink_task(__unused void *params) {
    // make sure the pico is ready for IO calls
    hard_assert(cyw43_arch_init() == PICO_OK);

    // cycle the LED on and off
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        if (count++ % 11) on = !on;
        led_state(on);
        vTaskDelay(500);
    }
}

// main task for the program, run by the main loop
void main_task(__unused void *params) {
    // start blinking the light
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);

    // run a UART case swap letters
    char c;
    while(c = getchar()) {
        else putchar(char_swap(c));     // Default case, special character
    }
}

// starting point
int main( void )
{
    // initialize UART IO
    stdio_init_all();

    // give the RTOS a name, unused
    const char *rtos_name;
    rtos_name = "FreeRTOS";

    // schedule the task
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    // start running the main task
    vTaskStartScheduler();

    // shouldn't return
    return 0;
}
