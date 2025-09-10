#include "functions.h"

bool get_led(bool state){
    
}

char char_swap(char c){
    if (c <= 'z' && c >= 'a') putchar(c - 32);          // Check for lowercase, make uppercase
    else if (c >= 'A' && c <= 'Z') putchar(c + 32);     // Check for uppercase, make lowercase
}
