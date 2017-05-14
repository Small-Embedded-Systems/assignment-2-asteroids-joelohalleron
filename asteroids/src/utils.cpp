/* utility functions */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <model.h>
#include <utils.h>

#include <display.h>
#include "draw.h"
#include "gamestate.h"
#include "controller.h"
#include "asteroids.h"

static int x[55];  
static int y[55]; 
static bool populated = false;

void stars(void);

Display *screen2 = Display::theDisplay(); 

	/* some numerical helper functions */
	float norm(float value, float min, float max) 
	{
			return (value-min)/(max-min); 
	}
	float lerp(float min, float max, float value) 
	{
			return max*value+(1.0f-value)*min; 
	}
	float map(float value, float lower, float upper, float min, float max) 
	{
			return lerp(min,max, norm(value,lower,upper)); 
	}
	/*------*/

	/* random number between values, not including last
			randrange(0,360) produces numbers 0..359
	*/
	int randrange(int from, int to)
	{
			int range = to-from;
			return from + rand()%range;
	}

	/* Convert degrees to radians */
	static const float pi = 3.1415926f;
	float radians(float degrees) { return degrees/180*pi; }
	
	void stars (void)
	{
		srand(time(0));		
	
		if(populated == false)
		{
				int i = 1;
				
				while (i < 50)
				{
					
					x[i] = randrange(0,480);
					y[i] = randrange(0,240);
				
				i++;
			}
					populated = true;
		}
	}
	
	/*Draws the stars for the main menu using the stars linked list*/
	void populateStars(void)
	{
		stars();
		int i = 1;
		while( i < 50)
		{
			screen2->drawCircle(x[i],y[i], 1, WHITE);
			i++;
		}
	}
		
