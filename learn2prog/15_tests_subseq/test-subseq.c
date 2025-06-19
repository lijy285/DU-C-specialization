#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

size_t maxSeq(int * array, size_t n);

void test_maxSeq() {
    // Test 0: Empty array
    int a0[] = {};
    assert(maxSeq(a0, 0) == 0);

    // Test 1: One element
    int a1[] = {42};
    assert(maxSeq(a1, 1) == 1);

    // Test 2: All increasing
    int a2[] = {1, 2, 3, 4, 5};
    assert(maxSeq(a2, 5) == 5);

    // Test 3: All decreasing
    int a3[] = {5, 4, 3, 2, 1};
    assert(maxSeq(a3, 5) == 1);

    // Test 4: All same
    int a4[] = {7, 7, 7, 7, 7};
    assert(maxSeq(a4, 5) == 1);

    // Test 5: Mixed up and down
    int a5[] = {1, 2, 3, 2, 3, 4, 5, 2};
    assert(maxSeq(a5, 8) == 4); // 2,3,4,5

    // Test 6: Negative numbers
    int a6[] = {-3, -2, -1, 0, 1};
    assert(maxSeq(a6, 5) == 5);

    // Test 7: Sequence at the end
    int a7[] = {10, 5, 1, 2, 3};
    assert(maxSeq(a7, 5) == 3);

    // Test 8: Sequence at the start
    int a8[] = {1, 2, 3, 2, 1};
    assert(maxSeq(a8, 5) == 3);

    // Test 9: Zigzag
    int a9[] = {1, 3, 2, 4, 3, 5};
    assert(maxSeq(a9, 6) == 2);

    // Test 10: Two increasing of equal length
    int a10[] = {1, 2, 3, 2, 3, 4};
    assert(maxSeq(a10, 6) == 3);

    // Test 11: Large array
    int a11[1000];
    for (int i = 0; i < 1000; i++) {
        a11[i] = i;
    }
    assert(maxSeq(a11, 1000) == 1000);
}

int main(void) {
    test_maxSeq();
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
