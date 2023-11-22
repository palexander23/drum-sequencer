#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  tone(0, 880);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  noTone(0);
  delay(150);
}
