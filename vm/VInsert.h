#ifndef LSQL_VM_VINSERT_H_
#define LSQL_VM_VINSERT_H_

#include "VSQL.h"

/*
插入语句
*/
class VInsert : public VSQL
{
public :
  VInsert() { sql_type_ = SQL_STATEMENT_INSERT; }
};

#endif//LSQL_VM_VINSERT_H_
