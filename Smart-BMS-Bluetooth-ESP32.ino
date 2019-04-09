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
//#define SIMULATION
#include <Arduino.h>
#include "BLEDevice.h"
//#include "BLEScan.h"  //why this is commented?
#include "mydatatypes.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <NeoPixelBrightnessBus.h>
#include <U8g2lib.h>
#include <Wire.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include "webpages.h"

HardwareSerial commSerial(0);
HardwareSerial bmsSerial(1);
WebServer server(80);

//---- global variables ----

static boolean doConnect = false;
static boolean BLE_client_connected = false;
static boolean doScan = false;

packBasicInfoStruct packBasicInfo; //here shall be the latest data got from BMS
packEepromStruct packEeprom;	   //here shall be the latest data got from BMS
packCellInfoStruct packCellInfo;   //here shall be the latest data got from BMS

const byte cBasicInfo3 = 3; //type of packet 3= basic info
const byte cCellInfo4 = 4;  //type of packet 4= individual cell info

unsigned long previousMillis = 0;
const long interval = 2000;

bool toggle = false;
bool newPacketReceived = false;

void setup()
{

	commSerial.begin(115200, SERIAL_8N1, 3, 1);
	bmsSerial.begin(9600, SERIAL_8N1, 21, 22);
	commSerial.println("Starting ebike dashboard application...");
	//	stripStartup();
	//	oled_startup();
	lcdStartup();
	newtworkStartup();
	bleStartup();
}
//---------------------main loop------------------
void loop()
{
	bleRequestData();
	server.handleClient();
	if (newPacketReceived == true)
	{
		showInfoLcd;
	}
}
//---------------------/ main loop------------------
