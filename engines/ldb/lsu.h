#ifndef _LSQL_ENGINES_LDB_LSU_H
#define _LSQL_ENGINES_LDB_LSU_H

#include <stdint.h>
#include "lfile.h"

/*
  lsu:lsql storage unit
  lsql数据存储单元，实现了页存储部分，可以简单的看待，一个lsu就是一个索引，而一个索引就是一个B+树。
  特性说明：
  1、存储的页面大小可定义为4k，8k，16k，32k和64k。
  2、一个存储单元的结构可以看作如下
  {storage item}+，storage item的定义如下缩写为SI
  storage item=cbp+extends，其中cbp是控制块页，extends是数据块页，以4k页的情况来说明
  4k的cbp+64*(64*4k)的dbps构成一个storage item
  4k的cbp可以存储64个extends的信息，8k可以存储128个，16k的256，32k的512，64k的1024
  3、cbp分为两类。第一个cbp和后续的cbp，第一个cbp除了保存extend管理的信息，还保存LSU级别的信息。
  功能定义：
  1、extend管理。
  2、page管理。extend中的页面分为两类，internal node page和data node page。简称inp和dnp。extend也就分为inp的extend和dnp的extend。
*/

#define PAGE_NUMBER_PER_EXTEND (64)
#define FIRST_CB_PAGE_NO (0)

/*
  控制块的头长度。对于第一个cbp来说其内容有意义，后续的cbp初始化为0——也就是256个0填充
*/
#define LSU_CB_HEAD_SIZE (256)

/*定义control block的布局*/
/*可用的extend*/
#define LSU_CB_FREE_EXTEND_LIST
/*所有页面用尽的inp的extend链表*/
#define LSU_CB_INP_FULL_EXTEND_LIST
/*存在可用页面的inp的extend链表*/
#define LSU_CB_INP_FRAG_EXTEND_LIST
/*和inp的链表相同*/
#define LSU_CB_DNP_FULL_EXTEND_LIST
#define LSU_CB_DNP_FRAG_EXTEND_LIST

/*头部定义，对于第一个控制页头部包括各个xdes entry的链表等信息，对于后续的控制页，初始化为0*/
#define LSU_CB_HEAD (0)
#define LSU_CB_XDES_ENTRIES (LSU_CB_HEAD + LSU_CB_HEAD)

/*
  extend entry 的指针（借用C语言指针概念），记录extend entry的位置
*/
struct xdes_entry_pointer_struct
{
  uint32_t page_no;       //0-based。extend entry所在的page页，也就是cbp的页号
  uint16_t entry_offset;  //0-based。用于指明extend entry的位置。
};
typedef struct xdes_entry_pointer_struct xdes_entry_pointer_t;

/*
  list的内存结构
*/
struct xdes_entry_list_struct
{
  uint32_t number;
  xdes_entry_pointer_t first;
  xdes_entry_pointer_t last;
};
typedef struct xdes_entry_list_struct xdes_entry_list_t;

/*
  link
*/
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
#define XDES_ENTRY_STATE_UNDEFINED (0xFFFFFFFF)
#define XDES_ENTRY_STATE_FREE (1)
#define XDES_ENTRY_STATE_FREE_FRAG (2)
#define XDES_ENTRY_STATE_FULL (3)

//extend page state
#define EXTEND_PAGE_STATE_UNDEFINED (0x3)
#define EXTEND_PAGE_STATE_OCCUPIED (0)
#define EXTEND_PAGE_STATE_FREE (1)

class LSU
{
public :
  /*
    创建一个存储单元。
   */
  static LSU* Create(const char* path, const char *name, uint32_t page_size);
public :
  /*读取页*/
  int Read(uint32_t page_no);
  /*写入页*/
  int Write(uint32_t page_no);
  /*分配internal node page*/
  int AllocateINP();
  /*分配data node page*/
  int AllocateDNP();

private :
  /*
    初始化lsu。
  */
  void Initialize();
  /*
    创建存储的文件
  */
  void CreateStorage();
  /*
    初始化第一个存储
  */
  void InitializeFirstSI();
  /*
    扩展存储空间
  */
  void Expand(uint64_t size);
  /*
    初始化第一个控制块
  */
  void InitializeFirstCB();
  void AllocateExtend();
  void InitializeCBHead(uint32_t page_no);
  void InitializeXDES();

  LSU() {}

  uint32_t page_size_; //lsu的页大小
  char path_[256]; //存储的位置
  char name_[256]; //存储单元的名字
  uint32_t last_cbp_;  //0-based。最后一个cbp的页号

  lfile_t  lfile_; //LSU的存储文件
  uint64_t size_;  //LSU的大小

  
};

#endif //_LSQL_ENGINES_LDB_LSU_H
