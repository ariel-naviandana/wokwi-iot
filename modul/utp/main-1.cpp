#include <Arduino.h>
#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 23
#define DHT_PIN 14

long duration;
float distance;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 displayDist(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHTesp dhtSensor;

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Mulai Pembacaan Jarak HC-SR04...");

    dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

    if (!displayDist.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("Gagal memulai OLED suhu!"));
        for (;;)
            ;
    }
    else
    {
        Serial.println(F("OLED suhu dimulai!"));
    }

    displayDist.clearDisplay();
    displayDist.setTextSize(1);
    displayDist.setTextColor(SSD1306_WHITE);
    displayDist.setCursor(15, 25);
    displayDist.println("OLED Suhu Siap!");
    displayDist.display();

    delay(2000);
}

void loop()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.0343) / 2;
    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");

    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temp = data.temperature;
    float hum = data.humidity;

    if (isnan(temp) || isnan(hum))
    {
        Serial.println("Gagal membaca sensor!");
        return;
    }

    Serial.print("Suhu: ");
    Serial.print(temp);
    Serial.print("°C  |  Kelembapan: ");
    Serial.print(hum);
    Serial.println("%");

    displayDist.clearDisplay();
    displayDist.setTextColor(SSD1306_WHITE);

    if (distance < 30)
    {
        Serial.println(distance);
        displayDist.setTextSize(1.5);
        displayDist.setCursor(0, 25);
        displayDist.println("AWAS!!!");
    }
    else
    {
        Serial.println(distance);
        displayDist.setTextSize(2);
        displayDist.setCursor(10, 10);
        displayDist.print(distance, 1);
        displayDist.println(" cm");
        displayDist.print(temp, 1);
        displayDist.println(" °C");
    }
    displayDist.display();

    if (temp > 50)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    delay(500);
}
