#include <Arduino.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

long duration;
float distance;

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.println("Mulai Pembacaan Jarak HC-SR04...");
}

void loop()
{
    // Kirim pulsa trigger 10 μs
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // Baca lama pantulan echo HIGH
    duration = pulseIn(ECHO_PIN, HIGH);
    // Hitung jarak (cm)
    distance = (duration * 0.0343) / 2;
    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
}
