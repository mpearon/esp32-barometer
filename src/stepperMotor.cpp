#include <Arduino.h>
#include <stepperMotor.h>
#include <storage.h>
#include <config.h>
#include <motor.h>

void stepperMotor::step( int steps ){
	if( this->ccwRotation == true ){
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
	int touchBaseline = touchRead( 15 );
	delay( 1000 );
	pinMode( 2, OUTPUT );
	digitalWrite( 2, HIGH );
	this->setSpeed( 2 );
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
	return;
}
void stepperMotor::calculateTravelDistance(){
	this->positionDifference = ( this->currentPosition - this->targetPosition );
}
void stepperMotor::stepToTarget(){
	for( int i = 0; i < ( abs( this->positionDifference ) ); i++ ){
		this->step( 1 );
	}
	if( this->positionDifference != 0 ){
		setStoredValue( ( this->name ).c_str(), "lastPosition", this->targetPosition );
		this->currentPosition = this->targetPosition;
	}
}