#ifndef LSQL_INCLUDE_LMEMORY_H_
#define LSQL_INCLUDE_LMEMORY_H_

#include <stdint.h>

inline void* lmalloc(size_t size, uint32_t alloc_id)
{
  return malloc(size);
}

inline void lfree(void *ptr)
{
  free(ptr);
}

#endif //LSQL_INCLUDE_LMEMORY_H_
