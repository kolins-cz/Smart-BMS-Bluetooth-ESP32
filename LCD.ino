//lcd 128 x 160 px

#define LCDCONSTRUCTOR TFT_eSPI
LCDCONSTRUCTOR tft = TFT_eSPI();

void showInfoLcd()
{
    TRACE;

    //tft.fillScreen(TFT_BLACK); // CLEAR makes nasty flicker, don't use
    tft.setCursor(0, 5);

    tft.setTextSize(2);

    //---main voltage---

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.print((float)packBasicInfo.Volts / 1000);
    
    tft.print("V");
    tft.println();

    /*
    //---single cell voltage---
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.print("(");
    tft.print((float)packCellInfo.CellMedian / 1000);
    tft.print("V");
    tft.print(")");
    tft.println();
*/
    //---main current---
    tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK);
    tft.print((float)packBasicInfo.Amps / 1000);
    tft.print("A    ");
    tft.println();

    /*
    //---ampere hours---
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.print((float)packBasicInfo.CapacityRemainAh / 1000);
    tft.print("Ah");
    tft.println();
*/

    //---watts---
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.print(packBasicInfo.Watts);
    tft.print("W    ");
    tft.println();

    //---battery percent---
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(packBasicInfo.CapacityRemainPercent);
    tft.print("%");
    //tft.println();

    tft.print(" ");
    //---battery Wh---
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(packBasicInfo.CapacityRemainWh);
    tft.print("Wh");
    tft.println();

    //---temperatures---
    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.print((float)packBasicInfo.Temp1 / 10);
    tft.print("C");
    tft.print("    ");
    tft.print((float)packBasicInfo.Temp2 / 10);
    tft.print("C");
    tft.println();

    //------------draw little battery symbols---------
    for (uint8_t i = 0; i < 12; i++)
    {
        //       (uint8_t origin_x, uint8_t origin_y, uint8_t width, uint8_t height, float value, float valueMin, float valueMax, LCDCONSTRUCTOR &refLCD)
        lcdBargraphVertical(i * 10 + 4, 135, 8, 20, packCellInfo.CellVolt[i], c_cellAbsMin, c_cellAbsMax, packCellInfo.CellColor[i], packCellInfo.CellColorDisbalance[i], tft); 
    }

    //------------draw testing rectagle---------
    /*
    tft.fillRect(120, 10, 5, 10, TFT_RED);
    tft.fillRect(120, 21, 5, 10, TFT_GREEN);
    tft.fillRect(120, 32, 5, 10, TFT_BLUE);
    //tft.fillRect(100, 10, 5, 10, color24to16(packCellInfo.CellColor[0]));
*/

    //-------------print cell voltges--------
    /*
    for (byte i = 1; i <= packCellInfo.NumOfCells; i++)
    {
        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        tft.print(i);
        if (i < 10)
        {
            tft.print(".  ");
        }
        else
        {
            tft.print(". ");
        }
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.print((float)packCellInfo.CellVolt[i - 1] / 1000);
        tft.print("V");
        if (i % 2 != 0)
        {
            tft.print("  ");
        }
        else
        {
            tft.println();
        }
    }

*/
    //----draw wifi icon----
    if (WiFi.status() == WL_CONNECTED)
    {
        tft.fillRect(122, 0, 5, 5, TFT_GREEN);
    }
    else
    {
        tft.fillRect(122, 0, 5, 5, TFT_DARKGREY);
    }

    //-----draw progressbar-----

    drawBar(3, 85, 122, 15, packBasicInfo.CapacityRemainPercent, TFT_WHITE, color24to16(getPixelColorHsv(mapHue(packBasicInfo.CapacityRemainPercent, 0, 100), 255, 255)), tft);
    
    drawBar(3, 105, 122, 15, map(abs(packBasicInfo.Watts), 0, c_packMaxWatt, 0,100),TFT_WHITE, color24to16(getPixelColorHsv(mapHue(abs(packBasicInfo.Watts), c_packMaxWatt, 0), 255, 255)), tft);

}

void lcdStartNetworking()
{

    tft.println("looking for wifi AP");
}

void lcdNetworkStatus(uint8_t state)
{
    switch (state)
    {
    case 0:
        tft.println("wifi connected");
        tft.println(WiFi.localIP());
        break;
    case 1:
        tft.println("wifi failed connect");
    default:
        tft.println("unkwon error");
        break;
    }
}

void lcdStartup()
{
    tft.init();
    tft.setTextWrap(false);
    tft.fillScreen(TFT_BLACK); // CLEAR

    tft.setRotation(0); //
    tft.setCursor(3, 5);
    tft.setTextColor(TFT_WHITE);
    tft.println("starting ebike");
}

void lcdDisconnect()
{
    tft.fillScreen(TFT_BLACK); // CLEAR
    tft.setCursor(3, 5);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(2);
    tft.println("BMS lost");

    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    tft.println("");
    tft.println("reconnecting....");
    tft.println("(it may take a while)");
}

void lcdConnected()
{
    tft.setTextColor(TFT_GREEN);
    tft.println("connected!");
    delay(200);
    tft.fillScreen(TFT_BLACK); // CLEAR
}

void lcdConnectionFailed()
{

    commSerial.println("We have failed to connect to the server; there is nothin more we will do.");
    tft.setTextColor(TFT_RED);
    tft.println("connection failed!");
}

void lcdConnectingStatus(uint8_t state)
{
    switch (state)
    {
    case 0:
        tft.setTextColor(TFT_YELLOW);
        tft.setTextSize(1);
        tft.println("connecting to BMS...");
        break;
    case 1:
        tft.println("created client");
        break;
    case 2:
        tft.println("connected to server");
        break;
    case 3:
        tft.println("service not found");
        break;
    case 4:
        tft.println("found service");
        break;
    case 5:
        tft.println("char. not found");
        break;
    case 6:
        tft.println("char. found");
        break;
    default:
        break;
    }
}
void lcdExample()
{
}

void lcdBargraphVertical(uint8_t origin_x, uint8_t origin_y, uint8_t width, uint8_t height, uint16_t value, uint16_t valueMin, uint16_t valueMax, uint32_t insideColor, uint32_t outsideColor, LCDCONSTRUCTOR &refLCD)
{
    const uint8_t spacing = 2;
    if (value < valueMin)
    {
        value = valueMin;
    }
    if (value > valueMax)
    {
        value = valueMax;
    }

    uint8_t box_origin_x = origin_x + spacing;
    uint8_t box_origin_y = origin_y + spacing;
    uint8_t box_width = width - spacing * 2;
    uint8_t box_min_height = 1;
    uint8_t box_max_height = height - spacing;

    uint8_t nipple_origin_x = box_origin_x;
    uint8_t nipple_origin_y = origin_y - spacing;
    uint8_t nipple_width = box_width;
    uint8_t nipple_height = spacing;

    refLCD.fillRect(box_origin_x, box_origin_y, box_width, box_max_height, TFT_BLACK); // "delete" old battery

    int16_t box_height = map(value, valueMax, valueMin, box_min_height, box_max_height);
    box_origin_y = box_origin_y + box_height;
    box_height = box_max_height - box_height - spacing;
    if (box_height < 0) //ugly hack
    {
        box_height = 0;
    }
    outsideColor = 0xFAFAFA;
    refLCD.drawRect(origin_x, origin_y, width, height, color24to16(outsideColor)); //(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h)
    refLCD.fillRect(nipple_origin_x, nipple_origin_y, nipple_width, nipple_height, color24to16(outsideColor));

    refLCD.fillRect(box_origin_x, box_origin_y, box_width, box_height, color24to16(insideColor));
}

void drawBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t percent, uint16_t frameColor, uint16_t barColor, LCDCONSTRUCTOR &refLCD)
{
    if (percent == 0)
    {
        refLCD.fillRoundRect(x, y, w, h, 3, TFT_BLACK);
    }
    uint8_t margin = 2;
    uint16_t barHeight = h - 2 * margin;
    uint16_t barWidth = w - 2 * margin;
    refLCD.drawRoundRect(x, y, w, h, 3, frameColor);
    refLCD.fillRect(x + margin, y + margin, barWidth * percent / 100.0, barHeight, barColor);
}