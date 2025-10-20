#include "WiFi.h"
const char *ssid = "Wokwi-GUEST";
const char *password = "";

void initWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Menghubungkan ke jaringan wifi ...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nTerhubung ke jaringan");
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
    delay(10);
}
