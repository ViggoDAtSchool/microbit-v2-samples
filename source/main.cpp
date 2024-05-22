#include "MicroBit.h"
#include "Adafruit_NeoPixel.h"
#include "samples/Tests.h"

MicroBit uBit;

int main()
{
    uBit.init();

    out_of_box_experience();

    microbit_panic( 999 );
}

