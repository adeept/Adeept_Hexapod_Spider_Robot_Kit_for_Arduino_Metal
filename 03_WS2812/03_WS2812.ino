/***********************************************************
Function: Ws2812 LED
Website: www.adeept.com
***********************************************************/
#include <Adafruit_NeoPixel.h>

#define LED_PIN    A3         // WS2812 connect to pin A3 .
#define NUM_LEDS   5         // LED number.
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


const int base_colors[][3] = {
    {0, 255, 255},  
    {255, 0, 0},    
    {0, 255, 0},    
    {0, 0, 255},    
    {255, 255, 0},  
    {255, 0, 255},  
    {0, 128, 255}
};


void generate_color_sequences(int color_sequences[][NUM_LEDS][3]) {
    for (int i = 0; i < sizeof(base_colors) / sizeof(base_colors[0]); i++) {
        for (int j = 0; j < NUM_LEDS; j++) {
            int index = (j + i) % (sizeof(base_colors) / sizeof(base_colors[0]));
            color_sequences[i][j][0] = base_colors[index][0];
            color_sequences[i][j][1] = base_colors[index][1];
            color_sequences[i][j][2] = base_colors[index][2];
        }
    }
}

void setup() {
  pixels.begin();         // Initialize the NeoPixel library.
  pixels.setBrightness(5); // Set WS2812 LED brightness.
}

void loop() {
  int color_sequences[sizeof(base_colors) / sizeof(base_colors[0])][NUM_LEDS][3];
  generate_color_sequences(color_sequences);

  for (int s = 0; s < sizeof(base_colors) / sizeof(base_colors[0]); s++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      pixels.setPixelColor(i, pixels.Color(color_sequences[s][i][0], color_sequences[s][i][1], color_sequences[s][i][2]));
    }
    pixels.show();
    delay(300); 
  }
}


void WS2812Color(int num, int R, int G, int B){
  pixels.setPixelColor(num,pixels.Color(R,G,B));
  pixels.show();    
}

void WS2812ColorAll(int R, int G, int B){
    for(int i=0; i<=NUM_LEDS; i++){
      pixels.setPixelColor(i,pixels.Color(R,G,B));
  }
  pixels.show();  
}