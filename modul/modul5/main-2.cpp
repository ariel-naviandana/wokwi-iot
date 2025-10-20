#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;

void setup()
{
    Serial.begin(115200);
    myservo.attach(13);
    Serial.println("Uji Servo SG90 pada ESP32...");
}

void loop()
{
    Serial.println("Servo ke 0°");
    myservo.write(0);
    delay(1000);
    Serial.println("Servo ke 90°");
    myservo.write(90);
    delay(1000);

    Serial.println("Servo ke 180°");
    myservo.write(180);
    delay(1000);
}
