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
	calibrateStepper();
}