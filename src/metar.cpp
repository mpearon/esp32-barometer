#include <HTTPClient.h>
#include <regex>
#include <vector>

std::string getMetarString( std::string icaoId ){
  	HTTPClient http;
	Serial.println("[HTTP] GET...]");
	std::string urlBase = ("https://aviationweather.gov/api/data/metar?format=raw&taf=false&ids=");
	std::string url = urlBase + icaoId;
	http.begin(url.c_str());
	int httpCode = http.GET();
	if(httpCode > 0){
		Serial.printf("[HTTP] GET... code: %d\n", httpCode);
		if(httpCode == HTTP_CODE_OK) {
			std::string payload = (http.getString()).c_str();
			return (payload);
		}
		else{
			return ( "M1/M51 A2601" );
		}
	}
	else{
		return ( "M1/M51 A2601" );
	}
	http.end();
}

std::vector<double> parseMetar( std::string metarString ){
	std::vector<double> metarSet = { 0, 0, 0, 0, 0 };

	std::regex metarRegex( "(M?)(\\d{2})/((M?)(\\d{2}))\\sA(\\d{4})" );
	std::smatch matchStrings;
	std::regex_search(metarString, matchStrings, metarRegex);

	metarSet[0] = ( std::stod( matchStrings[6].str() ) / 100 );	// Altimeter
	metarSet[1] = ( std::stod( matchStrings[2].str() ) ); 		// TemperatureC
	if( matchStrings[1].str() == "M" ){
		metarSet[1] = -(metarSet[1]); // Convert TemperatureC to negative
	}
	metarSet[2] = ( ( metarSet[1] * 1.8 ) + 32 ); 				// TemperatureF
	metarSet[3] = ( std::stod( matchStrings[5].str() ) ); 		// DewpointC
	if( matchStrings[4].str() == "M" ){
		metarSet[3] = -(metarSet[3]); // DewpointC to negative
	}

	metarSet[4] = (100.0 * exp((17.625 * metarSet[3]) / (243.04 + metarSet[3])) / exp((17.625 * metarSet[1]) / (243.04 + metarSet[1]))); // Relative Humidity

	return metarSet;
}