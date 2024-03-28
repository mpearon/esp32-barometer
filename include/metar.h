#include <Arduino.h>
#include <vector>

std::string getMetarString( std::string icaoId );
std::vector<double> parseMetar( std::string metarString );