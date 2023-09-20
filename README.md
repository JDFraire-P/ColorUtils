# JDFraire_ColorsUtils Library

**Creator:** JDFraire

**Description:** Colors utilities library that adds color types and conversion functions.

**Date:** 2023-08-31

**Version:** 1.0.2

## Introduction

The JDFraire_ColorsUtils library is a utility library for Arduino that provides color-related functionalities. It introduces two custom color types, `rgb888_t` and `rgb565_t`, along with conversion functions between these types and standard color formats. Additionally, the library includes functions for comparing colors and a list of named colors.

## Order of Components

The library operates on 24-bit RGB888 and 16-bit RGB565 color representations. Here's the order of components in these formats:

**RGB888:**
1. Red
2. Green
3. Blue

**RGB565:**
1. Red
2. Red
3. Red
4. Red
5. Red
6. Green
7. Green
8. Green
9. Green
10. Green
11. Green
12. Blue
13. Blue
14. Blue
15. Blue
16. Blue

## Color Conversion Functions

### Convert 24-bit RGB888 to 16-bit RGB565

1. Extract the red, green, and blue components of the 24-bit RGB888 color value, each ranging from 0 to 255.
2. Convert each component to a 5 or 6-bit value, depending on whether it corresponds to the red or blue channel (5-bit) or the green channel (6-bit). To do this, divide each component by 255 and then multiply by the maximum value for that channel in the target format (31 for red and blue, 63 for green).
3. Shift the 5-bit red value to the left by 11 bits to make room for the green and blue values (totaling 11 bits).
4. Shift the 6-bit green value to the left by 5 bits to make room for the blue value (5 bits).
5. The blue value does not need to be shifted as it will occupy the lower 5 bits of the RGB565 value.
6. Concatenate the red, green, and blue values to create the 16-bit RGB565 color value.

### Convert 16-bit RGB565 to 24-bit RGB888

1. Extract the red, green, and blue components of the 16-bit RGB565 color value, each ranging from 0 to 31 (red and blue) or 0 to 63 (green).
2. To extract the red component, shift the 16-bit RGB565 value to the right by 11 bits.
3. To extract the green component, shift the 16-bit RGB565 value to the right by 5 bits, then mask the result with 0b111111 (63) to keep only the lower 6 bits.
4. To extract the blue component, mask the 16-bit RGB565 value with 0b11111 (31) to keep only the lower 5 bits.
5. Convert each component to an 8-bit value by dividing by the maximum possible value in the source format and then multiplying by 255.

## Usage

### Color Structs

- `rgb888_t`: Represents a 24-bit RGB color with red, green, blue components, and a name (optional).
- `rgb565_t`: Represents a 16-bit RGB color with red, green, blue components, and a name (optional).

### Color Conversion Functions

- `rgb565_t rgb888_to_rgb565(rgb888_t rgb888)`: Converts RGB888 to RGB565.
- `rgb888_t rgb565_to_rgb888(rgb565_t rgb565)`: Converts RGB565 to RGB888.
- `String rgb888_to_String(rgb888_t rgb888)`: Converts RGB888 to a hex color code string.
- `String rgb565_to_String(rgb565_t rgb565)`: Converts RGB565 to a hex color code string.

### Compare Colors Functions

- `float color_similarity(rgb888_t rgb888_1, rgb888_t rgb888_2)`: Compares two RGB888 colors.
- `float color_similarity(rgb565_t rgb565_1, rgb565_t rgb565_2)`: Compares two RGB565 colors.
- `float color_similarity(rgb888_t rgb888, rgb565_t rgb565)`: Compares RGB888 with RGB565.
- `float color_similarity(rgb565_t rgb565, rgb888_t rgb888)`: Compares RGB565 with RGB888.

### Named Colors List

- `extern const rgb888_t COLORS[]`: A list of named RGB888 colors.

### Color List Functions

- `rgb888_t get_color_by_name(const char* name, const rgb888_t* colors_list)`: Get a color by name from the list.
- `rgb888_t get_color_by_hex(int hex_color_code, const rgb888_t* colors_list)`: Get a color by hex color code from the list.
- `rgb888_t get_similar_color888(rgb888_t rgb888, const rgb888_t* colors_list)`: Get the most similar RGB888 color from the list.
- `rgb565_t get_similar_color565(rgb565_t rgb565, const rgb888_t colors_list[])`: Get the most similar RGB565 color from the list.

## Named Colors List

The library includes a list of named colors with their corresponding RGB888 values.

## Examples

Examples and usage can be found in the Arduino sketch provided with the library.

## License

This library is released under the [MIT License](LICENSE).

---
© 2023 JDFraire
