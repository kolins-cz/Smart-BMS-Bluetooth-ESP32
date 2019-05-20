
const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 5;    // make sure to set this to the correct pin, ignored for Esp8266
NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void stripStartup()
{
    strip.Begin();
    strip.Show(); // Initialize all pixels to 'off'
    strip.SetBrightness(32);
    strip.SetPixelColor(0, HtmlColor(color16to24(TFT_DARKGREEN)));
    strip.Show();
}




void toggleLed()
{
    static bool mem = false;
    if (mem == true)
    {
        strip.SetPixelColor(4, HtmlColor(color16to24(TFT_RED)));
    }
    else
    {
        strip.SetPixelColor(4, HtmlColor(color16to24(TFT_GREEN)));
    }
    mem = !mem;
    strip.Show();
    
}



