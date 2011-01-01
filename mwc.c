#include "mwc.h"
#include <time.h>

void InitializeSeed(mwc_seed_t *seed)
{
    /* cheesy initializer.  good enough for generating values to sort. */
    seed->m_z = (uint32_t)time(NULL);
    seed->m_w = UINT32_MAX ^ seed->m_z;
    seed->m_w = (seed->m_z << 16) | (seed->m_w >> 16);
}

uint32_t RandMWC(mwc_seed_t *seed)
{
    /* implements George Marsaglia's multiply-with-carry */
    seed->m_z = 36969 * (seed->m_z & UINT16_MAX) + (seed->m_z >> 16);
    seed->m_w = 18000 * (seed->m_w & UINT16_MAX) + (seed->m_w >> 16);
    return (seed->m_z << 16) + (seed->m_w & UINT16_MAX);
}

int64_t RandMWC64(mwc_seed_t *seed)
{
    int64_t value;

    value = RandMWC(seed);
    value <<= 32;
    value |= RandMWC(seed);

    return value;
}
