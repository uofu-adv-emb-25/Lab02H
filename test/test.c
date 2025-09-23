#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include <string.h>
#include "unity_config.h"
#include "functions.h"

int state = 0;
bool on = false;

// reset the test cases
void setUp(void) {
    state = 0;
    on = false;
}

// nothing to do here
void tearDown(void) {}

void test_run_led_state() {
    const bool states[] = {true, false, true, false, true, false, true, false, true, false, false};
    for (int i = 0; i < 30; i++) {
        char buf[64];
        sprintf(buf, "LED does not time correctly: %d", i);
        TEST_ASSERT_TRUE_MESSAGE(states[i % 11] == run_led_state(&state, &on), buf);
    }
}

void test_char_swap() {
    const char testString[] = "Hello, World!";
    const char outString[] = "hELLO, wORLD!";
    for (int i = 0; i < strlen(testString); i++) {
        TEST_ASSERT_TRUE_MESSAGE(char_swap(testString[i]) == outString[i], "Character swap does not work");
    }
}

int main (void)
{
        stdio_init_all();
        sleep_ms(5000); // Give time for TTY to attach.
        while (1) {
            printf("Start tests\n");
            UNITY_BEGIN();
            RUN_TEST(test_run_led_state);
            RUN_TEST(test_char_swap);
            sleep_ms(5000);
            UNITY_END();
        }
}
