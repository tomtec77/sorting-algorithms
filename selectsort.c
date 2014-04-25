/*
 * selectsort.c
 *
 * Implementation of the selectionsort algorithm
 * Created on: Mar 13, 2014
 * Author: Tomas E. Tecce
 */

void uselectionsort(unsigned int *array, int size)
{
	int i, j, min;
	unsigned int temp;

	for (i=0; i<size-1; i++) {
		min = i;
		for (j=i+1; j<size; j++) {
			if (array[j] < array[min])
				min = j;
		}
		temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}
	return;
}
