#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define EDebug  1
#define TDebug  1000
#define TLcd    1000

#define LCD_I2C_ADDR    0x27
#define DS1307_ADDRESS  0x68 // Indirizzo dell'integrato DS1307 
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define EdButt 2
#define UpButt 3
#define DwButt 4

#define EdSelPatt  100
#define EdEntPatt  2000
#define EdButtEnt 1
#define EdButtSel 2
#define ExitTimeMenu 60000
#define MenuPage 6

char buffer[16];

long TimeLcd  = 0;  //Tempo aggiornamento schermo base
long TimeDeb  = 0;  //Tempo scrittura debug

byte DataTime[7];
byte SetDataTime[7];

char EditState = 0;
boolean EditMode = 0;
boolean InitEdit = 0;
long TimeMenu = 0;
char Menu = 0;
char MenuOld = 0;
char i;
char Cursor, OldCursor;


LiquidCrystal_I2C lcd(LCD_I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void setup()
{
  pinMode(EdButt, INPUT_PULLUP);
  pinMode(UpButt, INPUT_PULLUP);
  pinMode(DwButt, INPUT_PULLUP);
  Wire.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);
  if (! GetDateTime(0, 0)) {
    Serial.println("RTC is NOT running!");
  }

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(4 , 0);
  lcd.print("Msystem");
  lcd.setCursor(1, 1);
  lcd.print("Old Clock V2.0");
  delay(600);
  lcd.clear();

}

void Debug() {
  Serial.println("Debug Programma");
  Serial.println(Menu, DEC);
  Serial.println(EditMode, DEC);
  Serial.println(InitEdit, DEC);
  Serial.println(Cursor, DEC);
}

char ButtonState(char PinN) {
  long Time = millis();

  while (!digitalRead(PinN)) {} //Serial.print("1");}
  if (millis() >= EdEntPatt + Time) {
    //Serial.println(EdEntPatt + Time);
    //Serial.println(millis());
    //Serial.println("2");
    return 2;
  }
  if (millis() >= EdSelPatt + Time) {
    //Serial.println(EdSelPatt + Time);
    //Serial.println(millis());
    //Serial.println("1");
    return 1;
    delay(100);
  }
  return false;
}



byte DecToBcd(byte val)
{
  return (((val / 10) << 4) + (val % 10));
}

byte BcdToDec(byte val)
{
  return (((val >> 4) * 10) + (val & 0b1111) );
}


boolean GetDateTime(uint8_t *Array, char Len)
{
  Wire.beginTransmission(DS1307_ADDRESS);// inizializzo la trasmissione partendo dall'indirizzo 0x00
  Wire.write(0x00);
  Wire.endTransmission();                // richiede 7 bytes alla device con l'indirizzo indicato il DS1307 utilizza 56 bit per registrare la data/ora
  Wire.requestFrom(DS1307_ADDRESS, 7);
  if (Wire.available())
  {
    *(Array + 6) = BcdToDec(Wire.read());
    *(Array + 5) = BcdToDec(Wire.read());
    *(Array + 4) = BcdToDec(Wire.read() & 0b111111); // modo 24 ore considero i primi 6 bit
    *(Array + 3) = Wire.read(); // non mi serve convertire (Range da 1 a 7 => 3 bit)
    *(Array + 2) = BcdToDec(Wire.read());
    *(Array + 1) = BcdToDec(Wire.read());
    *Array = BcdToDec(Wire.read());
    return true;
  }
  return false;
}

void SendDateTime(uint8_t *Array)
{
  Wire.beginTransmission(DS1307_ADDRESS); // il primo byte inviato stabilisce il registro iniziale su cui scrivere
  Wire.write(0x00);
  for ( i = 7; i != 0; i--) {
    Wire.write(DecToBcd(*(Array + i - 1)));
  }
  Wire.write(0x00);
  Wire.endTransmission();
}

byte readByte()
{
  while (!Serial.available()) delay(10);
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n')
  {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}

boolean CtrlData(byte dd, byte mm, byte yy)
{
  uint8_t GGMese[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if ((mm < 1) || (mm > 12)) return false; // non e' un mese!
  if (yy % 4 == 0) GGMese[1] = 29; // Bisestile
  if (dd < 1 || dd > GGMese[mm - 1]) return false;
  return true;
}


void loop()
{

  if ((millis() > (TimeDeb + TDebug)) && EDebug) {
    TimeDeb = millis();
    Debug();
  }

  if (millis() > (TimeLcd + TLcd) && (Menu == 0)) {
    TimeLcd = millis();
    //DateTime now = RTC.now();
    GetDateTime(&DataTime[0], 6);
    lcd.clear();
    sprintf(buffer,  "%02d/%02d/%d", DataTime[2], DataTime[1], DataTime[0]);
    lcd.setCursor(4, 0);
    lcd.print( buffer );
    //buffer[10] = 0;
    sprintf(buffer,  "%02d:%02d:%02d", DataTime[4], DataTime[5], DataTime[6]);
    lcd.setCursor(4, 1);
    lcd.print( buffer );
  }

  EditState = ButtonState(EdButt);
  if ( EditState) TimeMenu =  millis();
  if (millis() > TimeMenu + ExitTimeMenu)  {
    Menu = 0;
    EditMode = 0;
    InitEdit = 0;
    Cursor = 0;
    lcd.noBlink();
  }
  if ((EditState == 1) && (EditMode == 0)) Menu += 1;
  if ((EditState == 2) && Menu && (EditMode == 1)) {        //Salvataggio ora sul RTC
    EditMode = 0;
    Menu = 0;
    InitEdit = 0;
    Cursor = 0;
    lcd.noBlink();
    if (CtrlData(SetDataTime[2], SetDataTime[1], SetDataTime[0])) {  //Controllo data corretta
      SendDateTime(&SetDataTime[0]);
      Serial.print("OK");
    }
    else {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Errore Data");
      delay(1500);

    }
  }
  if ((EditState == 2) && Menu && (EditMode == 0)) EditMode = 1;
  if (Menu >= MenuPage)Menu = 0;
  if ((Menu != MenuOld) && (EditMode == 0)) {       //Menu
    lcd.clear();
    lcd.setCursor(0, 0);
    //Serial.println(Menu, DEC);
    switch (Menu) {
      case 1:
        lcd.print("Imposta data ora");
        break;
      case 2:
        lcd.print("Velocita motore");
        break;
      case 3:
        lcd.print("Crepuscolare");
        break;
      case 4:
        lcd.print("Intensita luce");
        break;
      case 5:
        lcd.print("Log Errori");
        break;
    }
    MenuOld = Menu;
  }
  //--------EDIT MODE-------------
  if ((Menu == 1) && (EditMode)) {
    if (InitEdit == 0) {
      lcd.clear();
      for (i = 7; i != 0; i--) SetDataTime[i - 1] = DataTime[i - 1];
      sprintf(buffer,  "%02d/%02d/%d", SetDataTime[2], SetDataTime[1], SetDataTime[0]);
      lcd.setCursor(4, 0);
      lcd.print( buffer );
      //buffer[10] = "";
      sprintf(buffer,  "%02d:%02d:%02d", SetDataTime[4], SetDataTime[5], SetDataTime[6]);
      lcd.setCursor(4, 1);
      lcd.print( buffer );
      Cursor = 0;
      lcd.setCursor(4, 0);
      lcd.blink();
      InitEdit = 1;
    }
    if (InitEdit) {
      if ( EditState == 1) Cursor += 1;
      if (Cursor != OldCursor)
      {
        if (Cursor > 5)      Cursor = 0;
        OldCursor = Cursor;
        switch (Cursor) {
          case 0: lcd.setCursor(4, 0); break;
          case 1: lcd.setCursor(7, 0); break;
          case 2: lcd.setCursor(10, 0); break;
          case 3: lcd.setCursor(4, 1); break;
          case 4: lcd.setCursor(7, 1); break;
          case 5: lcd.setCursor(10, 1); break;
        }
      }

      if (ButtonState(3)) {
        //buffer[10] = "";
        switch (Cursor) {
          case 0:
            lcd.setCursor(4, 0);
            if (SetDataTime[2] < 31) SetDataTime[2] += 1;
            sprintf(buffer,  "%02d" , SetDataTime[2]);
            lcd.print(buffer);
            lcd.setCursor(4, 0);
            break;
          case 1:
            lcd.setCursor(7, 0);
            if (SetDataTime[1] < 12) SetDataTime[1] += 1;
            sprintf(buffer,  "%02d" , SetDataTime[1]);
            lcd.print(buffer);
            lcd.setCursor(7, 0);
            break;
          case 2:
            lcd.setCursor(10, 0);
            if (SetDataTime[0] < 98)SetDataTime[0] += 1;
            sprintf(buffer,  "%02d" , SetDataTime[0]);
            lcd.print(buffer);
            lcd.setCursor(10, 0);
            break;
          case 3:
            lcd.setCursor(4, 1);
            if (SetDataTime[4] < 23)SetDataTime[4] += 1;
            sprintf(buffer,  "%02d" , SetDataTime[4]);
            lcd.print(buffer);
            lcd.setCursor(4, 1);
            break;
          case 4:
            lcd.setCursor(7, 1);
            if (SetDataTime[5] < 59)SetDataTime[5] += 1;
            sprintf(buffer,  "%02d" , SetDataTime[5]);
            lcd.print(buffer);
            lcd.setCursor(7, 1);
            break;
          case 5:
            lcd.setCursor(10, 1);
            if (SetDataTime[6] < 59)SetDataTime[6] += 1;
            sprintf(buffer,  "%02d" , SetDataTime[6]);
            lcd.print(buffer);
            lcd.setCursor(10, 1);
            break;
        }
      }
      if (ButtonState(4)) {
        //buffer[10] = "";
        switch (Cursor) {
          case 0:
            lcd.setCursor(4, 0);
            if (SetDataTime[2] > 0) SetDataTime[2] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[2]);
            lcd.print(buffer);
            lcd.setCursor(4, 0);
            break;
          case 1:
            lcd.setCursor(7, 0);
            if (SetDataTime[1] > 0) SetDataTime[1] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[1]);
            lcd.print(buffer);
            lcd.setCursor(7, 0);
            break;
          case 2:
            lcd.setCursor(10, 0);
            if (SetDataTime[0] > 0)SetDataTime[0] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[0]);
            lcd.print(buffer);
            lcd.setCursor(10, 0);
            break;
          case 3:
            lcd.setCursor(4, 1);
            if (SetDataTime[4] > 0) SetDataTime[4] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[4]);
            lcd.print(buffer);
            lcd.setCursor(4, 1);
            break;
          case 4:
            lcd.setCursor(7, 1);
            if (SetDataTime[5] > 0)  SetDataTime[5] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[5]);
            lcd.print(buffer);
            lcd.setCursor(7, 1);
            break;
          case 5:
            lcd.setCursor(10, 1);
            if (SetDataTime[6] > 0)SetDataTime[6] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[6]);
            lcd.print(buffer);
            lcd.setCursor(10, 1);
            break;
        }
      }
    }
  }
}
