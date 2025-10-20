#include <WiFi.h>

// dapat diganti dengan SSID dan password jaringan anda
const char *ssid = "Wokwi-GUEST";
const char *password = "";
unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Menghubungkan ke jaringan ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(115200);
    initWiFi();
    Serial.print("RSSI:");
    Serial.println(WiFi.RSSI());
}

void loop()
{
    unsigned long currentMillis = millis();
    // Menghubungkan kembali ke jaringan wifi apabila wifi down
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval))
    {
        Serial.print(millis());
        Serial.println("Menghubungkan kembali ke jaringan...");
        WiFi.disconnect();
        WiFi.reconnect();
        previousMillis = currentMillis;
    }
}
