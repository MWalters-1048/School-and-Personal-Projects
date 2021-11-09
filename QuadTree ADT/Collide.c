#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "QTree.h"

// Destroy all points inside the explosion range in quadtree.
// The explosion range is 4*radius starting from the center of all collision dots
// [Return] number of points have been deleted from the quadtree due to the explosions
int explosion(quadNode Q, pointsContainer ap, int radius)
{
	int deleted = 0;
	for (int i=0; i<ap->size; i++) {
		deleted += deletePoint(Q, ap->list[i]);
	}
	return deleted;
}




// Check how many collision events occur in the current map
// Leverage explosion function to destroy all points in the explosion range
// [Return] the number of collision events
int collision(quadNode Q, int radius)
{
	pointsContainer all = getAllPoints(Q);
	
	quadNode copy = createQuadTree(Q->topLeft, Q->botRight);
	for (int i=0; i<all->size; i++) {
		insertPoint(copy, all->list[i]);
	}

	int events = 0;

	for (int i=0; i<all->size; i++) {
		pointsContainer close = getNeighbors(copy, all->list[i], radius);

		events += close->size;


		for (int k=0; k<close->size; k++) {
			pointsContainer other = getNeighbors(copy, close->list[k], radius);
			explosion(Q, other, radius);
			freePointsContainer(&other);
		}
		if (close->size) {
			explosion(Q, close, radius);
		}
		freePointsContainer(&close);
	}

	deleteQuadTree(&copy);
	freePointsContainer(&all);

	return events;
}

int main()
{
	char	line[100];
	char 	*command;
	int done = 0;
	
	quadNode Q = NULL;
	int size, x, y, radius, seed, numPoints;

	// process input
	while( !done ) {
		// read an entire line as a string
		fgets(line, 100, stdin);

		// pulls command code, assume comma or tab separated
		command = strtok( line, " \t" );

		if (strncmp(command, "ex", 2) == 0) {
			if (Q)
				deleteQuadTree(&Q);
			printf( "Exited Program\n" );
			done = 1;
		} else if (strncmp(command, "ct", 2) == 0) {
			size = atoi( strtok( NULL, " " ) );
			radius = atoi( strtok( NULL, " " ) );
			
			if (Q != NULL)
				deleteQuadTree(&Q);
		 
			 Q = createQuadTree(createPoint(0, 0), createPoint(size-1, size-1));
			
		} else if (strncmp(command, "ap", 2) == 0) {
			if (Q == NULL) {
				printf("Please create QuadTree first...\n");
				continue;
			}
			x = atoi( strtok( NULL, " " ) );
			y = atoi( strtok( NULL, " " ) );
			insertPoint(Q, createPoint(x, y));
		} else if (strncmp(command, "dp", 2) == 0) {
			if (Q == NULL) {
				printf("Please create QuadTree first...\n");
				continue;
			}
			x = atoi( strtok( NULL, " " ) );
			y = atoi( strtok( NULL, " " ) );
			point p = createPoint(x, y);
			deletePoint(Q, p);
			free(p);	
		} else if (strncmp(command, "se", 2) == 0) {
			seed = atoi( strtok( NULL, " " ) );
			srand(seed);
		} else if (strncmp(command, "ip", 2) == 0) {
			if (Q == NULL) {
				printf("Please create QuadTree first...\n");
				continue;
			}
			numPoints = atoi( strtok( NULL, " " ) );
			for (int i = 0; i < numPoints; i++) {
				x = rand() % size;
				y = rand() % size;
				insertPoint(Q, createPoint(x, y));
			}
		} else if (strncmp(command, "gn", 2) == 0) {
			// Get neighbors of (x, y)
			if (Q == NULL) {
				printf("Please create QuadTree first...\n");
				continue;
			}
			x = atoi( strtok( NULL, " " ) );
			y = atoi( strtok( NULL, " " ) );
			point p = createPoint(x, y);
			pointsContainer pc = getNeighbors(Q, p, radius);

			free(p);
			freePointsContainer(&pc);
		} else if (strncmp(command, "pt", 2) == 0) {
			if (Q == NULL) {
				printf("Please create QuadTree first...\n");
				continue;
			}
			displayQuadTree(Q);
			printf("\n");
		
		} else if (strncmp(command, "co", 2) == 0) {
			if (Q == NULL) {
				printf("Please create QuadTree first...\n");
				continue;
			}
			point p = createPoint(x, y);
			pointsContainer pc = getNeighbors(Q, p, radius);
			int numExplosion = explosion(Q, pc, radius);
			int numCollision = collision(Q, radius);
      			
			printf("%d points have been deleted since explosion!!!\n", numExplosion);
			printf("%d collisions happened in the map!\n", numCollision);

			free(p);
			freePointsContainer(&pc);
		
		}
		else printf("Unrecognized command: %2s\n", command);
	}

	return 0;
}
