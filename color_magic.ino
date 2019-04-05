unsigned int color24to16(unsigned long rgb)
{ //convert 24 bit RGB to 16bit 5:6:5 RGB

    return (((rgb & 0xf80000) >> 8) | ((rgb & 0xfc00) >> 5) | ((rgb & 0xf8) >> 3));
}


uint16_t mapHue(uint16_t input, uint16_t min, uint16_t max) 
{//maps hue from 0 to max to 330 to 120 like in betaflight. hue can be 0-359 hence the condidion used
    uint16_t temp = map(input, min, max, 1, 150);
    
    if (temp < 30)
    {
        return 330 + temp;
    }
    else
    {
        return temp - 30;
    }
}



const byte dim_curve[] = {
    0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
    3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
    6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
    8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
    11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
    15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
    20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
    27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
    36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
    48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
    63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
    83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
    110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
    146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
    193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

// downloaded from here
// https://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/
// hue 0-359, sat 0-255, val 0-255
//returns 24bpp color information
uint32_t getPixelColorHsv(uint16_t hue, uint8_t sat, uint8_t val)
{
    val = dim_curve[val];
    sat = 255 - dim_curve[255 - sat];

    int r;
    int g;
    int b;
    int base;

    if (sat == 0)
    { // Acromatic color (gray). Hue doesn't mind.
        r = val;
        g = val;
        b = val;
    }
    else
    {

        base = ((255 - sat) * val) >> 8;

        switch (hue / 60)
        {
        case 0:
            r = val;
            g = (((val - base) * hue) / 60) + base;
            b = base;
            break;

        case 1:
            r = (((val - base) * (60 - (hue % 60))) / 60) + base;
            g = val;
            b = base;
            break;

        case 2:
            r = base;
            g = val;
            b = (((val - base) * (hue % 60)) / 60) + base;
            break;

        case 3:
            r = base;
            g = (((val - base) * (60 - (hue % 60))) / 60) + base;
            b = val;
            break;

        case 4:
            r = (((val - base) * (hue % 60)) / 60) + base;
            g = base;
            b = val;
            break;

        case 5:
            r = val;
            g = base;
            b = (((val - base) * (60 - (hue % 60))) / 60) + base;
            break;
        }
    }
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}
