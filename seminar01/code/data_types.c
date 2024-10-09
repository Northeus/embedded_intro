// Standard library for fix-sized integer types
#include <stdint.h>

int main() {
    //===============//
    // Numeric types //
    //===============//

    // Integral numbers
    int integer = 30;
    uint8_t integer_with_fixed_size = 20;
    uint32_t unsigned_fixed_integer = 10u; // Note the suffix u
    int bin = 0b0011;   // Prefix "0b" for binary
    int oct = 011;      // Prefix "0" for octal
    int dec = 11;       // Prefix nothing for decimal
    int hex = 0x11;     // Prefix "0x" for hexa

    /**
     * Note:
     *  Binary and hexadecimal literals might be prefered
     *  when working with individual bits as it is easier
     *  to see, which bits are manipulated.
     */

    // Floating numbers
    // (be aware of the precision)
    float float_has_smaller_precision_than_double = 0.4f; // Note the suffix f
    double scientific_notation = 5.3e-1;

    //============//
    // Characters //
    //============//

    const char* null_terminated_string = "String";
    char terminator = '\0';
    char letter = 'a';
    char newline = '\n'; // Be aware of Windows, which also require '\r'

    return 0;
}
