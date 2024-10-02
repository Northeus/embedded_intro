int main() {
    int x;

    // Obtain the address of x
    int* x_address = &x;
    // Obtain the value at the address of x
    int value_at_x_address = *x_address;

    return 0;
}
