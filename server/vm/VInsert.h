#ifndef LSQL_VM_VINSERT_H_
#define LSQL_VM_VINSERT_H_

#include "VSQL.h"

/*
VInsert运行时的参数，包含进行插入的数据
*/
class VInsertParam
{
};

/*
插入语句
*/
class VInsert : public VSQL
{
public :
  VInsert() { }
};

#endif//LSQL_VM_VINSERT_H_
