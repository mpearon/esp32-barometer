#include <Arduino.h>
#include <vector>
#include <Stepper.h>
#include <stepperMotor.h>

std::string hostname = "sensESP-barometer";
std::string mDnsHostname = "sensESP-baro";

// Define airport by ICAO
std::string icaoId = "KMKC";

// Floor of gauges in order: Barometer, Temperature, Hygrometer
std::vector<double_t> gaugeFloorValues = { 26, 30, 0 };

// Define stepper motor information
//Stepper baroStepper = Stepper( 2048, 19, 18, 5, 17 );
int currentBaroStepperPosition = 0;

stepperMotor baroStepper = stepperMotor( "barometer", 0, 0, 0, 2048, false, 2048, 19, 18, 5, 7 );