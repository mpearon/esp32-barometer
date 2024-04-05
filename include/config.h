#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ota.h>
#include <vector>
#include <stepperMotor.h>
#include <gauge.h>

extern std::string hostname;
extern int otaPort;
extern ArduinoOTAClass otaHandler;

extern std::string icaoId;
extern std::vector<double_t> gaugeFloorValues;
extern stepperMotor baroStepper;
extern stepperMotor tempStepper;
extern stepperMotor humidStepper;
extern gauge barometerGauge;
extern gauge thermometerGauge;
extern gauge hygrometerGauge;

#endif