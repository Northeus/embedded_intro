#include <stdio.h>

// Macro can be used to substitute string within code
#define ZERO 0

// Function taking two floats and returning int
int add(float x, float y) {
    return x + y + ZERO;
}

int main() {
    // If statement
    if (0) {
        // ...
    } else if (1) {
        // ...
    } else {
        // ...
    }

    // For loop
    for (int x = 0; x < 10; x++) {
        // ...
    }

    // While
    int x = 10;

    while (x < 10) {
        x++;
        // ...
    }

    while (1) {
        x++;

        if (x >= 10) {
            break;
        }

        // ...
    }

    // Switch
    int y = 10;

    switch (y) {
    case 10:
        // ...
        break;
    case 11:
    case 12:
    case 13:
        // ...
        break;
    default:
        // ...
        printf("Default code block\r\n");
    }

    // Jumps
    goto landing;

    // ...

    landing:

    // ...

    return 0;
}
