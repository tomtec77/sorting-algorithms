/*
 * bubblesort.c
 *
 * Implementation of the bubblesort algorithm
 * Created on: Mar 13, 2014
 * Author: Tomas E. Tecce
 */

/*
 * Perform a bubblesort on the elements of an array of unsigned int of
 * size n
 */
void ububblesort(unsigned int *array, int n)
{
	int i, j;
	unsigned int temp;

	for (i=n-1; i>=1; i--) {
		for (j=1; j<=i; j++) {
			if (array[j-1] > array[j]) {
				temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
			}
		}
	}

	return;
}
