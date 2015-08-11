#ifndef _LSQL_ENGINES_LDB_LMPAGE_H
#define _LSQL_ENGINES_LDB_LMPAGE_H

#include <stdint.h>

class LPage;

/*
  page的buffer pool
  管理页面，
*/

class LPagePool
{
public :
  static LPagePool* CreatePagePool(uint32_t page_size, uint32_t pool_size
                                   , uint8_t id);
  LPage* AllocatePage();
  void FreePage(LPage *page);

private :
  LPagePool();
  void AllocateResource();

private :
  /*内存空间*/
  void *pages_
  /*页面对象*/
  LPage *lpages_;

  /*未使用页面*/
  /*使用中页面*/
  /*可淘汰页面*/

  uint32_t page_size_;
  uint32_t pool_size_;
  uint8_t id_; //
};

#endif //_LSQL_ENGINES_LDB_LMPAGE_H
