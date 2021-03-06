typedef struct {
  byte Enable;   // If Lights, not used                                                             //
  byte On1Hr;                                                                                       //
  byte On1Min;                                                                                      //
  byte Dur1Min;  // If Lights, then Lights1 Off1Hr                                                  //
  byte Dur1Sec;  // If Lights, then Lights1 Off1Min                                                 //
  byte On2Hr;                                                                                       //
  byte On2Min;                                                                                      //
  byte Dur2Min;  // If Lights, then Lights2 Off2Hr                                                  //
  byte Dur2Sec;  // If Lights, then Lights2 Off2Min                                                 //
  byte OnDay;    // If Lights, not used  On1   ( 0x7F = All week; 0/Sat/Fri/Thu/Wed/Tue/Mon/Sun )   //
  byte OnDay2;   //                      On2   ( 0x7F = All week; 0/Sat/Fri/Thu/Wed/Tue/Mon/Sun )   //
} SCHEDULE ;                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    FIRST RUN SETUP   /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void firstRunSetup()
{
  // I'm going to save 51 into EEPROM bank 2000 as a check
  if (EEPROM.read(2000) != 52)
  {
    EEPROM.write(2000, 52);      // write to EEPROM so this never runs again
    EEPROM.write(1, 1);          //       <- HomeDelay
    EEPROM.write(2, 16);         //       <- BackLight
    EEPROM.write(3, 1);          //       <- AutoDim
    EEPROM.write(4, 10);         //       <- TouchDelay
    EEPROM.writeFloat(5, 42.9);  //       <- Heater
    EEPROM.writeFloat(9, 102.9); //       <- Fan
    EEPROM.write(13, 8);         //       <- Light.On1Hr
    EEPROM.write(14, 15);        //       <- Light.On1Min
    EEPROM.write(15, 10);        //       <- Light.Dur1Min
    EEPROM.write(16, 30);        //       <- Light.Dur1Sec
    EEPROM.write(17, 16);        //       <- Light.On2Hr
    EEPROM.write(18, 30);        //       <- Light.On2Min
    EEPROM.write(19, 19);        //       <- Light.Dur2Min
    EEPROM.write(20, 45);        //       <- Light.Dur2Sec
    EEPROM.write(21, 0xFF);      //       <- Fog.Enable ( F0 = 1 enable, 2 disable, FF = 1 & 2 enable )
    EEPROM.write(22, 8);         //       <- Fog.On1Hr
    EEPROM.write(23, 15);        //       <- Fog.On1Min
    EEPROM.write(24, 10);        //       <- Fog.Dur1Min
    EEPROM.write(25, 30);        //       <- Fog.Dur1Sec
    EEPROM.write(26, 16);        //       <- Fog.On2Hr
    EEPROM.write(27, 30);        //       <- Fog.On2Min
    EEPROM.write(28, 19);        //       <- Fog.Dur2Min
    EEPROM.write(29, 45);        //       <- Fog.Dur2Sec
    EEPROM.write(30, 0x33);      //       <- Fog.OnDay
    EEPROM.write(31, 0x55);      //       <- Fog.OnDay2
    EEPROM.write(32, 0xFF);      //       <- Mist.Enable ( F0 = 1 enable, 2 disable, FF = 1 & 2 enable )
    EEPROM.write(33, 8);         //       <- Mist.On1Hr
    EEPROM.write(34, 15);        //       <- Mist.On1Min
    EEPROM.write(35, 0);         //       <- Mist.Dur1Min
    EEPROM.write(36, 30);        //       <- Mist.Dur1Sec
    EEPROM.write(37, 16);        //       <- Mist.On2Hr
    EEPROM.write(38, 0);         //       <- Mist.On2Min
    EEPROM.write(39, 0);         //       <- Mist.Dur2Min
    EEPROM.write(40, 45);        //       <- Mist.Dur2Sec
    EEPROM.write(41, 127);       //       <- Mist.OnDay
    EEPROM.write(42, 127);       //       <- Mist.OnDay2
    EEPROM.write(43, 0xF0);      //       <- Mist2.Enable ( F0 = 3 enable, 4 disable, FF = 3 & 4 enable )
    EEPROM.write(44, 8);         //       <- Mist2.On1Hr
    EEPROM.write(45, 15);        //       <- Mist2.On1Min
    EEPROM.write(46, 0);         //       <- Mist2.Dur1Min
    EEPROM.write(47, 30);        //       <- Mist2.Dur1Sec
    EEPROM.write(48, 16);        //       <- Mist2.On2Hr
    EEPROM.write(49, 50);        //       <- Mist2.On2Min
    EEPROM.write(50,  0);        //       <- Mist2.Dur2Min
    EEPROM.write(51, 45);        //       <- Mist2.Dur2Sec
    EEPROM.write(52, 127);       //       <- Mist2.OnDay  ( 0x7F = All week; 0/Sat/Fri/Thu/Wed/Tue/Mon/Sun )
    EEPROM.write(53, 127);       //       <- Mist2.OnDay2 ( 0x7F = All week; 0/Sat/Fri/Thu/Wed/Tue/Mon/Sun )
    EEPROM.write(54, 0x00);      //       <- Fan.Enable ( 0xF0 = 1 enable, 2 disable, 0xFF = 1 & 2 enable )
    EEPROM.write(55, 8);         //       <- Fan.On1Hr
    EEPROM.write(56, 15);        //       <- Fan.On1Min
    EEPROM.write(57, 10);        //       <- Fan.Dur1Min
    EEPROM.write(58, 30);        //       <- Fan.Dur1Sec
    EEPROM.write(59, 16);        //       <- Fan.On2Hr
    EEPROM.write(60, 30);        //       <- Fan.On2Min
    EEPROM.write(61, 19);        //       <- Fan.Dur2Min
    EEPROM.write(62, 45);        //       <- Fan.Dur2Sec
    EEPROM.write(63, 127);       //       <- Fan.OnDay
    EEPROM.write(64, 127);       //       <- Fan.OnDay2
  }
}

