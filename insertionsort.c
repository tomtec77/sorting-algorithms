/*
 * insertionsort.c
 *
 * Implementation of the insertionsort algorithm
 * Created on: Mar 13, 2014
 * Author: Tomas E. Tecce
 */

void uinsertionsort(unsigned int *array, int size)
{
	int i, j;
	unsigned int index;

	for (i=1; i<size; i++) {
		index = array[i];
		j = i;
		while (j>0 && array[j-1] > index) {
			array[j] = array[j-1];
			j--;
		}
		array[j] = index;
	}

	return;
}
