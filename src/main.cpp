#include <config.h>
#include <metar.h>
#include <wifi.h>
#include <vector>
#include <motor.h>
#include <storage.h>
#include <ota.h>
#include <stepperMotor.h>

void setup(){
	Serial.flush();
	Serial.begin(9600);
	initWifi();
	initializeMdns();
	initializeOta();
	currentBaroStepperPosition = getStoredValue( "barometer", "lastPosition" );
	Serial.printf( "[STEPPER] Current position from storage: %d\n", currentBaroStepperPosition);
	//calibrateStepper();
	//baroStepper.calibrate();
	baroStepper.setSpeed( 10 );
	baroStepper.step( 1024 );
}
void loop(){
	Serial.println("[PROCESS] Looping");
	delay(10000);
	std::string metarString = getMetarString( icaoId );
	Serial.println( metarString.c_str() );
	std::vector<double> metarSet = parseMetar( metarString );
	Serial.printf( "[METAR] Altimeter: %f\nTemperatureC: %f\nTemperatureF: %f\nDewpointC: %f\nHumidity: %f\n", metarSet[0], metarSet[1], metarSet[2], metarSet[3], metarSet[4] ); 

	// Calculate and update stepper position
	double difference = ( gaugeFloorValues[0] - metarSet[0] ); // Difference between floor Hg and altim Hg
	double points = ( difference * 10 ); // Convert difference into tenths
	double steps = ( points * 34.13 ); // Convert to steps

	int stepsToTravel = calculateStepperDistanceToTravel( steps );
	updateStepperPosition( stepsToTravel, false );

	// Wait 2 minutes
	uint32_t moment = millis();
	while (millis() - moment < 120000) {
		//otaHandler.handle();
		//yield();
	}
}
