
#include "MicroBit.h"
#include "Adafruit_NeoPixel.h"
MicroBit uBit;
static int BATTERY_ADC_CHANNEL = -1;
static int get_vdd_millivolts() {
    if (BATTERY_ADC_CHANNEL == -1) {
        return 0;
    }
    (void)uBit.adc.getChannel(uBit.io.P0, true);
    NRF_SAADC->CH[BATTERY_ADC_CHANNEL].CONFIG =
        (SAADC_CH_CONFIG_RESP_Bypass << SAADC_CH_CONFIG_RESP_Pos) |
        (SAADC_CH_CONFIG_RESN_Bypass << SAADC_CH_CONFIG_RESN_Pos) |
        (SAADC_CH_CONFIG_GAIN_Gain1_6 << SAADC_CH_CONFIG_GAIN_Pos) |
        (SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) |
        (SAADC_CH_CONFIG_TACQ_3us << SAADC_CH_CONFIG_TACQ_Pos) |
        (SAADC_CH_CONFIG_MODE_SE << SAADC_CH_CONFIG_MODE_Pos) |
        (SAADC_CH_CONFIG_BURST_Disabled << SAADC_CH_CONFIG_BURST_Pos);
    NRF_SAADC->CH[BATTERY_ADC_CHANNEL].PSELP = SAADC_CH_PSELP_PSELP_VDD << SAADC_CH_PSELP_PSELP_Pos;
    int vin_millivolts = (1000 * 0.6 * 6 * uBit.io.P0.getAnalogValue()) / 1024;
    return vin_millivolts;
}
static void vdd_adc_init() {
    (void)uBit.io.P0.getAnalogValue();
    (void)uBit.adc.getChannel(uBit.io.P0, true);
    (void)uBit.io.P0.getAnalogValue();
    for (size_t i = 0; i < NRF52_ADC_CHANNELS; i++) {
        if (NRF_SAADC->CH[i].PSELP == (SAADC_CH_PSELP_PSELP_AnalogInput0 << SAADC_CH_PSELP_PSELP_Pos)) {
            BATTERY_ADC_CHANNEL = i;
            break;
        }
    }
    (void)get_vdd_millivolts();
}
int main() {
    uBit.init();
    vdd_adc_init();
    while (true) {
        Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 0, NEO_GRB + NEO_KHZ800);
int x = 0;
void setup() {
    strip.begin();
    strip.show();
}
void loop() {
    x = 1;
    for (int index = 0; index < 12; index++) {
        strip.setPixelColor(0, strip.Color(255, 125, 0));
        strip.show();
        x += 1;
        delay(100);
    }
    strip.clear();
    strip.show();
    x = 1;
    for (int index = 0; index < 12; index++) {
        strip.setPixelColor(0, strip.Color(90, 45, 225));
        strip.show();
        x += 1;
            strip.clear();
    strip.show();
    ManagedString battery_mv = ManagedString(get_vdd_millivolts()) + " mV";
    uBit.serial.send(battery_mv + "\r\n");
    uBit.display.scroll(battery_mv);
    uBit.sleep(1000);
    }
}
}
}