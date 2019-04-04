//lcd 128 x 160 px

#define LCDCONSTRUCTOR TFT_eSPI
LCDCONSTRUCTOR tft = TFT_eSPI();

void showInfoLcd()
{
    TRACE;

    //drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color)
    //tft.drawRoundRect();

    //tft.fillScreen(TFT_BLACK); // CLEAR
    tft.setCursor(3, 5);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    tft.setTextSize(2);

    tft.print(packBasicInfo.Volts);
    tft.print("V");
    tft.println();
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.print(packBasicInfo.Amps);
    tft.print("A");
    tft.println();
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print(packBasicInfo.CapacityRemainAh);
    tft.print("Ah");
    tft.println();
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(packBasicInfo.CapacityRemainPercent);
    tft.print("%");
    tft.println();

    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    tft.print(packBasicInfo.Temp1);
    tft.print("C");
    tft.println();
    //------------draw little battery symbols---------
    for (uint8_t i = 0; i < 12; i++)
    {
        //       (uint8_t origin_x, uint8_t origin_y, uint8_t width, uint8_t height, float value, float valueMin, float valueMax, LCDCONSTRUCTOR &refLCD)
        lcdBargraphVertical(i * 10 + 4, 108, 8, 20, packCellInfo.CellVolt[i], c_cellAbsMin, c_cellAbsMax, packCellInfo.CellColor[i], tft); //packCellInfo.CellVolt[0]
    }

    //------------draw testing rectagle---------

    tft.fillRect(100, 10, 10, 10, packCellInfo.CellColor[0]);

    //-------------print cell voltges--------
    /*
    for (byte i = 1; i <= packCellInfo.NumOfCells; i++)
    {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
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
        tft.print(packCellInfo.CellVolt[i - 1]);
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
}

void lcdStartup()
{
    tft.init();
    tft.fillScreen(TFT_BLACK); // CLEAR

    tft.setRotation(0); //
    tft.setCursor(3, 5);
    tft.setTextColor(TFT_WHITE);
    tft.println("starting");
    tft.println("looking for BMS...");
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

void lcdBargraphVertical(uint8_t origin_x, uint8_t origin_y, uint8_t width, uint8_t height, float value, float valueMin, float valueMax, uint32_t insideColor, LCDCONSTRUCTOR &refLCD)
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
    uint8_t box_min_height = 0;
    uint8_t box_max_height = height - spacing;

    uint8_t nipple_origin_x = box_origin_x;
    uint8_t nipple_origin_y = origin_y - spacing;
    uint8_t nipple_width = box_width;
    uint8_t nipple_height = spacing;

    refLCD.fillRect(box_origin_x, box_origin_y, box_width, box_max_height, TFT_BLACK); // "delete" old battery

    // uint8_t box_height = map((value * 1000), (valueMin * 1000), (valueMax * 1000), box_min_height, box_max_height); //this doesnt not work. it writes to bad memory place breaking cellavg
    //fixed by this hack

    value = value * 1000;
    valueMin = valueMin * 1000;
    valueMax = valueMax * 1000;

    uint8_t box_height = round(map(value, valueMax, valueMin, box_min_height, box_max_height));
    box_origin_y = box_origin_y + box_height;
    box_height = box_max_height - box_height - spacing;

    //
    refLCD.drawRect(origin_x, origin_y, width, height, TFT_WHITE); //(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h)
    refLCD.fillRect(nipple_origin_x, nipple_origin_y, nipple_width, nipple_height, TFT_WHITE);

    refLCD.fillRect(box_origin_x, box_origin_y, box_width, box_height, insideColor);
}
