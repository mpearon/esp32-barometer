#include <motor.h>
#include <Stepper.h>
#include <config.h>
#include <storage.h>
#include <Arduino.h>

void calibrateStepper(){
	pinMode( 2, OUTPUT );
	digitalWrite( 2, HIGH );
	baroStepper.setSpeed(5);
	for (int i = 1; i < 4096; i++) {
		if( touchRead(32) > 40 ){
			baroStepper.step(-1);
		}
		else{
			digitalWrite( 2, LOW );
			currentBaroStepperPosition = 0;
		}
	}
	digitalWrite( 2, LOW );
	currentBaroStepperPosition = 0;
	setStoredValue( "barometer", "lastPosition", currentBaroStepperPosition );
}
int calculateStepperDistanceToTravel( int targetPosition ){
	return ( currentBaroStepperPosition - targetPosition );
}
void updateStepperPosition( int steps, bool smooth ){
	Serial.printf( "Moving stepper: %d", steps);
	baroStepper.step(-steps);
	currentBaroStepperPosition = currentBaroStepperPosition + (-steps);
	if( steps != 0 ){
		Serial.printf( "Committing new position to storage: %d", currentBaroStepperPosition);
		setStoredValue( "barometer", "lastPosition", currentBaroStepperPosition );
	}
}