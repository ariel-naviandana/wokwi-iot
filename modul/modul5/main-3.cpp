#include <Arduino.h>
#include <ESP32Servo.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 13

long duration;
float distance;

Servo myservo;

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    myservo.attach(SERVO_PIN);

    Serial.println("Mulai gabungan HC-SR04 + Servo...");
}

void loop()
{
    // Trigger sensor HC-SR04
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Baca lama pantulan echo HIGH
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.0343) / 2;

    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Logika servo
    if (distance <= 30)
    {
        Serial.println("Servo ke 90°");
        myservo.write(90);
    }
    else
    {
        Serial.println("Servo ke 180°");
        myservo.write(180);
    }

    delay(500);
}
