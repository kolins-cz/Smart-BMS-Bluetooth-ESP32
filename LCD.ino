TFT_eSPI tft = TFT_eSPI();



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

    tft.print(packBasicInfo.Amps);
    tft.print("A");
    tft.println();

    tft.print(packBasicInfo.CapacityRemainAh);
    tft.print("Ah");
    tft.println();

    tft.print(packBasicInfo.CapacityRemainPercent);
    tft.print("%");
    tft.println();

    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    tft.print(packBasicInfo.Temp1);
    tft.print("C");
    tft.println();

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
