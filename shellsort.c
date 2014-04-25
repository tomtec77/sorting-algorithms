/*
 * shellsort.c
 *
 * Implementation of the shellsort algorithm
 * Created on: Mar 13, 2014
 * Author: Tomas E. Tecce
 */

void ushellsort(unsigned int *array, int size)
{
	int i, j, increment;
	unsigned int temp;

	for (increment = size/2; increment>0; increment/=2) {
		for (i=increment; i<size; i++) {
			temp = array[i];
			for(j=i; j>=increment; j-=increment) {
				if (temp < array[j-increment]) {
					array[j] = array[j-increment];
				}
				else
					break;
			}
			array[j] = temp;
		}
	}

	return;
}
