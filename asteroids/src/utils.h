/* utility functions */

/* some numerical helper functions */
float norm(float value, float min, float max);
float lerp(float min, float max, float value);
float map(float value, float lower, float upper, float min, float max);

/* make a 16bit colour */
typedef uint16_t colour_t;


int randrange(int from, int to);


extern const float pi;

float radians(float degrees);//degrees to radian conversion method
void stars(void);
void populateStars(void);
