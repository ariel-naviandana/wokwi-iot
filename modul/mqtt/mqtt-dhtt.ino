#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>

// Konfigurasi WiFi
const char *ssid = "Redmi AR";
const char *password = "chelsea13";

// Konfigurasi MQTT Broker
const char *mqtt_server = "192.168.131.212";
const int mqtt_port = 1883;
const char *mqtt_user = "admin";
const char *mqtt_pass = "admin";

// Topik MQTT
const char *topic_temperature = "esp32/dht11/temperature";
const char *topic_humidity = "esp32/dht11/humidity";
const char *topic_status = "esp32/dht11/status";

// Konfigurasi DHT
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long previousMillis = 0;
const long interval = 5000; // Interval pengiriman data (5 detik)

void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Menghubungkan ke ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi terhubung");
    Serial.println("Alamat IP: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Pesan diterima [");
    Serial.print(topic);
    Serial.print("]: ");

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect()
{
    // Loop sampai terhubung kembali
    while (!client.connected())
    {
        Serial.print("Menghubungkan ke MQTT Broker...");

        // Client ID unik
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        // Attempt to connect
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
        {
            Serial.println("terhubung");

            // Once connected, publish an announcement...
            client.publish(topic_status, "ESP32 DHT11 connected");
        }
        else
        {
            Serial.print("gagal, rc=");
            Serial.print(client.state());
            Serial.println(" coba lagi dalam 5 detik");
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    dht.begin();

    setup_wifi();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    Serial.println("DHT11 Sensor dengan MQTT pada ESP32");
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;

        // Baca data dari sensor DHT
        float kelembapan = dht.readHumidity();
        float suhu = dht.readTemperature();

        if (isnan(kelembapan) || isnan(suhu))
        {
            Serial.println("Gagal membaca dari sensor DHT!");
            client.publish(topic_status, "Error reading DHT sensor");
            return;
        }

        // Tampilkan di Serial Monitor
        Serial.print("Suhu: ");
        Serial.print(suhu);
        Serial.print(" °C || Kelembapan: ");
        Serial.print(kelembapan);
        Serial.println(" %");

        // Konversi float ke string
        char tempString[8];
        char humString[8];

        dtostrf(suhu, 4, 2, tempString);
        dtostrf(kelembapan, 4, 2, humString);

        // Kirim data ke MQTT Broker
        client.publish(topic_temperature, tempString);
        client.publish(topic_humidity, humString);

        Serial.println("Data terkirim ke MQTT Broker");

        // Kirim data dalam format JSON (opsional)
        String jsonPayload = "{\"temperature\":" + String(suhu, 2) +
                             ",\"humidity\":" + String(kelembapan, 2) + "}";
        client.publish("esp32/dht11/data", jsonPayload.c_str());
    }
}