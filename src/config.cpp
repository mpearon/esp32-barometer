#include <Arduino.h>
#include <vector>
#include <Stepper.h>

// Define airport by ICAO
std::string icaoId = "KMKC";

// Floor of gauges in order: Barometer, Temperature, Hygrometer
std::vector<double_t> gaugeFloorValues = { 26, 30, 0 };

// Define stepper motor information
Stepper baroStepper = Stepper( 2048, 19, 18, 5, 17 );
