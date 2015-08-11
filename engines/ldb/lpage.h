#ifndef _LSQL_ENGINES_LDB_LPAGE_H
#define _LSQL_ENGINES_LDB_LPAGE_H

#include <stdint.h>

/*
  内存中的page页，和保存于磁盘的数据页对应
*/

class LPage
{
public :
  void* GetPage() { return page_; }
  uint8_t GetPoolId() { return pool_id_; }

private :
  void *page_; //内存页的地址
  uint8_t pool_id_; //所属pool的id
};


#endif //_LSQL_ENGINES_LDB_LPAGE_H
