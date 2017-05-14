
#include <mbed.h>
#include "controller.h"
#include "gamestate.h"


static int button;//Int to determine which joy button has been pressed
static int orientation;//Used for ship movement
static bool jsReleased(btnId_t b);//Handles the button with a parameter for a buttons' ID
static bool Pressed = false; //Bool for a button being pressed

  /*Main method in controller class, calls the button task for hardware detection*/
	void controller(void)
	{
			buttonTask();
		
	}

  /*The button task to detect when the joystick is pressed, and inform the program as such*/
	void buttonTask(void)
	{
		
					if (jsPrsdAndRlsd(JLT)) { // NB response to JS L, R reversed
					button = 2; 
					orientation = 1;					
						
						//   because JS is upside-down
					}
					else if (jsPrsdAndRlsd(JRT)) { 
						button = -2;
						orientation = 3;					
					}
					else if(jsPrsdAndRlsd(JUP))
					{
						orientation = 2;		
					}
					else if(jsPrsdAndRlsd(JDN))
					{
						orientation = 4;				
					}
					else if(jsPrsdAndRlsd(JCR))
					{
						orientation = 5;
						if(getShipDead())
						{
						respawn();
						}
						
						if(getMenu() == true)
						{
							setMenuFalse();
							resetScore();
						}

					}
					else
					{
						released();
					}

	}
  
	/*Some helper methods for detecting button presses in other files*/
	int getButton()
	{
		return button;
	}

	int getDirection()
	{
		return orientation;
	}
	
	/*Mutator method to allow the button bool to be reset externally*/
		void setButton()
	{
		button = 0;
	}
	
	/*Handles the button press based on id given*/
	bool jsPrsdAndRlsd(btnId_t b) 
	{
		static uint32_t savedState[4] = {1,1,1,1};

		bool result = false;
		uint32_t state; //initially all 1s: nothing pressed
		
		state = jsBtns[b].read();
				
		if(state == 0)
		{
			return true;
			Pressed = true;
		}
				
		if(state == 1)
		{
			return false;
		}
		
	}

	/*Method to inform the program that a button has been released*/
	void released()
	{
		button = 0;
		orientation = 0;
		
	}



	
	
