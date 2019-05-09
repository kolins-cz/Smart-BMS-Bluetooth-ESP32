/*
 * IncFile1.h
 *
 * Created: 6.3.2019 11:58:57
 *  Author: z003knyu
 */

#ifndef mydatatypes_H_
#define mydatatypes_H_

typedef struct
{
	byte start;
	byte type;
	byte status;
	byte dataLen;
} bmsPacketHeaderStruct;

typedef struct
{
	uint16_t Volts; // unit 1mV
	int32_t Amps;   // unit 1mA
	int32_t Watts;   // unit 1W
	uint16_t CapacityRemainAh;
	uint8_t CapacityRemainPercent; //unit 1%
	uint32_t CapacityRemainWh; 	//unit Wh
	uint16_t Temp1;				   //unit 0.1C
	uint16_t Temp2;				   //unit 0.1C
	uint16_t BalanceCodeLow;
	uint16_t BalanceCodeHigh;
	uint8_t MosfetStatus;
	
} packBasicInfoStruct;

typedef struct
{
	uint8_t NumOfCells;
	uint16_t CellVolt[15]; //cell 1 has index 0 :-/
	uint16_t CellMax;
	uint16_t CellMin;
	uint16_t CellDiff; // difference between highest and lowest
	uint16_t CellAvg;
	uint16_t CellMedian;
	uint32_t CellColor[15];
	uint32_t CellColorDisbalance[15]; // green cell == median, red/violet cell => median + c_cellMaxDisbalance
} packCellInfoStruct;

struct packEepromStruct
{
	uint16_t POVP;
	uint16_t PUVP;
	uint16_t COVP;
	uint16_t CUVP;
	uint16_t POVPRelease;
	uint16_t PUVPRelease;
	uint16_t COVPRelease;
	uint16_t CUVPRelease;
	uint16_t CHGOC;
	uint16_t DSGOC;
};

#define STRINGBUFFERSIZE 300
char stringBuffer[STRINGBUFFERSIZE];

const int32_t c_cellNominalVoltage = 3700; //mV

const uint16_t c_cellAbsMin = 3000;
const uint16_t c_cellAbsMax = 4200;

const int32_t c_packMaxWatt = 1250;

const uint16_t c_cellMaxDisbalance = 1500; //200; // cell different by this value from cell median is getting violet (worst) color

#endif /* mydatatypes_H_ */

// Color definitions for 64k color mode
// Bits 0..4 -> Blue 0..4
// Bits 5..10 -> Green 0..5
// Bits 11..15 -> Red 0..4

#ifdef LCDDRIVER_TFT_eSPI
#define TFT_BLACK 0x0000	   /*   0,   0,   0 */
#define TFT_NAVY 0x000F		   /*   0,   0, 128 */
#define TFT_DARKGREEN 0x03E0   /*   0, 128,   0 */
#define TFT_DARKCYAN 0x03EF	/*   0, 128, 128 */
#define TFT_MAROON 0x7800	  /* 128,   0,   0 */
#define TFT_PURPLE 0x780F	  /* 128,   0, 128 */
#define TFT_OLIVE 0x7BE0	   /* 128, 128,   0 */
#define TFT_LIGHTGREY 0xC618   /* 192, 192, 192 */
#define TFT_DARKGREY 0x7BEF	/* 128, 128, 128 */
#define TFT_BLUE 0x001F		   /*   0,   0, 255 */
#define TFT_GREEN 0x07E0	   /*   0, 255,   0 */
#define TFT_CYAN 0x07FF		   /*   0, 255, 255 */
#define TFT_RED 0xF800		   /* 255,   0,   0 */
#define TFT_MAGENTA 0xF81F	 /* 255,   0, 255 */
#define TFT_YELLOW 0xFFE0	  /* 255, 255,   0 */
#define TFT_WHITE 0xFFFF	   /* 255, 255, 255 */
#define TFT_ORANGE 0xFDA0	  /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0 /* 180, 255,   0 */
#define TFT_PINK 0xFC9F
#endif

#ifdef LCDDRIVER_Adafruit_GFX
#define TFT_BLACK 0x0000
#define TFT_BLUE 0x001F
#define TFT_RED 0xF800
#define TFT_GREEN 0x07E0
#define TFT_CYAN 0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW 0xFFE0
#define TFT_WHITE 0xFFFF
#endif
