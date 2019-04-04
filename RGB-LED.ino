//#define PIN 26
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ400);

const uint16_t PixelCount = 12; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 26;    // make sure to set this to the correct pin, ignored for Esp8266
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void stripStartup()
{
    strip.Begin();
    strip.Show(); // Initialize all pixels to 'off'
}

uint16_t mySpectrum = 0;
void stripTest()
{
    // const uint8_t c_sat = 255;
    // const uint8_t c_val = 127;
    // mySpectrum++;
    // if (mySpectrum > 100)
    // {
    //     mySpectrum = 0;
    // }
    // commSerial.print("actual hue led strip: ");
    // commSerial.println(mySpectrum);

    for (uint16_t i = 0; i < 12; i++) // fill up all 12 leds
    {
        //setLedHue(mapHue(mySpectrum, 100), 255, 127, i);
        //strip.SetPixelColor(i, HtmlColor(getPixelColorHsv(mapHue(mySpectrum, 0, 100), c_sat, c_val))); //terribly looking function call :)
        strip.SetPixelColor(i, HtmlColor(packCellInfo.CellColor[i]));
    }
    strip.Show();
}

/*
void setLedHue(uint16_t hue, uint8_t sat, uint8_t val, uint16_t number)
{
    strip.SetPixelColor(number, HtmlColor(getPixelColorHsv(hue, sat, val)));
    strip.Show();
}
*/