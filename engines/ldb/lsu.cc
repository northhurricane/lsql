#include "lsu.h"
#include <string.h>
#include "lendian.h"
#include "ltypedef.h"

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

int
LSU::AllocateINP()
{
  //获取有空闲page的internal node簇
  //如果未找到，分配一个internal node簇
  //从有空闲的internal node簇中获取一页
  return 0;
}

int
LSU::AllocateDNP()
{
  //获取有空闲page的data node的extend
  //如果未找到，分配一个data node簇
  //从有空闲的data node簇中获取一页
  return 0;
}

void
LSU::Initialize()
{
  //创建存储空间
  CreateStorage();
  //初始化首个存储
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
  //初始化第一个控制页的内容
  InitializeFirstCB();

  //初始化extend的存储空间
  AllocateExtend();
}

void
LSU::Expand(uint64_t storage_size)
{
  lfile_expand(lfile_, storage_size);
}

void
LSU::InitializeFirstCB()
{
  uint32_t file_size = page_size_;

  Expand(file_size);

  //初始化第一控制页的特殊部分
  InitializeCBHead(0);

  //初始化xdes的通用字段
  InitializeXDES();
}

void
LSU::AllocateExtend()
{
  //
}

/*
  初始化控制块
*/
void
LSU::InitializeCBHead(uint32_t page_no)
{
  uint64_t offset_w;
  uint8_t buff[1024];
  uint32_t offset_buff;

  offset_buff = 0;
  if (page_no == FIRST_CB_PAGE_NO)
  {
    //第一个控制块的编号
    //初始化free xdes entry的list
    lendian_write_uint32(buff, 0);
    offset_buff += LINT32_SIZE;
    lendian_write_uint32(buff, UNDEFINED_PAGE_NO);
    offset_buff += LINT32_SIZE;
    lendian_write_uint16(buff, UNDEFINED_OFFSET);
    offset_buff += LINT16_SIZE;
    //初始化free-frag data xdes entry的list
    lendian_write_uint32(buff, 0);
    offset_buff += LINT32_SIZE;
    lendian_write_uint32(buff, UNDEFINED_PAGE_NO);
    offset_buff += LINT32_SIZE;
    lendian_write_uint16(buff, UNDEFINED_OFFSET);
    offset_buff += LINT16_SIZE;
    //初始化full data xdes entry的list
    lendian_write_uint32(buff, 0);
    offset_buff += LINT32_SIZE;
    lendian_write_uint32(buff, UNDEFINED_PAGE_NO);
    offset_buff += LINT32_SIZE;
    lendian_write_uint16(buff, UNDEFINED_OFFSET);
    offset_buff += LINT16_SIZE;
    //初始化free-frag internal xdes entry的list
    lendian_write_uint32(buff, 0);
    offset_buff += LINT32_SIZE;
    lendian_write_uint32(buff,UNDEFINED_PAGE_NO);
    offset_buff += LINT32_SIZE;
    lendian_write_uint16(buff, UNDEFINED_OFFSET);
    offset_buff += LINT16_SIZE;
    //初始化full internal xdes entry的list
    lendian_write_uint32(buff, 0);
    offset_buff += LINT32_SIZE;
    lendian_write_uint32(buff,UNDEFINED_PAGE_NO);
    offset_buff += LINT32_SIZE;
    lendian_write_uint16(buff, UNDEFINED_OFFSET);
    offset_buff += LINT16_SIZE;
  }
  else
  {
    offset_buff = LSU_CB_HEAD_SIZE;
    memset(buff, 0, LSU_CB_HEAD_SIZE);
    //检查控制块是否合法
    //4k页是n*(1+64*64),8k页是n*(1+128*64),16k是n*（1+256*64），32/64类推
  }

  memset(buff + offset_buff, 0, LSU_CB_HEAD_SIZE - offset_buff);
  offset_w = page_no * page_size_;
  //写入存储
  lfile_write(lfile_, offset_w, buff, LSU_CB_HEAD_SIZE);
}

void
LSU::InitializeXDES()
{
  
}

void
lsu_write_undef_xdes_entry(uint8_t *buff)
{
  uint32_t offset = 0;
  //写入link
  lendian_write_uint32(offset, PAGE_NO_UNDEFINED);
  offset += LINT32_SIZE;
  lendian_write_uint16(offset, PAGE_OFFSET_UNDEFINED);
  //写入state
  lendian_write(offset, EXTEND_STATE_UNDEFIN);
  //写入状态
  lendian_write(offset, EXTEND_BIT_MAP_UNDEFINED);
  offset += LINT8_SIZE;
  lendian_write(offset, EXTEND_BIT_MAP_UNDEFINED);
  offset += LINT8_SIZE;
}

  
