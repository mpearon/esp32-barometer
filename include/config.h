#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Stepper.h>
#include <ArduinoOTA.h>
#include <ota.h>
#include <vector>

extern std::string hostname;
extern std::string mDnsHostname;
extern int otaPort;
extern ArduinoOTAClass otaHandler;

extern std::string icaoId;
extern std::vector<double_t> gaugeFloorValues;
extern Stepper baroStepper;
extern int currentBaroStepperPosition;

#endif