/***************************************************************************
*                     Collection of Sorting Algorithms
*
*   File    : sort.c
*   Purpose : This implements a library containing a collection of
*             algorithms used to sort arrays of integers.
*   Author  : Michael Dipperstein
*   Date    : August 28, 2003
*
****************************************************************************
*   UPDATES
*
*   $Id: sort.c,v 1.7 2007/09/29 01:51:52 michael Exp $
*   $Log: sort.c,v $
*   Revision 1.7  2007/09/29 01:51:52  michael
*   Changes required for LGPL v3.
*
*
****************************************************************************
* sort: An ANSI C collection of sort algorithms.
*       I have implemented these algorithms out of personal interest.  They
*       are not inteded to be the best or the fastest.  They are intended
*       to be flexible, portable examples of techniques used to sort items.
*
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
#include "sort.h"
#include <string.h>

/***************************************************************************
*                                 MACROS
***************************************************************************/
#define Swap(x, y, temp, size)      {   memcpy(temp, x, size);  \
                                        memcpy(x, y, size);     \
                                        memcpy(y, temp, size);  }

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
void SiftDown(void *list, size_t root, size_t lastChild, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : VerifySort
*   Description: This function verifies that an array of integers is
*                sorted in ascending order.
*   Parameters : list - a pointer to a sorted array of items
*                numItems - number of items in the sorted array
*                itemSize - size of each item in the sorted array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : NONE
*   Returned   : 1 for success, 0 for failure (unsorted list).
***************************************************************************/
int VerifySort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    size_t i, endItem;

    endItem = (numItems - 1) * itemSize;
    for (i = 0; i < endItem; i += itemSize)
    {
        if (compareFunc((list + i), (list + i + itemSize)) > 0)
        {
            return (FALSE);
        }
    }

    return(TRUE);
}

/***************************************************************************
*   Function   : InsertionSort
*   Description: This function performs an insertion sort on array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : The contents of list are sorted in ascending order
*   Returned   : NONE
***************************************************************************/
void InsertionSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    size_t i, j, endItem;
    void *temp;

    /* create temporary swap variable */
    temp = malloc(itemSize);
    if (temp == NULL)
    {
        return;
    }

    endItem = numItems * itemSize;
    for (i = itemSize; i < endItem; i += itemSize)
    {
        j = i;
        memcpy(temp, (list + i), itemSize);

        /* look for a place to insert list[i] */
        while ((j > 0) &&
            (compareFunc(temp, (list + j - itemSize)) < 0))
        {
            memcpy((list + j), (list + j - itemSize), itemSize);
            j -= itemSize;
        }

        memcpy((list + j), temp, itemSize);
    }

    free(temp);
}

/***************************************************************************
*   Function   : BubbleSort
*   Description: This function performs an bubble sort on array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : The contents of list are sorted in ascending order
*   Returned   : NONE
***************************************************************************/
void BubbleSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    size_t i, endItem;
    char done = FALSE;  /* true if no swaps last pass */
    void *temp;

    /* create temporary swap variable */
    temp = malloc(itemSize);
    if (temp == NULL)
    {
        return;
    }

    while (!done)
    {
        done = TRUE;
        numItems--;     /* one less item left to sort after each pass */
        endItem = numItems * itemSize;

        /* push largest value to end of list each iteration */
        for (i = 0; i < endItem; i += itemSize)
        {
            if (compareFunc((list + i + itemSize), (list + i)) < 0)
            {
                /* swap values */
                Swap((list + i), (list + i + itemSize), temp, itemSize);
                done = FALSE;
            }
        }
    }

    free(temp);
}

/***************************************************************************
*   Function   : ShellSort
*   Description: This function performs an Shell sort on array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : The contents of list are sorted in ascending order
*   Returned   : NONE
***************************************************************************/
void ShellSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    size_t i, j, endItem;
    size_t increment, incrementItem;    /* spacing between sorted numbers */
    void *temp;

    /* create temporary swap variable */
    temp = malloc(itemSize);
    if (temp == NULL)
    {
        return;
    }

    /* determine starting increment size in the form of (3^k - 1) */
    for (increment = 1;
        increment <= numItems;
        increment = (increment * 3) + 1);

    endItem = numItems * itemSize;

    /* loop through partial sorts */
    for (increment /= 3; increment > 0; increment /= 3)
    {
        incrementItem = increment * itemSize;

        /* insertion sort at increment spacing */
        for (i = incrementItem; i < endItem; i += itemSize)
        {
            j = i;
            memcpy(temp, (list + i), itemSize);
            /* look for a place to insert list[i] using increment spacing */
            while ((j >= incrementItem) &&
                (compareFunc(temp, (list + j - incrementItem)) < 0))
            {
                memcpy((list + j), (list + j - incrementItem),
                    itemSize);
                j = j - incrementItem;
            }

            memcpy((list + j), temp, itemSize);
        }
    }

    free(temp);
}

/***************************************************************************
*   Function   : QuickSort
*   Description: This function performs an quick sort on array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : The contents of list are sorted in ascending order
*   Returned   : NONE
***************************************************************************/
void QuickSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    size_t left, right;         /* partition pointers */
    void *temp;

    /* create temporary swap variable */
    temp = malloc(itemSize);
    if (temp == NULL)
    {
        return;
    }

    if (numItems > 1)
    {
        left = 0;
        right = numItems * itemSize;

        while(TRUE)
        {
            /* seek until something on left partition is too large */
            while((compareFunc((list + (left += itemSize)), list) <= 0) &&
            (left <= right));

            if (left == right)
            {
                /* went too far */
                right -= itemSize;
                break;
            }

            /* seek until something on right partition is too small */
            while(compareFunc((list + (right -= itemSize)), list) > 0);

            if (left >= right)
            {
                /* went too far */
                break;
            }

            /* swap left and right */
            Swap((list + left), (list + right), temp, itemSize);
        }

        /* found place for start */
        Swap(list, (list + right), temp, itemSize);

        /* sort each partition  [0 .. right] and [right + 1 .. end] */
        QuickSort(list, right / itemSize, itemSize, compareFunc);
        QuickSort((list + right + itemSize),
        numItems - ((right / itemSize) + 1), itemSize, compareFunc);
    }

    free(temp);
}

/***************************************************************************
*   Function   : MergeSort
*   Description: This function performs an merge sort on array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : The contents of list are sorted in ascending order
*   Returned   : NONE
***************************************************************************/
void MergeSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    int pivot;
    void *merged;
    int lowPtr, highPtr, mergedPtr;

    if (numItems <= 1)
    {
        /* singleton lists are already sorted */
        return;
    }

    /* divide the list in half */
    pivot = (numItems - 1) / 2;

    /* sort each half of the list */
    MergeSort(list, (pivot + 1), itemSize, compareFunc);
    MergeSort(list + ((pivot + 1) * itemSize), numItems - pivot - 1,
        itemSize, compareFunc);

    merged = (void *)malloc(numItems * itemSize);
    if (merged == NULL)
    {
        /* couldn't get array to do merging */
        return;
    }

    /***********************************************************************
    * merge list[0] .. list[pivot] with
    * list[pivot + 1] .. list[numItems - 1]
    * Indices are itemSize from here on out
    ************************************************************************/
    pivot *=  itemSize;
    numItems *= itemSize;
    lowPtr = 0;
    highPtr = pivot + itemSize;
    mergedPtr = 0;

    while ((lowPtr <= pivot) && (highPtr < numItems))
    {
        if (compareFunc((list + lowPtr), (list + highPtr)) < 0)
        {
            memcpy((merged + mergedPtr), (list + lowPtr), itemSize);
            mergedPtr += itemSize;
            lowPtr += itemSize;
        }
        else
        {
            memcpy((merged + mergedPtr), (list + highPtr), itemSize);
            mergedPtr += itemSize;
            highPtr += itemSize;
        }
    }

    /* one of the halves ran out of data, just copy from the other half */
    if (lowPtr > pivot)
    {
        /* finish low half */
        while(highPtr < numItems)
        {
            memcpy((merged + mergedPtr), (list + highPtr), itemSize);
            mergedPtr += itemSize;
            highPtr += itemSize;
        }
    }
    else
    {
        /* finish high half */
        while(lowPtr <= pivot)
        {
            memcpy((merged + mergedPtr), (list + lowPtr), itemSize);
            mergedPtr += itemSize;
            lowPtr += itemSize;
        }
    }

    /* now copy the merged arrays out of merged */
    memcpy(list, merged, numItems);
    free(merged);
}

/***************************************************************************
*   Function   : SiftDown
*   Description: This function performs the "sift down" function described
*                in the heap sort algorithm.  It is used for both building
*                a heap and sorting the heap.  A heap is a collection of
*                items arranged in a binary tree, such that each child node
*                is less than or equal to its parent.
*                If list[k] is the parent, its children are list[(2 * k) + 1]
*                and list[(2 * k) + 2].
*   Parameters : list - a pointer of an array of items
*                root - the root index from which to start sifting
*                lastChild - the last child (largest node index) in the
*                            sift operation.
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : Promotes (sifts up) children larger than their parents
*                along a path starting at root.
*   Returned   : NONE
***************************************************************************/
void SiftDown(void *list, size_t root, size_t lastChild, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    size_t child;
    void *temp;

    /* create temporary swap variable */
    temp = malloc(itemSize);
    if (temp == NULL)
    {
        return;
    }

    for (; (child = (root * 2) + 1) <= lastChild; root = child)
    {
        /* assume left child (child) is the largest until proven otherwise */
        if (child < lastChild)
        {
            /* there is a right child */
            if (compareFunc((list + (child * itemSize)),
                (list + ((child + 1) * itemSize))) < 0)
            {
                /* right child is actually larger */
                child++;
            }
        }

        if (compareFunc((list + (child * itemSize)),
            (list + (root * itemSize))) <= 0)
        {
            break;
        }

        /* child is greater than its parent, swap them */
        Swap((list + (root * itemSize)), (list + (child * itemSize)),
            temp, itemSize);
    }

    free(temp);
}

/***************************************************************************
*   Function   : HeapSort
*   Description: This function performs an heap sort on array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                compareFunc - a comparison function such that:
*                   compareFunc(x, y) < 0  iff x precedes y
*                   compareFunc(x, y) = 0  iff x and y are ordered the same
*                   compareFunc(x, y) > 0  iff y precedes x
*   Effects    : The contents of list are sorted in ascending order
*   Returned   : NONE
***************************************************************************/
void HeapSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *))
{
    int i;
    void *temp;

    if (numItems <= 1)
    {
        return;
    }

    /* create temporary swap variable */
    temp = malloc(itemSize);
    if (temp == NULL)
    {
        return;
    }

    /* build a heap adding one element at a time */
    for (i = numItems / 2; i >= 0; i--)
    {
        SiftDown(list, i, numItems - 1, itemSize, compareFunc);
    }

    /***********************************************************************
    * The largest item is now at the top of the heap.  Pull it off the
    * top of the heap, and rebuild the rest of the heap.  Items pulled
    * off the top of the heap will be placed at the end of the heap, and
    * the heap size will be decremented by one.  This has the effect of
    * sorting the list backwards.
    ************************************************************************/
    while (numItems > 1)
    {
        /* swap the largest item with the last item in the heap */
        Swap(list, (list + ((numItems - 1) * itemSize)), temp,
            itemSize);

        /* make the heap one item smaller and rebuild the heap */
        numItems--;
        SiftDown(list, 0, numItems - 1, itemSize, compareFunc);
    }

    free(temp);
    return;
}

/***************************************************************************
*   Function   : RadixSort
*   Description: This function performs a single pass of a radix sort on
*                array of items.
*   Parameters : list - a pointer of an array of items to sort
*                numItems - number of items in the array
*                itemSize - size of each item in the array
*                numKeys - number of keys produced by keyFunc
*                keyFunc - a function that generates a key used for
*                          the current sorting pass.  The key values
*                          are expected to range from 0 to (numKeys - 1)
*   Effects    : The contents of list are sorted according to their key.
*                Multiple calls to this function may be required to obtain
*                the desired sort.
*   Returned   : NONE
***************************************************************************/
void RadixSort(void *list, size_t numItems, size_t itemSize,
    unsigned int numKeys, unsigned int (*keyFunc) (const void *))
{
    unsigned int *keyCounters;      /* num values with the same key */
    size_t *offsetTable;            /* position of next value with key */
    size_t i;
    size_t key;
    void *temp;

    /* create an array of zeroed key counters */
    keyCounters = (unsigned int *)calloc(numKeys, sizeof(unsigned int));

    if (keyCounters == NULL)
    {
        return;
    }

    /* count occurances of values with same key */
    for (i = 0; i < numItems; i++)
    {
        key = keyFunc(list + (itemSize * i));
        keyCounters[key] = keyCounters[key] + 1;
    }

    /* allocate offset table */
    offsetTable = (unsigned int *)malloc(numKeys * sizeof(unsigned int));

    if (offsetTable == NULL)
    {
        return;
    }

    offsetTable[0] = 0;         /* the first key 0 item starts at 0 */

    for(i = 1; i < numKeys; i++)
    {
        /* determine sorted offset for the first value with key i */
        offsetTable[i] = offsetTable[i - 1] + keyCounters[i - 1];
    }

    free(keyCounters);          /* we're done with keyCounters now */

    temp = malloc(numItems * itemSize);

    if (temp == NULL)
    {
        return;
    }

    /* now sort */
    for (i = 0; i < numItems; i++)
    {
        key = keyFunc(list + (itemSize * i));

        /* copy list + (itemSize * i) into its sorted position */
        memcpy(temp + (offsetTable[key] * itemSize),
            list + (itemSize * i),
            itemSize);

        /* the next item with the same key is sorted one position higher */
        offsetTable[key] = offsetTable[key] + 1;
    }

    /* copy sorted data back to list */
    memcpy(list, temp, itemSize * numItems);

    free(offsetTable);
    free(temp);
}
