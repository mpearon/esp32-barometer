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
}
int calculateStepperDistanceToTravel( int targetPosition ){
	return ( currentBaroStepperPosition - targetPosition );
}
void updateStepperPosition( int steps, bool smooth ){
	baroStepper.step(-steps);
	currentBaroStepperPosition = currentBaroStepperPosition + (-steps);
	setStoredValue( "barometer", "lastPosition", currentBaroStepperPosition );
}