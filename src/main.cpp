#include <config.h>
#include <metar.h>
#include <wifiControl.h>
#include <vector>
#include <storage.h>
#include <ota.h>
#include <stepperMotor.h>
#include <gauge.h>

void setup(){
	Serial.flush();
	Serial.begin(9600);
	initWifi();
	otaHandler.begin();
	baroStepper.currentPosition = getStoredValue( ( baroStepper.name ).c_str(), "lastPosition" );
	baroStepper.calibrate();
	tempStepper.currentPosition = getStoredValue( ( tempStepper.name ).c_str(), "lastPosition" );
	tempStepper.calibrate();
	humidStepper.currentPosition = getStoredValue( ( humidStepper.name ).c_str(), "lastPosition" );
	humidStepper.calibrate();
}
void loop(){
	Serial.println("[PROCESS] Looping");
	delay( 10000 );

	std::string metarString = getMetarString( icaoId );
	Serial.println( metarString.c_str() );
	std::vector<double> metarSet = parseMetar( metarString );
	Serial.printf( "[METAR] Altimeter: %f\nTemperatureC: %f\nTemperatureF: %f\nDewpointC: %f\nHumidity: %f\n", metarSet[0], metarSet[1], metarSet[2], metarSet[3], metarSet[4] ); 

	// Calculate and update stepper position
	double difference = ( gaugeFloorValues[0] - metarSet[0] ); // Difference between floor Hg and altim Hg
	double points = ( difference * 10 ); // Convert difference into tenths
	double steps = ( points * 34.13 ); // Convert to steps

	//int stepsToTravel = calculateStepperDistanceToTravel( steps );
	baroStepper.targetPosition = steps;
	baroStepper.calculateTravelDistance();
	//int difference = baroStepper.calculateTravelDistance();
	Serial.printf( "Steps: %f | Current: %d | Target: %d\n", steps, baroStepper.currentPosition, baroStepper.targetPosition );
	//updateStepperPosition( stepsToTravel, false );
	//baroStepper.stepToTarget();

	// Temperature
	double tempDifference = ( gaugeFloorValues[1] - metarSet[2] ); // Difference between thermometer floor and temperatureF
	double tempSteps = ( tempDifference * 13.83 ); // Convert to steps
	tempStepper.targetPosition = tempSteps;
	tempStepper.calculateTravelDistance();
	//tempStepper.stepToTarget();
	Serial.printf( "tempSteps: %f | tempCurrent: %d | tempTarget: %d\n", tempSteps, tempStepper.currentPosition, tempStepper.targetPosition );

	// Humidity
	double humidDifference = ( gaugeFloorValues[2] - metarSet[4] ); // Difference between hygrometer floor and rH
	double humidSteps = ( humidDifference * 11.13 ); // Convert to steps
	humidStepper.targetPosition = -humidSteps;
	humidStepper.calculateTravelDistance();
	//humidStepper.stepToTarget();
	Serial.printf( "humidSteps: %f | humidCurrent: %d | humidTarget: %d\n", humidSteps, humidStepper.currentPosition, humidStepper.targetPosition );

	baroStepper.setPowerState( true );
	tempStepper.setPowerState( true );
	humidStepper.setPowerState( true );

	while( 
		(baroStepper.distanceToGo != 0)
		|| ( tempStepper.distanceToGo != 0 )
		|| ( humidStepper.distanceToGo != 0 )
	){
		baroStepper.setSpeed(200);
		baroStepper.stepToTarget( true );

		tempStepper.setSpeed(200);
		tempStepper.stepToTarget( true );

		humidStepper.setSpeed(200);
		humidStepper.stepToTarget( true );
	}

	baroStepper.setPowerState( false );
	tempStepper.setPowerState( false );
	humidStepper.setPowerState( false );

	// Wait 2 minutes
	uint32_t moment = millis();
	while (millis() - moment < 120000) {
		otaHandler.handle();
		yield();
	}
}
