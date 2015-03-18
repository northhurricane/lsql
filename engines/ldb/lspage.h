#ifndef _LSQL_ENGINES_LDB_LSPAGE_H
#define _LSQL_ENGINES_LDB_LSPAGE_H

#include "ltypedef.h"
#include "lendian.h"

/*
  lspage:lsql storage page
  物理存储的页面描述和访问接口。
  对所存储的内容保持无知，仅知道存储数据的长度。
  排序等操作，有上一层逻辑完成
*/

typedef lbyte *lspage_t;

#define LSPAGE_EXTRA_SIZE (16)

#define LSPAGE_MAGE 0x38da5920fcbaff54

#define LSPAGE_HEAD 0
#define LSPAGE_HEAD_MAGIC LSPAGE_HEAD
#define LSPAGE_HEAD_EXTRA (LSPAGE_HEAD_MAGIC + LINT8_SIZE)
#define LSPAGE_HEAD_REC_NUM (LSPAGE_HEAD_EXTRA + LSPAGE_EXTRA_SIZE)
#define LSPAGE_HEAD_FREE_SPACE (LSPAGE_HEAD_REC_NUM + LINT2_SIZE)
#define LSPAGE_HEAD_AVAIL_OFFSET (LSPAGE_HEAD_FREE_SPACE + LINT2_SIZE)

/*每次增加内容必须修改*/
#define LSPAGE_HEAD_END (LSPAGE_HEAD_AVAIL_OFFSET + LINT2_SIZE)


inline void lspage_write_magic(lspage_t page, uint2_t size)
{
}

inline uint8_t lspage_read_magic(lspage_t page, uint2_t size)
{
  return 0;
}

inline void lspage_write_extra(lspage_t page, lbyte *extra)
{
}

inline void lspage_read_extra(lspage_t page, extra)
{
}

inline void lspage_write_rec_num(lspage_t page, uint2_t rec_num)
{
}

inline uint2_t lspage_read_rec_num(lspage_t page)
{
  return 0;
}

inline void lspage_write_free_space(lspage_t page, uint2_t free_space)
{
}

inline uint2_t lspage_read_free_space(lspage_t page)
{
  return 0;
}

inline void lspage_write_avail_offset(lspage_t page, uint2_t offset)
{
}

inline uint2 lspage_read_avail_offset(lspage_t page)
{
  return 0;
}

inline uint2_t lspage_read_free_space(lspage_t page)
{
  return 0;
}

inline bool lspage_check_space(lspage_t page, uint2_t rec_len)
{
  return true;
}

inline void lspage_write_nth_rec(lspage_t page, uint2_t nth
                                 , lbyte* rec, uint2_t rec_len)
{
}

inline void *lspage_read_nth_rec(lspage_t page, uint2_t nth)
{
  return NULL;
}

#endif //_LSQL_ENGINES_LDB_LSPAGE_H

