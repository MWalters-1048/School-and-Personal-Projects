//--------------------------------
// Your quadtree ADT implementation
//--------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "QTree.h"


// Definitions of helper funcitons---------------------------------------------
// Some useful helper functions that can be used to finish this program (not mandatory to use)
// Feel free to add more if needed
point getCenter(point tl, point br);
int isSamePoint(point p1, point p2);
int getIndexOfChild(point p, point tl, point br);
static int getSubTree(point center, point p);

// Constructors-Destructors ---------------------------------------------------
point createPoint(int x, int y) {
	point p = malloc(sizeof(*p));
	p->x = x;
	p->y = y;
	return p;
}

// Return a new point which contains the same coordinate as point q
point copyPoint(point q) {
	return createPoint(q->x, q->y);
}

pointsContainer createPointsContainer() {
    pointsContainer pc = (pointsContainer) malloc(sizeof(pointsContainerObj));
    memset(pc, 0, sizeof(pointsContainerObj));
    pc->size = 0;
    pc->topLeft = NULL;
    pc->botRight = NULL;
    pc->target = NULL;
    return pc;
}

void freePointsContainer(pointsContainer* pc_ptr) {
    if (pc_ptr && *pc_ptr) {
        pointsContainer pc = *pc_ptr;
        for (int i = 0; i < pc->size; i++) 
            free(pc->list[i]);
        free(pc->topLeft);
        free(pc->botRight);
        free(pc->target);
        free(pc->list);
        free(pc);
        pc = NULL;
        *pc_ptr = NULL;
    }
    
}

quadNode createQuadTree(point topLeft, point botRight) {
	quadNode q = calloc(1, sizeof(*q));
	q->topLeft = copyPoint(topLeft);
	q->botRight = copyPoint(botRight);
	q->child = calloc(4, sizeof(quadNode));
	return q;
}

void deleteQuadTree(quadNode* pRoot) {
	quadNode r = *pRoot;
	free(r->topLeft);
	free(r->botRight);
	free(r->node);  

	if (r->count > 1) {
		for (int i=0; i<4; i++) {
			deleteQuadTree(&r->child[i]);
		}
	}
	free(r->child);
	free(r);
	*pRoot = NULL;
}

// Insert point p into the quadtree. If p is already in the quadtree, do nothing
void insertPoint(quadNode root, point p) {
	if (!root || !p) {
		return;
	}

	// empty leaf, just add the point
	if (!root->count) {
		root->node = copyPoint(p);
		root->count++;
		return;
	}
	
	point c = getCenter(root->topLeft, root->botRight);
	int sub;
	// if node is full, break into subquadrands
	if (root->count == 1) {
		if (isSamePoint(root->node, p)) {
			return;
		}
		point tl, br;

		tl = root->topLeft;
		br = c;
		if (!root->child[0]) {
			root->child[0] = createQuadTree(tl, br);
		}

		tl = createPoint(c->x+1, root->topLeft->y);
		br = createPoint(root->botRight->x, c->y);
		if (!root->child[2]) {
			root->child[2] = createQuadTree(tl, br);
		}
		free(tl);
		free(br);

		tl = createPoint(root->topLeft->x, c->y+1);
		br = createPoint(c->x, root->botRight->y);
		if (!root->child[1]) {
			root->child[1] = createQuadTree(tl, br);
		}

		tl = createPoint(c->x+1, c->y+1);
		br = root->botRight;
		if (!root->child[3]) {
			root->child[3] = createQuadTree(tl, br);
		}
		free(tl);

		sub = getSubTree(c, root->node);
		insertPoint(root->child[sub], root->node);
		root->node = NULL;
	}

	sub = getSubTree(c, p);
	insertPoint(root->child[sub], p);
	free(c);
	root->count++;
}

static int isInRange(point p, point tl, point br)
{
	if (p->x < tl->x || p->y < tl->y || p->x > br->x || p->y > br->y) {
		return 0;
	}
	return 1;
}

// Delete the point from the quadtree
// Return 1 if point p is in the quadtree, otherwise return 0
int deletePoint(quadNode root, point p)
{
	// empty quadrant
	if (!root->count) {
		return 0;
	}

	// if point not in quadrant range, can't exist and return
	if (!isInRange(p, root->topLeft, root->botRight)) {
		return 0;
	}
	
	if (root->node) {
		// if leaf node and single point match, delete and return 1
		if (isSamePoint(root->node, p)) {
			free(root->node);
			root->node = NULL;
			root->count--;
			return 1;
		}
		return 0;
	}

	// find proper subquadrant and call recursively
	point c = getCenter(root->topLeft, root->botRight);
	int sub = getSubTree(c, p);
	free(c);
	
	int ret = deletePoint(root->child[sub], p);
	if (ret) {
		root->count--;

		// If count went from 2 to 1, have to absorb point from child
		// into ourselves, assumption is count == 1, is a leaf node and
		// root->node is that point 
		if (root->count == 1) {
			for (int i=0; i<4; i++) {
				if (root->child[i]->count == 1) {
					root->node = root->child[i]->node;

					root->child[i]->node = NULL;
					root->child[i]->count--;
					break;
				}
			}
		}
	}

	return ret;
}

static void getAllPoints_helper(quadNode root, pointsContainer pc, int* count)
{
	if (!root->count) {
		return;
	}

	if (root->node) {
		pc->list[*count] = copyPoint(root->node);
		(*count)++;
		return;
	}

	for (int i=0; i<4; i++) {
		getAllPoints_helper(root->child[i], pc, count);
	}
}

// Get all points in the quadtree
// Return a container that contains all points in the quadtree
pointsContainer getAllPoints(quadNode root)
{
	pointsContainer pc = calloc(1, sizeof(*pc));

	pc->size = root->count;
	pc->list = calloc(pc->size, sizeof(point));

	int count = 0;
	getAllPoints_helper(root, pc, &count);

	return pc;
}

static void getNeighborsRange(quadNode root, pointsContainer pc, point p, int* count)
{
	if (!root->count) {
		return;
	}

	if (root->botRight->x < pc->topLeft->x ||
	    root->botRight->y < pc->topLeft->y ||
	    root->topLeft->x > pc->botRight->x ||
	    root->topLeft->y > pc->botRight->y) {
			return;
	}

	if (root->node) {
		if (!isSamePoint(root->node, p) && isInRange(root->node, pc->topLeft, pc->botRight)) {
			pc->list[*count] = copyPoint(root->node);
			(*count)++;
		}
		return;
	}

	for (int i=0; i<4; i++) {
		getNeighborsRange(root->child[i], pc, p, count);
	}
}

// Get the neighbouring points of point p in region with length 4*radius
// Return a container that contains all neighbors of point p
pointsContainer getNeighbors(quadNode root, point p, int radius)
{
	pointsContainer pc = calloc(1, sizeof(*pc));

	// allocate max possible
	pc->size = root->count;
	pc->list = calloc(pc->size, sizeof(point));
	pc->target = copyPoint(p);
	pc->topLeft = createPoint(p->x-2*radius, p->y-2*radius);
	pc->botRight = createPoint(p->x+2*radius, p->y+2*radius);

	int count = 0;
	getNeighborsRange(root, pc, p, &count);

	pc->size = count;
	pc->list = realloc(pc->list, count*sizeof(point));

	return pc;
}

void printPoint(point p) {
    if (p)
        printf("(%d,%d)", p->x, p->y);
}

void displayQuadTree(quadNode root) {
    assert(root);

    printf("[");
    printPoint(root->topLeft);
    printf(", ");
    printPoint(root->botRight);
    printf(", ");
    if (root->node) {
        printPoint(root->node);
    } else {
        for (int i = 0; i < 4; i++) {
            if (root->child[i] && root->child[i]->count) {
                displayQuadTree(root->child[i]);
                printf(", ");
            }
            else
                printf("[], ");
        }
    }
    printf("]");
}

static int getSubTree(point center, point p)
{

	if (p->x <= center->x) {
		if (p->y <= center->y) {
			return 0;   // NW
		}
		return 1;  // SW
	}

	if (p->y <= center->y) {
		return 2;  // NE
	}

	return 3; // SE
}


// Helper functions
// Get the center point within a region
point getCenter(point tl, point br) {
    int mid_x = (br->x + tl->x)/2;
    int mid_y = (br->y + tl->y)/2;
    return createPoint(mid_x, mid_y);
}

// Check if two points are the same
int isSamePoint(point p1, point p2) {
    return (p1->x == p2->x) && (p1->y == p2->y);
}

// Get the index of the child node
int getIndexOfChild(point p, point tl, point br) {
    point center = getCenter(tl, br);
    int res = -1;
    if (p->y <= center->y) {
        if (p->x  <= center->x) {
        // NW
            res = 0;
        } else {
        // SW
            res = 2;
        }
    } else {
        if (p->x  <= center->x) {
        // NE
            res = 1;
        } else {
        // SE
            res = 3;
        }
    }
    free(center);
    return res;
}


