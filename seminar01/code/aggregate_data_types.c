struct Point {
    int x;
    int y;
};


int main() {
    // Structs
    struct Point origin;
    origin.x = 0;
    origin.y = 1;

    // Arrays
    int array_1[] = { 0, 1, 2, 3 };
    int array_2[10];

    // Which element do we set here?
    array_2[2] = 10;

    // Can you spot the differences?
    char string_1[] = { 'a', 'h', 'o', 'j' };
    const char* string_2 = "ahoj";

    return 0;
}
