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
/*算术运算类型*/
typedef uint64_t ladt_t;

/*broken-down类型*/
#ifndef WINDOWS
//类UNIX平台，假设支持POSIX标准，待以后逐步完善
struct lbdt_struct
{
  struct tm dt;
  uint32_t second_part;
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
ldt_current(lbdt_t *curr)
{
  return 0;
}

#endif //_LSQL_UTIL_LDT_
