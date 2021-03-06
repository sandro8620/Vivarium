//////////////////////////////////////////////////////////////////////////////////////////////////////
// Vivarium Management Controller w/ 7" touchscreen Interface                                       //
// Written and coded by David Sease, aka Bigsease30 and ghlawrence2000 on arduino.cc!               //
// Much code was swiped, modified, and integrated or otherwise inspired from other public works     //
//                                                                                                  //
// All code is public domain, feel free to use, abuse, edit, and share                              //
// Written for Arduino Mega 2560                                                                    //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     VERSION:  04/02/15 17:40GMT                                  //
//                                        Development Version 16                                    //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         CODE ORDER:                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//    Declare EEPROM useage                                                                         //
//    Declare Libraries needed                                                                      //
//    Compile time options                                                                          //
//    Initiate Screen, Touch, Imaging and Fonts                                                     //
//    Define Pins                                                                                   //
//    Global variables & setup                                                                      //
//    Main loop                                                                                     //
//    Routines to draw every screen                                                                 //
//    Routine to handle touch events                                                                //
//    Other supporting routines                                                                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 EEPROM locations (saved settings)                                //
//////////////////////////////////////////////////////////////////////////////////////////////////////
// SPACE //         DESCRIPTION              // DEFAULTS                                            //
//     0 //  ID     : 32                     // 32 if previously ran                                //
//     1 //  screen : return home            // 1 min                                               //
//     2 //  screen : brightness if no dim   // 16 max                                              //
//     3 //  screen : AutoDim level          // 1                                                   //
//     4 //  screen : AutoDim seconds        // 10 sec                                              //
//     5 //  Heater : Float byte 0           //\                                                    //
//     6 //  Heater : Float byte 1           //  _ Initial value                                    //
//     7 //  Heater : Float byte 2           //    42.9F                                            //
//     8 //  Heater : Float byte 3           ///                                                    //
//     9 //  Fan    : Float byte 0           //\                                                    //
//    10 //  Fan    : Float byte 1           //  _ Initial value                                    //
//    11 //  Fan    : Float byte 2           //    102.9F                                           //
//    12 //  Fan    : Float byte 3           ///                                                    //
//    13 //  Lights1: On1Hr                  // 8 am  //Light 1 ON (Day Light)                      //
//    14 //  Lights1: On1Min                 // 15 min                                              //
//    15 //  Lights1: Off1Hr                 // 20 pm //Light 1 OFF                                 //
//    16 //  Lights1: Off1Min                // 30 min                                              //
//    17 //  Lights2: On2Hr                  // 20 pm //Light 2 ON (Night Light)                    //
//    18 //  Lights2: On2Min                 // 30 min                                              //
//    19 //  Lights2: Off2Hr                 // 8 am //Light 2 OFF                                  //
//    20 //  Lights2: Off2Min                // 15 min                                              //
//    21 //  Fog    : Fog.Enable             // ( F0 = 1 enable, 2 disable, FF = 1 & 2 enable )     //
//    22 //  Fog    : Fog.On1Hr              //                                                     //
//    23 //  Fog    : Fog.On1Min             //                                                     //
//    24 //  Fog    : Fog.Dur1Min            //                                                     //
//    25 //  Fog    : Fog.Dur1Sec            //                                                     //
//    26 //  Fog    : Fog.On2Hr              //                                                     //
//    27 //  Fog    : Fog.On2Min             //                                                     //
//    28 //  Fog    : Fog.Dur2Min            //                                                     //
//    29 //  Fog    : Fog.Dur2Sec            //                                                     //
//    30 //  Fog    : Fog.OnDay              //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x3c=Tue-Fri       //
//    31 //  Fog    : Fog.OnDay2             //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x3c=Tue-Fri       //
//    32 //  Mist1&2: Mist.Enable            // ( F0 = 1 enable, 2 disable, FF = 1 & 2 enable )     //
//    33 //  Mist1  : Mist.On1Hr             //                                                     //
//    34 //  Mist1  : Mist.On1Min            //                                                     //
//    35 //  Mist1  : Mist.Dur1Min           //                                                     //
//    36 //  Mist1  : Mist.Dur1Sec           //                                                     //
//    37 //  Mist2  : Mist.On2Hr             //                                                     //
//    38 //  Mist2  : Mist.On2Min            //                                                     //
//    39 //  Mist2  : Mist.Dur2Min           //                                                     //
//    40 //  Mist2  : Mist.Dur2Sec           //                                                     //
//    41 //  Mist2  : Mist.OnDay             //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x70 =Thu-Sat      //
//    42 //  Mist2  : Mist.OnDay             //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x70 =Thu-Sat      //
//    43 //  Mist3&4: Mist2.Enable           // ( F0 = 3 enable, 4 disable, FF = 3 & 4 enable )     //
//    44 //  Mist3  : Mist2.On3Hr            //                                                     //
//    45 //  Mist3  : Mist2.On3Min           //                                                     //
//    46 //  Mist3  : Mist2.Dur3Min          //                                                     //
//    47 //  Mist3  : Mist2.Dur3Sec          //                                                     //
//    48 //  Mist4  : Mist2.On3Hr            //                                                     //
//    49 //  Mist4  : Mist2.On3Min           //                                                     //
//    50 //  Mist4  : Mist2.Dur3Min          //                                                     //
//    51 //  Mist4  : Mist2.Dur3Sec          //                                                     //
//    52 //  Mist4  : Mist2.OnDay            //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x0F =Sun-Wed      //
//    53 //  Mist4  : Mist2.OnDay2           //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x0F =Sun-Wed      //
//    54 //  Fan    : Fan.Enable             // ( F0 = 1 enable, 2 disable, FF = 1 & 2 enable )     //
//    55 //  Fan    : Fan.On1Hr              //                                                     //
//    56 //  Fan    : Fan.On1Min             //                                                     //
//    57 //  Fan    : Fan.Dur1Min            //                                                     //
//    58 //  Fan    : Fan.Dur1Sec            //                                                     //
//    59 //  Fan    : Fan.On2Hr              //                                                     //
//    60 //  Fan    : Fan.On2Min             //                                                     //
//    61 //  Fan    : Fan.Dur2Min            //                                                     //
//    62 //  Fan    : Fan.Dur2Sec            //                                                     //
//    63 //  Fan    : Fan.OnDay              //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x0F =Sun-Wed      //
//    64 //  Fan    : Fan.OnDay2             //  0/Sat/Fri/Thu/Wed/Tue/Mon/Sun   0x0F =Sun-Wed      //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Decare Libraries                                                //
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>                  // needed by tons of stuff  <== Davids excellent description!!   //
#include <EEPROM.h>                // used to store and retrieve settings from memory               //
#include <UTFT.h>                  // used to interface with the TFT display                        //
#include <UTouch.h>                // used to interface with the touch controller on the TFT display//
#include <SdFat.h>                 // used to access the SD card                                    //
#include <UTFT_SdRaw.h>            // used to read .raw images from the SD card                     //
#include <RTClib.h>                // RTC library (software or hardware capable)                    //
#include <Time.h>                  // allows conversion to UNIX time for easier date/time math      //
#include <TimeAlarms.h>            // used to power schedules                                       //
#include <OneWire.h>               // library to communicate with the DallasTemperature sensor      // 
#include <DallasTemperature.h>     // library for the Temp sensor itself                            //
#include <dht.h>                   // Rob Tillaart's improved humidity library                      //
#include "includes.h"              // Workaround for quirk in Arduino IDE                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Compile time options                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define DS1307   1 // <====== 1 for DS1307, 0 for Software                                          //
#define fastest  1 // <====== 1 = MAX speed all screens in own page / 0 = 2 Screens share a page... //
#define debug    1 // <====== 1 = Serial output enabled                                             //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                           Initiate Screen, Touch, Imaging and Fonts                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////
UTFT myGLCD(CTE70CPLD, 38, 39, 40, 41); // start up an instance of the TFT screen                   //
UTouch  myTouch( 6, 5, 4, 3, 2);        // start up an instance of for touch                        //
UTFT_SdRaw myFiles(&myGLCD);            // start up an instance to read images from SD              //
SdFat sd;                               // start up as instance of SD                               //
extern uint8_t SmallFont[];                                                                         //
extern uint8_t Sinclair_S[];                                                                        //
extern uint8_t arial_bold[];                                                                        //
extern uint8_t Ubuntubold[];                                                                        //
extern unsigned int frog[0x654];
extern unsigned int smfrog[0x3B1];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         Define pins                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//           Declare Pins and binary bits for Relays (analog to save digital pins)                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define FAN1        A0                                                                              //
#define MISTING1    A1                                                                              //
#define FOGGER1     A2                                                                              //
#define TEMP1       A3                                                                              //
#define LIGHTS2     A4                                                                              //    
#define LIGHTS1     A5                                                                              //                     
#define pwrFan1      0   // binary  1                                                               //  
#define pwrMisting1  1   // binary  2                                                               //
#define pwrFogger1   2   // binary  4                                                               //
#define pwrTemp1     3   // binary  8                                                               //
#define pwrLight2    4   // binary 16                                                               //
#define pwrLight1    5   // binary 32                                                               //
byte Relay = 0x00, prevRelay = 0x40;                                                                //
/*struct PWR                                                                                        //
{                                                                                                   //
  byte pwrLight1;                                                                                   //
  byte pwrLight2;                                                                                   //
  byte pwrTemp1;                                                                                    //
  byte pwrFogger1;                                                                                  //
  byte pwrMisting1;                                                                                 //
  byte pwrAUX1;                                                                                     //
}*/                                                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         Pins for sensors                                         //
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define ONE_WIRE_BUS     8                                                                          //
//#define TEMPERATURE_PRECISION 9           // Unused ????                                          //
#define DHTPIN           9                                                                          //
#define SD_CHIP_SELECT  53                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    Humidity and Temperature                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup our humidity sensor                                                                        //
dht DHT;                                                                                            //
// Setup oneWire instance to communicate with any OneWire devices                                   //
OneWire oneWire(ONE_WIRE_BUS);                                                                      //
// Pass our oneWire reference to Dallas Temperature.                                                //
DallasTemperature sensors(&oneWire);                                                                //
//DeviceAddress tempLeft, tempMiddle, tempRight;                                                    //
//DeviceAddress tempLeft = { 0x28, 0x24, 0x18, 0x5D, 0x06, 0x00, 0x00, 0xA2 };                      //
//DeviceAddress tempMiddle = { 0x28, 0x39, 0x0B, 0x5C, 0x06, 0x00, 0x00, 0x0E };                    //
//DeviceAddress tempRight = { 0x28, 0xED, 0x16, 0x5C, 0x06, 0x00, 0x00, 0x86 };                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           Time                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////////////
#if DS1307 ==1                                                                                      //
RTC_DS1307 rtc;                                                                                     //
#else                                                                                               //
RTC_Millis rtc;                                                                                     //
#define TIME_HEADER  "T"   // Header tag for serial time sync message                               //
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message                     //
#endif                                                                                              //
boolean updateTime = false; // keep track of when to udpate the clock                               //
// days and month character strings for displaing at the top of the screen                          //
const char *Day[] = {
  "", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};                                                                                                  //
const char *Month[] = {
  "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};                                                                                                  //
tmElements_t tmpRTC, prevRTC, lastLoopRTC;                                                          //
unsigned long tempTime;                                                                             //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Various timings to keep track of                                //
//////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long prevMillisTouch = 0; // track time between touches                                    //
unsigned long prevMillis5sec = 0; // track 5 seconds for refreshing clock and temp                  //
unsigned long millisDim = 0; // used for brightness adjustment                                      //
unsigned long millisHome = 0; // used for returning home after configured time                      //
unsigned long TouchRepeatDelay = 500; // millis                                                     //
unsigned long tmpTouchRepeatDelay = 500; //millis                                                   //
unsigned long humidTime = 0; // 2 seconds minimum reading                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Various screen settings                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////////
byte HomeDelay;  // (Return Home) Minutes 0-59                                                      //
byte BackLight;  // (Bright) (not AutoDim) startup brightness to 100% 1-16                          //
byte AutoDim;    // (AutoDim Level) maximum brightness when dimmed 1-5                              //
byte TouchDelay; // (AutoDim Seconds) 0-59                                                          //
byte dispScreen = 1;  // Currently displayed screen, screens shown below                            //
// 1-home, 2-lights, , 3-temp, 4-fogger, 5-mister, 6-fan, 7-clock, 8-screen                         //
byte mistScreen = 1;                                                                                //
byte fanScreen = 1;                                                                                 //
byte fogScreen = 1;                                                                                 //
boolean BackLightTouch = true; // initial setting to allow the screen to stay on after boot         //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                               Scheduling and Alarm related variables                             //
//////////////////////////////////////////////////////////////////////////////////////////////////////
SCHEDULE Light, Fog, Mist, Mist2, Fan;                                                              //
SCHEDULE tempM1, tempM2, tempFan1;                                                                  //

float heater;    // = 35.9;                                                                         //
float fan;       // = 87.9;                                                                         //
float temp1 = 0.0, temp2 = 0.0, temp3 = 0.0, hum1 = 0.0;                                            //
//byte FogOn1Hr, FogOn1Min, FogDur1Min, FogDur1Sec;                                                 //
//byte FogOn2Hr, FogOn2Min, FogDur2Min, FogDur2Sec;                                                 //
//byte FogDay;                                                                                      //
//byte MistOn1Hr, MistOn1Min, MistDur1Min, MistDur1Sec;                                             //
//byte MistOn2Hr, MistOn2Min, MistDur2Min, MistDur2Sec;                                             //
//byte MistDay;                                                                                     //
//byte MistOn1Hr, MistOn1Min, MistDur1Min, MistDur1Sec;                                             //
//byte MistOn2Hr, MistOn2Min, MistDur2Min, MistDur2Sec;                                             //
//byte MistDay;                                                                                     //
//byte FanOn1Hr, FanOn1Min, FanDur1Min, FanDur1Sec;                                                 //
//byte FanOn2Hr, FanOn2Min, FanDur2Min, FanDur2Sec;                                                 //
//byte FanDay;                                                                                      //
//                                                                                                  //
#define Sun          0   // binary  1                                                               //  
#define Mon          1   // binary  2                                                               //
#define Tue          2   // binary  4                                                               //
#define Wed          3   // binary  8                                                               //
#define Thu          4   // binary 16                                                               //
#define Fri          5   // binary 32                                                               //
#define Sat          6   // binary 64                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      SETUP CODE                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
#if debug
  // start serial port
  Serial.begin(57600);
#endif
  // Set default values for the first ever run
  firstRunSetup();
  // get screen settings from eeprom
  HomeDelay     = EEPROM.read(1);
  BackLight     = EEPROM.read(2);
  AutoDim       = EEPROM.read(3);
  TouchDelay    = EEPROM.read(4);
  heater        = EEPROM.readFloat(5);
  fan           = EEPROM.readFloat(9);
  Light.On1Hr   = EEPROM.read(13);
  Light.On1Min  = EEPROM.read(14);
  Light.Dur1Min = EEPROM.read(15);
  Light.Dur1Sec = EEPROM.read(16);
  Light.On2Hr   = EEPROM.read(17);
  Light.On2Min  = EEPROM.read(18);
  Light.Dur2Min = EEPROM.read(19);
  Light.Dur2Sec = EEPROM.read(20);
  Fog.Enable    = EEPROM.read(21);
  Fog.On1Hr     = EEPROM.read(22);
  Fog.On1Min    = EEPROM.read(23);
  Fog.Dur1Min   = EEPROM.read(24);
  Fog.Dur1Sec   = EEPROM.read(25);
  Fog.On2Hr     = EEPROM.read(26);
  Fog.On2Min    = EEPROM.read(27);
  Fog.Dur2Min   = EEPROM.read(28);
  Fog.Dur2Sec   = EEPROM.read(29);
  Fog.OnDay     = EEPROM.read(30);
  Fog.OnDay2    = EEPROM.read(31);
  Mist.Enable   = EEPROM.read(32);
  Mist.On1Hr    = EEPROM.read(33);
  Mist.On1Min   = EEPROM.read(34);
  Mist.Dur1Min  = EEPROM.read(35);
  Mist.Dur1Sec  = EEPROM.read(36);
  Mist.On2Hr    = EEPROM.read(37);
  Mist.On2Min   = EEPROM.read(38);
  Mist.Dur2Min  = EEPROM.read(39);
  Mist.Dur2Sec  = EEPROM.read(40);
  Mist.OnDay    = EEPROM.read(41);
  Mist.OnDay2   = EEPROM.read(42);
  Mist2.Enable  = EEPROM.read(43);
  Mist2.On1Hr   = EEPROM.read(44);
  Mist2.On1Min  = EEPROM.read(45);
  Mist2.Dur1Min = EEPROM.read(46);
  Mist2.Dur1Sec = EEPROM.read(47);
  Mist2.On2Hr   = EEPROM.read(48);
  Mist2.On2Min  = EEPROM.read(49);
  Mist2.Dur2Min = EEPROM.read(50);
  Mist2.Dur2Sec = EEPROM.read(51);
  Mist2.OnDay   = EEPROM.read(52);
  Mist2.OnDay2  = EEPROM.read(53);
  Fan.Enable    = EEPROM.read(54);
  Fan.On1Hr     = EEPROM.read(55);
  Fan.On1Min    = EEPROM.read(56);
  Fan.Dur1Min   = EEPROM.read(57);
  Fan.Dur1Sec   = EEPROM.read(58);
  Fan.On2Hr     = EEPROM.read(59);
  Fan.On2Min    = EEPROM.read(60);
  Fan.Dur2Min   = EEPROM.read(61);
  Fan.Dur2Sec   = EEPROM.read(62);
  Fan.OnDay     = EEPROM.read(63);
  Fan.OnDay2    = EEPROM.read(64);
  ///////////////////////////////////////////////////////////////////////////////////////////
  //                           Start up DS18B20 Temp Sensors                               //
  sensors.begin();                                                                         //
  ///////////////////////////////////////////////////////////////////////////////////////////
#if debug
  // locate DS18B20 temperature devices on the bus
  Serial.print(F("Locating Dallas 1820 devices... "));
  Serial.print(F("Found "));
  Serial.print(sensors.getDeviceCount());
  Serial.println(F("."));
#endif
  ///////////////////////////////////////////////////////////////////////////////////////////
  //                                 Initiate the SD Card                                  //
  ///////////////////////////////////////////////////////////////////////////////////////////
#if debug
  Serial.println(F("Initialising SD card..."));
#endif
  bool mysd = 0;
  // see if the card is present and can be initialized:
  while (!mysd)
  {
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
#if debug
      Serial.println(F("Card failed, or not present"));
      Serial.println(F("Retrying...."));
#endif
    }
    else
    {
      mysd = 1;
#if debug
      Serial.println(F("Card initialised."));
#endif
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //                            Start screen functions                                                //
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  myGLCD.InitLCD();        // <= Dont need LANDSCAPE since is default
  myGLCD.setBrightness(0); // <= Backlight Off
  myGLCD.setWritePage(1);  // <= Select writepage 1
  myGLCD.clrScr();         // <= Clear writepage 1
  myGLCD.setDisplayPage(1); //<= Display writepage 1
  myGLCD.setBrightness(BackLight); //<= Turn on BackLight Max brightness
  myTouch.InitTouch();      //<= Dont need LANDSCAPE since is default
  myTouch.setPrecision(PREC_MEDIUM);
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //                              Start RTC                                                           //
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  Wire.begin();
#if(DS1307)
  rtc.begin(); // Start the Clock
  delay(250);
  if (! rtc.isrunning())
  {
    // If no RTC is installed, alert on serial
#if debug
    Serial.println(F("DS1307 is NOT running!"));
    Serial.println(F("Define DS1307 0!"));
#endif
  }
#else
  rtc.begin(DateTime(F(__DATE__), F(__TIME__))); // Start the Clock
#if debug
  Serial.println(F("Software RTC is running!"));
  Serial.println(F("Send sync message eg T1420722534 (Can type in serial monitor)"));
#endif
#endif
  setSyncProvider(syncProvider);// reference our syncProvider function instead of RTC_DS1307::get();
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Turns OFF all relays until called in code (NO MISTAKE, HIGH IS OFF, LOW IS ON)
  digitalWrite(LIGHTS1, HIGH);
  digitalWrite(LIGHTS2, HIGH);
  digitalWrite(TEMP1, HIGH);
  digitalWrite(FOGGER1, HIGH);
  digitalWrite(MISTING1, HIGH);
  digitalWrite(FAN1, HIGH);
  // Initialise the Arduino data pins for OUTPUT
  pinMode(LIGHTS1, OUTPUT);
  pinMode(LIGHTS2, OUTPUT);
  pinMode(TEMP1, OUTPUT);
  pinMode(FOGGER1, OUTPUT);
  pinMode(MISTING1, OUTPUT);
  pinMode(FAN1, OUTPUT);
  delay(250); //Check that all relays are inactive at Reset


  myGLCD.setWritePage(0);  //  <= Still displaying writepage 1
  myGLCD.clrScr();        //   <= Clear writepage 0

  // boot up logo
#if debug
  unsigned long performance = millis();
#endif
  myFiles.loadcpld(230, 40, 378, 268, "Logo.raw", 0, 4);  // <==== Write to writepage 0
  myFiles.loadcpld(340, 360, 149, 47, "Copy.raw", 0, 6);  // <==== Write to writepage 0
  myGLCD.setDisplayPage(0);                               // <==== Display writepage 0
  myFiles.loadcpld(0, 0, 800, 480, "1Home.raw", 1, 2);
  myFiles.loadcpld(0, 0, 800, 480, "2Lights.raw", 2, 2);
  myFiles.loadcpld(0, 0, 800, 480, "3Temp.raw", 3, 2);
  myFiles.loadcpld(0, 0, 800, 480, "456Sched.raw", 4, 2); //Fan/Fog to save video pages...
  myFiles.loadcpld(0, 0, 800, 480, "5MistG.raw", 7, 2);   //New Mist...

#if fastest
  myFiles.loadcpld(0, 0, 800, 480, "7Clock.raw", 5, 2);
  myFiles.loadcpld(0, 0, 800, 480, "8Screen.raw", 6, 2);
#endif
  // display home screen
  screenHome();
  millisDim = millis();
#if debug
  Serial.print(F("Init time "));
  Serial.print(millisDim - performance);
  Serial.println(F(" ms"));
#endif
  myCopyTime(&prevRTC);
  sensors.setWaitForConversion(true);  // makes it wait for first reading
  tempRead(temp1, temp2, temp3);
  sensors.setWaitForConversion(false);  // makes it async (no more waiting)
  humRead(hum1);
  //relayOff(byte flag)
  //relayOn(byte flag)
  //#define pwrFan1      0   // binary  1                                                               //
  //#define pwrMisting1  1   // binary  2                                                               //
  //#define pwrFogger1   2   // binary  4                                                               //
  //#define pwrTemp1     3   // binary  8                                                               //
  //#define pwrLight2    4   // binary 16                                                               //
  //#define pwrLight1    5   // binary 32                                                               //

  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOn(pwrFogger1);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX );
  //  relayOn(pwrLight2);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOn(pwrFan1);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOff(pwrLight2);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOn(pwrLight1);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOff(pwrFogger1);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOn(pwrLight2);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //  relayOff(pwrFan1);
  //
  //  Serial.print("Relays ");
  //  Serial.println(~Relay, HEX);
  //relayOff(pwrLight2)
  //
  //  Serial.print("Relays ");
  //  Serial.println(Relay);
  //relayOn(pwrLight1)
}
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// VOID LOOP CODE /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
#if(!DS1307)
  if (Serial.available()) {
    processSyncMessage();
  }
#endif
  unsigned long currentMillis = millis(); // get current millis
  if (timeStatus() != timeNotSet) {
    updateTimeDate();
  }
  if ((AutoDim) != 0) {
    if (currentMillis - millisDim > TouchDelay * 1000) {
      myGLCD.setBrightness((AutoDim - 1) * 2);
      BackLightTouch = false;
    }
    else {
      myGLCD.setBrightness(16);
    }
  }
  else
  {
    myGLCD.setBrightness(BackLight);
  }
  if ((currentMillis - millisHome > (HomeDelay * 60000UL)) && dispScreen != 1) {
    millisHome = currentMillis;
    screenHome();
  }
  // check for touch events
  if (myTouch.dataAvailable())  {
    if (currentMillis - prevMillisTouch > TouchRepeatDelay) // make sure it's been .5 sec (initially) between touches
    {
      // set BackLight touch if not already set and turn up brightness
      if (BackLightTouch == false) // BackLight touch is for adjusting brightness after touch
      {
        //analogWrite(screenBrightPin, backLight);
        myGLCD.setBrightness(BackLight);
        BackLightTouch = true;
      }
      prevMillisTouch = currentMillis; // reset the touch timer
      millisDim = currentMillis; // reset screen dim timer
      millisHome = currentMillis; // reset return home timer
      processMyTouch();
    }
  }
  myCopyTime(&lastLoopRTC);
  unsigned long rightNow = now();  // Get the time in seconds (since 1970)
  if ((rightNow - humidTime) >= 2) {
    float tmphum;
    humRead(tmphum);
    if (hum1 != tmphum) {
      hum1 = tmphum;
#if debug
      Serial.print(F("Internal humidity update: "));
      Serial.println(hum1);
#endif
      if (dispScreen == 1)
      {
        char hum[6];
        dtostrf(hum1, 4, 1, hum);
        myGLCD.setColor(255, 77, 0);
        myGLCD.setFont(Ubuntubold);
        myGLCD.print(hum, 425, 405);
#if debug
        Serial.print(F("Screen (Home) humidity update: "));
        Serial.println(hum1);
#endif
      }
    }
  }
  if ((rightNow - tempTime) >= 1) {
    myGLCD.setColor(255, 77, 0);

    if (dispScreen == 1)
    {
      myGLCD.setFont(Ubuntubold);
    }
    if (dispScreen == 3)
    {
      myGLCD.setFont(Ubuntubold);
    }
    char sensor[6] = "     ";
    float tmptemp1, tmptemp2, tmptemp3;
    tempRead(tmptemp1, tmptemp2, tmptemp3);
    if (temp1 != tmptemp1)
    {
      temp1 = tmptemp1;
#if debug
      Serial.print(F("Internal temp1 update "));
      Serial.println(temp1);
#endif
      if (dispScreen == 1)
      {
        dtostrf(temp1, 4, 1, sensor);
        myGLCD.print(sensor, 411, 316);
#if debug
        Serial.print(F("Screen (Home) temp1 update "));
        Serial.println(temp1);
#endif
      }
      if (dispScreen == 3)
      {
        dtostrf(temp1, 4, 1, sensor);
        myGLCD.print(sensor, 47, 325);
#if debug
        Serial.print(F("Screen (Temp) temp1 update "));
        Serial.println(temp1);
#endif
      }
    }
    if (temp2 != tmptemp2)
    {
      temp2 = tmptemp2;
#if debug
      Serial.print(F("Internal temp2 update "));
      Serial.println(temp2);
#endif
      if (dispScreen == 1)
      {
        dtostrf(temp2, 4, 1, sensor);
        myGLCD.print(sensor, 537, 316);
#if debug
        Serial.print(F("Screen (Home) temp2 update "));
        Serial.println(temp2);
#endif
      }
      if (dispScreen == 3)
      {
        dtostrf(temp2, 4, 1, sensor);
        myGLCD.print(sensor, 197, 325);
#if debug
        Serial.print(F("Screen (Temp) temp2 update "));
        Serial.println(temp2);
#endif
      }
    }
    if (temp3 != tmptemp3) {
      temp3 = tmptemp3;
#if debug
      Serial.print(F("Internal temp3 update"));
      Serial.println(temp3);
#endif
      if (dispScreen == 1)
      {
        dtostrf(temp3, 4, 1, sensor);
        myGLCD.print(sensor, 668, 316);
#if debug
        Serial.print(F("Screen (Home) temp3 update "));
        Serial.println(temp3);
#endif
      }
      if (dispScreen == 3)
      {
        dtostrf(temp3, 4, 1, sensor);
        myGLCD.print(sensor, 353, 325);
#if debug
        Serial.print(F("Screen (Temp) temp3 update "));
        Serial.println(temp3);
#endif
      }
    }
  }
  procRelays(Relay);
}
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// PAGE SETUP ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void screenHome()  // draw main home screen showing overview info
{
  DoScreen(1, 1);
#if debug
  Serial.println(F("Home Screen"));
#endif
  updateTime = false;
  if (tmpTouchRepeatDelay != TouchRepeatDelay) TouchRepeatDelay = tmpTouchRepeatDelay;
  // Draw Temp to screen
  float tmptemp1, tmptemp2, tmptemp3, tmphum;
  if (temp1 + temp2 + temp3 == 0.0) {
    tempRead(temp1, temp2, temp3);
  }
  unsigned long rightNow = now();

  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(Ubuntubold);
  char sensor[6] = "     ";
  dtostrf(temp1, 4, 1, sensor);
  myGLCD.print(sensor, 411, 316);
  if (temp2 != 0.0)
  {
    dtostrf(temp2, 4, 1, sensor);
    myGLCD.print(sensor, 537, 316);
  }
  if (temp3 != 0.0)
  {
    dtostrf(temp3, 4, 1, sensor);
    myGLCD.print(sensor, 668, 316);
  }
  // Draw Humidity to screen
  if (hum1 == 0.0) {
    humRead(hum1);
  }
  if ((rightNow - humidTime) >= 2)
  {
    humRead(tmphum);
    hum1 = tmphum;
  }
  char hum[6];
  dtostrf(hum1, 4, 1, hum);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(Ubuntubold);
  myGLCD.print(hum, 425, 405);
}
void screenLights()  // Lights screen
{
  DoScreen(2, 2);
#if debug
  Serial.println(F("Lights Screen"));
#endif
  tmpTouchRepeatDelay = TouchRepeatDelay;
  TouchRepeatDelay = 150;
  updateTime = false;
}
void screenTemp()  // Temp Screen
{
  DoScreen(3, 3);
#if debug
  Serial.println(F("Temp Screen"));
#endif
  // Draw Temp to screen
  float tmptemp1, tmptemp2, tmptemp3, tmphum;
  unsigned long rightNow = now();
  if ((rightNow - tempTime) > 1) {
    tempRead(tmptemp1, tmptemp2, tmptemp3);
    if (temp1 != tmptemp1) {
      temp1 = tmptemp1;
    }
    if (temp2 != tmptemp2) {
      temp2 = tmptemp2;
    }
    if (temp3 != tmptemp3) {
      temp3 = tmptemp3;
    }
  }
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(Ubuntubold);
  char sensor[6] = "     ";
  dtostrf(temp1, 4, 1, sensor);
  myGLCD.print(sensor, 47, 325);
  if (temp2 != 0.0)
  {
    dtostrf(temp2, 4, 1, sensor);
    myGLCD.print(sensor, 197, 325);
  }
  if (temp3 != 0.0)
  {
    dtostrf(temp3, 4, 1, sensor);
    myGLCD.print(sensor, 353, 325);
  }
  tmpTouchRepeatDelay = TouchRepeatDelay;
  TouchRepeatDelay = 100;
  myGLCD.printNumF(heater, 1, 510, 296, '.', 4);
  myGLCD.printNumF(fan, 1, 628, 296, '.', 5);
  updateTime = false;
}
void screenFogger()  // Fogging screen
{
  myFiles.loadcpld(21, 6, 336, 74, "FogTitle.raw", 4, 6);
  DoScreen(4, 4);
#if debug
  Serial.println(F("Fogger Screen"));
#endif
  updateTime = false;
}
void screenMist()  // Misting Screen
{
  DoScreen(7, 5);
#if debug
  Serial.println(F("Misting Screen"));
#endif
  updateTime = false;
}
void screenFan()  // Fan screen
{
  myFiles.loadcpld(21, 6, 336, 74, "FanTitle.raw", 4, 6);
  DoScreen(4, 6);
#if debug
  Serial.println(F("Fan Screen"));
#endif
  updateTime = false;
}
//////////////////////////////////////////////////////////////////////////////
//   Modify the following 2 screens to be like the others for instant load  //
//////////////////////////////////////////////////////////////////////////////
void screenClock()  // Clock screen
{
#if fastest
  DoScreen(5, 7);
#else
  myGLCD.setWritePage(0);
  myGLCD.clrScr();
  myGLCD.setDisplayPage(0);
  myFiles.load(0, 0, 800, 480, "7Clock.raw", 3);
  dispScreen = 7;
#endif
#if debug
  Serial.println(F("Clock Screen"));
#endif
  myCopyTime(&tmpRTC);
  tmpTouchRepeatDelay = TouchRepeatDelay;
  TouchRepeatDelay = 150;
  updateTime = false;
}
void screenScreen()  // Screen Settings
{
#if fastest
  DoScreen(6, 8);
#else
  myGLCD.setWritePage(0);
  myGLCD.clrScr();
  myGLCD.setDisplayPage(0);
  myFiles.load(0, 0, 800, 480, "8Screen.raw", 3);
  dispScreen = 8;
#endif
#if debug
  Serial.println(F("Screen Screen"));
#endif
  myGLCD.setFont(Ubuntubold);
  myGLCD.printNumI(AutoDim, 713, 167);
  if (AutoDim != 0) {
    myGLCD.printNumI(TouchDelay, 689, 340, 3);
  }
  else
  {
    myGLCD.print("   ", 689, 340);
  }
  myGLCD.printNumI(HomeDelay, 338, 167, 2);
  myGLCD.printNumI(BackLight, 313, 340, 2);
  tmpTouchRepeatDelay = TouchRepeatDelay;
  TouchRepeatDelay = 150;
  updateTime = false;
}
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  PROCESS MY TOUCH ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void processMyTouch() // this is a huge block dedicated to processing all touch screen events
{
  static volatile byte tempAD, tempTD, tempHD, tempBL;
  static volatile float tempHeater, tempFan;
  static volatile byte tempL1OnHr, tempL1OnMin;
  static volatile byte tempL1OffHr, tempL1OffMin;
  static volatile byte tempL2OnHr, tempL2OnMin;
  static volatile byte tempL2OffHr, tempL2OffMin;
  myTouch.read();
  word x = myTouch.getX();
  word y = myTouch.getY();
  // we evaluate touch based on which screen we are in
  switch (dispScreen)
  {
    case 1:  // home screen
      if ((y >= 117) && (y < 235))
      {
        if ((x >= 59) && (x <= 134)) // Light Settings Page
        {
          tempL1OnHr = Light.On1Hr;
          tempL1OnMin = Light.On1Min;
          tempL1OffHr = Light.Dur1Min;
          tempL1OffMin = Light.Dur1Sec;
          tempL2OnHr = Light.On2Hr;
          tempL2OnMin = Light.On2Min;
          tempL2OffHr = Light.Dur2Min;
          tempL2OffMin = Light.Dur2Sec;
          screenLights();
          myGLCD.setFont(Ubuntubold);
          myGLCD.printNumI(tempL1OnHr, 211, 207, 2);
          myGLCD.printNumI(tempL1OffHr, 211, 342, 2);
          myGLCD.printNumI(tempL1OnMin, 330, 207, 2, '0');
          myGLCD.printNumI(tempL1OffMin, 330, 342, 2, '0');
          myGLCD.printNumI(tempL2OnHr, 591, 207, 2);
          myGLCD.printNumI(tempL2OffHr, 591, 342, 2);
          myGLCD.printNumI(tempL2OnMin, 709, 207, 2, '0');
          myGLCD.printNumI(tempL2OffMin, 709, 342, 2, '0');
        }
        if ((x >= 175) && (x <= 240)) // Temp Settings Page
        {
          tempHeater = heater;
          tempFan = fan;
          screenTemp();
        }
        if ((x >= 270) && (x <= 362)) // Fogger Settings Page
        {
          screenFogger();
        }
      }
      if (( y >= 285) && (y < 411)) {
        if ((x >= 46) && (x <= 141)) // Misting Settings Page
        {
          tempM1 = Mist;
          tempM2 = Mist2;
          screenMist();
          if ( mistScreen < 3)
          {
            MistTimePrint(tempM1, mistScreen);
          }
          else
          {
            MistTimePrint(tempM2, mistScreen);
          }
        }
        if ((x >= 171) && (x <= 237)) // Fan Settings Page
        {
          tempFan1 = Fan;
          screenFan();
          ffTimePrint(tempFan1, fanScreen);
        }
        if ((x >= 270) && (x <= 370)) // Clock Page
        {
          screenClock();
          SetDatePrint(56, 263);
          SetTimePrint(463, 263);
        }
      }
      if ((x >= 712) && (x <= 779) && (y >= 13) && (y <= 77)) // Screen Page
      {
        tempAD = AutoDim;
        tempTD = TouchDelay;
        tempHD = HomeDelay;
        tempBL = BackLight;
        screenScreen();
      }
      break;

    case 2:    // Light screen

      if ((x >= 363) && (x <= 444) && (y >= 422) && (y <= 479)) // Return Home button
      {
        TouchRepeatDelay = tmpTouchRepeatDelay;
        if (tempL1OnHr != Light.On1Hr) {
          EEPROM.write(13, tempL1OnHr);
          Light.On1Hr = tempL1OnHr;
#if debug
          Serial.println(F("Light.On1Hr -> EEPROM"));
#endif
        }
        if (tempL1OnMin != Light.On1Min) {
          EEPROM.write(14, tempL1OnMin);
          Light.On1Min = tempL1OnMin;
#if debug
          Serial.println(F("Light.On1Min -> EEPROM"));
#endif
        }
        if (tempL1OffHr != Light.Dur1Min) {
          EEPROM.write(15, tempL1OffHr);
          Light.Dur1Min = tempL1OffHr;
#if debug
          Serial.println(F("Light.Dur1Min -> EEPROM"));
#endif
        }
        if (tempL1OffMin != Light.Dur1Sec) {
          EEPROM.write(16, tempL1OffMin);
          Light.Dur1Sec = tempL1OffMin;
#if debug
          Serial.println(F("Light.Dur1Sec -> EEPROM"));
#endif
        }
        if (tempL2OnHr != Light.On2Hr) {
          EEPROM.write(17, tempL2OnHr);
          Light.On2Hr = tempL2OnHr;
#if debug
          Serial.println(F("Light.On2Hr -> EEPROM"));
#endif
        }
        if (tempL2OnMin != Light.On2Min) {
          EEPROM.write(18, tempL2OnMin);
          Light.On2Min = tempL2OnMin;
#if debug
          Serial.println(F("Light.On2Min -> EEPROM"));
#endif
        }
        if (tempL2OffHr != Light.Dur2Min) {
          EEPROM.write(19, tempL2OffHr);
          Light.Dur2Min = tempL2OffHr;
#if debug
          Serial.println(F("Light.Dur2Min -> EEPROM"));
#endif
        }
        if (tempL2OffMin != Light.Dur2Sec) {
          EEPROM.write(20, tempL2OffMin);
          Light.Dur2Sec = tempL2OffMin;
#if debug
          Serial.println(F("Light.Dur2Sec -> EEPROM"));
#endif
        }
        screenHome();
      }
      if ((x >= 150) && (x < 200)) // --> Hours
      {
        if ((y >= 173) && (y < 218)) // --> On1 Hours +
        {
          if (tempL1OnHr < 23)
            tempL1OnHr ++;
        }
        if ((y >= 227) && (y < 272)) // --> On1 Hours -
        {
          if (tempL1OnHr > 0)
            tempL1OnHr --;
        }
        if ((y >= 306) && (y < 351)) // --> Off1 Hours +
        {
          if (tempL1OffHr < 23)
            tempL1OffHr ++;
        }
        if ((y >= 360) && (y < 405)) // --> Off1 Hours -
        {
          if (tempL1OffHr > 0)
            tempL1OffHr --;
        }
        myGLCD.setFont(Ubuntubold);
        myGLCD.printNumI(tempL1OnHr, 211, 207, 2);
        myGLCD.printNumI(tempL1OffHr, 211, 342, 2);
      }
      if ((x >= 268) && (x < 318)) // ---> Minutes
      {
        if ((y >= 173) && (y < 218)) // -> On1 Minutes +
        {
          if (tempL1OnMin < 59)
            tempL1OnMin ++;
        }
        if ((y >= 227) && (y < 272)) // -> On1 Minutes -
        {
          if (tempL1OnMin > 0)
            tempL1OnMin --;
        }
        if ((y >= 306) && (y < 351)) // -> Off1 Minutes +
        {
          if (tempL1OffMin < 59)
            tempL1OffMin ++;
        }
        if ((y >= 360) && (y < 405)) // -> Off1 Minutes -
        {
          if (tempL1OffMin > 0)
            tempL1OffMin --;
        }
        myGLCD.setFont(Ubuntubold);
        myGLCD.printNumI(tempL1OnMin, 330, 207, 2, '0');
        myGLCD.printNumI(tempL1OffMin, 330, 342, 2, '0');
      }
      if ((x >= 530) && (x < 580)) // --> Hours
      {
        if ((y >= 173) && (y < 218)) // --> On1 Hours +
        {
          if (tempL2OnHr < 23)
            tempL2OnHr ++;
        }
        if ((y >= 227) && (y < 272)) // --> On1 Hours -
        {
          if (tempL2OnHr > 0)
            tempL2OnHr --;
        }
        if ((y >= 306) && (y < 351)) // --> Off1 Hours +
        {
          if (tempL2OffHr < 23)
            tempL2OffHr ++;
        }
        if ((y >= 360) && (y < 405)) // --> Off1 Hours -
        {
          if (tempL2OffHr > 0)
            tempL2OffHr --;
        }
        myGLCD.setFont(Ubuntubold);
        myGLCD.printNumI(tempL2OnHr, 591, 207, 2);
        myGLCD.printNumI(tempL2OffHr, 591, 342, 2);
      }
      if ((x >= 650) && (x < 700)) // ---> Minutes
      {
        if ((y >= 173) && (y < 218)) // -> On1 Minutes +
        {
          if (tempL2OnMin < 59)
            tempL2OnMin ++;
        }
        if ((y >= 227) && (y < 272)) // -> On1 Minutes -
        {
          if (tempL2OnMin > 0)
            tempL2OnMin --;
        }
        if ((y >= 306) && (y < 351)) // -> Off1 Minutes +
        {
          if (tempL2OffMin < 59)
            tempL2OffMin ++;
        }
        if ((y >= 360) && (y < 405)) // -> Off1 Minutes -
        {
          if (tempL2OffMin > 0)
            tempL2OffMin --;
        }
        myGLCD.setFont(Ubuntubold);
        myGLCD.printNumI(tempL2OnMin, 709, 207, 2, '0');
        myGLCD.printNumI(tempL2OffMin, 709, 342, 2, '0');
      }
      break;

    case 3:    // Temp screen
      if ((x >= 363) && (x <= 444) && (y >= 422) && (y <= 479)) // Return Home button
      {
        TouchRepeatDelay = tmpTouchRepeatDelay;
        if (tempFan != fan) {
          EEPROM.writeFloat(9, tempFan);
          fan = tempFan;
#if debug
          Serial.println(F("Fan -> EEPROM"));
#endif
        }
        if (tempHeater != heater) {
          EEPROM.writeFloat(5, tempHeater);
          heater = tempHeater;
#if debug
          Serial.println(F("Heater -> EEPROM"));
#endif
        }
        screenHome();
      }
      myGLCD.setFont(Ubuntubold);
      if ((x >= 520) && (x < 595))
      {
        if ((y >= 208) && (y < 282)) // Low Temp +
        {
          tempHeater += 0.1;
        }
        if ((y >= 342) && (y < 416)) // Low Temp -
        {
          tempHeater -= 0.1;
        }
        myGLCD.printNumF(tempHeater, 1, 510, 296, '.', 4);
      }
      if ((x >= 650) && (x < 725))
      {
        if ((y >= 208) && (y < 282)) // High Temp +
        {
          tempFan += 0.1;
        }
        if ((y >= 342) && (y < 416)) // High Temp -
        {
          tempFan -= 0.1;
        }
        myGLCD.printNumF(tempFan, 1, 628, 296, '.', 5);
      }
      break;

    case 4:    // Fogger screen
      if ((x >= 363) && (x < 445) && (y >= 422) && (y < 480)) // Return Home button
      {
        screenHome();
      }
      break;

    case 5:    // Misting screen
      if ((x >= 363) && (x < 445) && (y >= 422) && (y < 480)) // Return Home button
      {
        if (Mist.Enable != tempM1.Enable)
        {
          Mist.Enable = tempM1.Enable;
          EEPROM.write(32, Mist.Enable);
        }
        if (Mist.On1Hr != tempM1.On1Hr)
        {
          Mist.On1Hr = tempM1.On1Hr;
          EEPROM.write(33, Mist.On1Hr);
        }
        if (Mist.On1Min != tempM1.On1Min)
        {
          Mist.On1Min = tempM1.On1Min;
          EEPROM.write(34, Mist.On1Min);
        }
        if (Mist.Dur1Min != tempM1.Dur1Min)
        {
          Mist.Dur1Min = tempM1.Dur1Min;
          EEPROM.write(35, Mist.Dur1Min);
        }
        if (Mist.Dur1Sec != tempM1.Dur1Sec)
        {
          Mist.Dur1Sec = tempM1.Dur1Sec;
          EEPROM.write(36, Mist.Dur1Sec);
        }
        if (Mist.On2Hr != tempM1.On2Hr)
        {
          Mist.On2Hr = tempM1.On2Hr;
          EEPROM.write(37, Mist.On2Hr);
        }
        if (Mist.On2Min != tempM1.On2Min)
        {
          Mist.On2Min = tempM1.On2Min;
          EEPROM.write(38, Mist.On2Min);
        }
        if (Mist.Dur2Min != tempM1.Dur2Min)
        {
          Mist.Dur2Min = tempM1.Dur2Min;
          EEPROM.write(39, Mist.Dur2Min);
        }
        if (Mist.Dur2Sec != tempM1.Dur2Sec)
        {
          Mist.Dur2Sec = tempM1.Dur2Sec;
          EEPROM.write(40, Mist.Dur2Sec);
        }
        if (Mist.OnDay != tempM1.OnDay)
        {
          Mist.OnDay = tempM1.OnDay;
          EEPROM.write(41, Mist.OnDay);
        }
        if (Mist.OnDay2 != tempM1.OnDay2)
        {
          Mist.OnDay2 = tempM1.OnDay2;
          EEPROM.write(42, Mist.OnDay2);
        }
        if (Mist2.Enable != tempM2.Enable)
        {
          Mist2.Enable = tempM2.Enable;
          EEPROM.write(43, Mist2.Enable);
        }
        if (Mist2.On1Hr != tempM2.On1Hr)
        {
          Mist2.On1Hr = tempM2.On1Hr;
          EEPROM.write(44, Mist2.On1Hr);
        }
        if (Mist2.On1Min != tempM2.On1Min)
        {
          Mist2.On1Min = tempM2.On1Min;
          EEPROM.write(45, Mist2.On1Min);
        }
        if (Mist2.Dur1Min != tempM2.Dur1Min)
        {
          Mist2.Dur1Min = tempM2.Dur1Min;
          EEPROM.write(46, Mist2.Dur1Min);
        }
        if (Mist2.Dur1Sec != tempM2.Dur1Sec)
        {
          Mist2.Dur1Sec = tempM2.Dur1Sec;
          EEPROM.write(47, Mist2.Dur1Sec);
        }
        if (Mist2.On2Hr != tempM2.On2Hr)
        {
          Mist2.On2Hr = tempM2.On2Hr;
          EEPROM.write(48, Mist2.On2Hr);
        }
        if (Mist2.On2Min != tempM2.On2Min)
        {
          Mist2.On2Min = tempM2.On2Min;
          EEPROM.write(49, Mist2.On2Min);
        }
        if (Mist2.Dur2Min != tempM2.Dur2Min)
        {
          Mist2.Dur2Min = tempM2.Dur2Min;
          EEPROM.write(50, Mist2.Dur2Min);
        }
        if (Mist2.Dur2Sec != tempM2.Dur2Sec)
        {
          Mist2.Dur2Sec = tempM2.Dur2Sec;
          EEPROM.write(51, Mist2.Dur2Sec);
        }
        if (Mist2.OnDay != tempM2.OnDay)
        {
          Mist2.OnDay = tempM2.OnDay;
          EEPROM.write(52, Mist2.OnDay);
        }
        if (Mist2.OnDay2 != tempM2.OnDay2)
        {
          Mist2.OnDay2 = tempM2.OnDay2;
          EEPROM.write(53, Mist2.OnDay2);
        }
        screenHome();
      }
      if ((x >= 183) && (x < 236))
      {
        if ((y >= 209) && (y < 259))
        {
          switch (mistScreen) {
            case 1:
              if (!(tempM1.Enable & 0xF0)) // Set Enable Mist 1
              {
                tempM1.Enable = ((tempM1.Enable & 0x0F) + 0xF0);
              }
              else
              {
                tempM1.Enable = (tempM1.Enable & 0x0F);
              }
              MistTimePrint(tempM1, 1);
              break;
            case 2:
              if (!(tempM1.Enable & 0x0F)) // Set Enable Mist 2
              {
                tempM1.Enable = ((tempM1.Enable & 0xF0) + 0x0F);
              }
              else
              {
                tempM1.Enable = (tempM1.Enable & 0xF0);
              }
              MistTimePrint(tempM1, 2);
              break;
            case 3:
              if (!(tempM2.Enable & 0xF0)) // Set Enable Mist 3
              {
                tempM2.Enable = ((tempM2.Enable & 0x0F) + 0xF0);
              }
              else
              {
                tempM2.Enable = (tempM2.Enable & 0x0F);
              }
              MistTimePrint(tempM2, 3);
              break;
            case 4:
              if (!(tempM2.Enable & 0x0F))  // Set Enable Mist 4
              {
                tempM2.Enable = ((tempM2.Enable & 0xF0) + 0x0F);
              }
              else
              {
                tempM2.Enable = (tempM2.Enable & 0xF0);
              }
              MistTimePrint(tempM2, 4);
              break;
          }
        }
      }
      if ((y >= 174) && (y < 222)) // Up arrows row
      {
        if ((x >= 254) && (x < 308))
        { // Hr +1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Hour +1"));
                if (tempM1.On1Hr < 23)
                { tempM1.On1Hr++;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Hour +1"));
                if (tempM1.On2Hr < 23)
                { tempM1.On2Hr++;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Hour +1"));
                if (tempM2.On1Hr < 23)
                { tempM2.On1Hr++;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Hour +1"));
                if (tempM2.On2Hr < 23)
                { tempM2.On2Hr++;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
        if ((x >= 368) && (x < 422))
        { // Min +1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Min +1"));
                if (tempM1.On1Min < 59)
                { tempM1.On1Min++;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Min +1"));
                if (tempM1.On2Min < 59)
                { tempM1.On2Min++;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Min +1"));
                if (tempM2.On1Min < 59)
                { tempM2.On1Min++;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Min +1"));
                if (tempM2.On2Min < 59)
                { tempM2.On2Min++;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
        if ((x >= 516) && (x < 570))
        { // Min +1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Min +1"));
                if (tempM1.Dur1Min < 59)
                { tempM1.Dur1Min++;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Min +1"));
                if (tempM1.Dur2Min < 59)
                { tempM1.Dur2Min++;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Min +1"));
                if (tempM2.Dur1Min < 59)
                { tempM2.Dur1Min++;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Min +1"));
                if (tempM2.Dur2Min < 59)
                { tempM2.Dur2Min++;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
        if ((x >= 647) && (x < 701))
        { // Sec +1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Sec +1"));
                if (tempM1.Dur1Sec < 59)
                { tempM1.Dur1Sec++;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Sec +1"));
                if (tempM1.Dur2Sec < 59)
                { tempM1.Dur2Sec++;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Sec +1"));
                if (tempM2.Dur1Sec < 59)
                { tempM2.Dur1Sec++;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Sec +1"));
                if (tempM2.Dur2Sec < 59)
                { tempM2.Dur2Sec++;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
      }
      if ((y >= 242) && (y < 290))  // Down arrows row
      {
        if ((x >= 254) && (x < 308))
        { // Hr -1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Hour -1"));
                if (tempM1.On1Hr > 0)
                { tempM1.On1Hr--;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Hour -1"));
                if (tempM1.On2Hr > 0)
                { tempM1.On2Hr--;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Hour -1"));
                if (tempM2.On1Hr > 0)
                { tempM2.On1Hr--;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Hour -1"));
                if (tempM2.On2Hr > 0)
                { tempM2.On2Hr--;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
        if ((x >= 368) && (x < 422))
        { // Min -1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Min -1"));
                if (tempM1.On1Min > 0)
                { tempM1.On1Min--;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Min -1"));
                if (tempM1.On2Min > 0)
                { tempM1.On2Min--;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Min -1"));
                if (tempM2.On1Min > 0)
                { tempM2.On1Min--;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Min -1"));
                if (tempM2.On2Min > 0)
                { tempM2.On2Min--;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
        if ((x >= 516) && (x < 570))
        { // Min -1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Min -1"));
                if (tempM1.Dur1Min > 0)
                { tempM1.Dur1Min--;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Min -1"));
                if (tempM1.Dur2Min > 0)
                { tempM1.Dur2Min--;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Min -1"));
                if (tempM2.Dur1Min > 0)
                { tempM2.Dur1Min--;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Min -1"));
                if (tempM2.Dur2Min > 0)
                { tempM2.Dur2Min--;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
        if ((x >= 647) && (x < 701))
        { // Sec -1
          switch (mistScreen)
          {
            case 1:
              if ((tempM1.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 1 Sec -1"));
                if (tempM1.Dur1Sec > 0)
                { tempM1.Dur1Sec--;
                  MistTimePrint(tempM1, 1);
                }
              }
              break;
            case 2:
              if ((tempM1.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 2 Sec -1"));
                if (tempM1.Dur2Sec > 0)
                { tempM1.Dur2Sec--;
                  MistTimePrint(tempM1, 2);
                }
              }
              break;
            case 3:
              if ((tempM2.Enable & 0xF0) == 0xF0) {
                Serial.println(F("Mist 3 Sec -1"));
                if (tempM2.Dur1Sec > 0)
                { tempM2.Dur1Sec--;
                  MistTimePrint(tempM2, 1);
                }
              }
              break;
            case 4:
              if ((tempM2.Enable & 0x0F) == 0x0F) {
                Serial.println(F("Mist 4 Sec -1"));
                if (tempM2.Dur2Sec > 0)
                { tempM2.Dur2Sec--;
                  MistTimePrint(tempM2, 2);
                }
              }
              break;
          }
        }
      }
      if ((y >= 345) && (y < 403)) // Day of week row
      {
        if ((x >= 201) and (x < 261))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              //    Serial.println(F("Mist 1 Sun"));
              if ((tempM1.OnDay & (1 << Sun)) == (1 << Sun)) {
                Serial.println(F("Mist 1 Sun On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Sun));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Sun Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Sun));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //     Serial.println(F("Mist 2 Sun"));
              if ((tempM1.OnDay2 & (1 << Sun)) == (1 << Sun)) {
                Serial.println(F("Mist 2 Sun On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Sun));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 2 Sun Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Sun));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              //       Serial.println(F("Mist 3 Sun"));
              if ((tempM2.OnDay & (1 << Sun)) == (1 << Sun)) {
                Serial.println(F("Mist 3 Sun On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Sun));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Sun Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Sun));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              //    Serial.println(F("Mist 4 Sun"));
              if ((tempM2.OnDay2 & (1 << Sun)) == (1 << Sun)) {
                Serial.println(F("Mist 4 Sun On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Sun));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Sun Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Sun));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        if ((x >= 277) and (x < 336))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              //       Serial.println(F("Mist 1 Mon"));
              if ((tempM1.OnDay & (1 << Mon)) == (1 << Mon)) {
                Serial.println(F("Mist 1 Mon On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Mon));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Mon Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Mon));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //   Serial.println(F("Mist 2 Mon"));
              if ((tempM1.OnDay2 & (1 << Mon)) == (1 << Mon)) {
                Serial.println(F("Mist 2 Mon On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Mon));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 2 Mon Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Mon));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              //  Serial.println(F("Mist 3 Mon"));
              if ((tempM2.OnDay & (1 << Mon)) == (1 << Mon)) {
                Serial.println(F("Mist 3 Mon On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Mon));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Mon Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Mon));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              //   Serial.println(F("Mist 4 Mon"));
              if ((tempM2.OnDay2 & (1 << Mon)) == (1 << Mon)) {
                Serial.println(F("Mist 4 Mon On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Mon));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Mon Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Mon));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        if ((x >= 350) and (x < 411))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              // Serial.println(F("Mist 1 Tue"));
              if ((tempM1.OnDay & (1 << Tue)) == (1 << Tue)) {
                Serial.println(F("Mist 1 Tue On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Tue));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Tue Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Tue));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 2 Tue"));
              if ((tempM1.OnDay2 & (1 << Tue)) == (1 << Tue)) {
                Serial.println(F("Mist 1 Tue On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Tue));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 1 Tue Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Tue));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              // Serial.println(F("Mist 3 Tue"));
              if ((tempM2.OnDay & (1 << Tue)) == (1 << Tue)) {
                Serial.println(F("Mist 3 Tue On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Tue));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Tue Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Tue));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              // Serial.println(F("Mist 4 Tue"));
              if ((tempM2.OnDay2 & (1 << Tue)) == (1 << Tue)) {
                Serial.println(F("Mist 4 Tue On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Tue));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Tue Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Tue));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        if ((x >= 427) and (x < 487))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 1 Wed"));
              if ((tempM1.OnDay & (1 << Wed)) == (1 << Wed)) {
                Serial.println(F("Mist 1 Wed On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Wed));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Wed Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Wed));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 2 Wed"));
              if ((tempM1.OnDay2 & (1 << Wed)) == (1 << Wed)) {
                Serial.println(F("Mist 2 Wed On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Wed));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 2 Wed Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Wed));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 3 Wed"));
              if ((tempM2.OnDay & (1 << Wed)) == (1 << Wed)) {
                Serial.println(F("Mist 3 Wed On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Wed));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Wed Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Wed));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 4 Wed"));
              if ((tempM2.OnDay2 & (1 << Wed)) == (1 << Wed)) {
                Serial.println(F("Mist 4 Wed On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Wed));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Wed Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Wed));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        if ((x >= 503) and (x < 564))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 1 Thu"));
              if ((tempM1.OnDay & (1 << Thu)) == (1 << Thu)) {
                Serial.println(F("Mist 1 Thu On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Thu));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Thu Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Thu));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 2 Thu"));
              if ((tempM1.OnDay2 & (1 << Thu)) == (1 << Thu)) {
                Serial.println(F("Mist 2 Thu On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Thu));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 2 Thu Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Thu));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 3 Thu"));
              if ((tempM2.OnDay & (1 << Thu)) == (1 << Thu)) {
                Serial.println(F("Mist 3 Thu On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Thu));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Thu Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Thu));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 4 Thu"));
              if ((tempM2.OnDay2 & (1 << Thu)) == (1 << Thu)) {
                Serial.println(F("Mist 4 Thu On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Thu));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Thu Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Thu));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        if ((x >= 581) and (x < 640))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 1 Fri"));
              if ((tempM1.OnDay & (1 << Fri)) == (1 << Fri)) {
                Serial.println(F("Mist 1 Fri On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Fri));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Fri Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Fri));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 2 Fri"));
              if ((tempM1.OnDay2 & (1 << Fri)) == (1 << Fri)) {
                Serial.println(F("Mist 2 Fri On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Fri));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 2 Fri Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Fri));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 3 Fri"));
              if ((tempM2.OnDay & (1 << Fri)) == (1 << Fri)) {
                Serial.println(F("Mist 3 Fri On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Fri));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Fri Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Fri));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 4 Fri"));
              if ((tempM2.OnDay2 & (1 << Fri)) == (1 << Fri)) {
                Serial.println(F("Mist 4 Fri On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Fri));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Fri Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Fri));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        if ((x >= 655) and (x < 717))
        {
          if (mistScreen == 1)
          {
            if ((tempM1.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 1 Sat"));
              if ((tempM1.OnDay & (1 << Sat)) == (1 << Sat)) {
                Serial.println(F("Mist 1 Sat On"));
                tempM1.OnDay = (tempM1.OnDay & ~ (1 << Sat));
                //dowBlank(tempM1.OnDay);
              }
              else
              {
                Serial.println(F("Mist 1 Sat Off"));
                tempM1.OnDay = (tempM1.OnDay | (1 << Sat));
                //dowFrog(tempM1.OnDay);
              }
            }
          }
          if (mistScreen == 2)
          {
            if ((tempM1.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 2 Sat"));
              if ((tempM1.OnDay2 & (1 << Sat)) == (1 << Sat)) {
                Serial.println(F("Mist 2 Sat On"));
                tempM1.OnDay2 = (tempM1.OnDay2 & ~ (1 << Sat));
                //dowBlank(tempM1.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 2 Sat Off"));
                tempM1.OnDay2 = (tempM1.OnDay2 | (1 << Sat));
                //dowFrog(tempM1.OnDay2);
              }
            }
          }
          if (mistScreen == 3)
          {
            if ((tempM2.Enable & 0xF0) == 0xF0) {
              //Serial.println(F("Mist 3 Sat"));
              if ((tempM2.OnDay & (1 << Sat)) == (1 << Sat)) {
                Serial.println(F("Mist 3 Sat On"));
                tempM2.OnDay = (tempM2.OnDay & ~ (1 << Sat));
                //dowBlank(tempM2.OnDay);
              }
              else
              {
                Serial.println(F("Mist 3 Sat Off"));
                tempM2.OnDay = (tempM2.OnDay | (1 << Sat));
                //dowFrog(tempM2.OnDay);
              }
            }
          }
          if (mistScreen == 4)
          {
            if ((tempM2.Enable & 0x0F) == 0x0F) {
              //Serial.println(F("Mist 4 Sat"));
              if ((tempM2.OnDay2 & (1 << Sat)) == (1 << Sat)) {
                Serial.println(F("Mist 4 Sat On"));
                tempM2.OnDay2 = (tempM2.OnDay2 & ~ (1 << Sat));
                //dowBlank(tempM2.OnDay2);
              }
              else
              {
                Serial.println(F("Mist 4 Sat Off"));
                tempM2.OnDay2 = (tempM2.OnDay2 | (1 << Sat));
                //dowFrog(tempM2.OnDay2);
              }
            }
          }
        }
        // end of day of week row, so update frogs ONCE
        switch (mistScreen)
        {
          case 1:
            dowBlank(tempM1.OnDay);
            if ((tempM1.Enable & 0xf0))
              dowFrog(tempM1.OnDay);
            break;
          case 2:
            dowBlank(tempM1.OnDay2);
            if ((tempM1.Enable & 0x0f))
              dowFrog(tempM1.OnDay2);
            break;
          case 3:
            dowBlank(tempM2.OnDay);
            if ((tempM2.Enable & 0xf0))
              dowFrog(tempM2.OnDay);
            break;
          case 4:
            dowBlank(tempM2.OnDay2);
            if ((tempM2.Enable & 0x0f))
              dowFrog(tempM2.OnDay2);
            break;
        }
      }


      if ((x >= 51) && (x < 129))  // Misting screen select column
      {
        if ((y >= 106) && (y < 184))
        {
          myFiles.load(51, 106, 78, 78, "blues.raw", 16, 0);
          if ((tempM1.Enable & 0xF0) != 0xF0) // is blue set?
          {
            //            myGLCD.setColor(0, 0, 0);
            //            myGLCD.fillRect(187, 216, 231, 251);
          }
          else
          {
            //            myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);
          }
          MistTimePrint(tempM1, 1);
          switch (mistScreen)
          {
            case 2:
              myFiles.load(51, 193, 78, 78, "yellow.raw", 16, 0);
              break;
            case 3:
              myFiles.load(51, 281, 78, 78, "green.raw", 16, 0);
              break;
            case 4:
              myFiles.load(51, 368, 78, 78, "grey.raw", 16, 0);
              break;
          }
          mistScreen = 1;
        }
        if ((y >= 193) && (y < 271))
        {
          myFiles.load(51, 193, 78, 78, "yellows.raw", 16, 0);
          if ((tempM1.Enable & 0x0F) != 0x0F) // is yellow set?
          {
            //            myGLCD.setColor(0, 0, 0);
            //            myGLCD.fillRect(187, 216, 231, 251);
          }
          else
          {
            //            myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);

          }
          MistTimePrint(tempM1, 2);
          switch (mistScreen)
          {
            case 1:
              myFiles.load(51, 106, 78, 78, "blue.raw", 16, 0);
              break;
            case 3:
              myFiles.load(51, 281, 78, 78, "green.raw", 16, 0);
              break;
            case 4:
              myFiles.load(51, 368, 78, 78, "grey.raw", 16, 0);
              break;
          }
          mistScreen = 2;
        }
        if ((y >= 281) && (y < 359))
        {
          myFiles.load(51, 281, 78, 78, "greens.raw", 16, 0);
          if ((tempM2.Enable & 0xF0) != 0xF0) // is green set?
          {
            //            myGLCD.setColor(0, 0, 0);
            //            myGLCD.fillRect(187, 216, 231, 251);
          }
          else
          {
            //            myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);

          }
          MistTimePrint(tempM2, 3);
          switch (mistScreen)
          {
            case 1:
              myFiles.load(51, 106, 78, 78, "blue.raw", 16, 0);
              break;
            case 2:
              myFiles.load(51, 193, 78, 78, "yellow.raw", 16, 0);
              break;
            case 4:
              myFiles.load(51, 368, 78, 78, "grey.raw", 16, 0);
              break;
          }
          mistScreen = 3;
        }
        if ((y >= 368) && (y < 446))
        {
          myFiles.load(51, 368, 78, 78, "greys.raw", 16, 0);
          if ((tempM2.Enable & 0x0F) != 0x0F) // is grey set?
          {
            //            myGLCD.setColor(0, 0, 0);
            //            myGLCD.fillRect(187, 216, 231, 251);
          }
          else
          {
            //            myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);

          }
          MistTimePrint(tempM2, 4);
          switch (mistScreen)
          {
            case 1:
              myFiles.load(51, 106, 78, 78, "blue.raw", 16, 0);
              break;
            case 2:
              myFiles.load(51, 193, 78, 78, "yellow.raw", 16, 0);
              break;
            case 3:
              myFiles.load(51, 281, 78, 78, "green.raw", 16, 0);
              break;
          }
          mistScreen = 4;
        }
      }

      break;

    case 6:    // Fan screen
      if ((x >= 363) && (x < 445) && (y >= 422) && (y < 480)) // Return Home button
      {
        if (Fan.Enable != tempFan1.Enable)
        {
          Fan.Enable = tempFan1.Enable;
          EEPROM.write(54, Fan.Enable);
        }
        if (Fan.On1Hr != tempFan1.On1Hr)
        {
          Fan.On1Hr = tempFan1.On1Hr;
          EEPROM.write(55, Fan.On1Hr);
        }
        if (Fan.On1Min != tempFan1.On1Min)
        {
          Fan.On1Min = tempFan1.On1Min;
          EEPROM.write(56, Fan.On1Min);
        }
        if (Fan.Dur1Min != tempFan1.Dur1Min)
        {
          Fan.Dur1Min = tempFan1.Dur1Min;
          EEPROM.write(57, Fan.Dur1Min);
        }
        if (Fan.Dur1Sec != tempFan1.Dur1Sec)
        {
          Fan.Dur1Sec = tempFan1.Dur1Sec;
          EEPROM.write(58, Fan.Dur1Sec);
        }
        if (Fan.On2Hr != tempFan1.On2Hr)
        {
          Fan.On2Hr = tempFan1.On2Hr;
          EEPROM.write(59, Fan.On2Hr);
        }
        if (Fan.On2Min != tempFan1.On2Min)
        {
          Fan.On2Min = tempFan1.On2Min;
          EEPROM.write(60, Fan.On2Min);
        }
        if (Fan.Dur2Min != tempFan1.Dur2Min)
        {
          Fan.Dur2Min = tempFan1.Dur2Min;
          EEPROM.write(61, Fan.Dur2Min);
        }
        if (Fan.Dur2Sec != tempFan1.Dur2Sec)
        {
          Fan.Dur2Sec = tempFan1.Dur2Sec;
          EEPROM.write(62, Fan.Dur2Sec);
        }
        if (Fan.OnDay != tempFan1.OnDay)
        {
          Fan.OnDay = tempFan1.OnDay;
          EEPROM.write(63, Fan.OnDay);
        }
        if (Fan.OnDay2 != tempFan1.OnDay2)
        {
          Fan.OnDay2 = tempFan1.OnDay2;
          EEPROM.write(64, Fan.OnDay2);
        }
        screenHome();
      }
      if ((x >= 78) && (x < 115))
      {
        if ((y >= 229) && (y < 263))
        {
          if (!(tempFan1.Enable & 0xF0)) // Set Enable Fan 1
          {
            tempFan1.Enable = ((tempFan1.Enable & 0x0F) + 0xF0);
          }
          else
          {
            tempFan1.Enable = (tempFan1.Enable & 0x0F);
          }
          fanScreen = 1;
        }
        if ((y >= 359) && (y < 393))
        {
          if (!(tempFan1.Enable & 0x0F)) // Set Enable Fan 2
          {
            tempFan1.Enable = ((tempFan1.Enable & 0xF0) + 0x0F);
          }
          else
          {
            tempFan1.Enable = (tempFan1.Enable & 0xF0);
          }
          fanScreen = 2;
        }
        ffTimePrint(tempFan1, fanScreen);
      }
      break;

    case 7:    // Clock screen
      if ((x >= 363) && (x <= 444) && (y >= 422) && (y < 480)) // Return Home button
      {
        TouchRepeatDelay = tmpTouchRepeatDelay;
        screenHome();
      }
      if ((y >= 175) && (y < 250)) {  // 'Increase' row
        if ((x >= 55) && (x < 130)) { // 'Months'
          //Serial.println(F("Month+"));
          if (tmpRTC.Month < 12) tmpRTC.Month += 1;
        }
        if ((x >= 165) && (x < 240)) { // 'Days'
          //Serial.println(F("Days+"));
          if (((tmpRTC.Day < 31) && (tmpRTC.Month != 9 && tmpRTC.Month != 4 && tmpRTC.Month != 6 && tmpRTC.Month != 11
                                     &&  tmpRTC.Month != 2)) || ((tmpRTC.Day < 30) && (tmpRTC.Month == 9 || tmpRTC.Month == 4 || tmpRTC.Month == 6
                                         || tmpRTC.Month == 11 || tmpRTC.Month != 2)) || ((tmpRTC.Day < 28) && (tmpRTC.Month == 2)) || ((tmpRTC.Day < 29)
                                             && (tmpRTC.Month == 2) && (((float)(tmpRTC.Year / 4.0) - (int)(tmpRTC.Year / 4.0) == 0.00 )
                                                 || ((float)(tmpRTC.Year / 400.0) - (int)(tmpRTC.Year / 400.0) == 0.00 ))
                                             && ((float)(tmpRTC.Year / 100.0) - (int)(tmpRTC.Year / 100.0) != 0.00 )))
          {
            tmpRTC.Day += 1;
          }
        }
        if ((x >= 275) && (x < 350)) { // 'Years'
          //Serial.println(F("Years+"));
          tmpRTC.Year += 1;
        }
        if ((x >= 450) && (x < 525)) { // '24Hrs'
          if (tmpRTC.Hour < 23) tmpRTC.Hour += 1;
        }
        if ((x >= 560) && (x < 635)) { // Minutes'
          if (tmpRTC.Minute < 59) tmpRTC.Minute += 1;
        }
        if ((x >= 665) && (x < 740)) { // 'Seconds'
          // Not implementing second updates....
        }
        SetDatePrint(56, 263);
        SetTimePrint(463, 263);
      }
      if ((y >= 310) && (y < 385)) {  // 'Decrease' row
        if ((x >= 55) && (x < 130)) { // 'Months'
          //Serial.println(F("Month-"));
          if (tmpRTC.Month > 1) tmpRTC.Month -= 1;
        }
        if ((x >= 165) && (x < 240)) { // 'Days'
          //Serial.println(F("Days-"));
          if (tmpRTC.Day > 1) tmpRTC.Day -= 1;
        }
        if ((x >= 275) && (x < 350)) { // 'Years'
          //Serial.println(F("Years-"));
          tmpRTC.Year -= 1;
        }
        if ((x >= 450) && (x < 525)) { // '24Hrs'
          if (tmpRTC.Hour > 0 ) tmpRTC.Hour -= 1;
        }
        if ((x >= 560) && (x < 635)) { // Minutes'
          if (tmpRTC.Minute > 0 ) tmpRTC.Minute -= 1;
        }
        if ((x >= 665) && (x < 740)) { // 'Seconds'
          // Not implementing second updates....
        }
        SetDatePrint(56, 263);
        SetTimePrint(463, 263);
      }
      if ((y >= 410) && (y < 445)) { // 'Set' 'Cancel' Row
        if ((x >= 225) && (x < 345)) { //'Set'
#if debug
          Serial.println(F("Time Set"));
#endif
          time_t xo = makeTime(tmpRTC);
          rtc.adjust(xo);
          rtc.now();
          //Serial.println(xo);
          TouchRepeatDelay = tmpTouchRepeatDelay;
          screenHome();
        }
        if ((x >= 460) && (x < 580)) { //'Cancel'
          TouchRepeatDelay = tmpTouchRepeatDelay;
          screenHome();
        }
      }
      break;

    case 8:    // Screen screen
      if ((x >= 363) && (x <= 444) && (y >= 422) && (y < 480)) // Return Home button
      {
        TouchRepeatDelay = tmpTouchRepeatDelay;
        if (tempAD != AutoDim) {
          EEPROM.write(3, tempAD);
          AutoDim = tempAD;
#if debug
          Serial.println(F("AutoDim -> EEPROM"));
#endif
        }
        if (tempTD != TouchDelay) {
          EEPROM.write(4, tempTD);
          TouchDelay = tempTD;
#if debug
          Serial.println(F("TouchDelay -> EEPROM"));
#endif
        }
        if (tempHD != HomeDelay) {
          EEPROM.write(1, tempHD);
          HomeDelay = tempHD;
#if debug
          Serial.println(F("HomeDelay -> EEPROM"));
#endif
        }
        if (tempBL != BackLight) {
          EEPROM.write(2, BackLight);
          //BackLight = tempBL;
#if debug
          Serial.println(F("BackLight -> EEPROM"));
#endif
        }
        screenHome();
      }

      if ((x >= 610 && x < 685)) { // 'Autodim' Column
        if ((y >= 105 && y < 175)) { // 'Level +'
          if ( tempAD < 5) {
            tempAD += 1;
          }
        }
        if ((y >= 190 && y < 260)) { // 'Level -'
          if (tempAD > 0) {
            tempAD -= 1;
          }
        }
        if ((y >= 280 && y < 350)) {  // 'Seconds +'
          if (tempTD < 255) {
            tempTD += 1;
          }
        }
        if ((y >= 365 && y < 435)) {  // 'Seconds -'
          if (tempTD > 0) {
            tempTD -= 1;
          }
        }
        myGLCD.setFont(Ubuntubold);
        myGLCD.printNumI(tempAD, 713, 167);
        if (tempAD != 0) {
          myGLCD.printNumI(tempTD, 689, 340, 3);
        }
        else
        {
          myGLCD.print("   ", 689, 340);
        }
      }
      if ((x >= 200 && x < 275)) { // 'Home' & 'Bright' Column
        if ((y >= 105 && y < 175)) { // 'Home +'
          if ( tempHD < 20) {
            tempHD += 1;
          }
        }
        if ((y >= 190 && y < 260)) { // 'Home -'
          if (tempHD > 1) {
            tempHD -= 1;
          }
        }
        if ((y >= 280 && y < 350)) {  // 'Bright +'
          if (BackLight < 16) {
            BackLight += 1;
          }
        }
        if ((y >= 365 && y < 435)) {  // 'Bright -'
          if (BackLight > 2) {
            BackLight -= 1;
          }
        }
        myGLCD.setFont(Ubuntubold);
        myGLCD.printNumI(tempHD, 338, 167, 2);
        myGLCD.printNumI(BackLight, 313, 340, 2);
      }
      break;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  ALL OTHER ROUTINES //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
time_t syncProvider()
{
  //this does the same thing as RTC_DS1307::get()
#if(DS1307)
  return rtc.now().unixtime();
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////
void updateTimeDate()
{
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  time_t timeNow = rtc.now().unixtime();
  // draw date and time
  if ((hour(timeNow) != prevRTC.Hour) || (minute(timeNow) != prevRTC.Minute) || !updateTime) { //time
    prevRTC.Hour = hour(timeNow);
    prevRTC.Minute = minute(timeNow);
    byte ampm = isPM(timeNow);
    int hr_12 = hourFormat12(timeNow);
    printTime(timeNow, 250, 2);
  }
  if ((day(timeNow) != prevRTC.Day) || (month(timeNow) != prevRTC.Month) ||
      (year(timeNow) != prevRTC.Year || !updateTime))
  {
    prevRTC.Day = day(timeNow);
    prevRTC.Month = month(timeNow);
    printDate(timeNow, 400, 2);
  }
  updateTime = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void printTime(time_t timeNow, int posx, int posy)
{
  char tmpTime[8], charT[3];
  tmpTime[0] = '\0';
  if (hourFormat12(timeNow) >= 0 && hourFormat12(timeNow) < 10) { //add space
    strcat(tmpTime, " ");
    itoa(hourFormat12(timeNow), charT, 10);
    strcat(tmpTime, charT);
  }
  else
    itoa(hourFormat12(timeNow), tmpTime, 10);
  strcat(tmpTime, ":");
  if (minute(timeNow) >= 0 && minute(timeNow) < 10) {
    strcat(tmpTime, "0");
    itoa(minute(timeNow), charT, 10);
    strcat(tmpTime, charT);
  }
  else {
    itoa(minute(timeNow), charT, 10);
    strcat(tmpTime, charT);
  }
  if (isPM(timeNow) == 0) strcat(tmpTime, "am");
  else strcat(tmpTime, "pm");
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(tmpTime, posx, posy);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void printDate(time_t timeNow, int x, int y)
{
  char  chDate[25], tmpChar[5];
  strcat(chDate, "     ");
  chDate[0] = '\0';
  strcat(chDate, Day[weekday(timeNow)]);
  strcat(chDate, ", ");
  strcat(chDate, Month[month(timeNow)]);
  if (day(timeNow) < 10)
  {
    strcat(chDate, "  ");
  }
  else
  {
    strcat(chDate, " ");
  }
  itoa(day(timeNow), tmpChar, 10);
  strcat(chDate, tmpChar);
  // this line is for omitting year
  strcat(chDate, "  ");
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(chDate, x, y);            //Display date
}
//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                Supporting 'stuff' added by Graham Lawrence                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////
void SetDatePrint(int x, int y)
{
  char  chDate[25], tmpChar[5];
  strcat(chDate, "     ");
  chDate[0] = '\0';
  strcat(chDate, Month[tmpRTC.Month]);
  if (tmpRTC.Day < 10) {
    strcat(chDate, "   ");
  }
  else
  {
    strcat(chDate, "  ");
  }
  itoa(tmpRTC.Day, tmpChar, 10);
  strcat(chDate, tmpChar);
  strcat(chDate, " ");
  itoa(tmpRTC.Year + 1970, tmpChar, 10);
  strcat(chDate, tmpChar);
  myGLCD.setFont(Ubuntubold);
  myGLCD.print(chDate, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetTimePrint(int x, int y)
{
  char  chDate[25], tmpChar[5];
  strcat(chDate, "     ");
  chDate[0] = '\0';
  if (tmpRTC.Hour < 10) {
    strcat(chDate, " ");
  }
  itoa(tmpRTC.Hour, tmpChar, 10);
  strcat(chDate, tmpChar);
  strcat(chDate, " : ");
  if (tmpRTC.Minute < 10) {
    strcat(chDate, "0");
  }
  itoa(tmpRTC.Minute, tmpChar, 10);
  strcat(chDate, tmpChar);
  strcat(chDate, " .00");
  myGLCD.setFont(Ubuntubold);
  myGLCD.print(chDate, x, y);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                         Misting Screen time printing and blanking routine                     //
///////////////////////////////////////////////////////////////////////////////////////////////////
void MistTimePrint(SCHEDULE mist, byte mscreen)
{
  byte stH, stM, duM, duS;
  switch (mscreen) {
    case 1:
      if (!(mist.Enable & 0xf0))
      {
        Serial.println("Mistscreen 1 AND disbled");
        blankMistTime();
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(187, 216, 231, 251);
        dowBlank(0);
      }
      else
      {
        Serial.println("Mistscreen 1 AND enabled");
        stH = mist.On1Hr;
        stM = mist.On1Min;
        duM = mist.Dur1Min;
        duS = mist.Dur1Sec;
        formatMistTime(stH, stM, duM, duS);
        myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);
        dowBlank(mist.OnDay);
        dowFrog(mist.OnDay);
      }
      break;
    case 2:
      if (!(mist.Enable & 0x0f))
      {
        Serial.println("Mistscreen 2 AND disabled");
        blankMistTime();
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(187, 216, 231, 251);
        dowBlank(0);
      }
      else
      {
        Serial.println("Mistscreen 2 AND enabled");
        stH = mist.On2Hr;
        stM = mist.On2Min;
        duM = mist.Dur2Min;
        duS = mist.Dur2Sec;
        formatMistTime( stH, stM, duM, duS);
        myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);
        dowBlank(mist.OnDay2);
        dowFrog(mist.OnDay2);
      }
      break;
    case 3:
      if (!(mist.Enable & 0xf0))
      {
        Serial.println("Mistscreen 3 AND disabled");
        blankMistTime();
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(187, 216, 231, 251);
        dowBlank(0);
      }
      else
      {
        Serial.println("Mistscreen 3 AND enabled");
        stH = mist.On1Hr;
        stM = mist.On1Min;
        duM = mist.Dur1Min;
        duS = mist.Dur1Sec;
        formatMistTime( stH, stM, duM, duS);
        myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);
        dowBlank(mist.OnDay);
        dowFrog(mist.OnDay);
      }
      break;
    case 4:
      if (!(mist.Enable & 0x0f))
      {
        Serial.println("Mistscreen 4 AND disabled");
        blankMistTime();
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(187, 216, 231, 251);
        dowBlank(0);
      }
      else
      {
        Serial.println("Mistscreen 4 AND enabled");
        stH = mist.On2Hr;
        stM = mist.On2Min;
        duM = mist.Dur2Min;
        duS = mist.Dur2Sec;
        formatMistTime( stH, stM, duM, duS);
        myFiles.load(187, 216, 45, 36, "Frog.raw", 16, 0);
        dowBlank(mist.OnDay2);
        dowFrog(mist.OnDay2);
      }
      break;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                  Misting Screen time printing and blanking support routines                   //
///////////////////////////////////////////////////////////////////////////////////////////////////
void formatMistTime(byte Hr, byte Min, byte dMin, byte dSec)
{
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(Ubuntubold);
  myGLCD.printNumI(Hr, 314, 216, 2, ' ');
  myGLCD.printNumI(Min, 428, 216, 2, '0');
  myGLCD.printNumI(dMin, 576, 216, 2 , ' ');
  myGLCD.printNumI(dSec, 707, 216, 2, '0');
}
void blankMistTime()
{
  myGLCD.setFont(Ubuntubold);
  myGLCD.print("  ", 314, 216);
  myGLCD.print("  ", 428, 216);
  myGLCD.print("  ", 576, 216);
  myGLCD.print("  ", 707, 216);
}
void dowFrog(byte dow)
{
  //  char fname[] = "Frog.raw";
  if (dow & 0x01) myGLCD.drawBitmap (209, 357, 45, 36, frog);
  if (dow & 0x02) myGLCD.drawBitmap (285, 357, 45, 36, frog);
  if (dow & 0x04) myGLCD.drawBitmap (358, 357, 45, 36, frog);
  if (dow & 0x08) myGLCD.drawBitmap (434, 357, 45, 36, frog);
  if (dow & 0x10) myGLCD.drawBitmap (511, 357, 45, 36, frog);
  if (dow & 0x20) myGLCD.drawBitmap (589, 357, 45, 36, frog);
  if (dow & 0x40) myGLCD.drawBitmap (663, 357, 45, 36, frog);
  // myFiles.load(209, 357, 45, 36, fname , 16, 0);
}
void dowBlank(byte dow)
{
  myGLCD.setColor(0, 0, 0);
  if (!(dow & 0x01)) myGLCD.fillRect(209, 357, 253, 392);
  if (!(dow & 0x02)) myGLCD.fillRect(285, 357, 328, 392);
  if (!(dow & 0x04)) myGLCD.fillRect(358, 357, 402, 392);
  if (!(dow & 0x08)) myGLCD.fillRect(434, 357, 479, 392);
  if (!(dow & 0x10)) myGLCD.fillRect(511, 357, 555, 392);
  if (!(dow & 0x20)) myGLCD.fillRect(589, 357, 632, 392);
  if (!(dow & 0x40)) myGLCD.fillRect(663, 357, 708, 392);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                         Fan/Fog Screen time printing and blanking routine                     //
///////////////////////////////////////////////////////////////////////////////////////////////////
void ffTimePrint(SCHEDULE mist, byte mscreen)
{
  byte stH, stM, duM, duS;
  switch (mscreen) {
    case 1:
      if (!(mist.Enable & 0xf0))
      {
        Serial.println("FanFog screen 1 AND disbled");
        blankFogfanTime(mscreen);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(79, 233, 113, 259);
        ffBlank(0);
      }
      else
      {
        Serial.println("FanFog screen 1 AND enabled");
        stH = mist.On1Hr;
        stM = mist.On1Min;
        duM = mist.Dur1Min;
        duS = mist.Dur1Sec;
        formatFogfanTime(stH, stM, duM, duS, mscreen);
        myGLCD.drawBitmap (79, 233, 35, 27, smfrog);
        ffBlank(mist.OnDay);
        ffFrog(mist.OnDay);
      }
      break;
    case 2:
      if (!(mist.Enable & 0x0f))
      {
        Serial.println("FanFog screen 2 AND disabled");
        blankFogfanTime(mscreen);
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(79, 363, 113, 389);
        ffBlank(0);
      }
      else
      {
        Serial.println("FanFog screen 2 AND enabled");
        stH = mist.On2Hr;
        stM = mist.On2Min;
        duM = mist.Dur2Min;
        duS = mist.Dur2Sec;
        formatFogfanTime( stH, stM, duM, duS, mscreen);
        myGLCD.drawBitmap (79, 363, 35, 27, smfrog);
        ffBlank(mist.OnDay2);
        ffFrog(mist.OnDay2);
      }
      break;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                  Fan/Fog Screen time printing and blanking support routines                   //
///////////////////////////////////////////////////////////////////////////////////////////////////
void formatFogfanTime(byte Hr, byte Min, byte dMin, byte dSec, byte mscreen)
{
  switch (mscreen)
  {
    case 1:
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(Ubuntubold);
      myGLCD.printNumI(Hr, 210, 210, 2, ' ');
      myGLCD.printNumI(Min, 328, 210, 2, '0');
      myGLCD.printNumI(dMin, 480, 210, 2 , ' ');
      myGLCD.printNumI(dSec, 598, 210, 2, '0');
      break;
    case 2:
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(Ubuntubold);
      myGLCD.printNumI(Hr, 210, 344, 2, ' ');
      myGLCD.printNumI(Min, 328, 344, 2, '0');
      myGLCD.printNumI(dMin, 480, 344, 2 , ' ');
      myGLCD.printNumI(dSec, 598, 344, 2, '0');
      break;
  }
}
void blankFogfanTime(byte mscreen)
{
  switch (mscreen)
  {
    case 1:
      myGLCD.setFont(Ubuntubold);
      myGLCD.print("  ", 210, 210);
      myGLCD.print("  ", 328, 210);
      myGLCD.print("  ", 480, 210);
      myGLCD.print("  ", 598, 210);
      break;
    case 2:
      myGLCD.setFont(Ubuntubold);
      myGLCD.print("  ", 210, 344);
      myGLCD.print("  ", 328, 344);
      myGLCD.print("  ", 480, 344);
      myGLCD.print("  ", 598, 344);
      break;
  }
}
void ffFrog(byte dow)
{
  if (dow & 0x01) myGLCD.drawBitmap (678, 133, 35, 27, smfrog);
  if (dow & 0x02) myGLCD.drawBitmap (722, 179, 35, 27, smfrog);
  if (dow & 0x04) myGLCD.drawBitmap (678, 225, 35, 27, smfrog);
  if (dow & 0x08) myGLCD.drawBitmap (722, 271, 35, 27, smfrog);
  if (dow & 0x10) myGLCD.drawBitmap (678, 317, 35, 27, smfrog);
  if (dow & 0x20) myGLCD.drawBitmap (722, 363, 35, 27, smfrog);
  if (dow & 0x40) myGLCD.drawBitmap (678, 408, 35, 27, smfrog);
}
void ffBlank(byte dow)
{
  myGLCD.setColor(0, 0, 0);
  if (!(dow & 0x01)) myGLCD.fillRect(678, 133, 712, 159);
  if (!(dow & 0x02)) myGLCD.fillRect(722, 179, 756, 205);
  if (!(dow & 0x04)) myGLCD.fillRect(678, 225, 712, 251);
  if (!(dow & 0x08)) myGLCD.fillRect(722, 271, 756, 297);
  if (!(dow & 0x10)) myGLCD.fillRect(678, 317, 712, 343);
  if (!(dow & 0x20)) myGLCD.fillRect(722, 363, 756, 389);
  if (!(dow & 0x40)) myGLCD.fillRect(678, 408, 712, 434);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
#if DS1307 == 0
void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
  if (Serial.find(TIME_HEADER)) {
    pctime = Serial.parseInt();
    if ( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
      rtc.adjust(pctime); // Sync Arduino clock to the time received on the serial port
      setTime(pctime);
#if debug
      Serial.println(F("Time Set"));
#endif
    }
  }
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
void myCopyTime(tmElements_t * mytime)
{
  DateTime now = rtc.now();
  mytime->Month = now.month();
  mytime->Day = now.day();
  mytime->Year = now.year() - 1970;
  mytime->Hour = now.hour();
  mytime->Minute = now.minute();
  mytime->Second = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void DoScreen(byte page, byte screen) {
  myGLCD.setDisplayPage(page);
  myGLCD.setWritePage(page);
  dispScreen = screen;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////    DS18b20 TEMP SENSORS   /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void tempRead(float & temp1a, float & temp2a, float & temp3a)
{
  byte numSensors = sensors.getDeviceCount();
  temp1a = 0.0, temp2a = 0.0, temp3a = 0.0;
  if (numSensors >= 1)
  {
    temp1a = sensors.getTempFByIndex(0);
    if (temp1a == 185.0) temp1a = 0.0;
  }
  if (numSensors >= 2)
  {
    temp2a = sensors.getTempFByIndex(1);
    if (temp2a == 185.0) temp2a = 0.0;
  }
  if (numSensors >= 3)
  {
    temp3a = sensors.getTempFByIndex(2);
    if (temp3a == 185.0) temp3a = 0.0;
  }
  sensors.requestTemperatures();
  tempTime = now();
}
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////    DHT22 HUMIDITY SENSORS   ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void humRead(float & hum1a)
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int chk = DHT.read22(DHTPIN);
  if (chk == DHTLIB_OK) {
    hum1a = DHT.humidity;
    humidTime = now();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    ALARM HANDLERS/   /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    Relay handlers    /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void relayOff(byte flag)
{
  Relay |= (1 << flag);
}
void relayOn(byte flag)
{
  Relay &= ~(1 << flag);
}

void procRelays(byte relay)
{
  char relays[][10] = {"swon.raw" , "swoff.raw" };
  if (relay != prevRelay)
  {
    if ((relay & (1 << pwrLight1)) == (1 << pwrLight1)) // Lights 1
    {
      myFiles.load(555, 418, 22, 22, relays[1], 16, 0);
    }
    else
    {
      myFiles.load(555, 418, 22, 22, relays[0], 16, 0);
    }
    if ((relay & (1 << pwrLight2)) == (1 << pwrLight2)) // Lights 2
    {
      myFiles.load(580, 418, 22, 22, relays[1], 16, 0);
    }
    else
    {
      myFiles.load(580, 418, 22, 22, relays[0], 16, 0);
    }
    if ((relay & (1 << pwrTemp1)) == (1 << pwrTemp1)) // Temp 1
    {
      myFiles.load(614, 418, 22, 22, relays[1], 16, 0);
    }
    else
    {
      myFiles.load(614, 418, 22, 22, relays[0], 16, 0);
    }
    if ((relay & (1 << pwrFogger1)) == (1 << pwrFogger1)) // Fog 1
    {
      myFiles.load(655, 418, 22, 22, relays[1], 16, 0);
    }
    else
    {
      myFiles.load(655, 418, 22, 22, relays[0], 16, 0);
    }
    if ((relay & (1 << pwrMisting1)) == (1 << pwrMisting1)) // Mist 1
    {
      myFiles.load(694, 418, 22, 22, relays[1], 16, 0);
    }
    else
    {
      myFiles.load(694, 418, 22, 22, relays[0], 16, 0);
    }
    if ((relay & (1 << pwrFan1)) == (1 << pwrFan1)) // Fan 1
    {
      myFiles.load(732, 418, 22, 22, relays[1], 16, 0);
    }
    else
    {
      myFiles.load(732, 418, 22, 22, relays[0], 16, 0);
    }
    prevRelay = relay;
  }
}

