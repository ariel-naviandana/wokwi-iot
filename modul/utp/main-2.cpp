#include <Arduino.h>

#define MQ2_PIN 34

void setup()
{
    Serial.begin(115200);
    pinMode(MQ2_PIN, INPUT);
}

void loop()
{
    int gasValue = analogRead(MQ2_PIN);
    Serial.print("Nilai Gas (analog): ");
    Serial.println(gasValue);

    delay(500);
}
