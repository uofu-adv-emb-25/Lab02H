#ifndef fucntions_h
#define functions_h

#include <stdbool.h>

// run the led with the count state and power state as inputs/outputs to the function
// this function is effective the update for each tick of the state FSM
bool run_led_state(int*, bool*);

// swap upper and lower case letters
char char_swap(const char c);

#endif