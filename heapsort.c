/*
 * heapsort.c
 *
 * Implementation of the heapsort algorithm
 * Created on: Mar 13, 2014
 * Author: Tomas E. Tecce
 */
#define IS_LESS(v1, v2)  (v1 < v2)

void usenddown(unsigned int *, int, int);


void uheapsort(unsigned int *array, int size)
{
    int start, end;
    unsigned int temp;

    /* Heapify */
    for (start=(size-2)/2; start>=0; start--) {
        usenddown(array, start, size);
    }

    for (end=size-1; end>0; end--) {
    	temp = array[end];
    	array[end] = array[0];
    	array[0] = temp;
        usenddown(array, 0, end);
    }

    return;
}


void usenddown(unsigned int *array, int start, int end)
{
    int root=start;
    int child;
    unsigned int temp;

    while (root*2+1 < end) {
    	child = 2*root + 1;
        if ((child+1<end) && IS_LESS(array[child],array[child+1])) {
        	child += 1;
        }
        if (IS_LESS(array[root], array[child])) {
            temp = array[child];
            array[child] = array[root];
            array[root] = temp;
        	root = child;
        }
        else
            return;
    }

    return;
}
