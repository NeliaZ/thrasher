#include <LiquidCrystal.h>          //the liquid crystal libarry contains commands for printing to the display

#define red_PIN 2
#define green_PIN 3
#define blue_PIN 4

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);   // tell the RedBoard what pins are connected to the display

void setup() {                     
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
  pinMode(red_PIN, INPUT);
  pinMode(green_PIN, INPUT);
  pinMode(blue_PIN, INPUT);
}

void loop() {
  detect_material();
}

void detect_material(){
  if ((digitalRead(red_PIN) == HIGH)&&(digitalRead(green_PIN) == LOW)&&(digitalRead(blue_PIN) == LOW)){
    lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
    lcd.print("Detecting...    ");       //print hello, world! starting at that position
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("^_^             ");         //print the number of seconds that have passed since the last reset  
  }
  else if ((digitalRead(red_PIN) == LOW)&&(digitalRead(green_PIN) == HIGH)&&(digitalRead(blue_PIN) == LOW)){
    lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
    lcd.print("It's paper!     ");       //print hello, world! starting at that position
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("Thank you! ^_^  ");         //print the number of seconds that have passed since the last reset  
  }
  else if ((digitalRead(red_PIN) == LOW)&&(digitalRead(green_PIN) == LOW)&&(digitalRead(blue_PIN) == HIGH)){
    lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
    lcd.print("It's plastic!   ");       //print hello, world! starting at that position
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("And I love you! ");         //print the number of seconds that have passed since the last reset  
  }
  else if ((digitalRead(red_PIN) == LOW)&&(digitalRead(green_PIN) == LOW)&&(digitalRead(blue_PIN) == LOW)){
    lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
    lcd.print(" MITKa is ready ");       //print hello, world! starting at that position
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("    for you!    ");         //print the number of seconds that have passed since the last reset
  }
  else{
    lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
    lcd.print(" MITKa is ready ");       //print hello, world! starting at that position
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("    for you!    ");         //print the number of seconds that have passed since the last reset
  }
}
