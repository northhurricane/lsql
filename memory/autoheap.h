#ifndef LSQL_MEMORY_AUTOHEAP_H_
#define LSQL_MEMORY_AUTOHEAP_H_

#include "lsql.h"
#include "memory.h"

using namespace std;

class HeapBlock;

class AutoHeap
{
public :
  static AutoHeap* Create();
  static AutoHeap* Create(uint32_t size);
  static void Destroy(AutoHeap *heap);

  virtual void *Allocate(uint32_t size);
  virtual void Free(void *p);

private :
  uint32_t total_bytes_;  //分配空间的全部字节数
  uint32_t used_bytes_;   //已使用的字节数

  HeapBlock *blocks_;
  HeapBlock *last_block_; //最后一次分配的block，也是blocks_链表的最后一个

  AutoHeap();
  ~AutoHeap();
  /*
    return success. true is successful, false is failed
   */
  bool Initialize(uint32_t size);
  /*
    销毁heap对象
   */
  void Deinitialize();

  uint32_t GetLastSize();

};

#endif //LSQL_MEMORY_AUTOHEAP_H_
