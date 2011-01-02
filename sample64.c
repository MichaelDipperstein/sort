/***************************************************************************
*                        Sort Library Sample Usage
*
*   File    : sample64.c
*   Purpose : This file demonstrates the use of the sort library functions
*             by sorting an array of 64-bit values.
*   Author  : Michael Dipperstein
*   Date    : October 19, 2010
*
****************************************************************************
* sample64: A sort library sample program
* Copyright (C) 2010
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
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "sort.h"
#include "optlist.h"
#include "mwc.h"

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/
typedef enum
{
    METHOD_NONE = 0x00,
    METHOD_INSERTION = 0x01,
    METHOD_BUBBLE = 0x02,
    METHOD_SHELL = 0x04,
    METHOD_QUICK = 0x08,
    METHOD_MERGE = 0x10,
    METHOD_HEAP = 0x20,
    METHOD_RADIX = 0x40
} sort_method_t;

/***************************************************************************
*                            GLOBAL VARIABLES
***************************************************************************/
unsigned long comparisons;

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
void ShowUsage(char *progPath);

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : CompareIntLessThan
*   Description: This function may be used by my sort library (and qsort)
*                to order 64 bit signed integers in assending order.
*   Parameters : x - a pointer to an int64_t recast as a pointer to void
*                y - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : compareFunc(x, y) < 0  iff x preceeds y
*                compareFunc(x, y) = 0  iff x and y are ordered the same
*                compareFunc(x, y) > 0  iff y preceeds x
***************************************************************************/
int CompareIntLessThan(const void *x, const void *y)
{
    int result;

    comparisons++;

    if (*(int64_t *)x < *(int64_t *)y)
    {
        result = -1;
    }
    else if (*(int64_t *)x > *(int64_t *)y)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    return result;
}

/***************************************************************************
*   Function   : CompareIntGreaterThan
*   Description: This function may be used by my sort library (and qsort)
*                to order 64 bit signed integers in decending order.
*   Parameters : x - a pointer to an int64_t recast as a pointer to void
*                y - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : compareFunc(x, y) > 0  iff x preceeds y
*                compareFunc(x, y) = 0  iff x and y are ordered the same
*                compareFunc(x, y) < 0  iff y preceeds x
***************************************************************************/
int CompareIntGreaterThan(const void *x, const void *y)
{
    int result;

    comparisons++;

    if (*(int64_t *)x > *(int64_t *)y)
    {
        result = -1;
    }
    else if (*(int64_t *)x < *(int64_t *)y)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    return result;
}

/***************************************************************************
*   Function   : Byte0Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 0 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 0 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte0Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)(asUnsigned & 0xFF);
}

/***************************************************************************
*   Function   : Byte1Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 1 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 1 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte1Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 8) & 0xFF);
}

/***************************************************************************
*   Function   : Byte2Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 2 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 2 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte2Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 16) & 0xFF);
}

/***************************************************************************
*   Function   : Byte3Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 3 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 3 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte3Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 24) & 0xFF);
}

/***************************************************************************
*   Function   : Byte4Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 4 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 4 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte4Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 32) & 0xFF);
}

/***************************************************************************
*   Function   : Byte5Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 5 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 5 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte5Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 40) & 0xFF);
}

/***************************************************************************
*   Function   : Byte6Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 6 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 6 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte6Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 48) & 0xFF);
}

/***************************************************************************
*   Function   : Byte7Key
*   Description: This function may be used by my RadixSort function to
*                to order int64_t values.  It provides a key for radix
*                sorting on byte 7 of the value (counting from the LSB).
*   Parameters : value - a pointer to an int64_t recast as a pointer to void
*   Effects    : NONE
*   Returned   : Sort key for byte 7 of an int64_t (counting from the LSB)
***************************************************************************/
unsigned int Byte7Key(const void *value)
{
    uint64_t asUnsigned;

    comparisons++;
    
    asUnsigned = (*(int64_t *)value) - INT64_MIN;

    return (unsigned int)((asUnsigned >> 56) & 0xFF);
}

/***************************************************************************
*   Function   : DumpList
*   Description: This function just prints all of the elements in an
*                array of integers.
*   Parameters : list - a pointer to an array of integers
*                numItems - the number of items in the array
*   Effects    : Array contents are printed to stdout
*   Returned   : NONE
***************************************************************************/
void DumpList(int64_t *list, size_t numItems)
{
    size_t i;

    for (i = 0; i < numItems; i++)
    {
        printf("%020" PRIi64 " ", list[i]);
    }

    printf("\n");
}

/***************************************************************************
*   Function   : main
*   Description: This function is the entry point for this program.  It
*                creates an array of argv[1] unsorted int64_t and uses
*                the specified sort functions to sort the array.
*   Parameters : argc - number of arguments
*                argv - an array of arguement values.  See ShowUsage for
*                       acceptable values
*   Effects    : Unsorted and sorted arrays are dumped to stdout.
*   Returned   : 0 for failure.  1 for success.
***************************************************************************/
int main(int argc, char *argv[])
{
    size_t numItems;                    /* number of items sorted */
    int64_t *list, *unsorted;           /* items to be sorted */
    size_t i;                           /* counter */
    unsigned char debug;                /* non-zero prints debug messages */
    mwc_seed_t seed;                    /* seed used for random numbers */
    sort_method_t methods;
    option_t *optList, *thisOpt;

    /* initialize variables */
    numItems = 0;
    debug = 0;
    methods = METHOD_NONE;

    /* parse command line */
    optList = GetOptList(argc, argv, "iIbBsSqQmMhHrRn:N:AadD?");
    thisOpt = optList;

    while (thisOpt != NULL)
    {
        switch(thisOpt->option)
        {
            case 'n':       /* number of items to sort */
            case 'N':
                numItems = (size_t)atoi(thisOpt->argument);

                if (numItems < 2)
                {
                    printf("At least 2 items are required for sort.\n");
                    return (0);
                }
                break;

            case 'i':       /* insertion sort */
            case 'I':
                methods |= METHOD_INSERTION;
                break;

            case 'b':       /* bubble sort */
            case 'B':
                methods |= METHOD_BUBBLE;
                break;

            case 's':       /* shell sort */
            case 'S':
                methods |= METHOD_SHELL;
                break;

            case 'q':       /* quick sort */
            case 'Q':
                methods |= METHOD_QUICK;
                break;

            case 'm':       /* merge sort */
            case 'M':
                methods |= METHOD_MERGE;
                break;

            case 'h':       /* heap sort */
            case 'H':
                methods |= METHOD_HEAP;
                break;

            case 'r':       /* radix sort */
            case 'R':
                methods |= METHOD_RADIX;
                break;

            case 'd':       /* enable debug dump of string */
            case 'D':
                debug = 1;
                break;

            case '?':
                ShowUsage(argv[0]);

                FreeOptList(optList);
                return EXIT_SUCCESS;
        }

        optList = thisOpt->next;
        free(thisOpt);
        thisOpt = optList;
    }

    if (METHOD_NONE == methods)
    {
        printf("Error: No Sort Methods Selected\n");
        ShowUsage(argv[0]);
        return EXIT_FAILURE;
    }

    if (0 == numItems)
    {
        printf("Number of items to sort is unspecified.\n");
        printf("Defaulting to 1000.\n");
        numItems = 1000;
    }

    /* allocate memory for sorted and unsorted lists */
    unsorted = (int64_t *)malloc(numItems * sizeof(int64_t));
    if (unsorted == NULL)
    {
        printf("Unable to allocate storage for %d items.\n", numItems);
        return EXIT_FAILURE;
    }

    list = (int64_t *)malloc(numItems * sizeof(int64_t));
    if (list == NULL)
    {
        printf("Unable to allocate storage for %d items.\n", numItems);
        free(unsorted);
        return EXIT_FAILURE;
    }

    /* create and display unsorted list of items */
    InitializeSeed(&seed);
    for (i = 0; i < numItems; i++)
    {
        unsorted[i] = RandMWC64(&seed);
    }

    if (debug)
    {
        printf("Unsorted list:\n");
        DumpList(unsorted, numItems);
    }

    /* --- Insertion Sort --- */
    if (methods & METHOD_INSERTION)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;
        InsertionSort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan);

        printf("Insertion sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* --- Bubble Sort --- */
    if (methods & METHOD_BUBBLE)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;
        BubbleSort((void *)list, numItems, sizeof(int64_t), CompareIntLessThan);


        printf("Bubble sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* --- Shell Sort --- */
    if (methods & METHOD_SHELL)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;
        ShellSort((void *)list, numItems, sizeof(int64_t), CompareIntLessThan);

        printf("Shell sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* --- Quick Sort --- */
    if (methods & METHOD_QUICK)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;
        QuickSort((void *)list, numItems, sizeof(int64_t), CompareIntLessThan);

        printf("Quick sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* --- Merge Sort --- */
    if (methods & METHOD_MERGE)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;
        MergeSort((void *)list, numItems, sizeof(int64_t), CompareIntLessThan);

        printf("Merge sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* --- Heap Sort --- */
    if (methods & METHOD_HEAP)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;
        HeapSort((void *)list, numItems, sizeof(int64_t), CompareIntLessThan);

        printf("Heap sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* --- Radix Sort --- */
    if (methods & METHOD_RADIX)
    {
        memcpy((void *)list, (void *)unsorted, numItems * sizeof(int64_t));
        comparisons = 0;

        /* make one Radix sort pass for every byte (LSB to MSB) */
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte0Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte1Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte2Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte3Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte4Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte5Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte6Key);
        RadixSort((void *)list, numItems, sizeof(int64_t), 256, Byte7Key);

        printf("Radix sort:\n");

        if (debug)
        {
            printf("Sorted list:\n");
            DumpList(list, numItems);
        }

        printf("Number of comparisons to sort %d Items: %lu\n",
            numItems, comparisons);

        if (!VerifySort((void *)list, numItems, sizeof(int64_t),
            CompareIntLessThan))
        {
            printf("ERROR: Sort results are incorrect.\n");
        }
    }

    /* clean-up and exit */
    free(unsorted);
    free(list);
    return EXIT_SUCCESS;
}

/****************************************************************************
*   Function   : RemovePath
*   Description: This is function accepts a pointer to the name of a file
*                along with path information and returns a pointer to the
*                character that is not part of the path.
*   Parameters : fullPath - pointer to an array of characters containing
*                           a file name and possibly path modifiers.
*   Effects    : None
*   Returned   : Returns a pointer to the first character after any path
*                information.
****************************************************************************/
char *RemovePath(char *fullPath)
{
    int i;
    char *start, *tmp;                          /* start of file name */
    const char delim[3] = {'\\', '/', ':'};     /* path deliminators */

    start = fullPath;

    /* find the first character after all file path delimiters */
    for (i = 0; i < 3; i++)
    {
        tmp = strrchr(start, delim[i]);

        if (tmp != NULL)
        {
            start = tmp + 1;
        }
    }

    return start;
}

/****************************************************************************
*   Function   : ShowUsage
*   Description: This is function provides usage instructions for this
*                program.  It may be used to provide help or alert the user
*                of errors in the command line parameters.
*   Parameters : progPath - pointer to an array of characters containing
*                           a file name and possibly path modifiers.
*   Effects    : Prints instructions for using this program to stdout.
*   Returned   : None
****************************************************************************/
void ShowUsage(char *progPath)
{
    printf("Usage: %s <options>\n\n", RemovePath(progPath));
    printf("Options:\n");
    printf("  -n : number of elements to sort.\n");
    printf("  -i : use insertion sort\n");
    printf("  -b : use bubble sort\n");
    printf("  -s : use shell sort\n");
    printf("  -q : use quick sort\n");
    printf("  -m : use merge sort\n");
    printf("  -h : use heap sort\n");
    printf("  -r : use radix sort\n");
    printf("  -d : display sort results and other debug information\n");
    printf("  -? : Print out command line options.\n\n");
    printf("Default: %s -n1000\n", RemovePath(progPath));
}

