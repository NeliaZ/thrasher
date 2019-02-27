/*
 * Author: Team THRASHERS at KAUST
 * First prototype of MITKA
 * Description:
 */

#include <Wire.h>
#include <Servo.h>
#include "Adafruit_APDS9960.h"

#define sensor_INT_PIN 5
#define servo_plastic_PIN 6
#define servo_glass_PIN 7
#define wireless_transmission_circuit_PIN 8
#define red_LED_PIN 10
#define green_LED_PIN 11
#define blue_LED_PIN 12

//Constants
#define color_threshold 10
#define wireless_transmission_circuit_ON_cycles 15

Adafruit_APDS9960 sensor;

Servo servo_plastic;
Servo servo_glass;

int bottle_detected = LOW;
int wireless_transmission_circuit_counter = 0;
uint16_t r, g, b, c;
  
void setup() {
  pinMode(wireless_transmission_circuit_PIN, OUTPUT); //Activates transistor/coil circuit with relay

  Serial.begin(9600);

  pinMode(servo_plastic_PIN, OUTPUT);
  digitalWrite(servo_plastic_PIN, LOW);
  pinMode(servo_glass_PIN, OUTPUT);
  digitalWrite(servo_glass_PIN, LOW);
  delay(200);

  servo_plastic.attach(servo_plastic_PIN);  // attaches the servo on pin 6 to the servo object
  servo_plastic.write(0);
  delay(200);

  servo_glass.attach(servo_glass_PIN);  // attaches the servo on pin 6 to the servo object
  servo_glass.write(0);
  delay(200);

  Serial.begin(115200);
  pinMode(sensor_INT_PIN, INPUT_PULLUP);

  if(!sensor.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable proximity mode
  sensor.enableProximity(true);
  //set the interrupt threshold to fire when proximity reading goes above 175
  sensor.setProximityInterruptThreshold(0,10);
  //enable the proximity interrupt
  sensor.enableProximityInterrupt();

  //enable color sensing mode
  sensor.enableColor(true);

  pinMode(red_LED_PIN, OUTPUT);
  digitalWrite(red_LED_PIN, LOW);
  pinMode(green_LED_PIN, OUTPUT);
  digitalWrite(green_LED_PIN, LOW);
  pinMode(blue_LED_PIN, OUTPUT);
  digitalWrite(blue_LED_PIN, LOW);
}

void loop() {
  proximity_sensor(); 
  wireless_transmission_circuit();
  rgb_light_sensor();
  tag_identification(r, g, b);
}

void proximity_sensor(){
  //print the proximity reading when the interrupt pin goes low
  if(!digitalRead(sensor_INT_PIN)){
    Serial.print("PROXIMITY: "); Serial.println(sensor.readProximity());
    bottle_detected = HIGH;
    //clear the interrupt
    sensor.clearInterrupt();
  }
  else{
    bottle_detected = LOW;
  }
}

void wireless_transmission_circuit(){
  if (bottle_detected == HIGH){
    digitalWrite(wireless_transmission_circuit_PIN,HIGH);
    Serial.println("wireless_transmission_circuit_PIN is HIGH");
    wireless_transmission_circuit_counter = wireless_transmission_circuit_ON_cycles;
  }
  else{
    if (wireless_transmission_circuit_counter > 0){
      wireless_transmission_circuit_counter = wireless_transmission_circuit_counter - 1;
      if (wireless_transmission_circuit_counter == 0){
        digitalWrite(wireless_transmission_circuit_PIN,LOW);
        Serial.println("wireless_transmission_circuit_PIN is LOW");
      }
    }
  }
}

void rgb_light_sensor()
{
  while(!sensor.colorDataReady()){
    delay(5);
  }

  //get the data and print the different channels
  sensor.getColorData(&r, &g, &b, &c);
  Serial.print("red: ");
  Serial.print(r);
  
  Serial.print(" green: ");
  Serial.print(g);
  
  Serial.print(" blue: ");
  Serial.println(b);

  delay(100);
}

void tag_identification(uint16_t r, uint16_t g, uint16_t b){
  if(((r >= color_threshold)||(g >= color_threshold)||(b >= color_threshold))
        && digitalRead(wireless_transmission_circuit_PIN) == HIGH){
    if((r > g) && (r > b)){
      digitalWrite(red_LED_PIN, HIGH);
      digitalWrite(green_LED_PIN, LOW);
      digitalWrite(blue_LED_PIN, LOW);
      //servo.write(90);   
      delay(100);
    }
    else if((g > b) && (g > r)){
      digitalWrite(red_LED_PIN, LOW);
      digitalWrite(green_LED_PIN, HIGH);
      digitalWrite(blue_LED_PIN, LOW);
      servo_glass.write(90);
      delay(1500);
      servo_glass.write(0);    
    }
    else if((b > r) && (b > g)){
      digitalWrite(red_LED_PIN, LOW);
      digitalWrite(green_LED_PIN, LOW);
      digitalWrite(blue_LED_PIN, HIGH);
      servo_plastic.write(90);
      delay(1500);
      servo_plastic.write(0);
    }
  }
  else{
    digitalWrite(red_LED_PIN, LOW);
    digitalWrite(green_LED_PIN, LOW);
    digitalWrite(blue_LED_PIN, LOW);
    //servo.write(90);
    delay(100);
  }
  Serial.print("Red PIN: "); Serial.print(digitalRead(red_LED_PIN)); Serial.print(" ");
  Serial.print("Green PIN: "); Serial.print(digitalRead(green_LED_PIN)); Serial.print(" ");
  Serial.print("Blue PIN: "); Serial.print(digitalRead(blue_LED_PIN)); Serial.print(" ");
  Serial.println(" ");
}
