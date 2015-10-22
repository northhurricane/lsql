#ifndef _LENDIAN_H
#define _LENDIAN_H

#include <stdint.h>

/*
用于处理不同CPU平台的数据存储
不同CPU对整型的存储方式不同，分为big endian和little endian两种

CPU对应的endian
little endian : intel系列
big enddian   : 86000/power pc

endian在内存中的布局
little endian
0x00f0   16
0x00f1    0

big endian
0x00f0    0
0x00f1   16

对于整型来说，lsql采用little endian的方式存储，所以在little endian的CPU平台上可以直接进行类型转换

ref:
1、关于little endian和big endian的讨论
http://programmers.stackexchange.com/questions/95556/what-is-the-advantage-of-little-endian-format
2、endian的起源
据说取自《格利佛游记》中，小人国里鸡蛋应该从大的一头打开还是从小的一头打开
*/

/*默认为LITTLE_ENDIAN，通过编译前生成的ldefs.h获得正确的宏定义*/
#define LITTLE_ENDIAN 1
#include "ldefs.h"

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
#ifdef LITTLE_ENDIAN
  return *((uint16_t*)source);
#else
  
#endif
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

inline uint64_t lendian_read_uint64(void *source)
{
  return *((uint64_t*)source);
}

inline void lendian_write_uint64(void *target, uint64_t value)
{
  *((uint64_t*)target) = value;
}

inline float lendian_read_float(void *source)
{
#ifdef LITTLE_ENDIAN
  return *((float*)source);
#else
  float value;
  *((uint8_t*)(&value) + 0) = *((uint8_t*)source + 3);
  *((uint8_t*)(&value) + 1) = *((uint8_t*)source + 2);
  *((uint8_t*)(&value) + 2) = *((uint8_t*)source + 1);
  *((uint8_t*)(&value) + 3) = *((uint8_t*)source + 0);
  return value;
#endif
}

inline void lendian_write_float(void *target, float value)
{
#ifdef LITTLE_ENDIAN
  *(float *)target = value;
#else
  memcpy(target, (uint8_t*)(&value) + 3, 1);
  memcpy((uint8_t*)target + 1, (uint8_t*)(&value) + 2, 1);
  memcpy((uint8_t*)target + 2, (uint8_t*)(&value) + 1, 1);
  memcpy((uint8_t*)target + 3, (uint8_t*)(&value), 1);
#endif
}

inline double lendian_read_double(void *source)
{
#ifdef LITTLE_ENDIAN
  return *((double*)source);
#else
  double value;

  *((uint8_t*)(&value) + 0) = *((uint8_t*)source + 7);
  *((uint8_t*)(&value) + 1) = *((uint8_t*)source + 6);
  *((uint8_t*)(&value) + 2) = *((uint8_t*)source + 5);
  *((uint8_t*)(&value) + 3) = *((uint8_t*)source + 4);
  *((uint8_t*)(&value) + 4) = *((uint8_t*)source + 3);
  *((uint8_t*)(&value) + 5) = *((uint8_t*)source + 2);
  *((uint8_t*)(&value) + 6) = *((uint8_t*)source + 1);
  *((uint8_t*)(&value) + 7) = *((uint8_t*)source + 0);

  return value;
#endif
}

inline void lendian_write_double(void *target, double value)
{
#ifdef LITTLE_ENDIAN
  *(double*)target = value;
#else
  memcpy(target, (uint8_t*)(&value) + 3, 1);
  memcpy((uint8_t*)target + 1, (uint8_t*)(&value) + 2, 1);
  memcpy((uint8_t*)target + 2, (uint8_t*)(&value) + 1, 1);
  memcpy((uint8_t*)target + 3, (uint8_t*)(&value), 1);
#endif
}

#endif //_LENDIAN_H
