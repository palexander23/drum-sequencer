#pragma once

#include <stdint.h>

#include <DrumKit.hpp>

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

#define HEADER_MATRIX_NUM_COLS 8
#define HEADER_MATRIX_NUM_ROWS 5

#define HEADER_MATRIX_MAX_COLS UINT8_MAX
#define HEADER_MATRIX_MAX_ROWS 32

#if HEADER_MATRIX_NUM_COLS > HEADER_MATRIX_MAX_COLS
#error Too many columns!
#endif

#if HEADER_MATRIX_NUM_ROWS > HEADER_MATRIX_MAX_ROWS
#error Too Many Rows!
#endif

extern const uint8_t col_selc_pin_arr[ HEADER_MATRIX_NUM_COLS ];
extern const uint8_t row_read_pin_arr[ HEADER_MATRIX_NUM_ROWS ];

#define BASSD_1_ROW 0
#define SNARE_1_ROW 1
#define HHATC_1_ROW 2
#define HHATO_1_ROW 3
#define BASSD_2_ROW 4

//-----------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------

void HeaderMatrix_init();

uint32_t HeaderMatrix_readCol( uint8_t col );
void HeaderMatrix_readMatrix( uint32_t* matrix );
void HeaderMatrix_PrintMatrix( void );

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------