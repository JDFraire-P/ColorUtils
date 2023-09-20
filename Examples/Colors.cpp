#include <JDFraire_ColorsUtils.h>

// Definimos algunos colores RGB888
rgb888_t red888 = {255, 0, 0, "Red"};
rgb888_t green888 = {0, 255, 0, "Green"};
rgb888_t blue888 = {0, 0, 255, "Blue"};

// Definimos algunos colores RGB565
rgb565_t yellow565 = {31, 63, 0, "Yellow"};
rgb565_t purple565 = {31, 0, 31, "Purple"};

void setup() {
  Serial.begin(9600);
  
  // Convertir RGB888 a RGB565 y viceversa
  rgb565_t convertedColor565 = rgb888_to_rgb565(red888);
  rgb888_t convertedColor888 = rgb565_to_rgb888(yellow565);

  Serial.println("RGB888 to RGB565 Conversion:");
  Serial.print("Red (RGB888): ");
  printColor(red888);
  Serial.print("Converted to RGB565: ");
  printColor(convertedColor565);

  Serial.println("RGB565 to RGB888 Conversion:");
  Serial.print("Yellow (RGB565): ");
  printColor(yellow565);
  Serial.print("Converted to RGB888: ");
  printColor(convertedColor888);

  // Comparar colores
  float similarity = color_similarity(red888, green888);
  Serial.println("Similarity between Red and Green (RGB888): " + String(similarity));

  similarity = color_similarity(yellow565, purple565);
  Serial.println("Similarity between Yellow and Purple (RGB565): " + String(similarity));

  // Obtener colores por nombre
  rgb888_t colorByName = get_color_by_name("Blue", COLORS);
  Serial.print("Color by Name (Blue): ");
  printColor(colorByName);

  // Obtener colores similares de la lista de colores predefinidos
  rgb888_t similarColor888 = get_similar_color888(blue888, COLORS);
  Serial.print("Most Similar Color to Blue (RGB888): ");
  printColor(similarColor888);

  rgb565_t similarColor565 = get_similar_color565(purple565, COLORS);
  Serial.print("Most Similar Color to Purple (RGB565): ");
  printColor(similarColor565);
}

void loop() {
  // Nada en el loop
}

void printColor(rgb888_t color) {
  Serial.print("Name: " + String(color.name));
  Serial.print(", Red: " + String(color.red));
  Serial.print(", Green: " + String(color.green));
  Serial.println(", Blue: " + String(color.blue));
}
