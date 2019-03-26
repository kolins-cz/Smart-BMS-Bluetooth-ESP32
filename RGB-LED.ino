#define PIN 26
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void stripStartup()
{
    strip.begin();
    strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'
}

void stripTest()
{
    static uint8_t hueMem;
    hueMem++;
    if (hueMem > 359)
    {
        hueMem = 0;
    }

    for (uint8_t i = 1; i <= 12; i++)
    {
        setLedHue(hueMem, 60, 60, i);
    }
}

void setLedHue(uint16_t hue, uint16_t sat, uint16_t val, uint8_t number)
{
    uint32_t temp = getPixelColorHsv(hue, sat, val);
    strip.setPixelColor(number, temp);
}



// downloaded from here
//https://github.com/RoboUlbricht/arduinoslovakia/blob/master/neopixel/hsv_test/hsv.h

uint32_t getPixelColorHsv(uint16_t h, uint8_t s, uint8_t v)
{

    uint8_t r, g, b;

    if (!s)
    {
        // Monochromatic, all components are V
        r = g = b = v;
    }
    else
    {
        uint8_t sextant = h >> 8;
        if (sextant > 5)
            sextant = 5; // Limit hue sextants to defined space

        g = v; // Top level

        // Perform actual calculations

        /*
       Bottom level:
       --> (v * (255 - s) + error_corr + 1) / 256
    */
        uint16_t ww; // Intermediate result
        ww = v * (uint8_t)(~s);
        ww += 1;       // Error correction
        ww += ww >> 8; // Error correction
        b = ww >> 8;

        uint8_t h_fraction = h & 0xff; // Position within sextant
        uint32_t d;                    // Intermediate result

        if (!(sextant & 1))
        {
            // r = ...slope_up...
            // --> r = (v * ((255 << 8) - s * (256 - h)) + error_corr1 + error_corr2) / 65536
            d = v * (uint32_t)(0xff00 - (uint16_t)(s * (256 - h_fraction)));
            d += d >> 8; // Error correction
            d += v;      // Error correction
            r = d >> 16;
        }
        else
        {
            // r = ...slope_down...
            // --> r = (v * ((255 << 8) - s * h) + error_corr1 + error_corr2) / 65536
            d = v * (uint32_t)(0xff00 - (uint16_t)(s * h_fraction));
            d += d >> 8; // Error correction
            d += v;      // Error correction
            r = d >> 16;
        }

        // Swap RGB values according to sextant. This is done in reverse order with
        // respect to the original because the swaps are done after the
        // assignments.
        if (!(sextant & 6))
        {
            if (!(sextant & 1))
            {
                uint8_t tmp = r;
                r = g;
                g = tmp;
            }
        }
        else
        {
            if (sextant & 1)
            {
                uint8_t tmp = r;
                r = g;
                g = tmp;
            }
        }
        if (sextant & 4)
        {
            uint8_t tmp = g;
            g = b;
            b = tmp;
        }
        if (sextant & 2)
        {
            uint8_t tmp = r;
            r = b;
            b = tmp;
        }
    }
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}