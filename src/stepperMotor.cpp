#include <Arduino.h>
//#include <motorInfo.h>
//#include <Stepper.h>
#include <stepperMotor.h>
#include <storage.h>

/* stepperMotor::stepperMotor()
	: Stepper( 2048, 19, 18, 5, 17 )
	, name( "barometer" )
	, currentPosition()
	, targetPosition()
	, minimumStep( 0 )
	, maximumStep ( 2048 ){

} */

void stepperMotor::step( int steps ){
	if( ccwRotation == true ){
		this->stepperObject.step( steps );
	}
	else{
		this->stepperObject.step( -steps );
	}
}
void stepperMotor::setSpeed( int speed ){
	this->stepperObject.setSpeed( speed );
}
void stepperMotor::calibrate(){
	pinMode( 2, OUTPUT );
	digitalWrite( 2, HIGH );
	this->setSpeed( 2 );
	for( int i = 1; i < 6144; i++ ){
		if( touchRead( 15 ) > 40 ){
			this->step( 1 );
		}
		else{
			digitalWrite( 2, LOW );
			this->currentPosition = 0;
			setStoredValue( name.c_str(), "lastPosition", 0 );
		}
	}
	this->setSpeed( 10 );
}