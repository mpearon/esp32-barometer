#ifndef stepperMotor_h
#define stepperMotor_h

#include <Arduino.h>
#include <Stepper.h>

class stepperMotor: public Stepper{
	using Stepper::Stepper;
	public:
		std::string name;
		int currentPosition;
		int targetPosition;
		int maximumStep;
		int minimumStep;
};

#endif