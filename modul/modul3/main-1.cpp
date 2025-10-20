#include <Arduino.h>

const int potPin = 34;
const int ledPin = 17;

const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 12;

void setup()
{
    Serial.begin(115200);
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(ledPin, pwmChannel);
}

void loop()
{
    int potValue = analogRead(potPin);
    ledcWrite(pwmChannel, potValue);

    Serial.print("ADC=");
    Serial.print(potValue);
    Serial.print(" PWM=");
    Serial.println(potValue);
}