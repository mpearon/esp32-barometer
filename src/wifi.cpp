#include <Arduino.h>
#include <WiFi.h>
#include <secrets.h>
void initWifi(){
	String hostname = "sensESP-barometer";
	WiFi.setHostname(hostname.c_str());
	Serial.print("Connecting to WiFi");
	WiFi.begin( wlanSsid, wlanPass );
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(5000);
	}
	Serial.print("Connected to WiFi: ");
	Serial.println(WiFi.localIP());
	Serial.println();
}