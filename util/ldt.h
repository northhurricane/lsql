#ifndef _LSQL_UTIL_LDT_
#define _LSQL_UTIL_LDT_

#include <stdint.h>
#include <time.h>
/*
底层时间日期相关函数
1、日期时间分为两个类型。一个是算术运算类型(arithmetic)，一是broken-down类型
2、秒精度为毫秒。
3、以POSIX标准为基础，Epoch
*/

#ifndef WINDOWS
//类UNIX平台，假设支持POSIX标准，待以后逐步完善
/*算术运算类型*/
typedef time_t ladt_t;

/*broken-down类型*/
struct lbdt_struct
{
  struct tm tm;
  uint32_t second_part; //micro second
}
typedef struct lbdt_struct lbdt_t;
#else
//WINDOWS平台
#endif //WINDOWS

/*
ladt_t类型和lbdt_t类型的互转
*/
/*
  broken-down转换为arithmetic
*/
inline int
ldt_b2a(const lbdt_t &source, ladt_t *target)
{
  return 0;
}

inline int
ldt_a2b(const ladt_t &source, lbdt_t *target)
{
  return 0;
}

inline int
ldt_current(lbdt_t *current)
{
#ifndef WINDOWS
  struct timeval t;
  int r = gettimeofday(&t, NULL);
  if (r < 0)
    return -1;
  time_t curr_time;
  struct tm curr_tm;

  curr_time = t.tv_sec;
  curr_tm = localtime(&curr_time);
  current->tm = *curr_tm;
  current->second_part = (uint32_t)tv.tv_usec;
#else
  compile_error;
#endif

  return 0;
}

inline int
ldt_current_micro(uint64_t *current)
{
#ifndef WINDOWS
  struct timeval t;
  int r = gettimeofday(&t, NULL);
  if (r < 0)
    return -1;
  *current = (uint64_t)t.tv_sec * 1000000 + t.tv_usec;
  return 0;
#else
  compile_error;
#endif
}

#endif //_LSQL_UTIL_LDT_

