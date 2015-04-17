#ifndef LSQL_SERVER_VM_VFCalc_H_
#define LSQL_SERVER_VM_VFCalc_H_

#include "vm.h"
#include "column.h"

class VFCalc : VFunction
{
public :
  virtual void Run(VProcess *process);
};

#endif //LSQL_SERVER_VM_VFCalc_H_
