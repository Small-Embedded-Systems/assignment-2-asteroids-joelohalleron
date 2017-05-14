
typedef struct particle {
    float x,y;
    float v_x, v_y;
    float ttl;
    struct particle *next;
} node_t;

typedef struct missileS {
    float mx,my;
    float v_x, v_y;
    float ttl;
    struct missileS *next;
} node_m;




void initialise_heap(void);
void initialise_heap_missile(void);
node_t *allocnode(void);
node_m *allocnode_missile(void);
void freenode(node_t *m);
void freenode_missile(node_m *m);
