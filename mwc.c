/***************************************************************************
*                      A Pseudo Random Number Generator
*
*   File    : mwc.c
*   Purpose : This implements a library containing a multiply-with-carry
*             (MWC) based pseudo random number generator (PRNG) for 32 and
*             64 bit integers.  This generator is probably not good enough
*             for cryptographic uses, but it is fine for testing sorting
*             algorithms.
*   Author  : Michael Dipperstein
*   Date    : December 30, 2010
*
****************************************************************************
* mwc: An ANSI C99 multiply-with-carry based pseudo random number generator.
*      MWC is a library implementing George Marsaglia's multiply-with-carry
*      algorithm for generating 32 and 64 bit random numbers.  It is used
*      to demonstrate the usage of and test the sort library.
*
* Copyright (C) 2010, 2011 by
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
#include "mwc.h"
#include <time.h>
#include <stdio.h>

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/

/***************************************************************************
*                                 MACROS
***************************************************************************/

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : InitializeSeed
*   Description: This function provides a seed based for an MWC based PRNG
*                using the current system time.  Other initializers may be
*                used, but this is good enough for generating values to
*                sort.
*   Parameters : seed - a pointer to a seed for a multiply-with-carry based
*                pseudo random number generator.
*   Effects    : A seed for any MWC based PRNG is generated using the
*                current time.
*   Returned   : NONE
***************************************************************************/
void InitializeSeed(mwc_seed_t *seed)
{
    /* cheesy initializer.  good enough for generating values to sort. */
    seed->m_z = (uint32_t)time(NULL);
    seed->m_w = UINT32_MAX ^ seed->m_z;
    seed->m_w = (seed->m_z << 16) | (seed->m_w >> 16);
}

/***************************************************************************
*   Function   : RandMWC
*   Description: This function implements George Marsaglia's
*                multiply-with-carry (MWC) algorithm for generating pseudo
*                random 32 bit unsigned integers.
*   Parameters : seed - a pointer to a seed for a multiply-with-carry based
*                pseudo random number generator.
*   Effects    : The seed is modified for the current number and the next
*                number in the pseudo random sequence.
*   Returned   : A pseudo randomly generated 32 bit unsigned integer.
***************************************************************************/
uint32_t RandMWC(mwc_seed_t *seed)
{
    /* implements George Marsaglia's multiply-with-carry */
    seed->m_z = 36969 * (seed->m_z & UINT16_MAX) + (seed->m_z >> 16);
    seed->m_w = 18000 * (seed->m_w & UINT16_MAX) + (seed->m_w >> 16);
    return (seed->m_z << 16) | (seed->m_w & UINT16_MAX);
}

/***************************************************************************
*   Function   : RandMWC32
*   Description: This function uses RandomMWC to generate a pseudo random 32
*                bit signed integer.
*   Parameters : seed - a pointer to a seed for a multiply-with-carry based
*                pseudo random number generator.
*   Effects    : The seed is modified for the current number and the next
*                number in the pseudo random sequence.
*   Returned   : A pseudo randomly generated 32 bit signed integer.
***************************************************************************/
int32_t RandMWC32(mwc_seed_t *seed)
{
    return (int32_t)RandMWC(seed);
}

/***************************************************************************
*   Function   : RandMWC64
*   Description: This function uses RandomMWC to generate a pseudo random 64
*                bit signed integer.
*   Parameters : seed - a pointer to a seed for a multiply-with-carry based
*                pseudo random number generator.
*   Effects    : The seed is modified for the current number and the next
*                number in the pseudo random sequence.
*   Returned   : A pseudo randomly generated 64 bit signed integer.
***************************************************************************/
int64_t RandMWC64(mwc_seed_t *seed)
{
    int64_t value;

    value = RandMWC(seed);
    value <<= 32;
    value |= RandMWC(seed);

    return value;
}
