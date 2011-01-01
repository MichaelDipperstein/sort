#ifndef _MWC_H_
#define _MWC_H_

#include <stdint.h>

typedef struct mwc_seed_t
{
    uint32_t m_w;
    uint32_t m_z;
} mwc_seed_t;


void InitializeSeed(mwc_seed_t *seed);
int64_t RandMWC64(mwc_seed_t *seed);

#endif /* _MWC_H_ */
