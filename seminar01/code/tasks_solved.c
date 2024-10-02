#include <stdio.h>
#include <stdint.h>

uint8_t mask(uint8_t number) {
    /**
     * TODO:
     *  Implement function that mask given number and
     *  set all bits except second to fifth bit to zero.
     *  Thus for input 0b11111111 function returns 0b00011110.
     **/
    return number & 0b00011110;
}

uint8_t get_bit(uint8_t number, uint8_t n) {
    /**
     * TODO:
     *  Returns n-th bit of the given number,
     *  indexed from zero. For example, if we call
     *  get_bit(0b0010, 1), we receive 1.
     **/
    return (number >> n) & 1;
}

uint8_t bit_set(uint8_t number, uint8_t n, uint8_t value) {
    /**
     * TODO:
     *  Function should set n-th bit of the given number to the
     *  specified value, indexed from zero. For example, for calling
     *  bit_set(0b1111, 2, 0) should return 0b1011.
     **/

    return (number & (~(1u << n))) | (value << n);
}

uint8_t bit_flip(uint8_t number, uint8_t n) {
    /**
     * TODO:
     *  This function should flip the n-th bit of the given number,
     *  indexed from zero. Calling bit_flip(0b101, 1) returns 0b111.
     **/
    uint8_t bit = get_bit(number, n);

    return bit_set(number, n, !bit);
}

uint8_t increment(uint8_t* number_addr) {
    /**
     * TODO:
     *  Increment a number stored at the given address by one,
     *  if the number is greater or equal 100, set it to zero
     *  and return 1, otherwise do nothing and return 0.
     */

    (*number_addr) = ++(*number_addr) % 100;

    return *number_addr == 0;
}

//=======//
// TESTS //
//=======//

int test_mask() {
    return mask(0b11111111) == 0b00011110
        && mask(0b00000000) == 0b00000000
        && mask(0b01010101) == 0b00010100
        && mask(0b11100001) == 0b00000000;
}

int test_get_bit() {
    uint8_t number = 0b01101;
    uint8_t values[] = { 1u, 0u, 1u, 1u, 0u };

    for (uint8_t i = 0; i < 5; i++) {
        if (get_bit(number, i) != values[i]) {
            return 0;
        }
    }

    return 1;
}

int test_bit_set() {
    return bit_set(0b0000, 1, 0) == 0b0000
        && bit_set(0b1111, 1, 0) == 0b1101
        && bit_set(0b0000, 1, 1) == 0b0010
        && bit_set(0b1111, 1, 1) == 0b1111;
}

int test_bit_flip() {
    return bit_flip(0b0000, 1) == 0b0010
        && bit_flip(0b1111, 1) == 0b1101;
}

int test_incrementer() {
    uint8_t number = 0;

    for (int i = 0; i < 99; i++) {
        if (increment(&number) != 0 || number != i + 1) {
            return 0;
        }
    }

    int value = increment(&number);

    return value == 1 && number == 0;
}

void print_result(const char* test_name, int test_result) {

    printf("Test \"%s\" [%s]\r\n", test_name, test_result ? "PASSED" : "FAILED");
}

int main() {
    print_result("mask", test_mask());
    print_result("bit_set", test_bit_set());
    print_result("bit_flip", test_bit_flip());
    print_result("get_bit", test_get_bit());
    print_result("incrementer", test_incrementer());

    return 0;
}
