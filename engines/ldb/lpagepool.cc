#include "lpagepool.h"

LPagePool*
LPagePool::CreatePagePool(uint32_t page_size, uint32_t pool_size, uint8_t id)
{
  LPagePool *pool = NULL;

  pool->page_size_ = page_size;
  pool->pool_size_ = pool_size;
  pool->id_ = id;

  pool->AllocateResource();

  return pool;
}

LPage*
LPagePool::AllocatePage()
{
  return NULL;
}

void
LPagePool::FreePage()
{
}

