#ifndef MOTOR_H
#define MOTOR_H

void calibrateStepper();
int calculateStepperDistanceToTravel( int targetPosition );
void updateStepperPosition( int steps, bool smooth );

#endif