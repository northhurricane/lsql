#ifndef LSQL_MEMORY_OSMEMORY_H_
#define LSQL_MEMORY_OSMEMORY_H_

#include "memory.h"

class OSMemory : public Memory
{
public :
  static OSMemory* Create();
  static void Destroy(OSMemory *osmemory);

  virtual void *Allocate(uint4_t size);
  virtual void Free(void *p);
};

#endif //LSQL_MEMORY_OSMEMORY_H_
