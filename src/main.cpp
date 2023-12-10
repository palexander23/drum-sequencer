/*
// Simple DIY Electronic Music Projects
//    diyelectromusic.wordpress.com
//
//  Arduino Mozzi Sample Drum Machine
//  https://diyelectromusic.wordpress.com/2021/06/22/arduino-mozzi-sample-drum-machine/
//
      MIT License

      Copyright (c) 2020 diyelectromusic (Kevin)

      Permission is hereby granted, free of charge, to any person obtaining a copy of
      this software and associated documentation files (the "Software"), to deal in
      the Software without restriction, including without limitation the rights to
      use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
      the Software, and to permit persons to whom the Software is furnished to do so,
      subject to the following conditions:

      The above copyright notice and this permission notice shall be included in all
      copies or substantial portions of the Software.

      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
      FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
      COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHERIN
      AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
      WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*
  Using principles from the following Arduino tutorials:
    Arduino Digital Input Pullup - https://www.arduino.cc/en/Tutorial/DigitalInputPullup
    Mozzi Library        - https://sensorium.github.io/Mozzi/

  Some of this code is based on the Mozzi example "Sample" (C) Tim Barrass

*/
#include <MozziGuts.h>
#include <Sample.h> // Sample template

#include "HeaderMatrix.hpp"
#include "d_kit.h"

// Uncomment to output max/min values of the samples for calibration purposes
// #define CALIBRATE 1

// This defines the size of the combined output value from summing
// all the samples together.  The worst case has to allow for adding
// up +/- 127 for each sample, but a more accurate estimation can be
// obtained by running the "CALIBRATE" mode above which will output
// the maximum and minimum values for each sample, then you just need
// to cope with a "bit depth" that supports the worst cases.
//
// Example: If the output of the CALIBRATE function is:
// Data for drum on pin 5: Max: 103 Min: -128
// Data for drum on pin 4: Max: 95 Min: -128
// Data for drum on pin 3: Max: 127 Min: -121
// Data for drum on pin 2: Max: 98 Min: -128
//
// Then the worst case - i.e. all peaks occuring at the same time:
//    Positive range: 103+95+127+98 = 423
//    Negative range: -106-114-19-13 = -505
//
// So allowing for +/-512 in the output is plenty.  This is satisfied
// with a 10-bit signed value, so we use an OUTPUTSCALING of 10 bits.
//
// The most likely case though is that all samples won't play at the same
// time, and almost certainly not with their peaks together, so in reality
// you could probably get away with less anyway.
//
#define OUTPUTSCALING 9

#define D_NUM 4
#define D_BD 0
#define D_SD 1
#define D_CH 2
#define D_OH 3
int d_pins[ D_NUM ] = { D_BD, D_SD, D_OH, D_CH };

// use: Sample <table_size, update_rate> SampleName (wavetable)
Sample<BD_NUM_CELLS, AUDIO_RATE> aBD( BD_DATA );
Sample<SD_NUM_CELLS, AUDIO_RATE> aSD( SD_DATA );
Sample<CH_NUM_CELLS, AUDIO_RATE> aCH( CH_DATA );
Sample<OH_NUM_CELLS, AUDIO_RATE> aOH( OH_DATA );

#define TRIG_LED LED_BUILTIN
#define LED_ON_TIME 300 // On time in mS
bool trig[ D_NUM ];

void startDrum( int drum )
{
    switch( drum )
    {
    case D_BD:
        aBD.start();
        break;
    case D_SD:
        aSD.start();
        break;
    case D_CH:
        aCH.start();
        break;
    case D_OH:
        aOH.start();
        break;
    }
}

unsigned long millitime;
void ledOff()
{
    if( millitime < millis() )
    {
        digitalWrite( TRIG_LED, LOW );
    }
}

void ledOn()
{
    millitime = millis() + LED_ON_TIME;
    digitalWrite( TRIG_LED, HIGH );
}

void setup()
{
    Serial.begin( 115200 );

    pinMode( TRIG_LED, OUTPUT );
    ledOff();
    for( int i = 0; i < D_NUM; i++ )
    {
        pinMode( d_pins[ i ], INPUT_PULLUP );
    }
    startMozzi();
    // Initialise all samples to play at the speed it was recorded
    aBD.setFreq( ( float )D_SAMPLERATE / ( float )BD_NUM_CELLS );
    aSD.setFreq( ( float )D_SAMPLERATE / ( float )SD_NUM_CELLS );
    aCH.setFreq( ( float )D_SAMPLERATE / ( float )CH_NUM_CELLS );
    aOH.setFreq( ( float )D_SAMPLERATE / ( float )OH_NUM_CELLS );

    HeaderMatrix_init();

    Serial.println( "Hello!" );

#ifdef CALIBRATE
    Serial.begin( 9600 );
    calcMaxMin( D_BD );
    calcMaxMin( D_SD );
    calcMaxMin( D_CH );
    calcMaxMin( D_OH );
#endif
}

void updateControl()
{
    // static uint32_t last_millis = 0;
    // static uint8_t drum = 0;

    // uint32_t curr_time = millis();

    // if ((curr_time - last_millis) > 500)
    // {
    //     ledOn();
    //     startDrum(drum);
    //     last_millis = curr_time;
    // }

    // drum++;
    // if (drum > 3)
    // {
    //     drum = 0;
    // }

    static uint32_t lastPrintTimeMs = 0;
    uint32_t currTimeMs = millis();

    if( ( currTimeMs - lastPrintTimeMs ) > 500 )
    {
        HeaderMatrix_PrintMatrix();
        lastPrintTimeMs = currTimeMs;
    }
}

AudioOutput_t updateAudio()
{
    // Need to add together all the sample sources.
    // We down-convert using the scaling factor worked out
    // for our specific sample set from running in "CALIBRATE" mode.
    //
    int16_t d_sample = aBD.next() + aSD.next() + aCH.next() + aOH.next();
    return MonoOutput::fromNBit( OUTPUTSCALING, d_sample );
}

void loop()
{
    audioHook();
}