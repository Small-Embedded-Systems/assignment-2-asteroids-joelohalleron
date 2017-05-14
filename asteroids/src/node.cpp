/* simple node allocator for linked list */
#include <stdlib.h>
#include <node.h>

static const int heapsize = 1000;
static node_t heap[heapsize];
static node_t *freenodes;

static const int missileHeapSize = 1000;
static node_m heapMissile[missileHeapSize];
static node_m *freenodes_missile;

void initialise_heap(void)
{
    int n;
    for( n=0 ; n<(heapsize-1) ; n++) {
        heap[n].next = &heap[n+1];
    }
    heap[n].next = NULL;
    freenodes = &heap[0];
}

node_t *allocnode(void)
{
    node_t *node = NULL;
    if( freenodes ) {
        node = freenodes;
        freenodes = freenodes->next;
    }
    return node;
}

void freenode(node_t *n)
{
    n->next = freenodes;
    freenodes = n;
}

//Missile

void initialise_heap_missile(void)
{
    int n;
    for( n=0 ; n<(missileHeapSize-1) ; n++) {
        heapMissile[n].next = &heapMissile[n+1];
    }
    heapMissile[n].next = NULL;
    freenodes_missile = &heapMissile[0];
}

node_m *allocnode_missile(void)
{
    node_m *nodeMissile = NULL;
    if( freenodes_missile ) {
        nodeMissile = freenodes_missile;
        freenodes_missile = freenodes_missile->next;
    }
    return nodeMissile;
}

void freenode_missile(node_m *m)
{
    m->next = freenodes_missile;
    freenodes_missile = m;
}

