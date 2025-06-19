#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expans){
  unsigned result = power(x, y);
  if (result != expans){
    printf("power(%u, %u) = %u, expans %u\n", x, y, result, expans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
    // Basic cases
    run_check(2, 3, 8);
    run_check(3, 2, 9);

    // Edge cases
    run_check(0, 0, 1);    // 0^0 is 1 by convention
    run_check(0, 5, 0);
    run_check(5, 0, 1);

    // 1 as base or exponent
    run_check(1, 100, 1);
    run_check(100, 1, 100);

    // Large numbers
    run_check(2, 16, 65536);
    run_check(2, 31, 2147483648U);

    // Max unsigned value as base
    run_check(4294967295U, 1, 4294967295U);
    run_check(4294967295U, 0, 1);

    // Other cases
    run_check(10, 5, 100000);

    // If all tests passed
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
