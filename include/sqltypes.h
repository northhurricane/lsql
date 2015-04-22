#ifndef LSQL_INCLUDE_SQLTYPE_H_
#define LSQL_INCLUDE_SQLTYPE_H_

typedef int16_t sqltype_t;

#define LSQL_TYPE_VARCHAR 1 //变长字符类型
#define LSQL_TYPE_CHAR    2 //定长字符类型
#define LSQL_TYPE_INT     3 //4字节长度整形

#define LSQL_TYPE_INT_PREC  10
#define LSQL_TYPE_INT_SCALE 0

inline bool type_is_fix_storage_lenght(sqltype_t type)
{
  switch (type)
  {
  case LSQL_TYPE_INT:
    return true;

  case LSQL_TYPE_VARCHAR:
  case LSQL_TYPE_CHAR:
    return false;

  defaults :
    //所以类型都应该有明确的结果
    //lsql_assert(false);
    return false;
  }
}

#endif //LSQL_INCLUDE_SQLTYPE_H_
