/*
 * sorting.c
 *
 * Test different sorting algorithms. This programs first generates an
 * array of random positive integers (size specified by the user), then
 * the different sorting algorithms are called and timed to measure their
 * performance.
 *
 * TO DO:
 *     - Add mergesort
 *     - Add quicksort
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

/* We don't want to create something over 512MB = 4*512*1024*1024 */
#define MAX_ARRAY_SIZE 134217728

/* Function prototypes */
void ububblesort(unsigned int *, int);
void uinsertionsort(unsigned int *, int);
void uselectionsort(unsigned int *, int);
void ushellsort(unsigned int *, int);
void uheapsort(unsigned int *, int);


int main(int argc, char **argv)
{
	FILE *fp;
	time_t t0, t1;
	clock_t c0, c1;
	int i, size=0;
	unsigned int maxvalue;
	unsigned int *numarray, *temparray;


	/* I/O section. Here we ask the user for the size of the array */
	while (size <= 0 || size > MAX_ARRAY_SIZE) {
		printf("Testing sorting algorithms. Please input array size: ");
		scanf("%d", &size);
		if (size <= 0 || size > MAX_ARRAY_SIZE) {
			printf("Invalid number entered, please try again\n");
		}
	}
	printf("\n"); fflush(stdout);

	/* Create an array of integers with the specified size, then fill it
	   with random numbers */
	t0 = time(NULL);    /* To time this part of the program */
	c0 = clock();
	printf("Creating an array of %d random integers...\n", size);
	numarray  = malloc((size_t)(size*sizeof(unsigned int)));
	temparray = malloc((size_t)(size*sizeof(unsigned int)));

	/* Open a file to save the initial unsorted data to it */
	fp = fopen("unsortedarray.dat", "w");
	if (fp==NULL) {
		printf("Error: cannot write file 'unsortedarray.dat' - Stop.\n");
		fflush(stdout);
	    exit(EXIT_FAILURE);
	}

	/* We will use the final sorted array to test search algorithms, so we
	   would like to restrict the values the array elements can take in
	   order to have a reasonable chance of guessing correctly which
	   numbers actually are in the array */
	maxvalue = 2*size;
	rnd_setup(0,0,0);    /* Initialise random number generator */
	for (i=0; i<size; i++) {
		do {
			numarray[i] = KISS();
		} while (numarray[i] > maxvalue);
		/*printf("i, n[i]: %u %u\n", i, numarray[i]);*/
		fprintf(fp, "%d %u\n", i, numarray[i]); /* Write to file */
	}
	fflush(stdout);
	t1 = time(NULL);
	c1 = clock();
	printf("Data array created.\n");
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n\n", (double)(c1-c0)/CLOCKS_PER_SEC);
	fflush(stdout);

	fclose(fp);

	/* We make a copy of the array and sort the copy, in order to apply
	  different sorting algorithms to the same set */
	for (i=0; i<size; i++)
		temparray[i] = numarray[i];

	/* First we'll sort the array using bubblesort */
	printf("Sorting the array with bubblesort...\n");
	t0 = time(NULL);
	c0 = clock();

	ububblesort(temparray,size);

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n",(double)(c1-c0)/CLOCKS_PER_SEC);
	fflush(stdout);

	/* Now use selectionsort */
	printf("\nSorting the array with selectionsort...\n");
	t0 = time(NULL);
	c0 = clock();

	uselectionsort(temparray,size);

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n", (double)(c1-c0)/CLOCKS_PER_SEC);
	fflush(stdout);

	/* Now use insertionsort */
	for (i=0; i<size; i++)
		temparray[i] = numarray[i];

	printf("\nSorting the array with insertionsort...\n");
	t0 = time(NULL);
	c0 = clock();

	uinsertionsort(temparray,size);

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n", (double)(c1-c0)/CLOCKS_PER_SEC);
	fflush(stdout);

	/* Now we close the group of O(n^2) algorithms with shellsort */
	for (i=0; i<size; i++)
		temparray[i] = numarray[i];

	printf("\nSorting the array with shellsort...\n");
	t0 = time(NULL);
	c0 = clock();

	ushellsort(temparray,size);

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n", (double)(c1-c0)/CLOCKS_PER_SEC);
	fflush(stdout);

	/* Now for the O(n log n) algorithms, starting with heapsort */
	for (i=0; i<size; i++)
		temparray[i] = numarray[i];

	printf("\nSorting the array with heapsort...\n");
	t0 = time(NULL);
	c0 = clock();

	uheapsort(temparray,size);

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n", (double)(c1-c0)/CLOCKS_PER_SEC);
	fflush(stdout);

	/*printf("Sorted array:\n");
	for (i=0; i<size; i++)
		printf("i, n[i]: %u %u\n", i, temparray[i]);
	fflush(stdout);*/

	/* Open a file to save the sorted data to it */
	fp = fopen("array.dat", "w");
	if (fp==NULL) {
		printf("Error: cannot write file 'array.dat' - Stop.\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	for (i=0; i<size; i++)
		fprintf(fp, "%d %u\n", i, temparray[i]);
	fclose(fp);

	/* Free allocated memory */
	free(numarray);
	free(temparray);

	return EXIT_SUCCESS;
}
