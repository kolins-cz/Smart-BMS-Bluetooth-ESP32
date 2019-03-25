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
	float Volts;
	float Amps;
	float CapacityRemainAh;
	int CapacityRemainPercent; //in %
	float Temp1;
	float Temp2;
	uint16_t BalanceCodeLow;
	uint16_t BalanceCodeHigh;
	uint8_t MosfetStatus;
} packBasicInfoStruct;

typedef struct
{
	byte NumOfCells;
	float CellVolt[15]; //cell 1 has index 0 :-/
	float CellMax;
	float CellMin;
	float CellDiff; // difference between highest and lowest
	float CellAvg;
} packCellInfoStruct;


struct  packEepromStruct
{
	float POVP; 
	float PUVP;
	float COVP;
	float CUVP;
	float POVPRelease;
	float PUVPRelease;
	float COVPRelease;
	float CUVPRelease;
	uint16_t CHGOC;
	uint16_t DSGOC;
};










#endif /* mydatatypes_H_ */

#ifdef LCDDRIVER_TFT_eSPI
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFC9F
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

