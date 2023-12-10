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

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

#include <MozziGuts.h>

#include "DrumKit.hpp"
#include "HeaderMatrix.hpp"
#include "LEDTicker.hpp"
#include "Sequencer.hpp"
#include "SpeedControl.hpp"

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------

// None

//=================================================================
//-----------------------------------------------------------------
// Private Functions
//-----------------------------------------------------------------
//=================================================================

// None

//=================================================================
//-----------------------------------------------------------------
// Public Functions
//-----------------------------------------------------------------
//=================================================================

void setup()
{
    Serial.begin( 115200 );
    Serial.println( "=========================================" );
    Serial.print( "Drum Sequencer Initializing..." );

    DrumKit_init();
    HeaderMatrix_init();
    Sequencer_init();
    SpeedControl_init();
    LEDTicker_init();

    startMozzi();

    Serial.println( "Complete!" );
    Serial.println( "-----------------------------------------\n\n" );
}

void updateControl()
{
    Sequencer_run();
}

AudioOutput_t updateAudio()
{
    return DrumKit_updateAudio();
}

void loop()
{
    LEDTicker_run();
    audioHook();
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------