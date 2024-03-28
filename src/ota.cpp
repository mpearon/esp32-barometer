#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <config.h>
#include <ota.h>

void initializeMdns(){
	Serial.println( "[mDNS] Initialize" );
	if (!MDNS.begin( mDnsHostname.c_str() )) {
        Serial.println( "     [mDNS] ERROR: Error setting up mDNS responder" );
        while(1) {
            delay(1000);
        }
    }
	else{
		Serial.println( "     [mDNS] SUCCESS: Initialized mDNS" );
	}
}
ArduinoOTAClass initializeOta(){
	Serial.println( "[OTA] Initialize" );
	ArduinoOTA
    .onStart([]() {
      	String type;
      	if (ArduinoOTA.getCommand() == U_FLASH)
        	type = "sketch";
      	else // U_SPIFFS
        	type = "filesystem";

      	// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      	Serial.println("     [OTA] Start update " + type);
    })
    .onEnd([]() {
		Serial.println("     [OTA] End update");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      	Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
		String printString = ( String("     [OTA] Progress: ") + (progress / (total / 100)) + String("%"));
    })
	.onError([](ota_error_t error) {
		Serial.printf("     [OTA] ERROR: Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

	Serial.println( "     [OTA] SUCCESS: Initialized OTA" );
	return ArduinoOTA;
}