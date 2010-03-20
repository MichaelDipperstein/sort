/***************************************************************************
*                        Sort Library Sample Usage
*
*   File    : sample.c
*   Purpose : This file demonstrates the use of the sort library functions
*   Author  : Michael Dipperstein
*   Date    : August 28, 2003
*
****************************************************************************
*   UPDATES
*
*   $Id: sample.c,v 1.7 2010/01/07 04:16:34 michael Exp $
*   $Log: sample.c,v $
*   Revision 1.7  2010/01/07 04:16:34  michael
*   - Clean-up compiler warnings.
*   - Reduce the amount of compares for a Radix sort.
*
*   Revision 1.6  2007/09/29 01:51:52  michael
*   Changes required for LGPL v3.
*
*
****************************************************************************
* sample: A sort library sample program
* Copyright (C) 2003, 2007 by
*       Michael Dipperstein (mdipper@alumni.engr.ucsb.edu)
*
* This file is part of the sort library.
*
* The sort library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 3 of the
* License, or (at your option) any later version.
*
* The sort library is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
* General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

/***************************************************************************
*                            GLOBAL VARIABLES
***************************************************************************/
unsigned long comparisons;

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : CompareIntLessThan
*   Description: This function may be used by my sort library (and qsort)
*                to order integers in assending order.
*   Parameters : x - a pointer to an integer recast as a pointer to void
*                y - a pointer to an integer recast as a pointer to void
*   Effects    : NONE
*   Returned   : compareFunc(x, y) < 0  iff x preceeds y
*                compareFunc(x, y) = 0  iff x and y are ordered the same
*                compareFunc(x, y) > 0  iff y preceeds x
***************************************************************************/
int CompareIntLessThan(const void *x, const void *y)
{
    comparisons++;
    return (*(int *)x - *(int *)y);
}

/***************************************************************************
*   Function   : CompareIntGreaterThan
*   Description: This function may be used by my sort library (and qsort)
*                to order integers in decending order.
*   Parameters : x - a pointer to an integer recast as a pointer to void
*                y - a pointer to an integer recast as a pointer to void
*   Effects    : NONE
*   Returned   : compareFunc(x, y) < 0  iff x preceeds y
*                compareFunc(x, y) = 0  iff x and y are ordered the same
*                compareFunc(x, y) > 0  iff y preceeds x
***************************************************************************/
int CompareIntGreaterThan(const void *x, const void *y)
{
    comparisons++;
    return (*(int *)y - *(int *)x);
}

/***************************************************************************
*   Function   : Byte0Key
*   Description: This function may be used by my RadixSort function to
*                to order integers in decending order.  It provides byte 0,
*                the LSB of an integer, to be used as the first pass of a
*                radix sort.
*   Parameters : value - a pointer to an integer recast as a pointer to void
*   Effects    : NONE
*   Returned   : Byte 0 (the LSB of an integer)
***************************************************************************/
unsigned int Byte0Key(const void *value)
{
    /* return byte 0 of an int */
    comparisons++;
    return (unsigned int)((*(int *)value) & 0xFF);
}

/***************************************************************************
*   Function   : Byte1Key
*   Description: This function may be used by my RadixSort function to
*                to order integers in decending order.  It provides byte 1,
*                the second LSB of an integer, to be used as the second pass
*                of a radix sort.
*   Parameters : value - a pointer to an integer recast as a pointer to void
*   Effects    : NONE
*   Returned   : Byte 1 (the second LSB of an integer)
***************************************************************************/
unsigned int Byte1Key(const void *value)
{
    /* return byte 1 of an int */
    comparisons++;
    return (unsigned int)(((*(int *)value) >> 8) & 0xFF);
}

/***************************************************************************
*   Function   : Byte2Key
*   Description: This function may be used by my RadixSort function to
*                to order integers in decending order.  It provides byte 2,
*                the second MSB of an integer, to be used as the third pass
*                of a radix sort.
*   Parameters : value - a pointer to an integer recast as a pointer to void
*   Effects    : NONE
*   Returned   : Byte 2 (the second MSB of an integer)
***************************************************************************/
unsigned int Byte2Key(const void *value)
{
    /* return byte 2 of an int */
    comparisons++;
    return (unsigned int)(((*(int *)value) >> 16) & 0xFF);
}

/***************************************************************************
*   Function   : Byte3Key
*   Description: This function may be used by my RadixSort function to
*                to order integers in decending order.  It provides byte 3,
*                the MSB of an integer, to be used as the fourth pass of a
*                radix sort.
*   Parameters : value - a pointer to an integer recast as a pointer to void
*   Effects    : NONE
*   Returned   : Byte 3 (the MSB of an integer)
***************************************************************************/
unsigned int Byte3Key(const void *value)
{
    /* return byte 3 of an int */
    comparisons++;
    return (unsigned int)(((*(int *)value) >> 24) & 0xFF);
}

/***************************************************************************
*   Function   : main
*   Description: This function is the entry point for this program.  It
*                creates an array of argv[1] unsorted integers and uses
*                each of the sort functions to sort the array.
*   Parameters : argc - number of arguments
*                argv - array of arguement values.  argv[1] should be the
*                       number of integers to sort.
*   Effects    : Unsorted and sorted arrays are dumped to stdout.
*   Returned   : 0 for failure.  1 for success.
***************************************************************************/
int main(int argc, char *argv[])
{
    int numItems;                       /* number of items sorted */
    int *list, *unsorted;               /* items to be sorted */
    int i;                              /* counter */
    time_t timer;                       /* time - used for random seed */

    /* check for input */
    if (argc < 2)
    {
        printf("Program must be called with number of items.\n");
        return (0);
    }

    numItems = (int)atoi((const char *)argv[1]);

    if (numItems < 2)
    {
        printf("At least 2 items are required for sort.\n");
        return (0);
    }

    /* allocate memory for sorted and unsorted lists */
    unsorted = (int *)malloc(numItems * sizeof(int));
    if (unsorted == NULL)
    {
        printf("Unable to allocate storage for %d items.\n", numItems);
        return (0);
    }

    list = (int *)malloc(numItems * sizeof(int));
    if (list == NULL)
    {
        printf("Unable to allocate storage for %d items.\n", numItems);
        return (0);
    }

    /* create and display unsorted list of items */
    srand((unsigned int)time(&timer));
    printf("Unsorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        unsorted[i] = rand() % 1000;
        printf("%d ", unsorted[i]);
    }
    printf("\n");

    /* --- Insertion Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;
    InsertionSort((void *)list, numItems, sizeof(int), CompareIntLessThan);

    printf("Insertion sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* --- Bubble Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;
    BubbleSort((void *)list, numItems, sizeof(int), CompareIntLessThan);
    printf("Bubble sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* --- Shell Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;
    ShellSort((void *)list, numItems, sizeof(int), CompareIntLessThan);
    printf("Shell sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* --- Quick Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;
    QuickSort((void *)list, numItems, sizeof(int), CompareIntLessThan);
    printf("Quick sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* --- Merge Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;
    MergeSort((void *)list, numItems, sizeof(int), CompareIntLessThan);
    printf("Merge sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* --- Heap Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;
    HeapSort((void *)list, numItems, sizeof(int), CompareIntLessThan);
    printf("Heap sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* --- Radix Sort --- */
    memcpy((void *)list, (void *)unsorted, numItems * sizeof(int));
    comparisons = 0;

    /* make one Radix sort pass for every byte (LSB to MSB) */
    RadixSort((void *)list, numItems, sizeof(int), 256, Byte0Key);
    RadixSort((void *)list, numItems, sizeof(int), 256, Byte1Key);
#if 0
    /* this sample only uses values 0 - 999 (that's only two bytes) */
    RadixSort((void *)list, numItems, sizeof(int), 256, Byte2Key);
    RadixSort((void *)list, numItems, sizeof(int), 256, Byte3Key);
#endif

    printf("Radix sorted list:\n");
    for (i = 0; i < numItems; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\nNumber of comparisons to sort %d Items: %ld\n",
        numItems, comparisons);

    if (!VerifySort((void *)list, numItems, sizeof(int), CompareIntLessThan))
    {
        printf("ERROR: Sort results are incorrect.\n");
    }

    /* clean-up and exit */
    free(unsorted);
    free(list);
    return(1);
}
