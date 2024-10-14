#include <Adafruit_NeoPixel.h>
#define pin_neo 8
#define numero_pixeles 8
Adafruit_NeoPixel tira = Adafruit_NeoPixel(numero_pixeles, pin_neo, NEO_GRB + NEO_KHZ800);

void setup() {
  tira.begin();
}

void loop() {
  tira.fill(tira.Color(0, 255, 0), 0, 8);
  tira.show();
}
