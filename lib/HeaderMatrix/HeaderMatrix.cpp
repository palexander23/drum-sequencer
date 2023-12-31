

//-----------------------------------------------------------------
// Preprocessor Switches
//-----------------------------------------------------------------

// None

//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

#include "HeaderMatrix.hpp"

#include <Arduino.h>

//-----------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------

const pin_size_t col_selc_pin_arr[ HEADER_MATRIX_NUM_COLS ] = { 14, 1, 2, 3, 4, 5, 15, 6 };
const pin_size_t row_read_pin_arr[ HEADER_MATRIX_NUM_ROWS ] = { 9, 10, 11, 12, 13 };

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

/**
 * @brief Initialize all hardware required for the button Matrix
 *
 * 1) Initialize all the COL Pins as GPIO Outputs held high by default.
 * 2) Initialize all Row pins as GPIO Inputs with weak pull ups.
 */
void HeaderMatrix_init()
{
    // Initialize Column Selector Outputs
    int i;
    for( i = 0; i < HEADER_MATRIX_NUM_COLS; i++ )
    {
        pinMode( col_selc_pin_arr[ i ], OUTPUT );
        digitalWrite( col_selc_pin_arr[ i ], HIGH );
    }

    // Initialize Row Reader Inputs
    for( i = 0; i < HEADER_MATRIX_NUM_ROWS; i++ )
    {
        pinMode( row_read_pin_arr[ i ], INPUT_PULLUP );
    }
}

/**
 * @brief Read a single column of the Header Matrix.
 *
 * 1) Set the column select pin high
 * 2) Read the row pins into a uint32_t representing each header as a 1 in that array position.
 *
 * @return uint32_t
 */
uint32_t HeaderMatrix_readCol( uint8_t col )
{
    // Create output variable
    uint32_t col_value = 0;

    // Select the column to read
    digitalWrite( col_selc_pin_arr[ col ], LOW );

    // Read each of the rows into the output value
    int i;
    for( i = 0; i < HEADER_MATRIX_NUM_ROWS; i++ )
    {
        bitWrite( col_value, i, digitalRead( row_read_pin_arr[ i ] ) == LOW );
    }

    digitalWrite( col_selc_pin_arr[ col ], HIGH );

    return col_value;
}

void HeaderMatrix_readMatrix( uint32_t matrixArr[ HEADER_MATRIX_NUM_COLS ][ HEADER_MATRIX_NUM_ROWS ] )
{
    uint32_t currentCol;

    int col, row;
    for( col = 0; col < HEADER_MATRIX_NUM_COLS; col++ )
    {
        currentCol = HeaderMatrix_readCol( col );

        for( row = 0; row < HEADER_MATRIX_NUM_ROWS; row++ )
        {
            matrixArr[ col ][ row ] = bitRead( currentCol, row );
        }
    }
}

void HeaderMatrix_PrintMatrix( void )
{
    int col, row;
    uint32_t matrixArr[ HEADER_MATRIX_NUM_COLS ][ HEADER_MATRIX_NUM_ROWS ] = { 0 };

    HeaderMatrix_readMatrix( matrixArr );

    Serial.println( "---------------" );

    for( row = 0; row < HEADER_MATRIX_NUM_ROWS; row++ )
    {
        for( col = 0; col < HEADER_MATRIX_NUM_COLS; col++ )
        {
            Serial.printf( "%i, ", matrixArr[ col ][ row ] );
        }
        Serial.println();
    }

    Serial.println( "---------------\n\r" );
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------