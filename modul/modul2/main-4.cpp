// Memasukan library WiFi
#include "WiFi.h"

// Memasukan ssid dan password const
char *ssid = "Wokwi-GUEST";
const char *password = "";

// Memasukan alamat IP, gateway, subnet mask serta DNS
IPAddress local_IP(10, 10, 0, 5);
IPAddress gateway(10, 10, 0, 1);
IPAddress subnet(255, 255, 255, 252);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(4, 4, 4, 4);

void setup()
{
    Serial.begin(115200);
    // Proses menghubungkan ke jaringan
    // Memasukan alamat IP, gateway, subnet mask dan DNS sebagai argument
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    {
        Serial.println("Station gagal terhubung");
    }

    Serial.print("Menghubungkan ke ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    // Menampilkan alamat IP, gateway dan DNS pada serial monitor
    Serial.println("\nWiFi terhubung");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("IP Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.println("IP DNS: ");
    Serial.print(WiFi.dnsIP());
}

void loop()
{
    // put your main code here, to run repeatedly:
    delay(10); // this speeds up the simulation
}
