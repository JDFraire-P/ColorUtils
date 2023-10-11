// ColorsUtils.cpp

// Creator: JDFraire-P

// Description: Colors utilities library, add color types and conversion functions

// Date: 2023-08-31

// Version: 1.0

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
#include <ColorsUtils.h>

/* CLASS RGB888*/

RGB888::RGB888() {
  _red = 0;
  _green = 0;
  _blue = 0;
  _name = "";
}

RGB888::RGB888(uint32_t rgb888, String name) {
  _red =   (rgb888 >> 16) & 0xFF;
  _green = (rgb888 >>  8) & 0xFF;
  _blue =  (rgb888 >>  0) & 0xFF;
  _name = name;
}


RGB888::RGB888(uint8_t red, uint8_t green, uint8_t blue, String name) {
  _red = red;
  _green = green;
  _blue = blue;
  _name = name;
}

uint8_t RGB888::red() {
  return _red;
}

uint8_t RGB888::green() {
  return _green;
}

uint8_t RGB888::blue() {
  return _blue;
}

String RGB888::name() {
  return _name;
}

uint32_t RGB888::uintRGB888() {
  return ((uint32_t)red() << 16) | ((uint32_t)green() << 8) | (uint32_t)blue();
}

uint16_t RGB888::uintRGB565() {
  uint8_t r = (uint8_t)round((float)red() / 255.0 * 31.0);
  uint8_t g = (uint8_t)round((float)green() / 255.0 * 63.0);
  uint8_t b = (uint8_t)round((float)blue() / 255.0 * 31.0);
  uint16_t rgb565 = ((uint16_t)r << 11) | ((uint16_t)g << 5) | ((uint16_t)b);
  return rgb565;
}

String RGB888::strRGB888() {
  String hexColor = String(uintRGB888(), HEX);
  while (hexColor.length() < 6) {
      hexColor = "0" + hexColor;
  }
  return "0x" + hexColor;
}

String RGB888::strRGB565() {
  String hexColor = String(uintRGB565(), HEX);
  while (hexColor.length() < 4) {
      hexColor = "0" + hexColor;
  }
  return "0x" + hexColor;
}

float RGB888::compare(RGB888 color) {
  // Calculate the Euclidean difference between colors
  float dr = _red - color.red();
  float dg = _green - color.green();
  float db = _blue - color.blue();
  float distance = sqrt(dr * dr + dg * dg + db * db);

  // Normalizes the distance in the range [0, 1]
  float maxDistance = sqrt(255UL * 255UL + 255UL * 255UL + 255UL * 255UL);
  return 1.0 - (distance / maxDistance);
}

RGB888 RGB888::getClosest(RGB888 list[], size_t size){
  RGB888 color;
  float similarity = 0.0;
  float max_similarity = 0.0;
  int index = 0;
  for (int i = 0; i < size; i++){
    similarity = compare(list[i]);
    if (similarity > max_similarity){
      max_similarity = similarity;
      index = i;
    }
  }
  color = list[index];
  return color;
}


/* CLASS RGB565 */

RGB565::RGB565() {
  _rgb565 = 0;
  _name = "";
}

RGB565::RGB565(uint16_t rgb565, String name) {
  _rgb565 = rgb565;
  _name = name;
}

RGB565::RGB565(uint8_t red, uint8_t green, uint8_t blue, String name) {
  uint16_t r = red & 0x1F;
  uint16_t g = green & 0x3F;
  uint16_t b = blue & 0x1F;

  _rgb565 = ((r << 11) | (g << 5) | b);
  _name = name;
}

uint8_t RGB565::red() {
  return ((_rgb565 >> 11) & 0x1F);
}

uint8_t RGB565::green() {
  return ((_rgb565 >> 5) & 0x3F);
}

uint8_t RGB565::blue() {
  return (_rgb565 & 0x1F);
}

String RGB565::name() {
  return _name; 
}

uint16_t RGB565::uintRGB565() {
  return _rgb565;
}

uint32_t RGB565::uintRGB888() {
  uint8_t r = (uint8_t)round((float)red() / 31.0 * 255.0);
  uint8_t g = (uint8_t)round((float)green() / 63.0 * 255.0);
  uint8_t b = (uint8_t)round((float)blue()/ 31.0 * 255.0);
  uint32_t rgb888 = ((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b);

  return rgb888;
}

String RGB565::strRGB565() {
  String hexColor = String(_rgb565, HEX);
  while (hexColor.length() < 4) {
    hexColor = "0" + hexColor;
  }
  return "0x" + hexColor;
}

String RGB565::strRGB888() {
  String hexColor = String(uintRGB888(), HEX);
  while (hexColor.length() < 6) {
      hexColor = "0" + hexColor;
  }
  return "0x" + hexColor;
}

float RGB565::compare(RGB565 color) {
  // Calculate the Euclidean difference between colors
  int16_t dr = red() - color.red();
  int16_t dg = green() - color.green();
  int16_t db = blue() - color.blue();
  float distance = sqrt(dr * dr + dg * dg + db * db);

  // Normalizes the distance in the range [0, 1]
  float maxDistance = sqrt(255UL * 255UL + 255UL * 255UL + 255UL * 255UL);
  return 1.0 - (distance / maxDistance);
}

RGB565 RGB565::getClosest(RGB565 list[], size_t size){
  RGB565 color;
  float similarity = 0.0;
  float max_similarity = 0.0;
  int index = 0;
  for (int i = 0; i < size; i++){
    similarity = compare(list[i]);
    if (similarity > max_similarity){
      max_similarity = similarity;
      index = i;
    }
  }
  color = list[index];
  return color;
}

RGB888 toRGB888(RGB565 color) {
  return RGB888(color.uintRGB888(), color.name());
}

RGB565 toRGB565(RGB888 color) {
  return RGB565(color.uintRGB565(), color.name());
}

RGB888 getColorRGB888(String name, RGB888 list[], size_t size) {
  RGB888 color;
  for (int i = 0; i < size; i++){
    if (name.equals(list[i].name())){
      color = list[i];
      break;
    }
  }
  return color;
}

RGB565 getColorRGB565(String name, RGB565 list[], size_t size) {
  RGB565 color;
  for (int i = 0; i < size; i++){
    if (name.equals(list[i].name())){
      color = list[i];
      break;
    }
  }
  return color;
}
