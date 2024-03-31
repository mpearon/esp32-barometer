#ifndef stepperMotor_h
#define stepperMotor_h

#include <Arduino.h>
#include <Stepper.h>

class stepperMotor : public Stepper{
	using Stepper::Stepper;

	public:
		stepperMotor( String name, int currentPosition, int targetPosition, int minimumStep, int maximumStep, bool ccwRotation, int steps, int inPin1, int inPin2, int inPin3, int inPin4 )
		: Stepper( steps, inPin1, inPin2, inPin3, inPin4 )
		, name( name )
		, currentPosition( currentPosition )
		, targetPosition( targetPosition )
		, minimumStep( minimumStep )
		, maximumStep( maximumStep )
		, ccwRotation( ccwRotation )
		, stepperObject( steps, inPin1, inPin2, inPin3, inPin4 ){
			Stepper( steps, inPin1, inPin2, inPin3, inPin4 );
		}

		String name;
		int currentPosition;
		int targetPosition;
		int positionDifference;
		int minimumStep;
		int maximumStep;
		bool ccwRotation;

		void calibrate();
		void setSpeed( int speed );
		void stepToTarget();
		void calculateTravelDistance();

	private:
		Stepper stepperObject;
		void step( int steps );
};

#endif
