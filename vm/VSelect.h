#ifndef LSQL_VM_VSELECT_
#define LSQL_VM_VSELECT_

#include "VSQL.h"

class VSelect : public VSQL
{
  VSelect() { stmt_type_ = SQL_STATEMENT_SELECT; }
};

#endif //LSQL_VM_VSELECT_
