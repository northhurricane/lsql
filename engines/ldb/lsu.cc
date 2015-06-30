#include "lsu.h"
#include <string.h>

LSU*
LSU::Create(const char* path, const char *name, uint32_t page_size)
{
  LSU *su = new LSU();

  su->page_size_ = page_size;
  strcpy(su->path_, path);
  strcpy(su->name_, name);

  su->Initialize();

  return su;
}

void
LSU::Initialize()
{
  CreateStorage();
  InitializeFirstSI();
}

void
LSU::CreateStorage()
{
  char file[1024];
  strcpy(file, path_);
  strcat(file, name_);
  lfile_ = lfile_create(file);
}

void
LSU::InitializeFirstSI()
{
  uint32_t head_xdes_size = page_size_;
  uint32_t extend_size = page_size_ * PAGE_NUMBER_PER_EXTEND;
  uint32_t file_size = head_xdes_size + extend_size;

  Expand(file_size);
}

void
LSU::Expand(uint64_t storage_size)
{
  lfile_expand(lfile_, storage_size);
}


LSU::LSU()
{
}
