#pragma once

#include <stdint.h>

#define HEADER_MATRIX_NUM_COLS 2
#define HEADER_MATRIX_NUM_ROWS 2

#define HEADER_MATRIX_MAX_COLS UINT8_MAX
#define HEADER_MATRIX_MAX_ROWS 32

#if HEADER_MATRIX_NUM_COLS > HEADER_MATRIX_MAX_COLS
#error Too many columns!
#endif

#if HEADER_MATRIX_NUM_ROWS > HEADER_MATRIX_MAX_ROWS
#error Too Many Rows!
#endif

extern const uint8_t col_selc_pin_arr[ HEADER_MATRIX_NUM_COLS ];
extern const uint8_t row_read_pin_arr[ HEADER_MATRIX_NUM_COLS ];

void HeaderMatrix_init();

uint32_t HeaderMatrix_readCol( uint8_t col );
void HeaderMatrix_readMatrix( uint32_t* matrix );
void HeaderMatrix_PrintMatrix( void );
