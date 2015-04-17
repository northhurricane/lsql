#ifndef LSQL_SERVER_VM_VFCalc_H_
#define LSQL_SERVER_VM_VFCalc_H_

#include "vm.h"
#include "column.h"

class VFCalc : VFunction
{
private :
  coldef_array_t columns;
};

#endif //LSQL_SERVER_VM_VFCalc_H_
