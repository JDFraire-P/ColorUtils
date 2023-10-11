# ColorsUtils Library

![Arduino](https://img.shields.io/badge/Arduino-Compatible-brightgreen.svg)

## Description

The ColorsUtils library is a utility library for Arduino that provides functions for working with RGB colors in both RGB888 and RGB565 formats. It allows you to convert between these formats, compare colors for similarity, and find the closest matching color from a list. This can be useful in various projects where you need to work with colors, such as LED control, display applications, and more.

## Features

- Conversion between RGB888 and RGB565 color formats.
- Color comparison to measure similarity between two colors.
- Finding the closest matching color from a list.
- Support for common web colors.

## Installation

To use the ColorsUtils library in your Arduino project, follow these steps:

1. Download the library ZIP file from the [GitHub repository](https://github.com/JDFraire-P/ColorsUtils).
2. Open the Arduino IDE.
3. Go to "Sketch" -> "Include Library" -> "Add .ZIP Library...".
4. Select the downloaded ZIP file.
5. The library is now installed and ready for use in your project.

## Usage

### Creating RGB Colors

You can create RGB colors in both RGB888 and RGB565 formats using the `RGB888` and `RGB565` classes. Here's how to create them:

```cpp
RGB888 redColor888(255, 0, 0); // Create an RGB888 color (Red)
RGB888 blueColor888(0x0000FF);  // Create an RGB888 color (blue)
RGB565 redColor565(0xF800);    // Create an RGB565 color (Red)
RGB565 blueColor565(0, 0, 31);  // Create an RGB565 color (blue)
```

# Color Conversion

You can convert between RGB888 and RGB565 formats using the `toRGB888` and `toRGB565` functions:

```cpp
RGB888 convertedColor = toRGB888(redColor565); // Convert RGB565 to RGB888
RGB565 convertedColor = toRGB565(blueColor888); // Convert RGB888 to RGB565
```

## Color Comparison

You can measure the similarity between two RGB colors using the `compare` function, which returns a similarity value between 0 (not similar) and 1 (identical):

```cpp
float similarity = redColor888.compare(blueColor888); // Compare two RGB888 colors
```

## Web Colors

The library includes a predefined list of 50 common web colors, which you can find in the `WebColors.h` file.

## Finding Closest Color

You can find the closest matching color to a target color from a list of colors using the `getClosest` function:

```cpp
RGB888 closestColor = targetColor.getClosest(colorList, listSize); // Find the closest color
```

## Examples

For detailed usage examples and more information, refer to the [Examples](Examples/) directory in this repository.

## License

This library is open-source software licensed under the [MIT License](LICENSE.md).

## Credits

- Created by [Your Name](https://github.com/yourusername)
- Inspired by Arduino and the open-source community.

If you find this library useful, consider giving it a star on [GitHub](https://github.com/yourrepository/ColorsUtils) and contributing to its development.

For bug reports, feature requests, and contributions, please use the [GitHub Issues](https://github.com/yourrepository/ColorsUtils/issues) page.

Happy coding!