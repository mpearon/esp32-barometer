#include <Arduino.h>
#include <motorInfo.h>
#include <Stepper.h>

StepperMotor::StepperMotor( String name, int steps, int in1Pin, int in2Pin, int in3Pin, int in4Pin, Stepper stepperObject ) : stepperObject( steps, in1Pin, in2Pin, in3Pin, in4Pin ){
}
void StepperMotor::stepMotor( int steps ){
	stepperObject.step( steps );
}
void StepperMotor::updateLastPosition( int position ){
	lastPosition = position;
}