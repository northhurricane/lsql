#ifndef LSQL_SERVER_VM_VMSQL_H_
#define LSQL_SERVER_VM_VMSQL_H_

#include "sql_statement.h"
#include "vm.h"

class VMSelect : public VMSQL
{
public :
  VMSelect() { set_stmt_type(SQL_STATEMENT_SELECT); }
};

class VMInsert : public VMSQL
{
public :
  VMInsert() { set_stmt_type(SQL_STATEMENT_INSERT); }
};

class VMDelete : public VMSQL
{
public :
  VMDelete() { set_stmt_type(SQL_STATEMENT_DELETE); }
};

class VMUpdate : public VMSQL
{
public :
  VMUpdate() { set_stmt_type(SQL_STATEMENT_UPDATE); }
};

#endif //LSQL_SERVER_VM_VMSQL_H_
