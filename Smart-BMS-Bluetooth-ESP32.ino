/**
  Program to read out and display
  data from xiaoxiang Smart BMS
  over Bluetooth Low Energy
  https://www.lithiumbatterypcb.com/
  Tested with original BLE module provided.
  Might work with generic BLE module when UUIDs are modified

  Needs ESP32 and graphic display.
  Tested on TTGO TS https://github.com/LilyGO/TTGO-TS

  (c) Miroslav Kolinsky 2019
  https://www.kolins.cz

  thanks to Petr Jenik for big parts of code
  thanks to Milan Petrzilka

  known bugs:
  -if BLE server is not available during startup, program hangs
  -reconnection sort of works, sometimes ESP reboots
*/

//#define TRACE commSerial.println(__FUNCTION__)
#define TRACE
#include <Arduino.h>
#include "BLEDevice.h"
#include "BLEScan.h"  //why this is commented?
#include "mydatatypes.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Wire.h>
#include "settings.h"

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <WebServer.h>
// #include <Update.h>
// #include "webpages.h"

HardwareSerial commSerial(0);
HardwareSerial bmsSerial(1);
//WebServer server(80);

//---- global variables ----

static boolean doConnect = false;
static boolean BLE_client_connected = false;
static boolean doScan = false;

packBasicInfoStruct packBasicInfo;  //here shall be the latest data got from BMS
packEepromStruct packEeprom;	      //here shall be the latest data got from BMS
packCellInfoStruct packCellInfo;    //here shall be the latest data got from BMS

const byte cBasicInfo3 = 3; //type of packet 3= basic info
const byte cCellInfo4 = 4;  //type of packet 4= individual cell info

unsigned long previousMillis = 0;
unsigned long previousMillisl = 0;
const long myinterval = 5000;
const long interval = 4000;

bool toggle = false;
bool newPacketReceived = false;
int i = 0;
void setup()
{

  commSerial.begin(115200, SERIAL_8N1, 3, 1);
  bmsSerial.begin(9600, SERIAL_8N1, 21, 22);
  commSerial.println("Starting BMS dashboard application...");
  //	stripStartup();
  //	oled_startup();
  lcdStartup();
  // newtworkStartup();
  commSerial.println("LCD fertig...");

  bleStartup();
  lcdclear();
  showInfoLcd();
  lcdwarte();
//  linearMeter(99, 10, 310, 5, 10, 1, 30, 5);
//  for (int wi = 0; wi <= 100; wi = wi + 5) {
//    kreis(wi,120, 90,80,80);
//   delay(500);
//  }
}
//---------------------main loop------------------
void loop()
{
  //server.handleClient();
  bleRequestData();

/*
  if (newPacketReceived == true)
  {
    showInfoLcd();
    printBasicInfo();
    printCellInfo();
    commSerial.println("-");

  }
  commSerial.print(".");
  i++;
  if (i > 60) {
    i = 0;
    commSerial.println();
  }
  */
  delay(1000);
}
//---------------------/ main loop------------------
