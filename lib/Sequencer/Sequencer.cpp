//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

#include "Sequencer.hpp"

#include <MozziGuts.h>

#include <Arduino.h>
#include <EventDelay.h>

#include "DrumKit.hpp"
#include "HeaderMatrix.hpp"
#include "LEDTicker.hpp"
#include "SpeedControl.hpp"

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

#define SEQUENCER_NUM_SEQUENCES 2

#define SEQUENCER_SEQUENCE_0_LAST_ROW 4
#define SEQUENCER_SEQUENCE_1_LAST_ROW 5

const drum_t drum_row_sounds_arr[ HEADER_MATRIX_NUM_ROWS ] {
    BASSD,
    SNARE,
    HHATC,
    HHATO,
    SNARE,
};

//-----------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------

void incrementCurrentBeat( void );

void incrementCurrentSequence( void );

void printSequenceInfoLine( void );

void runBeat( void );

//-----------------------------------------------------------------
// Local Storage
//-----------------------------------------------------------------

uint8_t currentBeat;
uint8_t currentSequence;
EventDelay beatEventDelay;
uint32_t beatLen_ms = SpeedControl_getBeatLen_ms();

//=================================================================
//-----------------------------------------------------------------
// Private Functions
//-----------------------------------------------------------------
//=================================================================

void incrementCurrentBeat( void )
{
    currentBeat++;
    if( currentBeat >= HEADER_MATRIX_NUM_COLS )
    {
        currentBeat = 0;
        incrementCurrentSequence();
    }
}

void incrementCurrentSequence( void )
{
    currentSequence++;

    if( currentSequence >= SEQUENCER_NUM_SEQUENCES )
    {
        currentSequence = 0;
    }
}

void printSequenceInfoLine( void )
{
    Serial.print( "Sequence State \t " );
    Serial.printf( "currentBeat: %i\t", currentBeat );
    Serial.printf( "currentSequence: %i\t", currentSequence );
    Serial.println();
}

void runBeat( void )
{
    printSequenceInfoLine();

    uint32_t currBeatHeaderSettings = HeaderMatrix_readCol( currentBeat );

    uint32_t lastRow;
    if( currentSequence == 0 )
    {
        lastRow = SEQUENCER_SEQUENCE_0_LAST_ROW;
    }
    else if( currentSequence == 1 )
    {
        lastRow = SEQUENCER_SEQUENCE_1_LAST_ROW;
    }

    int drumRow;
    for( drumRow = 0; drumRow < lastRow; drumRow++ )
    {
        bool drumSet = bitRead( currBeatHeaderSettings, drumRow );

        if( drumSet )
        {
            DrumKit_play( drum_row_sounds_arr[ drumRow ] );
        }
    }

    if( currentBeat == 0 )
    {
        if( currentSequence == 0 )
        {
            LEDTicker_set( beatLen_ms / 2 );
        }
        if( currentSequence == 1 )
        {
            LEDTicker_set( beatLen_ms / 4 );
        }
    }
    else if( currentBeat % 2 == 0 )
    {
        LEDTicker_set( 1 );
    }

    LEDTicker_run();

    incrementCurrentBeat();
}

//=================================================================
//-----------------------------------------------------------------
// Public Functions
//-----------------------------------------------------------------
//=================================================================

void Sequencer_init()
{
    // Set up the basic sequence parameters
    currentBeat = 0;
    beatEventDelay.start( 200 );
}

void Sequencer_run()
{
    if( beatEventDelay.ready() )
    {
        runBeat();

        beatLen_ms = SpeedControl_getBeatLen_ms();
        beatEventDelay.start( beatLen_ms );
    }
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------