#include <Arduino.h>
#include <Wire.h>


#include "TLC59108.h"

#define I2C_ADDR TLC59108::I2C_ADDR::BASE
#ifndef CONFIG_SDA
#define CONFIG_SDA GPIO_NUM_47
#endif
#ifndef CONFIG_SCL
#define CONFIG_SCL GPIO_NUM_48
#endif

TLC59108 leds(&Wire, I2C_ADDR);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(CONFIG_SDA, CONFIG_SCL, 4000);
  leds.init();
  leds.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
}

void sweep() {
  byte pwm;

  for (pwm = 0; pwm < 0xff; pwm++) {
    leds.setAllBrightness(pwm);
    delay(10);
  }

  for (pwm = 0xfe; pwm < 0xff; pwm--) {
    leds.setAllBrightness(pwm);
    delay(10);
  }

  for (byte channel = 0; channel < 8; channel++)
    for (pwm = 0; pwm < 0xff; pwm++) {
      leds.setBrightness(channel, pwm);
      delay(10);
    }

  for (byte channel = 0; channel < 8; channel++)
    for (pwm = 0xfe; pwm < 0xff; pwm--) {
      leds.setBrightness(channel, pwm);
      delay(10);
    }
}

void loop() { sweep(); }
