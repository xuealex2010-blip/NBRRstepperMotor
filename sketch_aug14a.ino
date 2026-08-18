/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-drv8825-stepper-motor-driver
 */

#include <AccelStepper.h>



#define STEP_PIN 18 // The ESP32 pin GPIO18 connected to STEP pin of DRV8825 module
#define DIR_PIN  5 // The ESP32 pin GPIO5 connected to DIR pin of DRV8825 module
#define EN_PIN 19 // Enable the driver
#define LED_PIN 2 //Built in led

const int stepsPerRevolution = 200 * 8;
int target = 200;
int speed = 1;

int time1 = 0;

// Creates an instance
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);
  // set the maximum speed, acceleration factor
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(200);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);
  Serial.begin(115200); // Start communication at 9600 baud
  //pinMode(LED_PIN, OUTPUT);
}

void loop() {

  stepper.run();  // Move the motor one step


  int sensorValue = analogRead(13);
  int motorSpeed = map(sensorValue, 0, 4095, 0, stepper.maxSpeed());
  long target = map(sensorValue, 0, 4095, 0, stepper.maxSpeed());


  //Custom dead zones
  if (target <= 240 && target > 200) {
    target = 200;
  } else if (target > 20 && target < 140) {
    target = 140;
  } else if (target > 240 && target < 275) {
    target = 275;
  }

  stepper.setSpeed(target);
  if (motorSpeed > 0) {
    digitalWrite(EN_PIN, LOW);
    //stepper.move(2*motorSpeed);
    //digitalWrite(STEP_PIN, HIGH);
  } else {
    digitalWrite(EN_PIN, HIGH);
    //digitalWrite(STEP_PIN, LOW);
  }

  //if (Serial.available() > 0) { // Check if a command has arrived
  //String command = Serial.readStringUntil('\n'); // Read until Enter is pressed
  //command.trim(); // Clean up whitespace

  //  if (command == "ON") {
  //    digitalWrite(LED_PIN, HIGH);
  //  } else if (command == "OFF") {
  //    digitalWrite(LED_PIN, LOW);
  //}
    //Serial.println(" ");
    //Serial.print(" LED: ");
    //Serial.print(digitalRead(LED_PIN));
    //Serial.print("  Enabled: ");
    //Serial.print(!digitalRead(EN_PIN));
    //Serial.print("  Speed: ");
    //Serial.print(motorSpeed);
    //Serial.print("  Long: ");
    //Serial.print(target);
    //if ((time1 % 100) < 2) {
    //  Serial.print("POT: ");
    //  Serial.println(target);
    //  Serial.print("Raw: ");
    //  Serial.println(motorSpeed);
    //  //Serial.println(time);
    //}
    //time1++;
  //}
}
