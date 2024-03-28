#ifndef motorInfo_h
#define motorInfo_h

#include <Arduino.h>
#include <Stepper.h>

class StepperMotor{
	public:
		// Constructor
		StepperMotor( String name, int steps, int in1Pin, int in2Pin, int in3Pin, int in4Pin, Stepper stepperObject );
		StepperMotor( String name, int steps, int in1Pin, int in2Pin, int in3Pin, int in4Pin );

		// Members
		String name;
		int steps;
		int in1Pin;
		int in2Pin;
		int in3Pin;
		int in4Pin;

		// Methods
		void stepMotor( int steps );

		private:
			Stepper stepperObject; //(int steps, int in1Pin, int int2Pin, int in3Pin, int in4Pin );

};

#endif