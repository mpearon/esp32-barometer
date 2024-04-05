#include <Arduino.h>
#include <vector>
#include <stepperMotor.h>
#include <ota.h>
#include <gauge.h>

std::string hostname = "sensESP-barometer";

// Define airport by ICAO
std::string icaoId = "KMKC";

// Floor of gauges in order: Barometer, Temperature, Hygrometer
std::vector<double_t> gaugeFloorValues = { 26, 28, 0 };

// Define gauge motor information
gauge barometerGauge( "barometer", 26.0, 32.0, false );
gauge thermometerGauge( "thermometer", 28.0, 112.0, false );
gauge hygrometerGauge( "hygrometer", 0.0, 100.0, true );

// Define stepper motor information
stepperMotor baroStepper( "barometer", 19, 5, 18, 17, barometerGauge );
stepperMotor tempStepper( "thermometer", 26, 33, 25, 32, thermometerGauge );
stepperMotor humidStepper( "hygrometer", 13, 14, 12, 27, hygrometerGauge );

// Define and initialize OTA information
ArduinoOTAClass otaHandler = initializeOta();