// JDFraire_ColorsUtils.h

// Creator: JDFraire

// Description: Colors utilities library, add color types and conversion functions

// Date: 2023-08-31

// Version: 1.0

/*  Order of components
bit   rgb888_t    rgb565_t
  1   blue        blue
  2   blue        blue
  3   blue        blue
  4   blue        blue
  5   blue        blue
  6   blue        green
  7   blue        green
  8   blue        green
  9   green       green
  10  green       green
  11  green       green
  12  green       red
  13  green       red
  14  green       red
  15  green       red
  16  green       red
  17  red
  18  red
  19  red
  20  red
  21  red
  22  red
  23  red
  24  red
*/

/*  Convert 24-bit RGB888 to 16-bit RGB565
1. First, extract the red, green, and blue components of the 24-bit RGB888 color value. Each component is an integer between 0 and 255.
2. Next, convert each component to a 5 or 6-bit value, depending on whether it corresponds to the red or blue channel (5-bit) or the green channel (6-bit). To do this, divide each component by the maximum possible value in the source format (255) and then multiply the result by the maximum value for that channel in the target format (31 for red and blue, 63 for green).
3. Shift the 5-bit red value to the left by 11 bits to make room for the green and blue values, which will be 6 + 5 = 11 bits. The red value will occupy the upper 5 bits of the 16-bit RGB565 value.
4. Shift the 6-bit green value to the left by 5 bits to make room for the blue value, which will be 5 bits. The green value will occupy bits 6 to 11 of the 16-bit RGB565 value.
5. The blue value does not need to be shifted t the left as it will occupy the lower 5 bits of the RGB565 value.
6. Finally, concatenate the red, green, and blue values to create the 16-bit RGB565 color value.
*/

/*  Convert 16-bit RGB565 to 24-bit RGB888
1. First, extract the red, green, and blue components of the 16-bit RGB565 color value. Each component is an integer between 0 and 31 for the red and blue channels and between 0 and 63 for the green channel.
2. To extract the red component, shift the 16-bit RGB565 value to the right by 11 bits to remove the green and blue values.
3. To extract the green component, shift the 16-bit RGB565 value to the right by 5 bits to remove the blue value and then mask the result with 0b111111 (63) to remove the red value by keeping only the lower 6 bits.
4. To extract the blue component, mask the 16-bit RGB565 value with 0b11111 (31) to remove the red and green values by keeping only the lower 5 bits.
5. Finally, convert each component to an 8-bit value, depending on whether it corresponds to the red, green, or blue channel. To do this, divide each component by the maximum possible value in the source format (31 for red and blue, 63 for green) and then multiply the result by the maximum value for that channel in the target format (255).
*/

#ifndef COLORSUTILS_H
#define COLORSUTILS_H

// Libraries
#include <Arduino.h>


/* COLORS STRUCTS */

// 24-bit RGB888 color type
struct rgb888_t{
  uint32_t value; // 24 bits
  String name; // Color name (if is provided)

  uint8_t red; // 8 bits 
  uint8_t green; // 8 bits
  uint8_t blue; // 8 bits

  // default constructor
  rgb888_t();
  // Constructor with 6 digits hex color code as argument ((int)0x000000 to (int)0xFFFFFF)
  rgb888_t(int hex_color_code);
  // Constructor with 3 arguments (red, green, blue) as arguments (0 to 255)
  rgb888_t(uint8_t red, uint8_t green, uint8_t blue);

  // NAMED COLORS CONSTRUCTORS

  // Constructor with 2 arguments (name, int hex_color_code) as arguments
  rgb888_t(const char* name, uint32_t hex_color_code);
  // Constructor with 4 arguments (name, red, green, blue) as arguments
  rgb888_t(const char* name, uint8_t red, uint8_t green, uint8_t blue);
};

// 16-bit RGB565 color type
struct rgb565_t{
  uint16_t value; // 16 bits
  uint8_t red; // 5 bits
  uint8_t green; // 6 bits
  uint8_t blue; // 5 bits

  String name; // Color name (if is provided)

  // default constructor
  rgb565_t();
  // Constructor with 4 digits hex color code as argument ((int)0x0000 to (int)0xFFFF) 
  rgb565_t(int hex_color_code);
  // Constructor with 3 arguments (red, green, blue) as arguments (0 to 255)
  rgb565_t(uint8_t red, uint8_t green, uint8_t blue);

  // NAMED COLORS CONSTRUCTORS

  // Constructor with 2 arguments (name, int hex_color_code) as arguments
  rgb565_t(const char* name, uint16_t hex_color_code);
  // Constructor with 4 arguments (name, red, green, blue) as arguments
  rgb565_t(const char* name, uint8_t red, uint8_t green, uint8_t blue);

};

/* COLOR CONVERSION FUNCTIONS */

// Convert 24-bit RGB888 to 16-bit RGB565
rgb565_t rgb888_to_rgb565(rgb888_t rgb888);
// Convert 16-bit RGB565 to 24-bit RGB888
rgb888_t rgb565_to_rgb888(rgb565_t rgb565);
// Convert 24-bit RGB888 to String hex color code
String rgb888_to_String(rgb888_t rgb888);
// Convert 16-bit RGB565 to String hex color code
String rgb565_to_String(rgb565_t rgb565);


/* COMPARE COLORS FUNCTIONS */

// Compare 24-bit RGB888 colors
float color_similarity(rgb888_t rgb888_1, rgb888_t rgb888_2);
// Compare 16-bit RGB565 colors
float color_similarity(rgb565_t rgb565_1, rgb565_t rgb565_2);
// Compare 24-bit RGB888 and 16-bit RGB565 colors
float color_similarity(rgb888_t rgb888, rgb565_t rgb565);
// Compare 24-bit RGB888 and 16-bit RGB565 colors
float color_similarity(rgb565_t rgb565, rgb888_t rgb888);

/* NAMED COLORS LIST */
extern const rgb888_t COLORS[];

/* COLOR LIST FUNCTIONS */

// Get color from color list by name
rgb888_t get_color_by_name(const char* name, const rgb888_t* colors_list);

// Get color from color list by hex color code
rgb888_t get_color_by_hex(int hex_color_code, const rgb888_t* colors_list);

// Get most similar color from color list
rgb888_t get_similar_color888(rgb888_t rgb888, const rgb888_t* colors_list);

// Get most similar color from color list
rgb565_t get_similar_color565(rgb565_t rgb565, const rgb888_t colors_list[]);

#endif