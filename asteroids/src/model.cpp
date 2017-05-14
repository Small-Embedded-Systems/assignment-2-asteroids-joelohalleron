/* Asteroids model */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <mbed.h>
#include "display.h"

#include "controller.h"
#include "gamestate.h"
#include "draw.h"
#include "model.h"
#include "node.h"
#include "utils.h"
#include "asteroids.h"

/* If you want to initialise a linked list:
    You'll have to replace node_t with the right type

typedef struct node {
    some data per node
    struct node *next;
} node_t;
const size_t MAXSize = 10;
node_t data[MAXSize];
node_t *initialise()
{
    int c;
    for(c=0 ; c<(MAXSize-1) ; c++){
        data[c].next = &data[c+1];
    }
    data[c].next = NULL;
    return data;
}
*/

Display *screen1 = Display::theDisplay(); 

static struct particle *active = NULL;
static struct missileS *active1 = NULL;

ship s = { 0, 240,240};

static int count = 0;
static int count3 = 0;
static bool hit = false;
static int count2 = 0;

struct nodeMissile
{
int dataMissile;
struct nodeMissile *next;
}*startMissile=NULL;

struct node
{
int data;
struct node *next;
}*start=NULL;

	
int strikeCount = 0;

void physicsAsteroids(void)
{
	  /*Call asteroid physics*/
	  particleSystem();

}

void physicsMissiles(void)
{
	/*Call missile physics*/
	missileSystem();
}

void collisions(void)
{
	/*Call Collision ship/asteroid detection*/
	updateCall();
	
	/*Call Collision missile/asteroid detection*/
	updateCallMissiles();
	
	/*Call Wraparound collision detection*/
	wrapAround();
}

	
	

/* Initialise the properties of a new particle */


/* update the position of each particle in a list
    of particles
*/



	


	const float Dt = 0.01;
	void update(struct particle *l)
	{

			for( ; l ; l = l->next ) 
		{

				l->x += l->v_x * Dt; 
				l->y += l->v_y * Dt;
					
				l->v_y += Dt;
					
				if( l->x<0 || 480<l->x ) l->ttl=0;

			  /*Calculate the distance between each asteroid and the ship*/
				int distance = sqrt( ((getShipX() - l->x) * (getShipX() - l->x))
														+ ((getShipY() - l->y) * (getShipY() - l->y)));
				
				/*If the ship comes into contact with an asteroid, it dies*/
				if (distance < 10 + 13)
				{
					if(hit == false)
					{
						count = count + 1;
						;
						l->ttl = 0;
						if(getShield() == true)
						{
							setShieldFalse();
						}
						else 
						{
							setShipDeadTrue();
						}
					}
					
					hit = true;
				}
			

				l->ttl -= Dt;
				 /* before moving on to the next element,
						check if it is still valid (has steps left)
						I have to do  this now, so I can remove the
						element from the linked-list*/
				
				 if( l->next->ttl<=0 )
				 {
					 struct particle *expired = l->next;
					 l->next = l->next->next;
					 freenode(expired);
				 }
				 
				 
		}
		
	}




	void strike(struct particle *r)
	{
		 int d ;
		 d = randrange (1,3);
		 screen1->setTextColor(WHITE);

		 screen1->setCursor(15,1);
		 screen1->printf("%i",d);
			
			if(d == 1)
			{
			 r->y = 15;

			 r->x = randrange(0,440);
			 r->v_x = randrange(-150,150);
			 r->v_y = randrange(70,150);
			 r->ttl = 10; /* how long to live (s) */
			}
			
			if(d == 2)
			{
			 r->y = 270;
			 r->x = randrange(20,480);

			 r->v_x = randrange(-150, 150);
			 r->v_y = randrange(-70,-150);
			 r->ttl = 20; /* how long to live (s) */	
			}
			
	}


	void particleSystem(void)
	{
				hit = false;

		if(getShipDead() == false && getMenu() == false)
		{
			
					struct particle *particles = allocnode();
					if(particles) 
					{
						/* put the new particle at the front of the list */
						particles->next = active;
						active = particles;
						strike(particles);
						
						
					}
					//update(active);
	  }
	}

	void updateCall(void)
	{
		if(getShipDead() == false)
		{
			update(active);
		}
	}
	
	int getCount(void)
	{
		return count;
	}
	
		void strikeMissiles(struct missileS *m)
	{
			 m->my = getShipY();
			 m->mx = getShipX();
			 double heading = radians(getShipHeading());

	     m->v_y = sin(heading + 1.5708) * 2; 
		   m->v_x = cos(heading + 1.5708) * 2; 		
			 m->ttl = 4; /* how long to live (s) */	
		
		
	}

	
//////Missiles //////////////////////////////////////////////////////////////////////////////////
/* Initialise the properties of a new particle */


/* update the position of each particle in a list
    of particles
*/
	
	void updateMissiles(struct missileS *m)
	{

			for( ; m ; m = m->next ) 
		{
				m->mx += m->v_x * 10 * 0.1; 
				m->my += m->v_y * 10 * 0.1;
		
				if( m->mx<0 || 480<m->mx ) m->ttl=0;
	
				m->ttl -= Dt;
				 /* before moving on to the next element,
						check if it is still valid (has steps left)
						I have to do  this now, so I can remove the
						element from the linked-list*/
				particle *l = getParticleList();
				for(; l ; l = l->next)
				{
						int distance = sqrt( ((m->mx - l->x) * (m->mx - l->x))
															+ ((m->my - l->y) * (m->my - l->y)));//Calculates distance between an asteroid and a missile
						
						if(distance < 10 + 2)//If distance implies contact
						{
							l->ttl = 0;	//Time to live is set to zero(asteroid deceased)
						}
						
					 if( m->next->ttl<=0 )//Missile reaches end of life
					 {
						 struct missileS *expired = m->next;
						 m->next = m->next->next;
						 freenode_missile(expired);//Missile removed from list
					 }
				} 
	}
	
	}
	
	/*
	* Method allows the updateMissile method to be called externally,
	* whilst maintaining static variables
	*/
	void updateCallMissiles(void)
	{
		updateMissiles(active1);
	}
	
	void missileSystem(void)
	{

				count2 += 1;//iterate count2 by one

				if(getShipDead() == false && getMenu() == false && getDirection() == 5)//ship is alive, in game, amd center is pressed
					
				{
					struct missileS *missiles = allocnode_missile();
					if(missiles) 
					{
						count3 += 1;
						/* put the new particle at the front of the list */
						missiles->next = active1;
						active1 = missiles;
						strikeMissiles(missiles);
					}
				}
	}
	
	void wrapAround(void)
	{
		
			 //Top Collision
				if(getShipY() <= 10)
				{
					setShipY(getShipY() + 265);
				}
			 //Bottom collision
			 if(getShipY() >= 275)
			 {
				 setShipY(getShipY() - 265);
			 }
			 
			 //Left collision
			 if(getShipX() <= 0)
			 {
				 setShipX(getShipX() + 480);
			 }
			 
			 //Right collision
			 if(getShipX() >= 480)
			 {
				 setShipX(getShipX() - 480);
			 }
	}
	
	/*Helper methods for use externally*/
	
	
	
	/*Get ships x coordinate
    
    return s.x ships x coordinate	
	*/ 
	float getShipX(void)
	{
		return s.x;
		
	}

	
	
	/*Get ships y coordinate
    
    return s.y ships y coordinate	
	*/ 
	float getShipY(void)
	{
		return s.y;
	}
	
	
	
	/*Get ships x velocity
    
    return s.v_x ships x velocity
	*/ 
	float getShipXVelocity(void)
	{
		return s.v_x;
	}
	
	
	
	/*Get ships y velocity
    
    return s.v_y ships y velocity
	*/ 
	float getShipYVelocity(void)
	{
		return s.v_y;
	}
	
	
	
	/*Get ships heading
    
    return ships current heading
	*/ 
	double getShipHeading(void)
	{
		return s.heading;
	}
	
	
	/*Returns current missile to be examined*/
	struct missileS* getMisLst(void)
	{
		return active1;
	}

	
	/*Returns current particle to be examined*/
	struct particle* getParticleList(void)
	{
		return active;
	}

	
	
	/*Mutator methods to allow external methods to manipulate statics*/
	
	
	
	/*Set ships x coordinate
    
    @param setX ships x coordinate	
	*/ 
	void setShipX(float setX)
	{
		s.x = setX;
	}
	
	
	
	/*Set ships y coordinate
    
    @param setY ships y coordinate	
	*/ 
	void setShipY(float setY)
	{
		s.y = setY;
	}
	
	
	
	/*Set Ships x velocity
	
		@param setv_x new ship velocity along x plane
	*/
	void setShipVelocityX(float setv_x)
	{
		s.v_x = setv_x;
	}
	
	
	
	/*Set Ships y velocity
	
		@param setv_y new ship velocity along y plane
	*/
	void setShipVelocityY(float setv_y)
	{
		s.v_y = setv_y;
	}
		
	
	
	/*Set Ships heading
	
	  @param sH ships new heading
	*/
  void setShipHeading(int sH)
	{
		s.heading = sH;
	}
	

