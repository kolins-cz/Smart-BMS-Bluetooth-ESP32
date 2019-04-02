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
#define SIMULATION
#include <Arduino.h>
#include "BLEDevice.h"
//#include "BLEScan.h"
#include "mydatatypes.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <Adafruit_NeoPixel.h>
#include <U8g2lib.h>
#include <Wire.h>

HardwareSerial commSerial(0);
HardwareSerial bmsSerial(1);

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
bool newPacketReceived = true;

void setup()
{

	commSerial.begin(115200, SERIAL_8N1, 3, 1);
	bmsSerial.begin(9600, SERIAL_8N1, 21, 22);
	commSerial.println("Starting Arduino BLE Client application...");
	stripStartup();
	oled_startup();
	lcdStartup();
#ifndef SIMULATION
	bleStartup();
#endif
}

void loop()
{
#ifndef SIMULATION
	// If the flag "doConnect" is true then we have scanned for and found the desired
	// BLE Server with which we wish to connect.  Now we connect to it.  Once we are
	// connected we set the connected flag to be true.
	if (doConnect == true)
	{
		if (connectToServer())
		{
			commSerial.println("We are now connected to the BLE Server.");
			lcdConnected();
		}
		else
		{
			lcdConnectionFailed();
		}
		doConnect = false;
	}

	// If we are connected to a peer BLE Server, update the characteristic each time we are reached
	// with the current time since boot.
	if (BLE_client_connected == true)
	{

		bmsWorker();
	}
	else if (doScan)
	{
		BLEDevice::getScan()->start(0); // this is just eample to start scan after disconnect, most likely there is better way to do it in arduino
	}
#endif

#ifdef SIMULATION
	bmsWorkerSimulation();
#endif


stripTest;
}

void bmsWorker()
{
TRACE;
	unsigned long currentMillis = millis();
	if ((currentMillis - previousMillis >= interval || newPacketReceived)) //every time period or when packet is received
	{
		previousMillis = currentMillis;
		showInfoLcd();
		if (toggle) //alternate info3 and info4
		{
			bmsGetInfo3();
			showBasicInfo();
			newPacketReceived = false;
		}
		else
		{
			bmsGetInfo4();
			showCellInfo();
			newPacketReceived = false;
		}
		toggle = !toggle;
	}
}


void bmsWorkerSimulation()
{
TRACE;
	unsigned long currentMillis = millis();
	if ((currentMillis - previousMillis >= 250)) 
	{ 
		previousMillis = currentMillis;
		showInfoLcd();
		showInfoOled();
		if (toggle) //alternate info3 and info4
		{
			bmsFakeInfo3();
			//showBasicInfo();
			newPacketReceived = false;
		}
		else
		{
			bmsFakeInfo4();
			//showCellInfo();
			
		}
		toggle = !toggle;
	}

}
