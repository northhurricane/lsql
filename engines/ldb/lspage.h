#ifndef _LSQL_ENGINES_LDB_LSPAGE_H
#define _LSQL_ENGINES_LDB_LSPAGE_H

#include "ltypedef.h"

/*
  物理存储的页面描述和访问接口
  lspage:lsql storage page
*/

#define LSPAGE_HEAD 0
#define LSPAGE_HEAD_MAGIC LSPAGE_HEAD
#define LSPAGE_HEAD_REC_NUM (LSPAGE_HEAD_MAGIC + LINT8_SIZE)
#define LSPAGE_HEAD_END (LSPAGE_HEAD_REC_NUM + LINT2_SIZE)

#define LSPAGE_REC LSPAGE_HEAD_END

inline void lspage_write_magic(lbyte *page, uint8_t magic)
{
}

inline uint8_t lspage_read_magic(lbyte *page)
{
  return 0;
}

inline void lspage_write_rec_num(lbyte *page, uint2_t rec_num)
{
}

inline uint2_t lspage_read_rec_num(lbyte *page)
{
  return 0;
}

inline void *lspage_read_nth_rec(lbyte *page, uint2_t nth)
{
}

#endif //_LSQL_ENGINES_LDB_LSPAGE_H

