#include <Arduino.h>
#include <stepperMotor.h>
#include <storage.h>
#include <config.h>
#include <stepperMotor.h>

void stepperMotor::step( int steps ){
	if( this->ccwRotation == true ){
		this->stepperObject.step( -steps );
	}
	else{
		this->stepperObject.step( steps );
	}
}
void stepperMotor::setSpeed( int speed ){
	this->stepperObject.setSpeed( speed );
}
void stepperMotor::calibrate(){
	delay( 2000 );
	int touchBaseline = touchRead( 15 );
	pinMode( 2, OUTPUT );
	digitalWrite( 2, HIGH );
	this->setSpeed( 2 );
	this->setPowerState( true );
	for( int i = 1; i < 6144; i++ ){
		if( touchRead( 15 ) > ( touchBaseline - 4 ) ){
			this->step( 1 );
		}
		else{
			i = 6145;
			digitalWrite( 2, LOW );
			this->currentPosition = 0;
			this->targetPosition = 0;
			setStoredValue( (this->name).c_str(), "lastPosition", 0 );
		}
	}
	digitalWrite( 2, LOW );
	this->setSpeed(10);
	this->setPowerState( false );
	return;
}
void stepperMotor::calculateTravelDistance(){
	this->positionDifference = ( abs( this->currentPosition ) - abs( this->targetPosition ) );
}
void stepperMotor::stepToTarget(){
	if( this->positionDifference != 0 ){
		this->setPowerState( true );
		this->step( positionDifference );
		this->setPowerState( false );
		setStoredValue( ( this->name ).c_str(), "lastPosition", this->targetPosition );
		this->currentPosition = this->targetPosition;
	}
}
void stepperMotor::setPowerState( bool state ){
	String mode;
	switch( state ){
		case true:
			mode = "HIGH";
		case false:
			mode = "LOW";
	}
	digitalWrite( this->inPin1, state );
	digitalWrite( this->inPin2, state );
	digitalWrite( this->inPin3, state );
	digitalWrite( this->inPin4, state );
}