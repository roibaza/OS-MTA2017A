//triangle {1.0, 1.0} {4.0, 5.0} {4.0, 1.0} perimeter = 12.0
//triangle {1.0, 1.0} {4.0, 5.0} {4.0, 1.0} area = 6.0

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

struct point {
 float x, y;
};

struct triangle {
 struct point vertices[3];
};

void READER();
void polygon();
double getDistance(struct point *a, struct point *b);
double calc_perimeter(struct point *a, struct point *b, struct point *c);
double calc_area(struct point *a, struct point *b, struct point *c);

int main(){

	int pipe_fd[2];
	pipe(pipe_fd);
	int pid;
	
	pid = fork();
	//printf("mypid=%d: just forked %d\n", getpid(), pid); 
	if (pid < 0) 
	{
		perror("Cannot fork()") ;
		exit(EXIT_FAILURE) ;
	}
	if (pid == 0)
	{
		printf("Hello from Son pid=%d\n", getpid());
		READER();
		exit(0);
	} 

	int status;
	// for (i=0; i< 2; i++)
	wait(&status); //int status
	return 0;

	//polygon();
}

void READER() {
	polygon();
}
void polygon()
{
	int N = 0, i=0, j=0;
	scanf("%d", &N);
	struct triangle *ptr = malloc(N *sizeof(struct triangle));

	for(i = 0; i < N; i++) 
	{
		for(j = 0; j < 3; j++){
			scanf("%f", &(ptr + i)->vertices[j].x);
			scanf("%f", &(ptr + i)->vertices[j].y);
		}

		printf("triangle {%.1f, %.1f} {%.1f, %.1f} {%.1f, %.1f} perimeter = %.1f\n",
		(ptr + i)->vertices[0].x, (ptr + i)->vertices[0].y,
		(ptr + i)->vertices[1].x, (ptr + i)->vertices[1].y,
		(ptr + i)->vertices[2].x, (ptr + i)->vertices[2].y,
		calc_perimeter(&(ptr + i)->vertices[0], &(ptr + i)->vertices[1], &(ptr + i)->vertices[2]));
		printf("triangle {%.1f, %.1f} {%.1f, %.1f} {%.1f, %.1f} area = %.1f\n",
		(ptr + i)->vertices[0].x, (ptr + i)->vertices[0].y,
		(ptr + i)->vertices[1].x, (ptr + i)->vertices[1].y,
		(ptr + i)->vertices[2].x, (ptr + i)->vertices[2].y,
		calc_area(&(ptr + i)->vertices[0], &(ptr + i)->vertices[1], &(ptr + i)->vertices[2]));
	}
}

double getDistance(struct point *a, struct point *b) 
{
   double distance;
   distance = sqrt((a->x - b->x) * (a->x - b->x) + (a->y-b->y) *(a->y-b->y));
   return distance;
}

double calc_perimeter(struct point *a, struct point *b, struct point *c) 
{
	return getDistance(a, b) + getDistance(a, c) + getDistance(b, c);
}

double calc_area(struct point *a, struct point *b, struct point *c) 
{
	float s;
	s = (getDistance(a, b) + getDistance(a, c) + getDistance(b, c))/2;
	return (sqrt(s* (s-getDistance(a, b)) * (s-getDistance(a, c)) * (s-getDistance(b, c))));
}
