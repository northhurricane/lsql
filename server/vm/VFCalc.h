#ifndef LSQL_SERVER_VM_VFCalc_H_
#define LSQL_SERVER_VM_VFCalc_H_

#include "vm.h"

class VFCalc : public VFunction
{
public :
  virtual void Run(VProcess *process);
  virtual void CreateScene(VFScene **pscene, Memory *memory);
};

#endif //LSQL_SERVER_VM_VFCalc_H_
