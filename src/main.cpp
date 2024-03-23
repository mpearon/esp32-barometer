#include <Arduino.h>
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include <wifi.h>
#include <metar.h>
#include <secrets.h>

// Wiring
// ESP VIN > Stepper VCC
// ESP GND > Stepper GND
// ESP TX2 > Stepper IN4
// ESP D18 > Stepper IN3
// ESP D5 > Stepper IN2
// ESP D19 > Stepper IN1

// 0.1mb is about 1.024 steps, rounded to 1
// Floor is 866.9mb and Ceiling is 1077.7mb
// so, to get value from 0, add current to floor

Stepper hygroStepper(2048, 19, 18, 5, 17);
LiquidCrystal_I2C lcd(0x27, 16, 2);
double currentPosition = 0;

void calibrateStepper(){
	Serial.begin(9600);
	while( !(Serial.available()) ){
		hygroStepper.setSpeed(1);
		hygroStepper.step(-1);
	}
	currentPosition = 0;
	Serial.flush();
}
void setup() {
	Serial.begin(115200);
	// Prepage LCD
	lcd.init();
	lcd.backlight();
	lcd.setCursor(0,0);
	lcd.print("Calibration     ");
	lcd.setCursor(0,1);
	lcd.print("Stepper         ");
	// Prepare stepper
	pinMode(19, OUTPUT);
	pinMode(18, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(17, OUTPUT);
	calibrateStepper();
	hygroStepper.setSpeed(10);
	delay(1000);
	lcd.setCursor(0,1);
	lcd.print("WiFi            ");
	lcd.clear();
	initWifi();
}
double getNewTarget(){
	double newTarget = 0;
	Serial.printf("Randomly chose %i", newTarget);
	Serial.println();
	return newTarget;
}
double calculateDifference(double currentPosition, double targetPosition){
	double difference = (currentPosition - targetPosition);
	double unrounded = (difference * 1.01);
	Serial.printf("%i - %i = %i", targetPosition, currentPosition, unrounded);
	Serial.println();
	return unrounded;
}

void loop() {
	lcd.clear();
	//double targetPosition = getNewTarget();
	JsonObject metar = getDeserializedMetar( getMetarJson() );
	double metarAltim = metar["altim"];
	double barometerFloor = 853.3999;
	double barometerCeiling = 1066.712;
	double targetPosition = (metarAltim - barometerFloor)*10;
	// Print C: ####
	lcd.setCursor(0, 0);
	lcd.print("C: ");
	lcd.setCursor(3, 0);
	lcd.print( currentPosition );
	// Print T: ####
	lcd.setCursor(9, 0);
	lcd.print("T: ");
	lcd.setCursor(12, 0);
	lcd.print( targetPosition );

	// Print Move: ####>####
	double moveSteps = calculateDifference( currentPosition, targetPosition );
	lcd.setCursor(0, 1);
	lcd.print("Move ");
	lcd.setCursor(5, 1);
	lcd.print(moveSteps);
	lcd.setCursor(9, 1);
	lcd.print(" >");
	lcd.setCursor(12, 1);
	lcd.print(targetPosition);
	
	// Actually move
	if( moveSteps != 0 ){
		hygroStepper.step(moveSteps);
	}

	// Print complete
	lcd.setCursor(0,1);
	lcd.printf("ARRIVED AT %1");
	currentPosition = targetPosition;
	delay(60000);
}