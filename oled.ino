


// //                                       (/* rotation */, /* reset=*/, /* clock=*/ , /* data=*/ );   // ESP32 Thing, HW I2C with pin remapping

// #define OLEDCONSTRUCTOR U8G2_SH1106_128X64_NONAME_F_HW_I2C

// OLEDCONSTRUCTOR oled1(U8G2_R0, U8X8_PIN_NONE, 27, 33); // ESP32 Thing, HW I2C with pin remapping
// OLEDCONSTRUCTOR oled2(U8G2_R0, U8X8_PIN_NONE, 27, 33); // ESP32 Thing, HW I2C with pin remapping

// void oled_startup()
// {
//     oled1.setI2CAddress(0x3C * 2); //<- SOLVED it works
//     oled2.setI2CAddress(0x3D * 2); //<- SOLVED it works

//     oled1.begin();
//     oled2.begin();
//     //oled1.setFont(u8g_font_6x10);
//     //oled2.setFont(u8g_font_6x10);
// }

// void showInfoOled()
// {
//     char buffer[10];
//     static uint8_t yy;
//     oled1.clearBuffer();
//     yy++;
//     if (yy > 63)
//     {
//         yy = 0;
//     }

//     oled1.drawHLine(0, yy, 128);

//     //oled1.setFont(u8g_font_6x10);
//     oled1.setFont(u8g_font_10x20);
//     oled1.drawStr(0, 20, "OLED 1");

//     dtostrf((float)packBasicInfo.Volts / 1000, 5, 2, buffer);

//     oled1.drawStr(0, 40, buffer);
//     oled1.drawStr(50, 40, "V");

//     itoa(yy, buffer, 10); //number to string
//     oled1.drawStr(0, 60, buffer);
//     oled1.sendBuffer();

//     oled2.clearBuffer();
//     //oled2.setFont(u8g_font_6x10);
//     for (uint8_t i = 0; i < 12; i++)
//     {
//         oledBargraphVertical(i * 10, 36, 8, 28, packCellInfo.CellVolt[i], c_cellAbsMin, c_cellAbsMax, oled2); //packCellInfo.CellVolt[0]
//     }

//     //oled2.setFont(u8g_font_10x20);
//     //oled2.drawStr(0, 20, "OLED 2");
//     //dtostrf(pokus, 5, 2, buffer);
//     //oled2.drawStr(0, 40, buffer);
//     //oled2.drawStr(50, 40, "V");
//     oled2.sendBuffer();
// }

// void oledBargraphVertical(uint8_t origin_x, uint8_t origin_y, uint8_t width, uint8_t height, uint16_t value, uint16_t valueMin, uint16_t valueMax, OLEDCONSTRUCTOR &refOled)
// {
//     const uint8_t spacing = 2;
//     if (value < valueMin)
//     {
//         value = valueMin;
//     }
//     if (value > valueMax)
//     {
//         value = valueMax;
//     }

//     uint8_t box_origin_x = origin_x + spacing;
//     uint8_t box_origin_y = origin_y + spacing;
//     uint8_t box_width = width - spacing * 2;
//     uint8_t box_min_height = 1;
//     uint8_t box_max_height = height - spacing;

//     uint8_t nipple_origin_x = box_origin_x;
//     uint8_t nipple_origin_y = origin_y - spacing;
//     uint8_t nipple_width = box_width;
//     uint8_t nipple_height = spacing;

//     int16_t box_height = map(value, valueMax, valueMin, box_min_height, box_max_height);
//     box_origin_y = box_origin_y + box_height;
//     box_height = box_max_height - box_height - spacing;
//     if (box_height < 0) //ugly hack
//     {
//         box_height = 0;
//     }

//     refOled.drawFrame(origin_x, origin_y, width, height); //(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h)
//     refOled.drawBox(box_origin_x, box_origin_y, box_width, box_height);
//     refOled.drawBox(nipple_origin_x, nipple_origin_y, nipple_width, nipple_height);
// }