#include <Arduino.h>
#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN 14

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 displayTemp(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 displayHum(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHTesp dhtSensor;

void setup()
{
    Serial.begin(115200);
    dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

    if (!displayTemp.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("Gagal memulai OLED suhu!"));
        for (;;)
            ;
    }
    if (!displayHum.begin(SSD1306_SWITCHCAPVCC, 0x3D))
    {
        Serial.println(F("Gagal memulai OLED kelembapan!"));
        for (;;)
            ;
    }

    displayTemp.clearDisplay();
    displayTemp.setTextSize(1);
    displayTemp.setTextColor(SSD1306_WHITE);
    displayTemp.setCursor(15, 25);
    displayTemp.println("OLED Suhu Siap!");
    displayTemp.display();

    displayHum.clearDisplay();
    displayHum.setTextSize(1);
    displayHum.setTextColor(SSD1306_WHITE);
    displayHum.setCursor(5, 25);
    displayHum.println("OLED Kelembapan Siap!");
    displayHum.display();

    delay(2000);
}

void loop()
{
    delay(2000);
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

    displayTemp.clearDisplay();
    displayTemp.setTextColor(SSD1306_WHITE);
    if (temp > 30)
    {
        displayTemp.setTextSize(1.5);
        displayTemp.setCursor(0, 25);
        displayTemp.println("SUHU TINGGI!");
    }
    else
    {
        displayTemp.setTextSize(2);
        displayTemp.setCursor(10, 10);
        displayTemp.print(temp, 1);
        displayTemp.println(" C");
    }
    displayTemp.display();

    displayHum.clearDisplay();
    displayHum.setTextColor(SSD1306_WHITE);
    if (hum < 20)
    {
        displayHum.setTextSize(1.5);
        displayHum.setCursor(0, 25);
        displayHum.println("KELEMBAPAN RENDAH!");
    }
    else
    {
        displayHum.setTextSize(2);
        displayHum.setCursor(10, 10);
        displayHum.print(hum, 1);
        displayHum.println(" %");
    }
    displayHum.display();
}
