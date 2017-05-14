
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
#include "node.h"
#include "icons.h"

void swapBuffers(void);
static int x1, y1, x2, y2, x3, y3;
static int x1r, y1r, x2r, y2r, x3r, y3r;
static double thrust = 0.0;

Display *screen = Display::theDisplay(); 


		void draw(void)
		{  		
				screen->fillScreen(BLACK);
				screen->setTextColor(WHITE);

			if(getMenu())
			{
				drawBitmap();
			  mainMenu();
			  populateStars();

			}
			
			else
			{
				drawScoreBoard();

				if(getShipDead() == false) //If game in progress 
				{
					motion();//draw ship based on updated location
					drawTriangle();//draw the ship 
					rotateTriangle();//draw the ship as it rotates
					wrapAround();//
				}
				else if(getShipDead() == true && getGameOver() == false) 
				{
					drawDeathContinue();
				}
				else if(getGameOver() == true)
				{
						screen->setCursor(200,240);
				    screen->printf("Game Over");
				}		
		}
		drawParticles();
		swapBuffers();
	}
	
	
	
  /*Initialise screen*/
	void initScreen(void)
	{
		screen->fillScreen(WHITE);
	}

	
	/*Initialise double buffering*/
	void initDoubleBuffering(void)
	{
		uint16_t *buffer = screen->getFb();
		uint16_t *buffer2 = buffer+(480*272);
		LPC_LCD->UPBASE = (uint32_t)buffer2;
	}

	
	/*Swap the current buffer with the one not in use*/
	void swapBuffers(void)
	{
		unsigned int b;
		b = LPC_LCD->UPBASE;
		LPC_LCD->UPBASE = (uint32_t)screen->getFb();
		screen->setFb((uint16_t *)b);
	}

	
	
  /*Rotates the triangle when either left or right button is pressed*/
	void rotateTriangle(void)
	{
		
		double heading = radians(getShipHeading());
		
			if(getDirection() == 1 || 3)
		{
			static int newHeading = getShipHeading();
			newHeading += getButton();
			setShipHeading(newHeading);
			x1r = ((x1 - getShipX()) * cos(heading)) - ((y1 - getShipY()) * sin(heading)) + getShipX();
			y1r = ((y1 - getShipY()) * cos(heading)) + ((x1 - getShipX()) * sin(heading)) + getShipY();
			x2r = ((x2 - getShipX()) * cos(heading)) - ((y2 - getShipY()) * sin(heading)) + getShipX();
			y2r = ((y2 - getShipY()) * cos(heading)) + ((x2 - getShipX()) * sin(heading)) + getShipY();
			x3r = ((x3 - getShipX()) * cos(heading)) - ((y3 - getShipY()) * sin(heading)) + getShipX();
			y3r = ((y3 - getShipY()) * cos(heading)) + ((x3 - getShipX()) * sin(heading)) + getShipY();
		}
	//setButton();
	}
	
	/*Draw the ship*/
	void drawTriangle(void)
	{
			double heading = radians(getShipHeading());

			if(getDirection() == 2) //up is pressed
			{
				if(thrust < 20.0)
				{	
				 thrust += 0.8;
				}	
			}
		 
			/*if(getDirection() == 4) //down is pressed
			{
				
			}*/
			
			/*Assign triangles coordinates*/
			x1 = getShipX();
			y1 = getShipY() + 13;
			x2 = getShipX() - 10;
			y2 = getShipY() - 10;
			x3 = getShipX() + 10;
			y3 = getShipY() - 10;
			/*Draw Triangle*/
			screen->fillTriangle(x1r, y1r, x2r, y2r, x3r, y3r, WHITE);
			
			if(getShield())
			{
				screen->drawCircle(getShipX(),getShipY(), 13, BLUE);
			}
			
	}
	
	
	/*Draws an asteroid passed as a parameter*/
	void drawCurrentParticle(struct particle *lst)
	{
		/* while there are particles to draw */
		if(getShipDead() == false && getMenu() == false)
		{
			while(lst) 
			{
				screen->fillCircle(lst->x,lst->y, 10, WHITE);
				lst = lst->next;/* itterate along the list */
			}
		}
		
	}
	
	
	
	/*Draws a missile passed as a parameter*/
	void drawCurrentMissile(struct missileS *mislst)
	{
		/* while there are particles to draw */
		
			while(mislst) 
			{
				screen->fillCircle(mislst->mx, mislst->my, 2, RED);
				mislst = mislst->next;/* itterate along the list */
			}
		
		
	}
	
	
	/*Calls the asteroid and missile draw methods*/
	void drawParticles(void)
	{
		drawCurrentParticle(getParticleList());
		drawCurrentMissile(getMisLst());
		
	}

	
	/*Uses the bitflip method from icons.cpp to draw the ufo2 bitmap*/
	void drawBitmap(void)
	{
		screen->drawBitmap(2,200,ufo2_bits_flipped(),ufo2_width,ufo2_height,RED);
	}
  void motion(void)
	{
		double heading = radians(getShipHeading());
		
		if(thrust > 0)
		{
			thrust -= 0.2;
		}
		
		setShipVelocityY(sin(heading + 1.5708) * 2); 
		setShipVelocityX(cos(heading + 1.5708) * 2); 
		
		setShipX(getShipX() + getShipXVelocity() * thrust * 0.1);
		setShipY(getShipY() + getShipYVelocity() * thrust * 0.1);
	}
	
	/*Methods to draw the various miscelaneous game features*/
	void drawScoreBoard(void)
	{
		screen->setTextSize(1);
    screen->setCursor(20,2);
		screen->fillRect ( 0, 10, 480, 3, WHITE); 
		screen->setCursor(390,2); 
		screen->printf("Total: %05d", getScore()); //Print the total score at the beginning
		screen->setCursor(10,2); 
		screen->printf("Lives Left: %d\n", getLives());
	}

	void drawDeathContinue(void)
	{
		screen->setTextSize(4);
		screen->setCursor(145,120); 
		screen->printf("YOU DIED");
		screen->setTextSize(2);
		screen->setCursor(110,170);
		screen->printf("Press Center to Resume");
	}

	
	void gameOverText(void)
	{
		screen->setCursor(150,240);
		screen->printf("Game Over");
		
	}

	
	void mainMenu(void)
	{
		screen->setCursor(180,100);
		screen->setTextSize(3);
		screen->printf("ASTEROIDS");
		screen->setCursor(120,190);
		screen->setTextSize(2);
		screen->printf("Press Center To Begin");
		screen->setCursor(180,145);
		screen->setTextSize(2);
		screen->printf("High Score"); 	
		screen->setCursor(320,145);
		screen->printf("%d", getScore());
	}

	/*Calls the stars method to draw from stars linked list*/
	void populateBackground(void)
	{
		stars();
	}

