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
  static LPagePool* CreatePagePool(uint32_t pool_size);
  LPage* Allocate();
  void Free(LPage *page);

private :
  LPagePool();

  /*内存空间*/
  /*页面对象*/

  /*未使用页面*/
  /*使用中页面*/
  /*可淘汰页面*/
};

#endif //_LSQL_ENGINES_LDB_LMPAGE_H
