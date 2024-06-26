#include <stepperMotor.h>
#include <Arduino.h>
#include <gauge.h>
#include <storage.h>

void stepperMotor::calibrate(){
	delay( 2000 );
	int touchBaseline = touchRead( 15 );
	pinMode( 2, OUTPUT );
	digitalWrite( 2, HIGH );
	int originalPosition = this->currentPosition;
	this->currentPosition = 0;
	this->targetPosition = 6144;
	this->calculateTravelDistance();
	this->setPowerState( true );
	this->setSpeed( 100 );
	while( this->distanceToGo > 0 ){
		if( ( touchRead( 15 ) > touchBaseline - 4 ) ){
			this->stepToTarget( false );
		}
		else{
			this->distanceToGo = 0;
			this->currentPosition = 0;
			this->targetPosition = 0;
			this->calculateTravelDistance();
			originalPosition = 0;
		}
	}
	this->stepperObject.stop();
	this->setPowerState( false );
	digitalWrite( 2, LOW );
	this->currentPosition = originalPosition;
	this->targetPosition = this->currentPosition;
	this->calculateTravelDistance();
	return;
}
void stepperMotor::setSpeed( int speed ){
	this->stepperObject.setMaxSpeed( speed );
	this->stepperObject.setAcceleration( speed / 2 );
}
void stepperMotor::calculateTravelDistance(){
	this->positionDifference = ( abs( this->currentPosition ) - abs( this->targetPosition ) );
	this->stepperObject.setCurrentPosition( this->currentPosition );
	this->stepperObject.moveTo( this->targetPosition );
	this->distanceToGo = this->stepperObject.distanceToGo();
}
void stepperMotor::setPowerState( bool state ){
	int powerMode;
	switch( state ){
		case true:
			powerMode = 1;
		case false:
			powerMode = 0;
	}
	digitalWrite( this->inPin1, powerMode );
	digitalWrite( this->inPin2, powerMode );
	digitalWrite( this->inPin3, powerMode );
	digitalWrite( this->inPin4, powerMode );
}
void stepperMotor::stepToTarget( bool recordPosition ){
	this->stepperObject.run();
	this->distanceToGo = this->stepperObject.distanceToGo();
	this->currentPosition = this->targetPosition;
	if( recordPosition == true ){
		setStoredValue( (this->name).c_str(), "lastPosition", this->targetPosition );
	}
}