#ifndef stepperMotor_h
#define stepperMotor_h

#include <Arduino.h>
#include <Stepper.h>

class stepperMotor : public Stepper{
	using Stepper::Stepper;
	public:
		//stepperMotor();
		stepperMotor( String name, int currentPosition, int targetPosition, int minimumStep, int maximumStep, bool ccwRotation, int steps, int inPin1, int inPin2, int inPin3, int inPin4 )
		: Stepper( steps, inPin1, inPin2, inPin3, inPin4 )
		, name( name )
		, currentPosition( currentPosition )
		, minimumStep( minimumStep )
		, maximumStep( maximumStep )
		, ccwRotation( ccwRotation )
		, stepperObject( Stepper( steps, inPin1, inPin2, inPin3, inPin4 )  ){}

		String name;
		int currentPosition;
		int targetPosition;
		int minimumStep;
		int maximumStep;
		bool ccwRotation;
		void calibrate();
		void step( int steps );

	private:
		Stepper stepperObject;
};

#endif