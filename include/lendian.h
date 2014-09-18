#ifndef _LENDIAN_H
#define _LENDIAN_H

#include <stdint.h>

inline uint8_t le_read_uint8(void *s)
{
  return *((uint8_t*)s);
}

inline void le_write_uint8(void *d, uint8_t v)
{
  *((uint8_t*)d) = v;
}

inline uint16_t le_read_uint16(void *s)
{
  return *((uint16_t*)s);
}

inline void le_write_uint16(void *d, uint16_t v)
{
  *(uint16_t*)d) = v;
}

inline uint32_t le_read_uint32(void *s)
{
  return *((uint32_t*)s);
}

inline void le_write_uint32(void *d, uint32_t v)
{
  *((uint32_t*)d) = v;
}

#endif //_LENDIAN_H
