/* Asteroids view
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

#include "asteroids.h"
#include "model.h"
#include "utils.h"

Display *graphics = Display::theDisplay();

	/* double buffering functions */
	void init_DBuffer(void)
	{   /* initialise the LCD driver to use second frame in buffer */
			uint16_t *bufferbase = graphics->getFb();
			uint16_t *nextbuffer = bufferbase+ (480*272);
			LPC_LCD->UPBASE = (uint32_t)nextbuffer;
	}

	void swap_DBuffer(void)
	{   /* swaps frames used by the LCD driver and the graphics object */
			uint16_t *buffer = graphics->getFb();
			graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
			LPC_LCD->UPBASE = (uint32_t)buffer;
	}



