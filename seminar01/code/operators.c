#include <stdio.h>

int main() {
    printf("Basic arithmetic operators:\r\n");
    printf("10 + 5 = %d\r\n", 10 + 5);
    printf("10 - 5 = %d\r\n", 10 - 5);
    printf("10 * 5 = %d\r\n", 10 * 5);
    printf("10 / 5 = %d\r\n", 10 / 5);
    printf("10 %% 5 = %d\r\n", 10 % 5);

    printf("Basic logic operators:\r\n");
    printf("1 == 0 = %d\r\n", 1 == 0);
    printf("1 == 1 = %d\r\n", 1 == 1);
    printf("1 != 0 = %d\r\n", 1 != 0);
    printf("1 && 1 = %d\r\n", 1 && 1);
    printf("1 && 0 = %d\r\n", 1 && 0);
    printf("1 || 0 = %d\r\n", 1 || 0);
    printf("0 || 0 = %d\r\n", 0 || 0);
    printf("!1 = %d\r\n", !1);

    printf("Basic bit operators:\r\n");
    printf("0b0011 & 0b0101 = %b\r\b", 0b0011 & 0b1100);
    printf("0b0011 | 0b0101 = %b\r\b", 0b0011 | 0b1100);
    printf("0b0011 ^ 0b0101 = %b\r\b", 0b0011 ^ 0b1100);
    printf("~0b01 = %b\r\b", ~0b01);

    int x = 10;
    x += 10;
    x *= 2;
    x--;

    return 0;
}
