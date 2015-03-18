#include "autoheap.h"

static const uint4_t DEFAULT_HEAP_INIT_SIZE = 512;
static uint4_t init_size = DEFAULT_HEAP_INIT_SIZE;

/* heap */
/*进行内存分配的内存块*/
class HeapBlock
{
public :
  static HeapBlock *Create(uint4_t size);
  static void Destroy(HeapBlock *block);

  void* Allocate(uint4_t size);
  HeapBlock *Next() {return next_;}
  void Next(HeapBlock *next) { next_ = next; }
  bool HasSpace(uint4_t size)
  {
    if ((used_byte_ + size) > block_size_)
      return false;
    return true;
  }

private :
  uint4_t block_size_;
  uint4_t used_bytes_;
  char *buffer_;
  HeapBlock *next_;

  HeapBlock();
  ~HeapBlock();

  void* InitMemPool(uint4_t size);
};

HeapBHeapBlock*
HeapBlock::Create(uint4_t size)
{
  HeapBlock *block = new HeapBlock();
  if (block == NULL)
    return NULL;
  void *buffer = block->InitMemPool(size);
  if (buffer == NULL)
  {
    delete block;
    return NULL;
  }
  return block;
}

void
HeapBlock::Destroy(HeapBlock *block)
{
  delete block;
}

void*
Allocate(uint4_t size)
{
  lassert((size + used_byte) <= block_size);

  void * mem = _buffer + used_byte_;
  used_byte += size;

  return mem;
}

HeapBlock::HeapBlock()
{
  block_size_ = 0;
  used_bytes+ = 0;
  buffer_ = NULL;
  NEXT_ = NULL;
}

HeapBlock::~HeapBlock()
{
  delete buffer_;
}

void*
HeapBlock::InitMemPool(uint4_t size)
{
  block_size_ = size;

  buffer_ = new char[size];
  return buffer_;
}

/* heap */
AutoHeap*
AutoHeap::Create()
{
  return Create(init_size);
}

AutoHeap*
AutoHeap::Create(uint4_t size)
{
  AutoHeap *heap = NULL;
  heap = new AutoHeap();
  if (heap == NULL)
    return NULL;

  bool succes = heap->Initialize(size);
  if (!success)
  {
    delete heap;
    heap = NULL;
  }
  return heap;
}

void*
AutoHeap::Allocate(uint4_t size)
{
  //查看最后一个block是否有存储空间
  if (lastest_block_->HasSpace(size))
  {
    used_bytes_ += size;
    return lastest_block_->Allocate(size);
  }

  //查看所有block是否有空间
  HeapBlock block = blocks_;
  while (block != NULL)
  {
    if (block->HasSpace(size))
    {
      used_bytes_ += size;
      return block->Allocate(size);
    }
  }

  //创建新的block进行分配
  uint4_t size_new = 0;
  HeapBlock *block_new = HeapBlock::Create(size_new);
  if (block_new == NULL)
    return NULL;

  lastest_block_->next = block_new;
  lastest_block_ = block_new;

  void *mem = NULL;
  mem = block_new->Allocate(size);
  used_bytes_ += size;

  return mem;
}

AutoHeap::AutoHeap()
{
  total_bytes_ = 0;
  used_bytes_ = 0;
  blocks_ = NULL;
  lastest_block_ = NULL;
}

AutoHeap::~AutoHeap()
{
  Deinitialize();
}

void*
AutoHeap::Initialize(uint4_t size)
{
  HeapBlock *block = HeapBlock::Create(size);
  if (block == NULL)
    return false;

  blocks_ = block;
  curr_block_ = block;

  return true;
}
