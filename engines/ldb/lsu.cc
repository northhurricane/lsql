#include "lsu.h"
#include <string.h>
#include "lendian.h"
#include "ltypedef.h"

/*指向*/
struct xdes_entry_pointer_struct
{
  uint32_t page_no;       //0-based。extend entry所在的
  uint16_t entry_offset;  //0-based。用于指明extend的
};
typedef struct xdes_entry_pointer_struct xdes_entry_pointer_t;

struct xdes_entry_list_struct
{
  xdes_entry_pointer_t first;
  xdes_entry_pointer_t last;
};
typedef struct xdes_entry_list_struct xdes_entry_list_t;

struct xdes_entry_link_struct
{
  xdes_entry_pointer_t prev;
  xdes_entry_pointer_t next;
};
typedef xdes_entry_link_struct xdes_entry_link_t;

//定义extend descriptor entry
//用于记录extend的页状态的数组长度。每页需要两个bit位进行描述，所以是(64 * 2)/8
#define PAGE_STATE_BITMAP_SIZE ((PAGE_NUMBER_PER_EXTEND * 2)  / 8)
struct xdes_entry_struct
{
  xdes_entry_link_t link;
  uint32_t state;
  uint64_t page_state_bitmap[PAGE_STATE_BITMAP_SIZE];
};
typedef struct xdes_entry_struct xdes_entry_t;

//extend pointer定义
#define UNDEFINED_PAGE_NO (0xFFFFFFFF)
#define UNDEFINED_OFFSET  (0xFFFF)

//extend entry定义
#define ENTRY_STATE_UNDEFINED (0xFFFFFFFF)
#define ENTRY_STATE_FREE (1)
#define ENTRY_STATE_FREE_FRAG (2)
#define ENTRY_STATE_FULL (3)

//extend page state
#define EXTEND_BIT_MAP_UNDEFINED (0xFF)
#define EXTEND_PAGE_STATE_UNDEFINED (0x3)
#define EXTEND_PAGE_STATE_OCCUPIED (0)
#define EXTEND_PAGE_STATE_FREE (1)

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

  //创建文件
  Expand(file_size);

  //初始化第一个控制页的内容
  InitializeFirstCB();
  //初始化簇
  InitializeExtend();
}

void
LSU::Expand(uint64_t storage_size)
{
  lfile_expand(lfile_, storage_size);
}

void
LSU::InitializeFirstCB()
{
  //初始化第一控制页的特殊部分
  InitializeCBHead(0);
  //初始化xdes的通用字段
  InitializeXDES();
}

void
LSU::InitializeExtend()
{
  //什么也不做
}

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
  lfile_write(lfile_, offset_w, buff, LSU_CB_HEAD_SIZE);
}

void
LSU::InitializeXDES()
{
  
}

struct xdes_entry_struct
{
  xdes_entry_link_t link;
  uint32_t state;
  uint64_t page_state_bitmap[PAGE_STATE_BITMAP_SIZE];
};
typedef struct xdes_entry_struct xdes_entry_t;

void
lsu_write_xdes_entry(uint8_t *buff)
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

  
