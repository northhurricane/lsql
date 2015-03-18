#ifndef _LSQL_ENGINES_LDB_LPAGE_H
#define _LSQL_ENGINES_LDB_LPAGE_H

#include <stdint.h>

/*
  page存储相关
*/

class lsu;
/*
  内存中的page页，和保存于磁盘的数据页对应
*/

class lpage
{
public :
  /*
    page分为如下几类
  */
  enum type_enum
  {
    LPAGE_ROOT_LEAF = 1,
    LPAGE_ROOT_INODE = 2,
    LPAGE_LEAF = 3,
    LPAGE_INODE = 4
  };
  typedef enum type_enum type_e;

  type_e GetType();

private :
  lsu *lsu_;
  type_e type_;
};


#endif //_LSQL_ENGINES_LDB_LPAGE_H
