#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS   300
CRGB leds[NUM_LEDS];

void setup() {
  // Initialize LED lib
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  for (int i = 0; i < 50; ++i) {
    MovingXMasStripe();
  }
  delay(1000 * 60 * 5);
  for (int i = 0; i < 1000; ++i) {
    RandomBlink();
  }
  delay(1000 * 60 * 1);
  for (int i = 0; i < 50; ++i) {
    FlyComet();
  }
}

void ResetStripe() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void FlyComet() {
  for (int i = 0; i < 200; ++i) {
    DisplayComet(i);
    delay(10);
  }
}

void DisplayComet(int start_pos_0) {
  int r_len = 5;
  int interval = 195;
  int w_len = 0;
  int block_len = r_len + interval + w_len;

  int start_pos = start_pos_0;
  int j = 0;

  // Forward
  while (j < NUM_LEDS) {
    for (j = start_pos; j < NUM_LEDS && (j - start_pos) < block_len; ++ j) {
      int pos = j - start_pos;
      if (pos == r_len - 1) {
        leds[j] = CRGB(150, 150, 150);
      } else if (pos < r_len - 1) {
        leds[j] = CRGB(10 + pos * 20, 5 + pos * 15, 0);
      } else {
        leds[j] = CRGB(0, 0, 0);
      }
    }
    start_pos += block_len;
  }
  // Backward
  start_pos = start_pos_0 - 1;
  while (j >= 0) {
    for (j = start_pos; j >= 0 && (start_pos - j) < block_len; --j) {
      int pos = start_pos - j;
      if ( pos < (block_len - r_len)) {
        leds[j] = CRGB(0, 0, 0);
      } else if (pos == block_len - r_len) {
        leds[j] = CRGB(150, 150, 150);
      } else {
        leds[j] = CRGB(90 - (pos - block_len + r_len) * 20, 70 - (pos - block_len + r_len) * 15, 0 );
        //          leds[j] = CRGB(255, 0, 0);
      }
    }
    start_pos -= block_len;
  }
  FastLED.show();
}

void MovingXMasStripe() {
  for (int i = 0; i < 28; i++) {
    XmasStripe(i);
    delay(50);
  }
}

void XmasStripe(int start_pos_0) {
  int r_len = 20;
  int g_len = 3;
  int w_len = 2;

  int block_len = r_len + g_len + w_len + g_len;
  int start_pos = start_pos_0;
  int j = 0;
  // Forward redering to NUM_LEDS
  while (j < NUM_LEDS) {
    // |46 R| 3 G | 2 W | 3G | 46 R |
    for (j = start_pos; j < NUM_LEDS && (j - start_pos) < block_len; ++j) {
      int pos = j - start_pos;
      if (pos < r_len) {
        leds[j] = CRGB(150,   0,   0);
      }
      else if (pos >= r_len && pos < r_len + g_len) {
        leds[j] = CRGB(  0, 150,   0);
      }
      else if (pos >= r_len + g_len && pos < r_len + g_len + w_len) {
        leds[j] = CRGB(150, 150, 150);
      }
      else {
        leds[j] = CRGB(  0, 150,   0);
      }
    }
    start_pos += block_len;
  }
  // Backward rendering to 0
  start_pos = start_pos_0 - 1;
  while (j >= 0) {
    for (j = start_pos; j >= 0 && (start_pos - j) < block_len; --j) {
      int pos = start_pos - j;
      if (pos < g_len) {
        leds[j] = CRGB(0, 255, 0);
      }
      else if (pos >= g_len && pos < g_len + w_len) {
        leds[j] = CRGB(255, 255, 255);
      }
      else if (pos >= g_len + w_len && pos < g_len + w_len + g_len) {
        leds[j] = CRGB(0, 255, 0);
      }
      else {
        leds[j] = CRGB(255, 0, 0);
      }
    }
    start_pos -= block_len;
  }
  FastLED.show();
}

void RandomBlink() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    int red   = random(50);
    int green = random(50);
    int blue  = random(50);
    leds[i] = CRGB(red, green, blue);
  }
  FastLED.show();
  delay(30);
}
