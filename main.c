#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

typedef struct airplane {
	double x,y;
	char mark[200];
}airplane_t;

typedef struct arrayplanes {
	airplane_t * plane;
	int capacity;
	int count;
}array_p_t;

typedef struct distance {
	int firstPlane;		// index of plane in sorted array
	int secondPlane;
}indexplanes_t;

typedef struct arraydistances {
	indexplanes_t * distance;
	int capacity;
	int count;
}array_i_t;

void appendArray(array_p_t * array, airplane_t temporary)
{
	if (array -> count == array -> capacity) {
		// expand array
		array -> capacity = (array -> capacity) * 2 + 1;
		array -> plane = (airplane_t *) realloc( array -> plane, array -> capacity * sizeof(airplane_t));
	}

	array -> plane[array -> count].x = temporary.x;
	array -> plane[array -> count].y = temporary.y;
	int n = strlen(temporary.mark);
	for (int i = 0; i < n; i++) {
		array->plane[array->count].mark[i] = temporary.mark[i];
	}
	array -> count += 1;
}


int loadAirplanes(array_p_t * array)
{
	int result;
	airplane_t temporary;
	printf("Pozice letadel:\n");
	while((result = scanf("%lf,%lf: %199s", &temporary.x, &temporary.y, temporary.mark)) == 3) {	//load input into temporary struct
		appendArray(array, temporary);
	}
	if (result != EOF || array -> count < 2) {
		return 1;
	}
	return 0;
}

void freePlane(array_p_t * array)
{
	free(array -> plane);
}

void freeDistance(array_i_t * arrayD)
{
	free(arrayD -> distance);
}

void printArray(array_p_t * array)
{
	for (int i = 0; i < (array -> count); i++) {
		printf("Letadlo %d:\n", i);
		printf("x: %lf y: %lf oznaceni: %s\n", array -> plane[i].x, array -> plane[i].y, array -> plane[i].mark);
	}
}


int compareDouble(const airplane_t * a, const airplane_t * b)
{

	if (a -> x > b -> x)
		return 1;
	if (b -> x > b -> x)
		return -1;
	if (a -> y > b -> y)		// if x's are equal, compare y's
		return 1;
	if (b -> y > a -> y)
		return -1;
	return 0;
}

void qsortSort(array_p_t * array)			/* Qsort a compareInts převzato od bitninjy https://gitlab.fit.cvut.cz/bittnja3/pa1-2022-cviceni/-/blob/master/cv07/arraysx.c */
{
	qsort(array -> plane, array -> count, sizeof(array -> plane[0]), (int (*)(const void *, const void *)) compareDouble);
}

double calculateDistance(array_p_t * array, int i, int j)
{
	double distance;
	distance = sqrt((array -> plane[i].x - array -> plane[j].x)*(array -> plane[i].x - array -> plane[j].x) + (array -> plane[i].y - array -> plane[j].y)*(array -> plane[i].y - array -> plane[j].y) );				//sqrt((x1-x2)^2 + (y1-y2)^2) pythagoras
	return distance;
}

void appendArrayD(array_i_t * array, int firstPlane, int secondPlane)
{
	if (array -> count == array -> capacity) {
		// expand array
		array -> capacity = (array -> capacity) * 2 + 1;
		array -> distance = (indexplanes_t *) realloc( array -> distance, array -> capacity * sizeof(indexplanes_t));
	}
	array -> distance[array -> count].firstPlane = firstPlane;
	array -> distance[array -> count].secondPlane = secondPlane;
	array -> count += 1;
}
//printf("\n compare: %.20lf %.20lf\na-b: %.20lf eps: %.20lf\n", a, *b, abs(a-*b), 10000* DBL_EPSILON * (abs(a) + abs(*b)));
int compare(double a, double b)
{
	if (abs(a - b) <= DBL_EPSILON * (abs(a) + abs(b)))
		return 0;
	if (a > b)
		return 1;
	else
		return -1;
}

void rewrite(array_i_t * arrayD, int firstPlane, int secondPlane)
{
	arrayD -> distance[0].firstPlane = firstPlane;
	arrayD -> distance[0].secondPlane = secondPlane;
	arrayD -> count = 1;

}

void decide(array_p_t * array, array_i_t * arrayD, int i, int j, double * minDistance)
{
	double distance = calculateDistance(array, i, j);
	if (i == 0 && j == 1) {                                        //first run
		appendArrayD(arrayD, i, j);
		*minDistance = distance;
	}
	else {				//every other run
		if (compare(distance, *minDistance) == 0) {		//they are equal, add new information about planes
			appendArrayD(arrayD, i, j);
		}
		else if (compare(distance, *minDistance) == -1) {                        //distance < minDistance, rewrites the first element
			rewrite(arrayD, i, j);
			*minDistance = distance;
		}
	}
}

void getShortestDistance(array_p_t * array, array_i_t * arrayD, double * minDistance)
{
	for (int i = 0; i < array -> count - 1; i++){
		for (int j = i + 1; j < array -> count; j++){
			decide(array, arrayD, i, j, minDistance);
		}
	}

}

void printDistances(array_p_t * array, array_i_t * arrayD, double * minDistance)
{
	printf("Vzdalenost nejblizsich letadel: %lf\n", *minDistance);
	printf("Nalezenych dvojic: %d\n", arrayD -> count);
	for (int i = 0; i < (arrayD -> count); i++) {

		printf("%s - %s\n",array->plane[arrayD -> distance[i].firstPlane].mark, array -> plane[arrayD -> distance[i].secondPlane].mark);
	}
}

int main(void) {
	array_p_t array = {};
	array_i_t arrayD = {};
	double minDistance;
	if (loadAirplanes(&array)) {
		printf("Nespravny vstup.\n");
		freePlane(&array);
		return 1;
	}
	//printArray(&array);
	//qsortSort(&array;
	//printArray(&array);
	getShortestDistance(&array, &arrayD, &minDistance);

	printDistances(&array, &arrayD, &minDistance);
	freePlane(&array);
	freeDistance(&arrayD);
	return 0;
}


