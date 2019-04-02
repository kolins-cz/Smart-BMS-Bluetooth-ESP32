//                                       (/* rotation */, /* reset=*/, /* clock=*/ , /* data=*/ );   // ESP32 Thing, HW I2C with pin remapping

U8G2_SH1106_128X64_NONAME_F_HW_I2C oled1(U8G2_R0, U8X8_PIN_NONE, 27, 33); // ESP32 Thing, HW I2C with pin remapping
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled2(U8G2_R0, U8X8_PIN_NONE, 27, 33); // ESP32 Thing, HW I2C with pin remapping


void oled_startup()
{
    oled1.setI2CAddress(0x3C * 2); //<- SOLVED it works
    oled2.setI2CAddress(0x3D * 2); //<- SOLVED it works
    
    oled1.begin();
    oled2.begin();
    oled1.setFont(u8g_font_6x10);
    oled2.setFont(u8g_font_6x10);
}


void showInfoOled()
{
     char buffer[10];
    oled1.clearBuffer();
    oled1.setFont(u8g_font_6x10);
    oled1.drawStr(0, 10, "OLED 1");
    dtostrf(packBasicInfo.Volts,5,2,buffer);
    oled1.drawStr(0, 30, buffer);
    oled1.drawStr(50, 30, "V");
    //oled1.drawFloat(packBasicInfo.Volts,2,2,30);
    oled1.sendBuffer();

    oled2.clearBuffer();
    oled2.setFont(u8g_font_6x10);
    oled2.drawStr(0, 10, "OLED 2");
    dtostrf(packCellInfo.CellAvg,5,2,buffer);
    oled2.drawStr(0, 30, buffer);
    oled2.drawStr(50, 30, "V");
    oled2.sendBuffer();
}