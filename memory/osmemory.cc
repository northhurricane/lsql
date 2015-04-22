#include "osmemory.h"
#include <stdlib.h>

OSMemory*
OSMemory::Create()
{
  return NULL;
}

void OSMemory::Destroy(OSMemory *osmemory)
{
}

void* OSMemory::Allocate(uint32_t size)
{
  return NULL;
}

void OSMemory::Free(void *p)
{
  return;
}
