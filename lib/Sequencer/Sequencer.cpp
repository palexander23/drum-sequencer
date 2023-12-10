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

#include "HeaderMatrix.hpp"

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

#define SEQUENCER_DEFAULT_BEAT_LENGTH_MS 100

#define SEQUENCER_NUM_SEQUENCES 2

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