#include <Arduino.h>
#include <ColorsUtils.h>
#include <WebColors.h>

void setup() {
    Serial.begin(9600);

    // Create RGB888 color for comparison
    RGB888 targetColor(255, 165, 0); // Orange color (no name)
    Serial.print("\n targetColor Hex code: " + targetColor.strRGB888());
    Serial.println(" (" +  String(targetColor.red()) + ", " + String(targetColor.green()) + ", " + String(targetColor.blue()) + ")");

    // Create RGB565 color for conversion
    RGB565 conversionColor(0xf800, "Red"); // Red color
    Serial.print("\n conversionColor Hex code: " + conversionColor.strRGB565());
    Serial.println(" (" +  String(conversionColor.red()) + ", " + String(conversionColor.green()) + ", " + String(conversionColor.blue()) + ")");

    // Convert RGB565 to RGB888 for comparison
    RGB888 comparisonColor = toRGB888(conversionColor);
    Serial.print("\n comparisonColor Hex code: " + comparisonColor.strRGB888());
    Serial.println(" (" +  String(comparisonColor.red()) + ", " + String(comparisonColor.green()) + ", " + String(comparisonColor.blue()) + ")");

    // Compare two RGB888 colors
    float similarity = targetColor.compare(comparisonColor);
    Serial.print("\n Similarity between Red and targetColor: ");
    Serial.println(similarity);

    // Search for the closest color to a target color in the WebColors array
    RGB888 closestColor = targetColor.getClosest(WebColors, WebColorsSize);
    Serial.println("\n Closest color to targetColor in WebColors: " + closestColor.name() + " (" + closestColor.strRGB888() + ")");
    similarity = closestColor.compare(targetColor);
    Serial.print(" Similarity between closestColor and targetColor: ");
    Serial.println(similarity);

    // Get color by name from List
    RGB888 crimsonColor = getColorRGB888("Crimson", WebColors, WebColorsSize);
    Serial.print("\n crimsonColor: " + crimsonColor.strRGB888());
    Serial.print(" (" +  String(crimsonColor.red()) + ", " + String(crimsonColor.green()) + ", " + String(crimsonColor.blue()) + ") ");
    Serial.print(crimsonColor.name() + " = ");
    Serial.println(crimsonColor.uintRGB888());
}

void loop() {
    // main loop
}
