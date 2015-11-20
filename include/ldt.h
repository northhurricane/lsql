#ifndef _LSQL_INCLUDE_LDT_H_
#define _LSQL_INCLUDE_LDT_H_

#include <stdint.h>
/*
  cfl的时间日期
*/

/*
以公元纪年的日期。秒最高精度9位，纳秒
*/

/*
  日期类型。d是date的缩写
  todo:仿照日期时间类型进行相应功能的编写
*/
struct ld_struct
{
  int16_t year;
  uint8_t month;
  uint8_t day;
};
typedef struct ld_struct ldate_t;

/*
32位有符号整型日期存储结构
16b |8b   |8b
year|month|day
*/
typedef int32_t lds_t;

/*to do ...*/

/*
  时间类型。t是time的缩写
*/
struct lt_struct
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint32_t second_fraction;
};
typedef struct lt_struct lt_t;

/*
64位无符号时间类型
8b|8b  |8b    |8b    |32b
0 |hour|minute|second|fraction
*/
typedef uint64_t lts_t;

/*
  日期时间类型。dt是date&time的缩写
*/
struct ldt_struct
{
  int16_t  year;
  uint8_t  month;
  uint8_t  day;
  uint8_t  hour;
  uint8_t  minute;
  uint8_t  second;
  uint32_t second_fraction;
};
typedef struct ldt_struct ldt_t;

/*
80位整型时间日期结构。头16位为年，后面为月日时分秒
从高到低
16b |4b|4b   |6b |6b  |6b    |6b    |32b
year|0 |month|day|hour|minute|second|microsecond
*/
/*压缩格式的时间日期类型。s是short的缩写*/
struct ldts_struct
{
  int16_t first;
  uint64_t second;
};
typedef struct ldts_struct ldts_t;

/*
  转换易读模式为短模式
*/
inline void ldt2dts(const ldt_t &dt, ldts_t &dts)
{
}

/*
  转换短模式为易读模式
*/
inline void ldts2dt(ldt_t &dt, const ldts_t &dt)
{
}

/*
  endian存储短模式的时间日期数据
*/
inline void ldts_endian_write(const ldts_t &dts, void *target)
{
}

/*
  读取endian存储的短模式时间日期数据
*/
inline void ldts_endain_read(ldts_t &dts, void *source)
{
}

/*
  比较两个短型时间日期的
  返回：
    1 , dts1大于dts2
    0 , dts1等于dts2
    -1, dts1小于dts2
*/
inline int ldts_cmp(const ldts_t &dts1, const ldts_t &dts2)
{
  if (dts1.first > dts2.first)
  {
    return 1;
  }
  if (dts1.first < dts2.first)
  {
    return -1;
  }

  if (dts1.first > 0)
  {
    //公元后比较
    if (dts1.second > dts2.second)
    {
    }
    if (dts1.second < dts2.second)
    {
    }
  }
  else
  {
    //公元前比较
  }

  //相等
  return 0;
}

#endif //_LSQL_INCLUDE_LDT_H_

