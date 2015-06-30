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

  功能定义：
  1、扩展extends用于存储
  2、分配新的internal node page和data node page。简称inp和dnp
*/

#define PAGE_NUMBER_PER_EXTEND (64)

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
  /*用于扩展文件，增加存储空间*/
  int AllocateExtend();
  int AllocateINP();
  int AllocateDNP();

private :
  void Initialize();
  void CreateStorage();
  void InitializeFirstSI();
  void Expand(uint64_t size);

  LSU();

  uint32_t page_size_; //lsu的页大小
  char path_[256]; //存储的位置
  char name_[256]; //存储单元的名字

  lfile_t  lfile_;
  uint64_t size_;
};

#endif //_LSQL_ENGINES_LDB_LSU_H
