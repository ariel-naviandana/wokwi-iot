#include <Arduino.h>

#define MQ2_PIN 34
#define LED_PIN 23
#define BUZZER_PIN 22

void setup()
{
    Serial.begin(115200);
    pinMode(MQ2_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    int gasValue = analogRead(MQ2_PIN);
    Serial.print("Nilai Gas (analog): ");
    Serial.println(gasValue);

    // Ambang batas bisa kamu ubah sesuai kebutuhan
    if (gasValue > 2000)
    {
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }

    delay(500);
}
