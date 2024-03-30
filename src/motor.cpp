#include <motor.h>
#include <Stepper.h>
#include <config.h>
#include <storage.h>
#include <Arduino.h>

void calibrateStepper(){
	int touchBaseline = touchRead( 15 );
	delay(1000);
	pinMode( 2, OUTPUT );
	digitalWrite( 2, HIGH );
	baroStepper.setSpeed(2);
	for (int i = 1; i < 6144; i++) {
		if( touchRead( 15 ) > ( touchBaseline - 4 ) ){
			baroStepper.step( 1 );
		}
		else{
			i = 6145;
			digitalWrite( 2, LOW );
			currentBaroStepperPosition = 0;
			setStoredValue( "barometer", "lastPosition", currentBaroStepperPosition );
		}
	}
	digitalWrite( 2, LOW );
	baroStepper.setSpeed(10);
	return;
}
int calculateStepperDistanceToTravel( int targetPosition ){
	return ( currentBaroStepperPosition - targetPosition );
}
void updateStepperPosition( int steps, bool smooth ){
	Serial.printf( "Moving stepper: %d\n", steps);
	baroStepper.step(steps);
	currentBaroStepperPosition = currentBaroStepperPosition - (steps);
	if( steps != 0 ){
		Serial.printf( "Committing new position to storage: %d\n", currentBaroStepperPosition);
		setStoredValue( "barometer", "lastPosition", currentBaroStepperPosition );
	}
}