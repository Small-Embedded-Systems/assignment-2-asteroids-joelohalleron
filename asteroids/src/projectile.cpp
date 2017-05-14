#include "projectile.h"
#include "node.h"
#include "display.h"
#include "utils.h"
#include "draw.h"
#include "model.h"

Display *screen3 = Display::theDisplay();

/* Draw a list of particles */
void drawProjectiles(struct particle *lst)
{
    /* while there are particles to draw */
    while(lst) {
        screen3->fillCircle(lst->x,lst->y, 1, RED);
        lst = lst->next;/* itterate along the list */
    }
}

/*Initialise properties of a new 'projectile' particle*/
void initProjectile(struct particle *r)
{
    r->x = getShipX();
    r->y = getShipY();
    r->v_x = getShipXVelocity();
    r->v_y = getShipYVelocity();
    r->ttl = 20; /* how long to live (s) */
}

const float Dtp = 0.01;
void updateProjectile(struct particle *l)
{
    for( ; l ; l = l->next ) {
        l->x += l->v_x * Dtp; 
        l->y += l->v_y * Dtp;
        
        
        
        if( l->y > 270 ){
            l->y = 270;
            l->v_y *= -0.7;
        }
        if( l->x<0 || 480<l->x ) l->ttl=0;
        l->ttl -= Dtp;
        /* before moving on to the next element,
           check if it is still valid (has steps left)
           I have to do  this now, so I can remove the
           element from the linked-list
        */
        if( l->next->ttl<=0 ) {
            struct particle *expired = l->next;
            l->next = l->next->next;
            freenode(expired);
        }
    }
}