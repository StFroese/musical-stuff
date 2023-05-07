#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden
#include <DMXSerial.h>
//#include <Encoder.h>

/////// LCD Screen
LiquidCrystal_I2C lcd(0x27, 16, 2); //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)"

/////// RLEAY
const int RELAY1 = 7;
const int RELAY2 = 8;
const int RELAY3 = 10;
const int RELAY4 = 11;

/////// Rotary Encoder
//const int CLK = 5;      // Definition der Pins. CLK an D6, DT an D5. 
//const int DT = 6;
//const int SW = 9;       // Der Switch wird mit Pin D2 Verbunden. ACHTUNG : Verwenden Sie einen interrupt-Pin!
//long oldPosition = -999;
//Encoder myEnc(6, 5);

/////// DMX
const int startChannel = 450; 
int ch1=0,ch2=0,ch3=0,ch4=0,ch5=0,ch6=0;
bool fired1=false,fired2=false,fired3=false,fired4=false;

void setup()
{
  
  // LCD Screen  
  lcd.init(); //Im Setup wird der LCD gestartet
  lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus).
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
  DMXSerial.write(1, 0);
  DMXSerial.write(2, 0);
  DMXSerial.write(3, 0);
  DMXSerial.write(4, 0);
  DMXSerial.write(5, 0);
  DMXSerial.write(6, 0);

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
  //ch2 = DMXSerial.read(startChannel+1);
  //ch3 = DMXSerial.read(startChannel+2);
  //ch4 = DMXSerial.read(startChannel+3);
  //ch5 = DMXSerial.read(startChannel+4);
  //ch6 = DMXSerial.read(startChannel+5);
  
  //ch1 = 13;
  //ch2 = 37;
  //ch3 = 255;
  //ch4 = 255;
  //ch5 = 255;
  //ch6 = 255;

  
  //if(ch1==13 && ch2==37){
  //  if(ch3 == 255 && fired1 == false){
  //    fire(RELAY1);
  //    fired1 = true;
  //  }
  //  if(ch4 == 255 && fired2 == false){
  //    fire(RELAY2);
  //    fired2 = true;
  //  }
  //  if(ch5 == 255 && fired3 == false){
  //    fire(RELAY3);
  //    fired3 = true;
  //  }
  //  if(ch6 == 255 && fired4 == false){
  //    fire(RELAY4);
  //    fired4 = true;
  //  }
  //}
  if(ch1 == 255 && fired1 == false){
      fire(RELAY1);
      fire(RELAY2);
      fire(RELAY3);
      fire(RELAY4);
      fired1 = true;
  }

  if(fired1 == true){
    delay(2000);
    off(RELAY1);
    off(RELAY2);
    //off(RELAY2);
    off(RELAY3);
    off(RELAY4);
  }
}
