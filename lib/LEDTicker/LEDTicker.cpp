#include "LEDTicker.hpp"

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include <MozziGuts.h>

#include <Arduino.h>
#include <EventDelay.h>

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

#define LED_PIN 25

//-----------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Local Storage
//-----------------------------------------------------------------

EventDelay LEDOnTimer;

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

void LEDTicker_init( void )
{
    pinMode( LED_PIN, OUTPUT );
}

void LEDTicker_set( uint32_t ledOnTime_ms )
{
    LEDOnTimer.start( ledOnTime_ms );
    digitalWrite( LED_PIN, HIGH );
}

void LEDTicker_clear( void )
{
    digitalWrite( LED_PIN, LOW );
}

void LEDTicker_run( void )
{
    if( LEDOnTimer.ready() )
    {
        LEDTicker_clear();
    }
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
