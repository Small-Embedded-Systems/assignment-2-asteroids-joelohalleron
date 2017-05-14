  
//exposes the parts of the controller needed elsewhere, mainly the bit needed to set up the ticker object.

//Initalise joystick
typedef enum {JLT = 0, JRT, JUP, JDN, JCR} btnId_t;
static DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
static DigitalIn left(P5_0);
static DigitalIn right(P5_4);
static DigitalIn up(P5_2);
static DigitalIn down(P5_1);

bool jsPrsdAndRlsd(btnId_t b);
bool jsHeld(btnId_t b);
int getButton();
int getDirection();
int getOrientation();
void userinput(void);
void testButtons(void);
void testUserInput(void);
void controller(void);
void setButton(void);
void buttonTask(void);
void setButton(void);
void released(void);