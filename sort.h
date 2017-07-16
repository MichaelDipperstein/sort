/***************************************************************************
*                     Collection of Sorting Algorithms
*
*   File    : sort.h
*   Purpose : This is the header for a library containing a collection of
*             algorithms used to sort arrays of integers.
*   Author  : Michael Dipperstein
*   Date    : August 28, 2003
*
****************************************************************************
*   UPDATES
*
*   $Id: sort.h,v 1.6 2007/09/29 01:51:52 michael Exp $
*   $Log: sort.h,v $
*   Revision 1.6  2007/09/29 01:51:52  michael
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

#ifndef _SORT_H_
#define _SORT_H_
/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdlib.h>

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
/* order N^2 insertion sort */
void InsertionSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/* order N^2 bubble sort */
void BubbleSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/* order N^(3/2) Shell sort */
void ShellSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/* order N * log(N) quick sort */
void QuickSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/* order N * log(N) merge sort */
void MergeSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/* order N * log(N) heap sort */
void HeapSort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

/* order N * k radix sort */
void RadixSort(void *list, size_t numItems, size_t itemSize,
    unsigned int numKeys, unsigned int (*keyFunc) (const void *));

/* tests sorts results */
int VerifySort(void *list, size_t numItems, size_t itemSize,
    int (*compareFunc) (const void *, const void *));

#endif /* _SORT_H_ */
