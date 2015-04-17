#ifndef LSQL_MEMORY_MEMORY_H_
#define LSQL_MEMORY_MEMORY_H_

class Memory
{
public :
  virtual void *Allocate(uint32_t size) = 0;
};

#endif //LSQL_MEMORY_MEMORY_H_
