#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <gauge.h>

class stepperMotor : public AccelStepper{
	using AccelStepper::AccelStepper;

	public:
		stepperMotor( 
			String name,
			int inPin1,
			int inPin2,
			int inPin3,
			int inPin4,
			gauge gaugeObject
		)
		: AccelStepper( 4, inPin1, inPin2, inPin3, inPin4 )
		, name( name )
		, currentPosition( 0 )
		, targetPosition( 0 )
		, distanceToGo( 0 )
		, inPin1( inPin1 )
		, inPin2( inPin2 )
		, inPin3( inPin3 )
		, inPin4( inPin4 )
		, gaugeObject( gaugeObject )
		, stepperObject( 4, inPin1, inPin2, inPin3, inPin4 ){
			AccelStepper( 4, inPin1, inPin2, inPin3, inPin4 );
		}

		String name;
		int currentPosition;
		int targetPosition;
		int positionDifference;
		int distanceToGo;
		int inPin1;
		int inPin2;
		int inPin3;
		int inPin4;

		void calibrate();
		void setSpeed( int speed );
		void calculateTravelDistance();
		void setPowerState( bool state );
		void stepToTarget( bool recordPosition );

	private:
		AccelStepper stepperObject;
		gauge gaugeObject;
};

#endif
