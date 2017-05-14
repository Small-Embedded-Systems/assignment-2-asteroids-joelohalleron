



/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <utils.h>

#include <string.h>
#include <display.h>


/* hardware platform libraries */
#include <mbed.h>
#include "asteroids.h"
#include "controller.h"
#include "gamestate.h"
#include "draw.h"
#include "model.h"
#include "node.h"



/*Initialise the Games tickers for time-loop method calling*/
Ticker gamestate, drawgame, control, physicsMissilesTick, physicsAsteroidsTick, collisionsTick;



	/*Main method used to attach the programs main methods to tickers, and assign reasonable tick intervals*/
	int main() 
	{
		setShipDeadFalse();
		srand (time(NULL));
		srand (1);
		initialise_heap();
		initialise_heap_missile();
		initDoubleBuffering();
	     
		gamestate.attach(game, 1.0); 
		drawgame.attach(draw, 0.025); 
		physicsMissilesTick.attach(physicsMissiles, 0.1);
		physicsAsteroidsTick.attach(physicsAsteroids, 0.25);
		collisionsTick.attach(collisions, 0.01);
		control.attach(controller, 0.01);

	}


