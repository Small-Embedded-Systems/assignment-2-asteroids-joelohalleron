/******model.h******/

extern const float Dt; /* Time step for physics, needed for consistent motion */

/* Ship Struct to be used in srawing and positioning the ship */
struct ship {
	int heading; // heading of the ship
	float x, y;  //X and Y coordinates of the ships origin
	float v_x, v_y; //Velocity or movement in the direction of, X and Y respectively
	
};

/*Struct Declarations*/
struct particle* getParticleList(void);
struct missileS* getMisLst(void);

/*Accessor Declarations*/
double getShipHeading(void); //returns ships heading/direction it is facing
float getShipX(void); //returns ships x coordinate
float getShipY(void); //returns ships y coordinate
float getShipXVelocity(void);//returns ships movement along the x plane
float getShipYVelocity(void);//returns ships movement along the y plane

/*Mutator Method Declarations*/
void setShipX(float); //sets ship X coordinate
void setShipY(float); //sets ship y coordinate
void setShipVelocityX(float);//sets ships movement along x plane
void setShipVelocityY(float);//sets ships movement along y plane
void setShipHeading(int);

/*Method Declarations*/
void physicsAsteroids(void);
void physicsMissiles(void);
void updateCall();
void linkedList(void);
void particleSystem(void);
void drawParticles(void);
void missileSystem(void);
void updateCallMissiles(void);
void drawParticlesMissiles(void);
void collisions(void);
void wrapAround(void);


