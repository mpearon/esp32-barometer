#include <Arduino.h>
#include <ArduinoJson.h>
String getMetarJson();
JsonObject getDeserializedMetar( String metarString);