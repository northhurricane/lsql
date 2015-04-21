#ifndef LSQL_SERVER_VM_VFCalc_H_
#define LSQL_SERVER_VM_VFCalc_H_

#include "vm.h"

class VFCalc : public VFunction
{
public :
  virtual vfreturn_t Run(VProcess *process);
  virtual VFScene* CreateScene(Memory *memory);
  virtual void DestroyScene();
};

#endif //LSQL_SERVER_VM_VFCalc_H_
