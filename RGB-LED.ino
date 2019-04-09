/*
const uint16_t PixelCount = 12; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 26;    // make sure to set this to the correct pin, ignored for Esp8266
NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void stripStartup()
{
    strip.Begin();
    strip.Show(); // Initialize all pixels to 'off'
    strip.SetBrightness(64);
}

uint16_t mySpectrum = 0;
void stripTest()
{
    for (uint16_t i = 0; i < 12; i++) // fill up all 12 leds
    {
        strip.SetPixelColor(i, HtmlColor(packCellInfo.CellColor[i]));
    }
    strip.Show();
}
*/