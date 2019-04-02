//                                       (/* rotation */, /* reset=*/, /* clock=*/ , /* data=*/ );   // ESP32 Thing, HW I2C with pin remapping

U8G2_SH1106_128X64_NONAME_F_HW_I2C oled1(U8G2_R0, U8X8_PIN_NONE, 27, 33); // ESP32 Thing, HW I2C with pin remapping
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled2(U8G2_R0, U8X8_PIN_NONE, 27, 33); // ESP32 Thing, HW I2C with pin remapping

void oled_startup()
{
    oled1.setI2CAddress(0x3C * 2); //<- SOLVED it works
    oled2.setI2CAddress(0x3D * 2); //<- SOLVED it works

    oled1.begin();
    oled2.begin();
    //oled1.setFont(u8g_font_6x10);
    //oled2.setFont(u8g_font_6x10);
}

void showInfoOled()
{
    char buffer[10];
    static uint8_t yy;
    oled1.clearBuffer();
    yy++;
    if (yy > 63)
    {
        yy = 0;
    }

    oled1.drawHLine(0, yy, 128);

    //oled1.setFont(u8g_font_6x10);
    oled1.setFont(u8g_font_10x20);
    oled1.drawStr(0, 20, "OLED 1");

    dtostrf(packBasicInfo.Volts, 5, 2, buffer);

    oled1.drawStr(0, 40, buffer);
    oled1.drawStr(50, 40, "V");

    itoa(yy, buffer, 10);
    oled1.drawStr(0, 60, buffer);
    oled1.sendBuffer();

    oled2.clearBuffer();
    //oled2.setFont(u8g_font_6x10);
    oledBargraphVerticaloled2(64,10, 15, 38, packCellInfo.CellAvg, 2.7, 4.2);
    oled2.setFont(u8g_font_10x20);
    oled2.drawStr(0, 20, "OLED 2");
    dtostrf(packCellInfo.CellAvg, 5, 2, buffer);
    oled2.drawStr(0, 40, buffer);
    oled2.drawStr(50, 40, "V");
    oled2.sendBuffer();
}

void oledBargraphVerticaloled2(uint8_t origin_x, uint8_t origin_y, uint8_t size_x, uint8_t size_y, uint8_t value, uint8_t valueMin, uint8_t valueMax)
{
    const uint8_t spacing = 2;
    uint8_t internal_height;
    uint8_t calc_origin_y;

    internal_height = origin_y - spacing * 2;
    calc_origin_y = map(value, valueMin, valueMax, origin_y+spacing, internal_height); //(long x, long in_min, long in_max, long out_min, long out_max)
    oled2.drawFrame(origin_x, origin_y, size_x, size_y); //(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h)
    
    oled2.drawBox(origin_x + spacing, calc_origin_y + spacing, size_x - spacing*2, size_y - spacing*2);

}