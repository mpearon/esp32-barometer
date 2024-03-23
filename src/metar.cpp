#include <HTTPClient.h>
#include <ArduinoJson.h>
JsonDocument json;
String getMetarJson(){
  	HTTPClient http;
	Serial.println("[HTTP] GET...]");
	http.begin("https://aviationweather.gov/api/data/metar?ids=KMKC&format=json&taf=false");
	int httpCode = http.GET();
	// httpCode will be negative on error
	if(httpCode > 0){
		// HTTP header has been send and Server response header has been handled
		Serial.printf("[HTTP] GET... code: %d\n", httpCode);
		// file found at server
		if(httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			return (payload);
		}
	}
	else{
		Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}
	http.end();
}
JsonObject getDeserializedMetar(String metarString){
	deserializeJson(json, metarString);
	JsonObject metar = json[0];
	return metar;
}