#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "backlight.h"
#include "matrix.h"


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
	palSetPadMode(GPIOB, 0,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 1,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 2,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 3,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 4,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 5,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 6,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 7,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 8,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 9,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 10,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 11,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 12,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 13,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 14,  PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 15,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 0,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 1,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
	palSetPadMode(GPIOA, 2,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 3,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 4,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 5,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 6,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 7,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 8,  PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 9,  PAL_MODE_OUTPUT_PUSHPULL);
	
	palClearPad(GPIOA, 2);
	palClearPad(GPIOA, 3);
	palClearPad(GPIOA, 4);
	palClearPad(GPIOA, 5);
	palClearPad(GPIOA, 6);
	palClearPad(GPIOA, 7);
	palClearPad(GPIOA, 8);
	palClearPad(GPIOA, 9);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);
}

uint8_t matrix_scan(void) {
    matrix_row_t data = 0;

    // read col data: { PA5, PA4, PB6, PB3 }
	for(int row = 0; row < MATRIX_ROWS;row++) {
		switch(row) {
			case 0: palSetPad(GPIOA, 2); break;
			case 1: palSetPad(GPIOA, 3); break;
			case 2: palSetPad(GPIOA, 4); break;
			case 3: palSetPad(GPIOA, 5); break;
			case 4: palSetPad(GPIOA, 6); break;
			case 5: palSetPad(GPIOA, 7); break;
			case 6: palSetPad(GPIOA, 8); break;
			case 7: palSetPad(GPIOA, 9); break;
		}
		
		wait_us(20);
		
		data = (palReadPort(GPIOB) | ((palReadPort(GPIOA) & 0x0003) << 16));
	
		switch(row) {
			case 0: palClearPad(GPIOA, 2); break;
			case 1: palClearPad(GPIOA, 3); break;
			case 2: palClearPad(GPIOA, 4); break;
			case 3: palClearPad(GPIOA, 5); break;
			case 4: palClearPad(GPIOA, 6); break;
			case 5: palClearPad(GPIOA, 7); break;
			case 6: palClearPad(GPIOA, 8); break;
			case 7: palClearPad(GPIOA, 9); break;
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

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    printf("\nr/c 01234567\n");
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
