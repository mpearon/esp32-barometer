#include <config.h>
#include <metar.h>
#include <wifi.h>
#include <vector>
#include <motor.h>

void setup(){
	Serial.flush();
	Serial.begin(9600);
	initWifi();

	calibrateStepper();
}
void loop(){
	Serial.println("Looping\n");
	delay(10000);
	std::string metarString = getMetarString( icaoId );
	Serial.println( metarString.c_str() );
	Serial.println("Matching\n");
	std::vector<double> metarSet = parseMetar( metarString );
	Serial.printf( "Altimeter: %f\nTemperatureC: %f\nTemperatureF: %f\nDewpointC: %f\nHumidity: %f\n", metarSet[0], metarSet[1], metarSet[2], metarSet[3], metarSet[4] ); 
}
