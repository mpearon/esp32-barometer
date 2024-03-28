#include <Arduino.h>
#include <Stepper.h>
#include <vector>

extern std::string icaoId;
extern std::vector<double_t> gaugeFloorValues;
extern Stepper baroStepper;