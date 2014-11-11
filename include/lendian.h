#ifndef _LENDIAN_H
#define _LENDIAN_H

#include <stdint.h>

inline uint8_t lendian_read_uint8(void *source)
{
  return *((uint8_t*)source);
}

inline void lendian_write_uint8(void *target, uint8_t value)
{
  *((uint8_t*)target) = value;
}

inline uint16_t lendian_read_uint16(void *source)
{
  return *((uint16_t*)source);
}

inline void lendian_write_uint16(void *target, uint16_t value)
{
  *((uint16_t*)target) = value;
}

inline uint32_t lendian_read_uint32(void *source)
{
  return *((uint32_t*)source);
}

inline void lendian_write_uint32(void *target, uint32_t value)
{
  *((uint32_t*)target) = value;
}

#endif //_LENDIAN_H
