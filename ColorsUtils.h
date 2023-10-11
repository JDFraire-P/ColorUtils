// ColorsUtils.h

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

#ifndef COLORSUTILS_H
#define COLORSUTILS_H

// Libraries
#include <Arduino.h>

/// @class RGB888
/// @brief Represents an RGB color in the 888 format (8 bits for red, green, and blue).
class RGB888{
  public:
    /// @brief Default constructor for RGB888 color.
    RGB888();

    /// @brief Constructor for RGB888 color using an RGB888 format (0xFFFFFF).
    /// @param rgb888 A 32-bit unsigned integer representing the color in RGB888 format.
    /// @param name (Optional) A string containing the name of the color.
    RGB888(uint32_t rgb888, String name = ""); 

    /// @brief Constructor for RGB888 color using individual 8-bit components for each color channel.
    /// @param red An 8-bit unsigned integer representing the red component (0-255).
    /// @param green An 8-bit unsigned integer representing the green component (0-255).
    /// @param blue An 8-bit unsigned integer representing the blue component (0-255).
    /// @param name (Optional) A string containing the name of the color.
    RGB888(uint8_t red, uint8_t green, uint8_t blue, String name = ""); 

    /// @brief Gets the red component of the RGB color.
    /// @return An 8-bit unsigned integer representing the red component (0-255).
    uint8_t red();

    /// @brief Gets the green component of the RGB color.
    /// @return An 8-bit unsigned integer representing the green component (0-255).
    uint8_t green();

    /// @brief Gets the blue component of the RGB color.
    /// @return An 8-bit unsigned integer representing the blue component (0-255).
    uint8_t blue();

    /// @brief Returns the name of the color.
    /// @return A String containing the name of the color.
    String name();

    /// @brief Retrieves a 24-bit color value in RGB888, hexadecimal format (0xRRGGBB).
    /// @return A 24-bit unsigned integer representing an RGB color in the 888 format.
    uint32_t uintRGB888();

    /// @brief Retrieves a 16-bit color value in RGB565, binary format (0bRRRRRGGGGGGBBBBB).
    /// @return A 16-bit unsigned integer representing an RGB color in the 565 format.
    uint16_t uintRGB565();

    /// @brief Generates a string representation of the RGB color in the format 0xFFFFFF.
    /// @return A String containing the hexadecimal representation of the RGB color.
    String strRGB888();

    /// @brief Generates a string representation of the RGB color in the format 0xFFFF.
    /// @return A String containing the hexadecimal representation of the RGB color.
    String strRGB565();

    /// @brief Compares the similarity of this RGB888 color to a provided RGB888 color.
    /// @param color Another RGB888 color object to compare to.
    /// @return A float value indicating the similarity between the colors, where 0 means not similar and 1 means identical.
    float compare(RGB888 color);

    /// @brief Finds the RGB888 color in the given list that is closest to the current RGB888 color.
    /// @param list An array of RGB888 colors to search for the closest match.
    /// @param size The size of the list, indicating the number of elements.
    /// @return The RGB888 color in the list that is closest in similarity to the current RGB888 color.
    RGB888 getClosest(RGB888 list[], size_t size);

  private:
    uint8_t _red;    // The red component of the RGB color (0-255).
    uint8_t _green;  // The green component of the RGB color (0-255).
    uint8_t _blue;   // The blue component of the RGB color (0-255).
    String _name;    // The name of the color.
};

/// @class RGB565
/// @brief Represents an RGB color in the 565 format (5 bits for red, 6 bits for green, and 5 bits for blue).
class RGB565{
  public:
    /// @brief Default constructor for RGB565 color.
    RGB565();

    /// @brief Constructor for RGB565 color using an RGB565 format (0xFFFF).
    /// @param rgb565 A 16-bit unsigned integer representing the color in RGB565 format.
    /// @param name (Optional) A string containing the name of the color.
    RGB565(uint16_t rgb565, String name = ""); 

    /// @brief Constructor for RGB565 color using individual 8-bit components for each color channel.
    /// @param red An 5-bit unsigned integer representing the red component (0-31).
    /// @param green An 6-bit unsigned integer representing the green component (0-63).
    /// @param blue An 5-bit unsigned integer representing the blue component (0-31).
    /// @param name (Optional) A string containing the name of the color.
    RGB565(uint8_t red, uint8_t green, uint8_t blue, String name = ""); 

    /// @brief Gets the red component of the RGB color.
    /// @return An 5-bit unsigned integer representing the red component (0-31).
    uint8_t red();

    /// @brief Gets the green component of the RGB color.
    /// @return An 6-bit unsigned integer representing the green component (0-63).
    uint8_t green();

    /// @brief Gets the blue component of the RGB color.
    /// @return An 5-bit unsigned integer representing the blue component (0-31).
    uint8_t blue();

    /// @brief Returns the name of the color.
    /// @return A String containing the name of the color.
    String name();

    /// @brief Retrieves a 16-bit color value in RGB565, binary format (0bRRRRRGGGGGGBBBBB).
    /// @return A 16-bit unsigned integer representing an RGB color in the 565 format.
    uint16_t uintRGB565();

    /// @brief Retrieves a 24-bit color value in RGB888, hexadecimal format (0xRRGGBB).
    /// @return A 24-bit unsigned integer representing an RGB color in the 888 format.
    uint32_t uintRGB888();

    /// @brief Generates a string representation of the RGB color in the format 0xFFFF.
    /// @return A String containing the hexadecimal representation of the RGB color.
    String strRGB565();

    /// @brief Generates a string representation of the RGB color in the format 0xFFFFFF.
    /// @return A String containing the hexadecimal representation of the RGB color.
    String strRGB888();

    /// @brief Compares the similarity of this RGB565 color to a provided RGB565 color.
    /// @param color Another RGB565 color object to compare to.
    /// @return A float value indicating the similarity between the colors, where 0 means not similar and 1 means identical.
    float compare(RGB565 color);

    /// @brief Finds the RGB565 color in the given list that is closest to the current RGB565 color.
    /// @param list An array of RGB565 colors to search for the closest match.
    /// @param size The size of the list, indicating the number of elements.
    /// @return The RGB565 color in the list that is closest in similarity to the current RGB565 color.
    RGB565 getClosest(RGB565 list[], size_t size);

  private:
    uint16_t _rgb565; // 16-bit color value in RGB565, binary format (0bRRRRRGGGGGGBBBBB).
    String _name; // The name of the color.
};

/// @brief Converts an RGB565 color to the RGB888 format.
/// @param color An RGB565 color to be converted.
/// @return An RGB888 color representing the converted result.
RGB888 toRGB888(RGB565 color);

/// @brief Converts an RGB888 color to the RGB565 format.
/// @param color An RGB888 color to be converted.
/// @return An RGB565 color representing the converted result.
RGB565 toRGB565(RGB888 color);

/// @brief Retrieves an RGB888 color from a list by its name.
/// @param name The name of the color to retrieve.
/// @param list An array of RGB888 colors to search within.
/// @param size The size of the list, indicating the number of elements.
/// @return The RGB888 color corresponding to the provided name, or a default color if not found.
RGB888 getColorRGB888(String name, RGB888 list[], size_t size);

// @brief Retrieves an RGB565 color from a list by its name.
/// @param name The name of the color to retrieve.
/// @param list An array of RGB565 colors to search within.
/// @param size The size of the list, indicating the number of elements.
/// @return The RGB565 color corresponding to the provided name, or a default color if not found.
RGB565 getColorRGB565(String name, RGB565 list[], size_t size);


#endif