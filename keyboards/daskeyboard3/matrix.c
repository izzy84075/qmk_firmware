#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "backlight.h"
#include "matrix.h"
#include "debug.h"


/* Clueboard4
 *
 * Column pins are input with internal pull-down. 
 * Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PA5, PA4, PB6, PB3 }
 *     row: { PA7 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void) {
    printf("matrix init\n");
    //debug_matrix = true;

    /* Column(sense) */
	palSetPadMode(GPIOD, 0,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 1,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 2,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 3,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 4,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 5,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 6,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 7,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 8,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 9,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 10,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 11,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 12,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 13,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 14,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 15,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 0,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 1,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
	palSetPadMode(GPIOC, 2,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 3,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 4,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 5,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 6,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 7,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 8,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 9,  PAL_MODE_OUTPUT_PUSHPULL);
	
	palClearPad(GPIOC, 2);
	palClearPad(GPIOC, 3);
	palClearPad(GPIOC, 4);
	palClearPad(GPIOC, 5);
	palClearPad(GPIOC, 6);
	palClearPad(GPIOC, 7);
	palClearPad(GPIOC, 8);
	palClearPad(GPIOC, 9);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);
	
	debug_enable = true;
	debug_matrix = true;
	debug_keyboard = true;
}

uint8_t matrix_scan(void) {
    matrix_row_t data = 0;

    // read col data: { PA5, PA4, PB6, PB3 }
	for(int row = 0; row < MATRIX_ROWS;row++) {
		switch(row) {
			case 0: palSetPad(GPIOC, 2); break;
			case 1: palSetPad(GPIOC, 3); break;
			case 2: palSetPad(GPIOC, 4); break;
			case 3: palSetPad(GPIOC, 5); break;
			case 4: palSetPad(GPIOC, 6); break;
			case 5: palSetPad(GPIOC, 7); break;
			case 6: palSetPad(GPIOC, 8); break;
			case 7: palSetPad(GPIOC, 9); break;
		}
		
		wait_us(20);
		
		data = ((matrix_row_t)(palReadPort(GPIOD)) | (((matrix_row_t)(palReadPort(GPIOC)) & 0x0003) << 16));
		//data = palReadPort(GPIOD);
	
		switch(row) {
			case 0: palClearPad(GPIOC, 2); break;
			case 1: palClearPad(GPIOC, 3); break;
			case 2: palClearPad(GPIOC, 4); break;
			case 3: palClearPad(GPIOC, 5); break;
			case 4: palClearPad(GPIOC, 6); break;
			case 5: palClearPad(GPIOC, 7); break;
			case 6: palClearPad(GPIOC, 8); break;
			case 7: palClearPad(GPIOC, 9); break;
		}
		
		if (matrix_debouncing[row] != data) {
			matrix_debouncing[row] = data;
			debouncing = true;
			debouncing_time = timer_read();
		}
	}

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
		for(int row = 0; row < MATRIX_ROWS; row++) {
			matrix[row] = matrix_debouncing[row];
		}
		debouncing = false;
    }

	//matrix_print();
	
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    printf("\nr/c 0123456789abcdef\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
