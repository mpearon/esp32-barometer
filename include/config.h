#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Stepper.h>
#include <ArduinoOTA.h>
#include <ota.h>
#include <vector>
#include <stepperMotor.h>

extern std::string hostname;
extern int otaPort;
extern ArduinoOTAClass otaHandler;

extern std::string icaoId;
extern std::vector<double_t> gaugeFloorValues;
//extern Stepper baroStepper;
extern int currentBaroStepperPosition;
extern stepperMotor baroStepper;
extern stepperMotor tempStepper;
extern stepperMotor humidStepper;

#endif