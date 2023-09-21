// ColorsUtils.cpp

// Creator: JDFraire-P

// Description: Colors utilities library, add color types and conversion functions

// Date: 2023-08-31

// Version: 1.0

/*  Order of components

rgb888_t bits order: RRRRRRRR GGGGGGGG BBBBBBBB
rgb565_t bits order: RRRRR GGGGGG BBBBB

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

// Libraries
#include <Arduino.h>
#include <ColorsUtils.h>

/* COLORS STRUCTS CONSTRUCTORS */

// 24-bit RGB888 color type
// default constructor
rgb888_t::rgb888_t(){
  value = 0;
  red = 0;
  green = 0;
  blue = 0;
  name = "Unknown";
}

// Constructor with 6 digits hex color code as argument ((int)0x000000 to (int)0xFFFFFF)
rgb888_t::rgb888_t(int hex_color_code){
  value = hex_color_code & 0xFFFFFF;
  red = (uint8_t)(hex_color_code >> 16) & 0xFF;
  green = (uint8_t)(hex_color_code >> 8) & 0xFF;
  blue = (uint8_t)(hex_color_code) & 0xFF;
  name = "Unknown";
}

// Constructor with 3 arguments (red, green, blue) as arguments (0 to 255)
rgb888_t::rgb888_t(uint8_t red, uint8_t green, uint8_t blue){
  value = ((uint32_t)red << 16) | ((uint32_t)green << 8) | ((uint32_t)blue);
  this->red = red;
  this->green = green;
  this->blue = blue;
  name = "Unknown";
}

// Constructor with 2 arguments (name, int hex_color_code) as arguments
rgb888_t::rgb888_t(const char* name, uint32_t hex_color_code){
  // Serial.println("hex_color_code: " + String(hex_color_code, HEX));
  value = hex_color_code & 0xFFFFFF;
  red = (uint8_t)(hex_color_code >> 16) & 0xFF;
  green = (uint8_t)(hex_color_code >> 8) & 0xFF;
  blue = (uint8_t)(hex_color_code) & 0xFF;
  this->name = name;
}

// Constructor with 4 arguments (name, red, green, blue) as arguments
rgb888_t::rgb888_t(const char* name, uint8_t red, uint8_t green, uint8_t blue){
  value = ((uint32_t)red << 16) | ((uint32_t)green << 8) | ((uint32_t)blue);
  this->red = red;
  this->green = green;
  this->blue = blue;
  this->name = name;
}

// 16-bit RGB565 color type
// default constructor
rgb565_t::rgb565_t(){
  value = 0;
  red = 0;
  green = 0;
  blue = 0;
  name = "Unknown";
}

// Constructor with 4 digits hex color code as argument ((int)0x0000 to (int)0xFFFF)
rgb565_t::rgb565_t(int hex_color_code){
  value = hex_color_code & 0xFFFF;
  red = (uint8_t)(hex_color_code >> 11) & 0x1F;
  green = (uint8_t)(hex_color_code >> 5) & 0x3F;
  blue = (uint8_t)(hex_color_code) & 0x1F;
  name = "Unknown";
}

// Constructor with 3 arguments (red, green, blue) as arguments (0 to 255)
rgb565_t::rgb565_t(uint8_t red, uint8_t green, uint8_t blue){
  value = ((uint16_t)red << 11) | ((uint16_t)green << 5) | ((uint16_t)blue);
  this->red = red & 0x1F;
  this->green = green & 0x3F;
  this->blue = blue & 0x1F;
  name = "Unknown";
}

// Constructor with 2 arguments (name, int hex_color_code) as arguments
rgb565_t::rgb565_t(const char* name, uint16_t hex_color_code){
  value = hex_color_code & 0xFFFF;
  red = (uint8_t)(hex_color_code >> 11) & 0x1F;
  green = (uint8_t)(hex_color_code >> 5) & 0x3F;
  blue = (uint8_t)(hex_color_code) & 0x1F;
  this->name = name;
}

// Constructor with 4 arguments (name, red, green, blue) as arguments
rgb565_t::rgb565_t(const char* name, uint8_t red, uint8_t green, uint8_t blue){
  value = ((uint16_t)red << 11) | ((uint16_t)green << 5) | ((uint16_t)blue);
  this->red = red & 0x1F;
  this->green = green & 0x3F;
  this->blue = blue & 0x1F;
  this->name = name;
}

/* COLOR CONVERSION FUNCTIONS */

// Convert 24-bit RGB888 to 16-bit RGB565
rgb565_t rgb888_to_rgb565(rgb888_t rgb888){
  rgb565_t rgb565;
  rgb565.red = (uint8_t)round((float)rgb888.red / 255.0 * 31.0) & 0x1F;
  rgb565.green = (uint8_t)round((float)rgb888.green / 255.0 * 63.0) & 0x3F;
  rgb565.blue = (uint8_t)round((float)rgb888.blue / 255.0 * 31.0) & 0x1F;
  rgb565.value = ((uint16_t)rgb565.red << 11) | ((uint16_t)rgb565.green << 5) | ((uint16_t)rgb565.blue);
  rgb565.name = rgb888.name;
  return rgb565;
}
// Convert 16-bit RGB565 to 24-bit RGB888
rgb888_t rgb565_to_rgb888(rgb565_t rgb565){
  rgb888_t rgb888;
  rgb888.red = (uint8_t)round((float)rgb565.red / 31.0 * 255.0) & 0xFF;
  rgb888.green = (uint8_t)round((float)rgb565.green / 63.0 * 255.0) & 0xFF;
  rgb888.blue = (uint8_t)round((float)rgb565.blue / 31.0 * 255.0) & 0xFF;
  rgb888.value = ((uint32_t)rgb888.red << 16) | ((uint32_t)rgb888.green << 8) | ((uint32_t)rgb888.blue);
  rgb888.name = rgb565.name;
  return rgb888;
}
// Convert 24-bit RGB888 to String hex color code
String rgb888_to_String(rgb888_t rgb888){
  String hex_color_code = "0x";
  if (rgb888.red < 16) hex_color_code += "0";
  hex_color_code += String(rgb888.red, HEX);
  if (rgb888.green < 16) hex_color_code += "0";
  hex_color_code += String(rgb888.green, HEX);
  if (rgb888.blue < 16) hex_color_code += "0";
  hex_color_code += String(rgb888.blue, HEX);
  return hex_color_code;
}
// Convert 16-bit RGB565 to String hex color code, consider the 16-bit RGB565 as a 4 digits hex color code RRRRR GGGGGG BBBBB more significant byte is RRRRRGGG less significant byte is GGGBBBBB
String rgb565_to_String(rgb565_t rgb565){
  String hex_color_code = "0x";
  // more significant byte is RRRRRGGG
  uint8_t more_significant_byte = (rgb565.red << 3) | (rgb565.green >> 3);
  if (more_significant_byte < 16) hex_color_code += "0";
  hex_color_code += String(more_significant_byte, HEX);

  // less significant byte is GGGBBBBB
  uint8_t less_significant_byte = ((rgb565.green & 0x07) << 5) | rgb565.blue;
  if (less_significant_byte < 16) hex_color_code += "0";
  hex_color_code += String(less_significant_byte, HEX);
  return hex_color_code;
}


/* COMPARE COLORS FUNCTIONS */

// Compare 24-bit RGB888 colors
float color_similarity(rgb888_t rgb888_1, rgb888_t rgb888_2){
  float similarity = 0.0;
  similarity += pow((float)rgb888_1.red - (float)rgb888_2.red, 2);
  similarity += pow((float)rgb888_1.green - (float)rgb888_2.green, 2);
  similarity += pow((float)rgb888_1.blue - (float)rgb888_2.blue, 2);
  similarity = sqrt(similarity);

  // normalize the similarity
  similarity = 1.0 - (similarity / (sqrt(pow(255.0, 2) * 3.0)));

  return similarity;
}

// Compare 16-bit RGB565 colors
float color_similarity(rgb565_t rgb565_1, rgb565_t rgb565_2){
  float similarity = 0.0;
  similarity += pow((float)rgb565_1.red - (float)rgb565_2.red, 2);
  similarity += pow((float)rgb565_1.green - (float)rgb565_2.green, 2);
  similarity += pow((float)rgb565_1.blue - (float)rgb565_2.blue, 2);
  similarity = sqrt(similarity);

  // normalize the similarity
  similarity = 1.0 - (similarity / (sqrt(pow(31.0, 2) * 3.0)));

  return similarity;
}

// Compare 24-bit RGB888 and 16-bit RGB565 colors
float color_similarity(rgb888_t rgb888, rgb565_t rgb565){
  float similarity = 0.0;

  // convert rgb888 to rgb565
  rgb565_t rgb565_2 = rgb888_to_rgb565(rgb888);

  similarity += pow((float)rgb565.red - (float)rgb565_2.red, 2);
  similarity += pow((float)rgb565.green - (float)rgb565_2.green, 2);
  similarity += pow((float)rgb565.blue - (float)rgb565_2.blue, 2);
  similarity = sqrt(similarity);

  // normalize the similarity
  similarity = 1.0 - (similarity / (sqrt(pow(255.0, 2) * 3.0)));

  return similarity;
}

// Compare 16-bit RGB565 and 24-bit RGB888 colors
float color_similarity(rgb565_t rgb565, rgb888_t rgb888){
  float similarity = 0.0;

  // convert rgb888 to rgb565
  rgb565_t rgb565_2 = rgb888_to_rgb565(rgb888);

  // calculate the similarity between the colors in rgb565 with method euclidean distance
  similarity += pow((float)rgb565.red - (float)rgb565_2.red, 2);
  similarity += pow((float)rgb565.green - (float)rgb565_2.green, 2);
  similarity += pow((float)rgb565.blue - (float)rgb565_2.blue, 2);
  similarity = sqrt(similarity);

  // normalize the similarity
  similarity = 1.0 - (similarity / (sqrt(pow(31.0,2.0)+pow(63.0,2.0)+pow(31.0,2.0))));
  
  // Serial.println("Color 1: " + rgb565_to_String(rgb565) + " Color 2: " + rgb565_to_String(rgb565_2) + " Similarity: " + String(similarity));

  return similarity;
}


/* COLOR LIST FUNCTIONS */

// Get color from color list by name
rgb888_t get_color_by_name(const char* name, const rgb888_t* colors_list){
  rgb888_t color;
  // size of the list
  int size = sizeof(colors_list) / sizeof(colors_list[0]);

  for (int i = 0; i < size; i++){
    if (name == colors_list[i].name){
      color = colors_list[i];
      break;
    }
  }
  return color;
}

// Get color from color list by hex color code
rgb888_t get_color_by_hex_color_code(int hex_color_code, const rgb888_t* colors_list){
  rgb888_t color;
  // size of the list
  int size = sizeof(colors_list) / sizeof(colors_list[0]);

  for (int i = 0; i < size; i++){
    if (hex_color_code == colors_list[i].value){
      color = colors_list[i];
      break;
    }
  }
  return color;
}

// Get most similar color from color list
rgb888_t get_similar_color888(rgb888_t rgb888, const rgb888_t* colors_list){
  rgb888_t color;
  // size of the list
  int size = sizeof(colors_list) / sizeof(colors_list[0]);

  float _similarity = 0.0;
  float max_similarity = 0.0;
  int index = 0;

  for (int i = 0; i < size; i++){
    _similarity = color_similarity(rgb888, colors_list[i]);
    if (_similarity > max_similarity){
      max_similarity = _similarity;
      index = i;
    }
  }
  color = colors_list[index];
  return color;
}

// Get most similar color from color list
rgb565_t get_similar_color565(rgb565_t rgb565, const rgb888_t colors_list[]){
  rgb565_t color;
  // size of the list
  // int size = sizeof(colors_list) / sizeof(colors_list[0]);
  int size = 50;
  // Serial.println("Size: " + String(size));

  float _similarity = 0.0;
  float max_similarity = 0.0;
  int index = 0;


  for (int i = 0; i < size; i++){
    _similarity = color_similarity(rgb565, colors_list[i]);
    if (_similarity > max_similarity){
      max_similarity = _similarity;
      index = i;
    }
    // Serial.println("Index: " + String(i) + " Similarity: " + String(_similarity) + " Max similarity: " + String(max_similarity) + " Color1: " + rgb565_to_String(rgb565) + " Color2: " + rgb888_to_String(colors_list[i]));
  }
  color = rgb888_to_rgb565(colors_list[index]);
  return color;
}

/* NAMED COLORS LIST */
extern const rgb888_t COLORS[] = {
  {"Aqua", 0x00FFFF},
  {"Aquamarine", 0x7FFFD4},
  {"Azure", 0xF0FFFF},
  {"Beige", 0xF5F5DC},
  {"Bisque", 0xFFE4C4},
  {"Black", 0x000000},
  {"Blue", 0x0000FF},
  {"Brown", 0xA52A2A},
  {"Chartreuse", 0x7FFF00},
  {"Chocolate", 0xD2691E},
  {"Coral", 0xFF7F50},
  {"Cornsilk", 0xFFF8DC},
  {"Crimson", 0xDC143C},
  {"Cyan", 0x00FFFF},
  {"Fuchsia", 0xFF00FF},
  {"Gainsboro", 0xDCDCDC},
  {"Gold", 0xFFD700},
  {"Gray", 0x808080},
  {"Green", 0x008000},
  {"Indigo", 0x4B0082},
  {"Ivory", 0xFFFFF0},
  {"Khaki", 0xF0E68C},
  {"Lavender", 0xE6E6FA},
  {"Lime", 0x00FF00},
  {"Linen", 0xFAF0E6},
  {"Magenta", 0xFF00FF},
  {"Maroon", 0x800000},
  {"Moccasin", 0xFFE4B5},
  {"Navy", 0x000080},
  {"Olive", 0x808000},
  {"Orange", 0xFFA500},
  {"Orchid", 0xDA70D6},
  {"Peru", 0xCD853F},
  {"Pink", 0xFFC0CB},
  {"Plum", 0xDDA0DD},
  {"Purple", 0x800080},
  {"Red", 0xFF0000},
  {"Salmon", 0xFA8072},
  {"Sienna", 0xA0522D},
  {"Silver", 0xC0C0C0},
  {"Snow", 0xFFFAFA},
  {"Tan", 0xD2B48C},
  {"Teal", 0x008080},
  {"Thistle", 0xD8BFD8},
  {"Tomato", 0xFF6347},
  {"Turquoise", 0x40E0D0},
  {"Violet", 0xEE82EE},
  {"Wheat", 0xF5DEB3},
  {"White", 0xFFFFFF},
  {"Yellow", 0xFFFF00}
};
