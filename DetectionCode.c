/*
 * Author: Team THRASHERS at KAUST
 * First prototype of MITKA
 * Description:
 */

#include <Wire.h>
#include "Adafruit_TCS34725.h"  //RGB sensor

#define wireless_transmission_circuit_PIN 2
#define LDR_sensor_PIN 3
#define digital_proximity_sensor_PIN 5
#define red_LED_PIN 10

#define green_LED_PIN 11
#define blue_LED_PIN 12
#define lux_threshold 40
#define wireless_transmission_circuit_ON_cycles 15

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_4X);

int bottle_detected = LOW;
int wireless_transmission_circuit_counter = 0;
uint16_t r, g, b, c, lux;
  
void setup() {
  pinMode(wireless_transmission_circuit_PIN, OUTPUT); //Activates transistor/coil circuit with relay
  pinMode(digital_proximity_sensor_PIN, INPUT); //Sharp digital sensor

  Serial.begin(9600);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  pinMode(red_LED_PIN, OUTPUT);
  digitalWrite(red_LED_PIN, LOW);
  pinMode(green_LED_PIN, OUTPUT);
  digitalWrite(green_LED_PIN, LOW);
  pinMode(blue_LED_PIN, OUTPUT);
  digitalWrite(blue_LED_PIN, LOW);
}

void loop() {
  digital_proximity_sensor(); //Sharp GP2Y0D805Z0F
  wireless_transmission_circuit();
  rgb_light_sensor(); //TCS
  tag_identification(lux, r, g, b);
}

void digital_proximity_sensor(){
  bottle_detected = (!digitalRead(digital_proximity_sensor_PIN));
  //Serial.print("bottle_detected = "); 
  //Serial.println(bottle_detected);
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
  tcs.getRawData(&r, &g, &b, &c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.println(" ");
  Serial.print("Red: "); Serial.print(r, DEC); Serial.print("   ");
  Serial.print("Green: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("Blue: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.println(" ");
}

void tag_identification(uint16_t lux, uint16_t r, uint16_t g, uint16_t b){
  if(lux >= lux_threshold && digitalRead(wireless_transmission_circuit_PIN) == HIGH){
    if((r > g) && (r > b)){
      digitalWrite(red_LED_PIN, HIGH);
      digitalWrite(green_LED_PIN, LOW);
  
    digitalWrite(blue_LED_PIN, LOW);
    }
    else if((g > b) && (g > r)){
      digitalWrite(red_LED_PIN, LOW);
      digitalWrite(green_LED_PIN, HIGH);
      digitalWrite(blue_LED_PIN, LOW);    }
    else if((b > r) && (b > g)){
      digitalWrite(red_LED_PIN, LOW);
      digitalWrite(green_LED_PIN, LOW);
      digitalWrite(blue_LED_PIN, HIGH);
    }
  }
  else{
    digitalWrite(red_LED_PIN, LOW);
    digitalWrite(green_LED_PIN, LOW);
    digitalWrite(blue_LED_PIN, LOW);
  }
  Serial.print("Red PIN: "); Serial.print(digitalRead(red_LED_PIN)); Serial.print(" ");
  Serial.print("Green PIN: "); Serial.print(digitalRead(green_LED_PIN)); Serial.print(" ");
  Serial.print("Blue PIN: "); Serial.print(digitalRead(blue_LED_PIN)); Serial.print(" ");
  Serial.println(" ");
}
