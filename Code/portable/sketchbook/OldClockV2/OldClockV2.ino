
/*
  Old clock for rail station V2.0
   This project is to control a flip clock using arduino nano with tiny rtc board,
   also a twilight control for night light.
   Can adjust: the date and time, motor speed for pallet revolution, twilight
   threshold, voltage supply allarm and and event/alarm log history.
*/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <avr/wdt.h>

//Alarm table
#define EVENT			'E'
#define ALARM			'A'
#define MESSAGE			'M'
#define START_UP		1
#define I2C_FAULT		2
#define CHANGE_DATA		3
#define DATA_FAULT		4
#define MCL_ADVANCE		5
#define MCL_DELAY		6
#define LCD_BUS_FAULT	7
#define RTC_BUSS_FAULT	8
#define EPR_BUSS_FAULT	9
#define RTC_NOT_RUN		10
#define SAVE_SHUTDOWN	11

//Alarm Led Blink Pattern
#define Pattern_No_All	2500
#define Pattern_All1	1000
#define Pattern_All2	500
#define Pattern_All3	200

#define EepromWipe		0 		// init procedure for new eeprom
#define EepromRead		0   	// all the eprom data is print on serial port in startup
#define SystemLog		1		//Enable of System Log on external eprom
#define FDebug			0		// Enable Fast Debug
#define SDebug			1		// Eneble Time Debug
#define TDebug			1000	// Time of debug 
#define TLcd			1000	// Time Lcd Refresh 
#define TTwl			1000	// Time for LDR value calculation
#define TRMot			62000	// Time 
#define TPatAll			30000	// Time of led alarm indication 
#define TExitMenu		30000	// Time for auto-exit menu 
#define TI2cTest		2000	// Time for bus test 
#define TSvTShDw		500	// Time to Save and Shutdown , power off the PerPwr enable

#define SelPatt			50		// Selection minimal time 
#define EntPatt			1500	// Enter

#define MenuPage		7		// Number of page in Menu 
#define SampleN			10		// Sample number for LDR Value 
#define TwlRDelta		30		// Delta between the Min and Max threshold in Twilight parameter 


#define UpLimMS			250		// Motor Speed limit
#define DwLimMS			12
#define UpLimTwlOn		250		// Twilight Sensor limit ON
#define DwLimTwlOn		10
#define	UpLimTwlOff		250		// Twilight Sensor limit OFF
#define DwLimTwlOff		10
#define UpLimVSens    	140   	// Twilight Sensor limit OFF
#define DwLimVSens    	50
#define HiEpromLim		4020	// Message limit for system log %10
#define LowEpromLim		0
#define EepromPageSize	32
#define SerAllMes		2



//I2C Addres and pinout
#define EEPROM_ADDR		0x50
#define LCD_I2C_ADDR	0x27
#define DS1307_ADDR		0x68
#define BACKLIGHT_PIN	3
#define En_pin			2
#define Rw_pin			1
#define Rs_pin			0
#define D4_pin			4
#define D5_pin			5
#define D6_pin			6
#define D7_pin			7


//Arduino PinOut
#define EdButt			2
#define UpButt			3
#define DwButt			4
#define FaseCTRL		5
#define LDR				A0
#define VSens			A1
#define Light			11
#define LedV			9
#define LedR			13
#define MotDir			6
#define MotEn			7
#define PerPwr			8


// Arduino EEPROM data storage
#define M_MotSpeed		1
#define M_TwlR_On		2						//Twilight relays threshold On
#define M_TwlR_Off		3						//Twilight relays threshold Off
#define M_HMec			4
#define M_MMec			5
#define M_MDir			6
#define M_EpromAdd		7
#define M_EpromAdd1		8
#define M_VSensLim		9     // 12V Sensor limit under this limit save the parameter and disable motor movement 



long TimeLcd  	= 0;  		//Update LCD Time
long TimeDeb 	= 0;  		//Debug Time
long TimeTwl  	= 0;		//
long TimeRMot 	= 0;		// Time to update the Mechanical time
long TimeMotSpeed = 0;
long TimeBlink 	= 0;
long TimeEdButt = 0;
long TimeUpButt	= 0;
long TimeDwButt = 0;
long TimePatt	= 0;
long TimeMenu 	= 0;
long TimeI2cTest = 0;
long TimeSvTShDw	= 0;

byte DataTime[7];
byte SetDataTime[7];
byte AllBuff[10];
char buffer[30];
byte SerAll[3];


int EpromAdd;
int Pattern = 0;
int SetData, SetDataOld;
int HMec, MMec ;
int MotorSpeed;
int TwlR_On, TwlR_Off, TwlAve, TwlVal;
int VSensVal;
int VSensValOld;
int VSensLim;
int j;

char EditState = 0;
char Menu = 0;
char MenuOld = 0;
char i = 0;
char Cursor, OldCursor;
char Sample;
char UpButtState, DwButtState;
char SerCount;

byte EpromPageOffset = 0;
byte NotAligLengt  = 0;
byte Char10[8] = { B00010, B00100, B01000, B10000, B01011, B11011, B01011, B01011 };
byte CharV[8] = { B10001, B10001, B01010, B01010, B00100, B00001, B00010, B00100 };

bool AllReady  = 0;
bool MClAdAll  = 0;
bool MClDlAll  = 0;
bool LcdAll    = 0;
bool RtcAll    = 0;
bool EpromAll  = 0;
bool PattAllOn = 0;
bool MoveMot   = 0;
bool EditMode  = 0;
bool InitEdit  = 0;
bool SvTShDw  = 0;



LiquidCrystal_I2C lcd(LCD_I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void(* resetFunc) (void) = 0;

void setup() {
  pinMode(EdButt, INPUT_PULLUP);
  pinMode(UpButt, INPUT_PULLUP);
  pinMode(DwButt, INPUT_PULLUP);
  pinMode(FaseCTRL, INPUT_PULLUP);
  pinMode(Light, OUTPUT);
  pinMode(LedR, OUTPUT);
  pinMode(LedV, OUTPUT);
  pinMode(MotDir, OUTPUT);
  pinMode(MotEn, OUTPUT);
  pinMode(PerPwr, OUTPUT);
  analogReference(DEFAULT);
  digitalWrite(PerPwr, HIGH);      //Turne On The Periferical Power
  delay(500);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.createChar(6, CharV);
  lcd.createChar(7, Char10);
  Serial.begin(115200);
  Serial.println("OdlClockV2");
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(4 , 0);
  lcd.print("Msystem");
  lcd.setCursor(1, 1);
  lcd.print("Old Clock V2.0");
  delay(1000);
  lcd.clear();
  lcd.setBacklight(LOW);
  MotorSpeed = EEPROM.read(M_MotSpeed);
  TwlR_On = EEPROM.read(M_TwlR_On);
  TwlR_Off = EEPROM.read(M_TwlR_Off);
  HMec = EEPROM.read(M_HMec);
  MMec = EEPROM.read(M_MMec);
  EpromAdd = EEPROM.read(M_EpromAdd1);
  EpromAdd = (EpromAdd << 8) + EEPROM.read(M_EpromAdd);
  EpromAdd += 10;
  digitalWrite(MotDir , EEPROM.read(M_MDir));
  VSensLim = EEPROM.read(M_VSensLim);


  // EpromAdd = 0;

  if (EpromAdd < LowEpromLim) EpromAdd = LowEpromLim;
  if (EepromWipe) {
    Serial.println("EEPROM Wipeing");
    lcd.setCursor(1 , 0);
    lcd.print("EEPROM Wipeing");
    for (j = 0; j < 10; j++) AllBuff[j] = 0;
    AllBuff[7] = '#';
    for (j = LowEpromLim; j <= HiEpromLim; j += 10)  EEpromWriteBuff(EEPROM_ADDR , j, &AllBuff[0], 10);
    EEPROM.write(M_EpromAdd, 0);
    EEPROM.write(M_EpromAdd1, 0);
    EpromAdd = LowEpromLim;
  }
  if (EepromRead) {
    Serial.println("EEPROM read Mesage");
    for (j = LowEpromLim; j <= HiEpromLim; j += 10) {
      EEpromReadBuff(EEPROM_ADDR , j, &AllBuff[0], 10);
      sprintf(buffer, "%02d;%02d/%02d/%02d;%02d:%02d:%02d;%c;%02d;%02d", ((j - LowEpromLim) / 10), AllBuff[2], AllBuff[1], AllBuff[0], AllBuff[4], AllBuff[5], AllBuff[6], AllBuff[7], AllBuff[8], AllBuff[9]);
      Serial.println(buffer);
    }
  }

  if (! GetDateTime(&DataTime[0], 6)) {
    if (FDebug) Serial.println("RTC is NOT running!");
    Pattern = Pattern_All3;
    for (i = 0; i <= 6; i++) AllBuff[i] = 99;
    AllBuff[7] =  'A';
    AllBuff[8] = RTC_NOT_RUN;
    AllReady = 1;
  }
  else {
    for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
    AllBuff[7] = 'E';
    AllBuff[8] = START_UP;
    AllReady = 1;
    Pattern = Pattern_No_All;
  }
  //TimeRMot =  millis();
  TimeRMot =  ((millis() + TRMot) - (DataTime[6] * 1000)); //To sync motor revolution with RTC
  //HMec = DataTime[4];
  //MMec = DataTime[5];

}



void Debug() {
  digitalWrite(LedV, !(digitalRead(LedV)));
  //  Serial.println("Debug Programma");
  //  Serial.print("Pattern");
  //  Serial.println(Pattern);
  //  Serial.print("VSens");
  //  Serial.println((analogRead(VSens) >> 2), DEC);
  //  Serial.print("MenuPg");
  //  Serial.println(Menu, DEC);
  //  Serial.print("Edit Mod");
  //  Serial.println(EditMode, DEC);
  //  Serial.print("InitEdit");
  //  Serial.println(InitEdit, DEC);
  //  Serial.print("Cursor");
  //  Serial.println(Cursor, DEC);
  Serial.print("HMec ");
  Serial.print(HMec, DEC);
  Serial.print("  ");
  Serial.println(DataTime[4], DEC);
  Serial.print("MMec ");
  Serial.print(MMec, DEC);
  Serial.print("  ");
  Serial.println(DataTime[5], DEC);
  Serial.print("Fase CTRL  ");
  Serial.println(digitalRead(FaseCTRL), DEC);
  //Serial.print("VSensVal   ");
  //Serial.println(VSensVal, DEC);
  //Serial.print("VSensValOld   ");
  //Serial.println(VSensValOld, DEC);
  //Serial.println(analogRead(VSens));
}

char ButtonState(char PinN, long *Time) {

  if ((*Time == 0) && (digitalRead(PinN) == 0)) *Time = millis();
  if (digitalRead(PinN) && (*Time)) {
    if (millis() >= EntPatt  + *Time) {
      //if (FDebug) Serial.print("2");
      *Time = 0;
      return 2;

    }
    if (millis() >= SelPatt  + *Time) {
      *Time = 0;
      //if (FDebug) Serial.print("1");
      return 1;
    }
  }
  else return 0;
}



byte DecToBcd(byte val) {
  return (((val / 10) << 4) + (val % 10));
}

byte BcdToDec(byte val) {
  return (((val >> 4) * 10) + (val & 0b1111) );
}


boolean GetDateTime(uint8_t *Array, char Len) {
  Wire.beginTransmission(DS1307_ADDR);			// init the transmission starting from the address 0x00
  Wire.write(0x00);
  Wire.endTransmission();                // requires 7 bytes to the devicese with the address indicated the DS1307 uses 56 bits to record the date / time
  Wire.requestFrom(DS1307_ADDR, 7);
  if (Wire.available())
  {
    *(Array + 6) = BcdToDec(Wire.read());
    *(Array + 5) = BcdToDec(Wire.read());
    *(Array + 4) = BcdToDec(Wire.read() & 0b111111); 	// 24 hours mode I consider the first 6 bits
    *(Array + 3) = Wire.read(); 						// I do not need to convert (Range da 1 a 7 => 3 bit)
    *(Array + 2) = BcdToDec(Wire.read());
    *(Array + 1) = BcdToDec(Wire.read());
    *Array = BcdToDec(Wire.read());
    return true;
  }
  return false;
}

void SendDateTime(uint8_t *Array) {
  Wire.beginTransmission(DS1307_ADDR); 					// the first byte sent establishes the initial register on which to write
  Wire.write(0x00);
  for ( i = 7; i != 0; i--) {
    Wire.write(DecToBcd(*(Array + i - 1)));
  }
  Wire.write(0x00);
  Wire.endTransmission();
}

byte readByte() {
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

boolean CtrlData(byte dd, byte mm, byte yy) {
  uint8_t GGMese[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if ((mm < 1) || (mm > 12)) return false;						 // Is not a mounth
  if (yy % 4 == 0) GGMese[1] = 29; 								 // leap year
  if (dd < 1 || dd > GGMese[mm - 1]) return false;
  return true;
}

void EEpromWriteBuff( int deviceaddress, int eeaddresspage, byte* buffer, int length ) {
  NotAligLengt = 0;
  byte c = 0;
  EpromPageOffset = eeaddresspage % EepromPageSize;
  if (EpromPageOffset > 0)  {
    NotAligLengt = EepromPageSize - EpromPageOffset;
    if (length < NotAligLengt) NotAligLengt = length;
    EEpromWrite(deviceaddress , eeaddresspage , buffer, NotAligLengt);
    length -= NotAligLengt;
  }
  if (length > 0) {
    eeaddresspage += NotAligLengt;
    buffer += NotAligLengt;
    EEpromWrite(deviceaddress , eeaddresspage , buffer, length);
  }
}
void EEpromWrite( int deviceaddress, int eeaddresspage, byte*buffer, int length ) {
  byte c = 0;
  Wire.beginTransmission(deviceaddress);
  Wire.write(eeaddresspage >> 8); // MSB
  Wire.write(eeaddresspage & 0xFF); // LSB
  for ( c = 0; c < length ; c++) Wire.write(*(buffer + c));
  Wire.endTransmission();
  delay(10);

}


void EEpromReadBuff( int deviceaddress, int eeaddress, byte* buffer, int length ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write(eeaddress >> 8); // MSB
  Wire.write(eeaddress & 0xFF); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, length);
  int c = 0;
  for ( c = 0; c < length; c++ )
    if (Wire.available()) {
      (*(buffer + c)) = Wire.read();
    }


}


void loop() {

  if ((AllReady) && (SystemLog)) {
    EEpromWriteBuff(EEPROM_ADDR, EpromAdd , &AllBuff[0], 10);
    EEPROM.write(M_EpromAdd, EpromAdd);
    EEPROM.write(M_EpromAdd1, (EpromAdd >> 8));
    EpromAdd += 10;
    if (EpromAdd >= HiEpromLim) EpromAdd = LowEpromLim;
    if (EpromAdd < LowEpromLim) EpromAdd = LowEpromLim;
    AllReady = 0;
  }

  if ((SvTShDw) && (millis() > TimeSvTShDw) && digitalRead(PerPwr))  {
    digitalWrite(PerPwr, LOW);
    if (FDebug) Serial.println("Per PWR Off");
    while (1) {
      VSensVal = ((analogRead(VSens) * 10) / 68);
      if (VSensVal > VSensLim + 20)   resetFunc();
      delay(500);
      digitalWrite(LedR, (digitalRead(LedR) ^ 1));
    }
  }

  //  if (Serial.available()) {
  //    SerAll[SerCount] = Serial.read();
  //    SerCount++;
  //    if (SerCount >= SerAllMes) {
  //      Serial.println("OK");
  //      sprintf(buffer, "%c;%02d;%02d" , SerAll[0], SerAll[1], SerAll[2]);
  //      Serial.println(buffer);
  //       SerCount=0;
  //       for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
  //        AllBuff[7] = SerAll[0];
  //        AllBuff[8] = SerAll[1];
  //        AllBuff[9] = SerAll[2];
  //        AllReady = 1;
  //        Pattern = Pattern_All1;
  //    }
  //  }

  if (millis() >= TimeBlink) {						//Led Program state
    digitalWrite(LedR, (digitalRead(LedR) ^ 1));
    if ((Pattern != Pattern_No_All) && !PattAllOn) {
      TimePatt = (millis() + TPatAll);
      PattAllOn = 1;
    }
    else TimeBlink = (millis() + Pattern);

    if (millis() > TimePatt) {
      Pattern = Pattern_No_All;
      PattAllOn = 0;
    }

  }
  if (millis() >= TimeI2cTest) {
    Wire.beginTransmission(LCD_I2C_ADDR);
    if (Wire.endTransmission()) {
      if (FDebug) Serial.println("Lcd Bus Fault");
      if (!LcdAll ) {
        for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
        AllBuff[7] = 'A';
        AllBuff[8] = LCD_BUS_FAULT;
        AllReady = 1;
        Pattern = Pattern_All2;
        LcdAll = 1;
      }
      goto Out;
    }
    LcdAll = 0;
    Wire.beginTransmission(DS1307_ADDR);
    if (Wire.endTransmission()) {
      if (FDebug) Serial.println("RTC Bus Fault");
      if (!RtcAll ) {
        for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
        AllBuff[7] = 'A';
        AllBuff[8] = RTC_BUSS_FAULT;
        AllReady = 1;
        Pattern = Pattern_All2;
        RtcAll = 1;
      }
      goto Out;
    }
    RtcAll = 0;
    Wire.beginTransmission(EEPROM_ADDR);
    if (Wire.endTransmission()) {
      if (FDebug) Serial.println("Eeprom Bus Fault");
      if (!EpromAll ) {
        for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
        AllBuff[7] = 'A';
        AllBuff[8] = EPR_BUSS_FAULT;
        AllReady = 1;
        Pattern = Pattern_All2;
        EpromAll = 1;
      }
      goto Out;
    }
    EpromAll = 0;

Out:
    TimeI2cTest = millis() + TI2cTest;
  }


  VSensVal = ((analogRead(VSens) * 10) / 68); //61);
  //VSensLim=VSensVal-20;
  //VSensVal = 10 + VSensLim;
  if ((VSensVal < VSensLim) && !SvTShDw) {
    EEPROM.write(M_MMec , MMec);
    EEPROM.write(M_HMec , HMec);
    EEPROM.write(M_MDir , digitalRead(MotDir));
    EEPROM.write(M_EpromAdd, EpromAdd);
    EEPROM.write(M_EpromAdd1, (EpromAdd >> 8));
    for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
    AllBuff[7] = 'A';
    AllBuff[8] = SAVE_SHUTDOWN;
    AllReady = 1;
    Pattern = Pattern_All2;
    SvTShDw = 1;                        //Save To ShutDown
    TimeSvTShDw = millis() + TSvTShDw;
    if (FDebug) Serial.println("Salvato");
  }


  if ((millis() >= TimeRMot ) && !SvTShDw) {
    // TimeRMot =  (millis() + TRMot);
    TimeRMot =  ((millis() + TRMot) - (DataTime[6] * 1000));
    if (((HMec <= 23 ) && (MMec <= 59)) && ((HMec > 10) && (digitalRead(FaseCTRL) == 0))) {
      if (FDebug) Serial.println("Anticipo");
      MMec++;
      if (MMec >= 60) {
        MMec = 0;
        HMec++;
      }
      if (HMec >= 24) HMec = 0;
      if (FDebug) Serial.println("Fase Ok");
      TimeRMot =  millis();
      //EEPROM.write(M_MMec , MMec);
      //EEPROM.write(M_HMec , HMec);
      if (MClAdAll) {
        if (FDebug) Serial.println("MCL_ADVANCE");
        for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
        AllBuff[7] = 'A';
        AllBuff[8] = MCL_ADVANCE;
        AllReady = 1;
        Pattern = Pattern_All1;
        MClAdAll = 1;
      }
    }
    else {
      if (!HMec && !MMec && digitalRead(FaseCTRL) && !MoveMot) {
        MoveMot = 1;
        TimeMotSpeed = ( millis() + (MotorSpeed * 10));
        TimeRMot = (millis() + (MotorSpeed * 20));
        digitalWrite (MotEn , HIGH);
        if (MClDlAll) {
          if (FDebug) Serial.println("MCL_DELAY");
          for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
          AllBuff[7] = 'A';
          AllBuff[8] = MCL_DELAY;
          AllReady = 1;
          Pattern = Pattern_All1;
          MClDlAll = 1;
        }
      }
      else {
        if (((HMec != DataTime[4]) || (MMec != DataTime[5])) && (MoveMot == 0)) {
          if (FDebug) Serial.println("Recupero");
          TimeMotSpeed = ( millis() + (MotorSpeed * 10));
          TimeRMot = (millis() + (MotorSpeed * 20));
          if ((HMec == DataTime[4]) && (MMec == (DataTime[5] - 1))) TimeRMot =  ((millis() + TRMot) - (DataTime[6] * 1000));
          digitalWrite (MotEn , HIGH);
          MoveMot = 1;
          MClAdAll = MClDlAll = 0;
        }
      }
    }
  }

  if ((MoveMot == 1) && !SvTShDw) {
    // if ((MoveMot == 1) ) {
    if (millis() >= TimeMotSpeed ) {
      if (FDebug) Serial.println("motore");
      digitalWrite(MotEn, LOW);
      digitalWrite(MotDir, ((digitalRead(MotDir) ^ 1)));
      MMec++;
      if (MMec >= 60) {
        MMec = 0;
        HMec++;
      }
      if (HMec >= 24) HMec = 0;
      //EEPROM.write(M_MMec , MMec);
      //EEPROM.write(M_HMec , HMec);
      //EEPROM.write(M_MDir , digitalRead(MotDir));
      MoveMot = 0;
    }
  }
  if (millis() > TimeTwl) {
    TwlAve += (analogRead(LDR) >> 2);
    Sample += 1;
  }

  if (Sample >= SampleN) {
    TwlVal = TwlAve / SampleN;
    TimeTwl = (millis() + TTwl);
    Sample = 0;
    TwlAve = 0;
    if (TwlVal >= TwlR_On) digitalWrite(Light, HIGH);
    if (TwlVal < TwlR_Off) digitalWrite(Light, LOW);
  }

  if ((millis() > TimeDeb) && SDebug) {
    TimeDeb = (millis() + TDebug);
    Debug();

  }

  if ((millis() > TimeLcd) && (Menu == 0)) {
    TimeLcd = (millis() + TLcd);
    GetDateTime(&DataTime[0], 6);
    lcd.clear();
    sprintf(buffer,  "%02d/%02d/%d", DataTime[2], DataTime[1], DataTime[0]);
    lcd.setCursor(1, 0);
    lcd.print( buffer );
    //buffer[10] = 0;
    sprintf(buffer,  "%02d:%02d:%02d", DataTime[4], DataTime[5], DataTime[6]);
    lcd.setCursor(1, 1);
    lcd.print( buffer );
    lcd.setCursor(11, 0);
    lcd.print("LSens");
    lcd.setCursor(11, 1);
    lcd.print(TwlVal, DEC);
  }

  EditState = ButtonState(EdButt, &TimeEdButt);
  UpButtState = ButtonState(UpButt, &TimeUpButt);
  DwButtState = ButtonState(DwButt, &TimeDwButt);
  if (( EditState) || (UpButtState) || (DwButtState)) {
    TimeMenu =  (millis() + TExitMenu);
    lcd.setBacklight(HIGH);
  }
  if (millis() > TimeMenu )  {
    Menu = 0;
    EditMode = 0;
    InitEdit = 0;
    Cursor = 0;
    lcd.noBlink();
    lcd.setBacklight(LOW);
  }
  if ((EditState == 1) && (EditMode == 0)) Menu += 1;
  if ((EditState == 2) && Menu && (EditMode == 1)) {        //Parameter saving and date-time consistency check
    if (Menu == 1) {
      if (CtrlData(SetDataTime[2], SetDataTime[1], SetDataTime[0])) {  //Coherent date control
        SendDateTime(&SetDataTime[0]);
        goto SaveOk;
      }
      else goto SaveFault;
    }
    if (Menu == 2) {
      MotorSpeed = SetData;
      EEPROM.write(M_MotSpeed, MotorSpeed);
      goto SaveOk;
    }
    if (Menu == 3) {
      if (SetData > (TwlR_Off + TwlRDelta)) {
        TwlR_On = SetData;
        EEPROM.write(M_TwlR_On, TwlR_On);
        goto SaveOk;
      }
      else {
        goto SaveFault;
      }
    }
    if (Menu == 4) {
      if (SetData < (TwlR_On - TwlRDelta)) {
        TwlR_Off = SetData;
        EEPROM.write(M_TwlR_Off, TwlR_Off);
        goto SaveOk;
      }
      else {
        goto SaveFault;
      }
    }

    if (Menu == 5) {
      if (SetData < (VSensVal - 10)) {
        VSensLim = SetData;
        EEPROM.write(M_VSensLim, VSensLim);
        goto SaveOk;
      }
      else {
        goto SaveFault;
      }
    }


SaveOk:
    lcd.setCursor(14, 1);
    lcd.print("Ok");
    if (FDebug) Serial.print("OK");
    //delay(1000);
    TimeLcd = (millis() + 1000);       //delay the LCD refresh
    for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
    AllBuff[7] = EVENT;
    AllBuff[8] = CHANGE_DATA;
    AllReady = 1;
    goto Exit;
SaveFault:
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Errore Data");
    if (FDebug) Serial.print("Errore Data");
    //delay(1500);
    TimeLcd = (millis() + 1500);
    for (i = 0; i <= 6; i++) AllBuff[i] = DataTime[i];
    AllBuff[7] = ALARM;
    AllBuff[8] = DATA_FAULT;
    AllReady = 1;
    Pattern = Pattern_All1;
Exit:
    SetData = 0;
    SetDataOld = 0;
    EditMode = 0;
    Menu = 0;
    MenuOld = 0;
    InitEdit = 0;
    Cursor = 0;
    lcd.noBlink();
  }
  if ((EditState == 2) && Menu && (EditMode == 0)) EditMode = 1;
  if (Menu >= MenuPage)Menu = 0;
  if ((Menu != MenuOld) && (EditMode == 0)) {       //Menu page update
    lcd.clear();
    lcd.setCursor(0, 0);
    //if (FDebug) Serial.println(Menu, DEC);
    switch (Menu) {
      case 1:
        lcd.print("Imposta data ora");
        break;
      case 2:
        lcd.print("Velocita motore");
        break;
      case 3:
        lcd.print("Crepuscolare On");
        break;
      case 4:
        lcd.print("Crepuscolare Off");
        break;
      case 5:
        lcd.print("CTRL Tensione");
        break;
      case 6:
        lcd.print("System LOG");
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
      if (UpButtState) {
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
      if (DwButtState) {
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
            if (SetDataTime[0] > 0) SetDataTime[0] -= 1;
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
            if (SetDataTime[6] > 0) SetDataTime[6] -= 1;
            sprintf(buffer,  "%02d" , SetDataTime[6]);
            lcd.print(buffer);
            lcd.setCursor(10, 1);
            break;
        }
      }
    }
  }
  if ((Menu == 2) && (EditMode)) { //Menu MotorSpeed
    if (InitEdit == 0) {
      //lcd.clear();
      SetData = MotorSpeed;
      lcd.setCursor(0, 1);
      lcd.print( SetData, DEC);
      lcd.print(" ->");
      lcd.blink();
      InitEdit = 1;
    }
    if (InitEdit) {
      if ((UpButtState) && (SetData < UpLimMS))SetData += 1;
      if ((DwButtState) && (SetData > DwLimMS))SetData -= 1;
      if (SetData != SetDataOld) {
        SetDataOld = SetData;
        lcd.setCursor(7, 1);
        lcd.print( SetData, DEC);
      }
    }
  }// End Motor Speed

  if ((Menu == 3) && (EditMode)) { //Twilight Relays On
    if (InitEdit == 0) {
      //lcd.clear();
      SetData = TwlR_On;
      lcd.setCursor(0, 1);
      lcd.print( SetData, DEC);
      lcd.print(" ->");
      lcd.blink();
      InitEdit = 1;
    }
    if (InitEdit) {
      if ((UpButtState) && (SetData < UpLimTwlOn))SetData += 1;
      if ((DwButtState) && (SetData > DwLimTwlOn))SetData -= 1;
      if (SetData != SetDataOld) {
        SetDataOld = SetData;
        lcd.setCursor(7, 1);
        lcd.print( SetData, DEC);
      }
    }
  }// End Twilight Relays On

  if ((Menu == 4) && (EditMode)) { //Twilight Relays Off
    if (InitEdit == 0) {
      //lcd.clear();
      SetData = TwlR_Off;
      lcd.setCursor(0, 1);
      lcd.print( SetData, DEC);
      lcd.print(" ->");
      lcd.blink();
      InitEdit = 1;
    }
    if (InitEdit) {
      if ((UpButtState) && (SetData < UpLimTwlOff))SetData += 1;
      if ((DwButtState) && (SetData > DwLimTwlOff))SetData -= 1;
      if (SetData != SetDataOld) {
        SetDataOld = SetData;
        lcd.setCursor(7, 1);
        lcd.print( SetData, DEC);
      }
    }
  }// End Twilight Relays On

  if ((Menu == 5) && (EditMode)) {      //Vsens Value
    if (InitEdit == 0) {
      SetData = VSensLim;
      lcd.setCursor(3, 1);
      lcd.write(byte(6));
      lcd.write(byte(7));
      lcd.setCursor(6, 1);
      lcd.print( VSensLim, DEC);
      lcd.setCursor(9, 1);
      lcd.print("->");
      lcd.blink();
      SetDataOld = VSensValOld = 0;
      InitEdit = 1;
    }
    if (InitEdit) {
      VSensValOld += 1;
      if (VSensValOld >= 3000) {
        lcd.noBlink();
        lcd.setCursor(0, 1);
        lcd.print( VSensVal, DEC);
        lcd.setCursor(11, 1);
        lcd.blink();
        VSensValOld = 0;
      }
      if ((UpButtState) && (SetData < UpLimVSens))SetData += 1;
      if ((DwButtState) && (SetData > DwLimVSens))SetData -= 1;
      if (SetData != SetDataOld) {
        SetDataOld = SetData;
        lcd.setCursor(11, 1);
        lcd.print( SetData, DEC);
      }
    }
  }
  if ((Menu == 6) && (EditMode)) { //Log page
    if (InitEdit == 0) {
      lcd.clear();
      SetData = (EpromAdd - 10);
      InitEdit = 1;
    }
    if (InitEdit) {
      if (UpButtState)SetData += 10;
      if (DwButtState)SetData -= 10;
      if (SetData > HiEpromLim) SetData = LowEpromLim;
      if (SetData < LowEpromLim) SetData = HiEpromLim;
      if (SetData != SetDataOld) {
        SetDataOld = SetData;
        EEpromReadBuff(EEPROM_ADDR, SetData, &AllBuff[0], 10);
        lcd.clear();
        sprintf(buffer,  "%02d/%02d/%d", AllBuff[2], AllBuff[1], AllBuff[0]);
        lcd.setCursor(1, 0);
        lcd.print( buffer );
        sprintf(buffer,  "%02d:%02d:%02d", AllBuff[4], AllBuff[5], AllBuff[6]);
        lcd.setCursor(1, 1);
        lcd.print( buffer );
        lcd.setCursor(11, 0);
        lcd.print(((SetData - LowEpromLim) / 10), DEC);
        lcd.setCursor(11, 1);
        lcd.write(AllBuff[7]);
        lcd.print(AllBuff[8], DEC);
      }
    }
  }
}

