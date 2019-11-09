#include <HixPinPWM25KHz.h>
#include <HixPinPWM.h>


HixPinPWM      g_pwm(3);
HixPinPWM25KHz g_pwm25k(9);

//declare reset function at address 0
void (*reset)(void) = 0;

void setup() {
  // Serial Monitor @ 9600 baud
  Serial.begin(19200);
  Serial.print(F("Startup..."));
  // setup PWM
  if (!g_pwm.begin() ) {
    Serial.print(F("Error initilizing PWM"));
    delay(2000);
    reset();
  }
  g_pwm.analogWritePercent(50);
  // setup 2nd 25KHz PWM
  if (!g_pwm25k.begin() ) {
    Serial.print(F("Error initilizing PWM 25Khz"));
    delay(2000);
    reset();
  }
  g_pwm25k.analogWritePercent(50);
}

void loop() {
  for (int nPercent = 1; nPercent < 100; nPercent++) {
    g_pwm.analogWritePercent(nPercent);
    g_pwm25k.analogWritePercent(nPercent);
    delay(25);
  }
}