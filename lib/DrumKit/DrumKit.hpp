#pragma once

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

#include <cstdint>

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------

typedef enum
{
    BASSD = 0,
    SNARE = 1,
    HHATC = 2,
    HHATO = 3,
} drum_t;

//-----------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------

void DrumKit_init( void );

int16_t DrumKit_updateAudio( void );

void DrumKit_play( drum_t drum );
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------