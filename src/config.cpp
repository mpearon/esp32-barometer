#include <Arduino.h>
#include <vector>
#include <Stepper.h>
#include <stepperMotor.h>
#include <ota.h>

std::string hostname = "sensESP-barometer";

// Define airport by ICAO
std::string icaoId = "KMKC";

// Floor of gauges in order: Barometer, Temperature, Hygrometer
std::vector<double_t> gaugeFloorValues = { 26, 30, 0 };

// Define stepper motor information
//Stepper baroStepper = Stepper( 2048, 19, 18, 5, 17 );
int currentBaroStepperPosition = 0;

stepperMotor baroStepper = stepperMotor( "barometer", 0, 0, 0, 2048, false, 2048, 19, 5, 18, 17 );
stepperMotor tempStepper = stepperMotor( "temperature", 0, 0, 0, 2048, false, 2048, 26, 33, 25, 32 );
stepperMotor humidStepper = stepperMotor( "humidity", 0, 0, 0, 2048, true, 2048, 13, 14, 12, 27 );

// Define and initialize OTA information
ArduinoOTAClass otaHandler = initializeOta();