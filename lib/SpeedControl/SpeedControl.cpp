#include "SpeedControl.hpp"

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

#include <MozziGuts.h>

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

#define SPEED_CONTROL_POT_PIN 28

#define SPEED_CONTROL_MIN_BEAT_TIME_MS 130
#define SPEED_CONTROL_MAX_BEAT_TIME_MS 300

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

void SpeedControl_init( void )
{
}

uint32_t SpeedControl_getBeatLen_ms( void )
{
    uint32_t potVal = mozziAnalogRead( SPEED_CONTROL_POT_PIN );

    return map( potVal, 0, 4096, SPEED_CONTROL_MIN_BEAT_TIME_MS, SPEED_CONTROL_MAX_BEAT_TIME_MS );
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------