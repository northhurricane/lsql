#include "autoheap.h"

static const uint32_t DEFAULT_HEAP_INIT_SIZE = 512;
static uint32_t init_size = DEFAULT_HEAP_INIT_SIZE;

/* heap */
/*进行内存分配的内存块*/
class HeapBlock
{
public :
  static HeapBlock *Create(uint32_t size);
  static void Destroy(HeapBlock *block);

  void* Allocate(uint32_t size);
  HeapBlock *next() {return next_;}
  void set_next(HeapBlock *next) { next_ = next; }
  uint32_t block_size() { return block_size_;; }
  bool HasSpace(uint32_t size)
  {
    if ((used_bytes_ + size) > block_size_)
      return false;
    return true;
  }

private :
  uint32_t block_size_;
  uint32_t used_bytes_;
  char *buffer_;
  HeapBlock *next_;

  HeapBlock();
  ~HeapBlock();

  void* InitMemPool(uint32_t size);
};

HeapBlock*
HeapBlock::Create(uint32_t size)
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
HeapBlock::Allocate(uint32_t size)
{
  lassert((size + used_bytes_) <= block_size_);

  void * mem = buffer_ + used_bytes_;
  used_bytes_ += size;

  return mem;
}

HeapBlock::HeapBlock()
{
  block_size_ = 0;
  used_bytes_ = 0;
  buffer_ = NULL;
  next_ = NULL;
}

HeapBlock::~HeapBlock()
{
  lfree(buffer_);
}

void*
HeapBlock::InitMemPool(uint32_t size)
{
  block_size_ = size;

  buffer_ = lmalloc(size);
  return buffer_;
}

/* heap */
AutoHeap*
AutoHeap::Create()
{
  return Create(init_size);
}

AutoHeap*
AutoHeap::Create(uint32_t size)
{
  AutoHeap *heap = NULL;
  heap = new AutoHeap();
  if (heap == NULL)
    return NULL;

  bool success = heap->Initialize(size);
  if (!success)
  {
    delete heap;
    heap = NULL;
  }
  return heap;
}

void
AutoHeap::Destroy(AutoHeap *heap)
{
  delete heap;
}

void*
AutoHeap::Allocate(uint32_t size)
{
  //查看最后一个block是否有存储空间
  if (last_block_->HasSpace(size))
  {
    used_bytes_ += size;
    return last_block_->Allocate(size);
  }

  //查看所有block是否有空间
  HeapBlock *block = blocks_;
  while (block != NULL)
  {
    if (block->HasSpace(size))
    {
      used_bytes_ += size;
      return block->Allocate(size);
    }
  }

  //创建新的block进行分配
  uint32_t size_new = 0, last_size = GetLastSize();

  size_new = last_size * 2;
  if (size > size_new)
  {
    size_new = size;
  }

  HeapBlock *block_new = HeapBlock::Create(size_new);
  if (block_new == NULL)
    return NULL;

  last_block_->set_next(block_new);
  last_block_ = block_new;
  total_bytes_ += size_new;

  void *mem = NULL;
  mem = block_new->Allocate(size);
  used_bytes_ += size;

  return mem;
}

void AutoHeap::Free(void *p)
{
  return;
}

AutoHeap::AutoHeap()
{
  total_bytes_ = 0;
  used_bytes_ = 0;
  blocks_ = NULL;
  last_block_ = NULL;
}

AutoHeap::~AutoHeap()
{
  Deinitialize();
}

bool
AutoHeap::Initialize(uint32_t size)
{
  HeapBlock *block = HeapBlock::Create(size);
  if (block == NULL)
    return false;

  blocks_ = block;
  last_block_ = block;

  total_bytes_ = size;

  return true;
}

void
AutoHeap::Deinitialize()
{
  HeapBlock *curr, *temp;

  curr = blocks_;
  while (curr != NULL)
  {
    temp = curr;
    curr = curr->next();

    HeapBlock::Destroy(temp);
  }
}

uint32_t
AutoHeap::GetLastSize()
{
  return last_block_->block_size();
}

/*calling function for c*/
extern "C"
void*
autoheap_alloc(void *heap, uint32_t size)
{
  AutoHeap *autoheap = (AutoHeap*)heap;

  return autoheap->Allocate(size);
}

