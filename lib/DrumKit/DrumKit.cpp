#include "DrumKit.hpp"

#include <Arduino.h>
#include <MozziGuts.h>
#include <Sample.h> // Sample template

#include "DrumSamples.h"

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

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
const int d_pins[ D_NUM ] = { D_BD, D_SD, D_OH, D_CH };

//-----------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Local Storage
//-----------------------------------------------------------------

// use: Sample <table_size, update_rate> SampleName (wavetable)
Sample<BD_NUM_CELLS, AUDIO_RATE> aBD( BD_DATA );
Sample<SD_NUM_CELLS, AUDIO_RATE> aSD( SD_DATA );
Sample<CH_NUM_CELLS, AUDIO_RATE> aCH( CH_DATA );
Sample<OH_NUM_CELLS, AUDIO_RATE> aOH( OH_DATA );

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

void DrumKit_init( void )
{
    // Initialise all samples to play at the speed it was recorded
    aBD.setFreq( ( float )D_SAMPLERATE / ( float )BD_NUM_CELLS );
    aSD.setFreq( ( float )D_SAMPLERATE / ( float )SD_NUM_CELLS );
    aCH.setFreq( ( float )D_SAMPLERATE / ( float )CH_NUM_CELLS );
    aOH.setFreq( ( float )D_SAMPLERATE / ( float )OH_NUM_CELLS );
}

int16_t DrumKit_updateAudio( void )
{
    // Need to add together all the sample sources.
    // We down-convert using the scaling factor worked out
    // for our specific sample set from running in "CALIBRATE" mode.
    //
    int16_t d_sample = aBD.next() + aSD.next() + aCH.next() + aOH.next();
    return MonoOutput::fromNBit( OUTPUTSCALING, d_sample );
}

void DrumKit_play( int drum )
{
    switch( drum )
    {
    case D_BD:
        aBD.start();
        break;
    case D_SD:
        break;
        aSD.start();
    case D_CH:
        aCH.start();
        break;
    case D_OH:
        aOH.start();
        break;
    }
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------