#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DMXSerial.h>
//#include <Encoder.h> unused

/////// LCD Screen
LiquidCrystal_I2C lcd(0x27, 16, 2); //16 charactes with 2 lines and HEX-adress 0x27

/////// RELAY
const int RELAY1 = 7;
const int RELAY2 = 8;
const int RELAY3 = 10;
const int RELAY4 = 11;

/////// Rotary Encoder unused
//const int CLK = 5;      // CLK at D6, DT at D5. 
//const int DT = 6;
//const int SW = 9;       // Switch at D9
//long oldPosition = -999;
//Encoder myEnc(6, 5);

/////// DMX
const int startChannel = 450; 
int ch1=0;
bool fired;

void setup()
{
  
  // LCD Screen  
  lcd.init();
  lcd.backlight();
  display("MS FX v0.1", false);
  display("Shock of Ages", true);

  // RELAY Pins
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, HIGH);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, HIGH);
  pinMode(RELAY3, OUTPUT);
  digitalWrite(RELAY3, HIGH);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY4, HIGH);

  // DMX Receiver
  DMXSerial.init(DMXReceiver);

}

void display(String text, bool top)
{
  if (top == false)
  {
    lcd.setCursor(0, 0);
    lcd.print(text);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print(text);
  }

}

void relayTest(){
  digitalWrite(RELAY1, HIGH);
  delay(500);
  digitalWrite(RELAY2, HIGH);
  delay(500);
  digitalWrite(RELAY3, HIGH);
  delay(500);
  digitalWrite(RELAY4, HIGH);
  delay(500);
  digitalWrite(RELAY1, LOW);
  delay(100);
  digitalWrite(RELAY2, LOW);
  delay(100);
  digitalWrite(RELAY3, LOW);
  delay(100);
  digitalWrite(RELAY4, LOW);
  delay(500);
}

void fire(int relay){
  digitalWrite(relay, LOW);
}

void off(int relay){
  digitalWrite(relay, HIGH);
}

//void encoder(){
//  long newPosition = myEnc.read();
//  if (newPosition != oldPosition) {
//    oldPosition = newPosition;
//    Serial.println(newPosition);
//  }
//}

void loop()
{

  ch1 = DMXSerial.read(startChannel);
  
  if(ch1 == 255 && fired == false){
      fire(RELAY1);
      fire(RELAY2);
      fire(RELAY3);
      fire(RELAY4);
      fired = true;
      delay(2000)
      off(RELAY1);
      off(RELAY2);
      off(RELAY3);
      off(RELAY4);
  }
}
