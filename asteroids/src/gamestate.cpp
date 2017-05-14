

#include "asteroids.h"
#include "gamestate.h"
#include <mbed.h>
#include "draw.h"
#include "model.h"


static bool shipDead = false;
static bool shield = true;
static bool menu = true;
static bool gameOver = false;

static int score = 0;
static int lives = 2;
static int newMissileTimer = 0;

	/*Main gamestate method*/
	void game(void)
	{
		if(getShipDead() == false && getMenu() == false)
		{
		scoring();
		
			newMissile();
			
			
			
		}
	}

	
  
	

	/*Increments score*/
	void scoring(void)
	{
		score += 1;
	}

	void resetScore(void)
	{
		score = 0;
	}
	
	
	/*Deals with player respawn to reset all conditions where appropriate*/
	void respawn(void)
	{
		setShipDeadFalse();
		setShieldTrue();
		setShipX(40);
		setShipY(40);
		
		if(gameOver)
		{
			gameOver = false;
		}
		
	}

	
	/*Helper methods for use externally*/
	int getLives(void)
	{
		return lives;
	}
	
	bool getGameOver(void)
	{
		return gameOver;
	}

	bool getShield(void)
	{
		return shield;
	}
	
	int getScore(void)
	{
		return score;
	}
	
	bool getShipDead(void)
	{
		return shipDead;
	}
	
	
	
	/*Mutator methods to be used externally*/
	void setShieldFalse(void)
	{
		shield = false;
	}
	
	void setShieldTrue(void)
	{
		shield = true;
	}
	
	bool getMenu(void)
	{
		return menu;
	}
	
	void setMenuFalse(void)
	{
		menu = false;
	}
	
	void setMenuTrue(void)
	{
		menu = true;
	}

	void setShipDeadFalse(void)
	{
		shipDead = false;
	}
	
	void setShipDeadTrue(void)
	{
		shipDead = true;
		lives = lives - 1;
		if(lives == 0)
		{
			gameOver = true;
			lives = 5;
			menu = true;

	  }
	}
	
	/*Adds a new missile*/
	void newMissile(void)
	{
		newMissileTimer++;
		if(newMissileTimer == 25)
		{
			missileSystem();
		}
	}