#ifndef LSQL_MEMORY_AUTOHEAP_H_
#define LSQL_MEMORY_AUTOHEAP_H_

#include "lsql.h"
#include "memory.h"
#include <list>

using namespace std;

class HeapBlock;

class AutoHeap : public Memory
{
public :
  static AutoHeap* Create();
  static AutoHeap* Create(uint4_t size);
  static void Destroy(AutoHeap *heap);

  virtual void *Allocate(uint4_t size);

private :
  uint4_t total_bytes_;  //分配空间的全部字节数
  uint4_t used_bytes_;   //已使用的字节数

  HeapBlock *blocks_;
  HeapBlock *lastest_block;  //最后一次分配的block，也是blocks_链表的最后一个

  AutoHeap();
  ~AutoHeap();
  /*
    return success. true is successful, false is failed
   */
  bool Initialize(uint4_t size);
  void Deinitialize();

  //for debug.
  typedef list<HeapBlock*> heaps;
};

#endif //LSQL_MEMORY_AUTOHEAP_H_
