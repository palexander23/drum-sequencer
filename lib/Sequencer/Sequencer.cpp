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

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

#define SEQUENCER_DEFAULT_BEAT_LENGTH_MS 200

#define SEQUENCER_NUM_SEQUENCES 2

#define SEQUENCER_SEQUENCE_1_LAST_ROW 4
#define SEQUENCER_SEQUENCE_2_LAST_ROW 5

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
    Serial.printf( "currentBeat: {%i}\t", currentBeat );
    Serial.printf( "currentSequence: {%i}\t", currentSequence );
    Serial.println();
}

void runBeat( void )
{
    printSequenceInfoLine();

    uint32_t currBeatHeaderSettings = HeaderMatrix_readCol( currentBeat );

    int drumRow;
    for( drumRow = 0; drumRow < SEQUENCER_SEQUENCE_1_LAST_ROW; drumRow++ )
    {
        bool drumSet = bitRead( currBeatHeaderSettings, drumRow );

        if( drumSet )
        {
            DrumKit_play( drum_row_sounds_arr[ drumRow ] );
        }
    }

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
    beatEventDelay.start( SEQUENCER_DEFAULT_BEAT_LENGTH_MS );
}

void Sequencer_run()
{
    if( beatEventDelay.ready() )
    {
        runBeat();
        beatEventDelay.start();
    }
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------