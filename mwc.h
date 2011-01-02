/***************************************************************************
*                      A Pseudo Random Number Generator
*
*   File    : mwc.h
*   Purpose : This is the header for a library containing a multiply-with-
*             carry (MWC) based pseudo random number generator (PRNG) for 32
*             and 64 bit integers.  This generator is probably not good
*             enough for cryptographic uses, but it is fine for testing
*             sorting algorithms.
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

#ifndef _MWC_H_
#define _MWC_H_
/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdint.h>

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/
typedef struct mwc_seed_t
{
    uint32_t m_w;
    uint32_t m_z;
} mwc_seed_t;

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
/* initializes seed for random number generator */
void InitializeSeed(mwc_seed_t *seed);

/* 32 and 64 bit multiple with carry based random number generators */
int32_t RandMWC32(mwc_seed_t *seed);
int64_t RandMWC64(mwc_seed_t *seed);

#endif /* _MWC_H_ */
