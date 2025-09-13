#include "functions.h"

#include <stdbool.h>

// run the led with the count state and power state as inputs/outputs to the function
// this function is effective the update for each tick of the state FSM
bool run_led_state(int* state, bool* on){
    *state = (*state + 1) % 11;
    if (*state) *on = !(*on);
    return *on;
}

// swap the charactar case
char char_swap(const char c){
    if (c <= 'z' && c >= 'a') return c - 32;          // Check for lowercase, make uppercase
    else if (c >= 'A' && c <= 'Z') return c + 32;     // Check for uppercase, make lowercase
    return c;
}