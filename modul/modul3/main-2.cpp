#include <Arduino.h>
#include <DHTesp.h>

#define pinDHT 14
#define pinLED1 26
#define pinLED2 27

DHTesp dhtSensor;

void setup()
{
    Serial.begin(115200);
    dhtSensor.setup(pinDHT, DHTesp::DHT22);

    pinMode(pinLED1, OUTPUT);
    pinMode(pinLED2, OUTPUT);
}

void loop()
{
    delay(2000);

    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temp = data.temperature;
    float hum = data.humidity;

    if (isnan(hum) || isnan(temp))
    {
        Serial.println(F("Pembacaan sensor DHT tidak berhasil!"));
        return;
    }

    Serial.print("Kelembaban: ");
    Serial.print(hum);
    Serial.print("% \tSuhu: ");
    Serial.print(temp);
    Serial.println("°C");

    if (temp > 25)
    {
        digitalWrite(pinLED1, HIGH);
    }
    else
    {
        digitalWrite(pinLED1, LOW);
    }

    if (hum > 50)
    {
        digitalWrite(pinLED2, HIGH);
    }
    else
    {
        digitalWrite(pinLED2, LOW);
    }
}
