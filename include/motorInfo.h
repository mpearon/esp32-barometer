#ifndef motorInfo_h
#define motorInfo_h

#include <Arduino.h>
#include <Stepper.h>

class StepperMotor{
	public:
		// Constructor
		StepperMotor( String name, int steps, int in1Pin, int in2Pin, int in3Pin, int in4Pin, Stepper stepperObject );

		// Members
		String name;
		int steps;
		int in1Pin;
		int in2Pin;
		int in3Pin;
		int in4Pin;
		int lastPosition;

		// Methods
		void stepMotor( int steps );
		void updateLastPosition( int position );

		private:
			Stepper stepperObject; //(int steps, int in1Pin, int int2Pin, int in3Pin, int in4Pin );

};

#endif