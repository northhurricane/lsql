#ifndef LSQL_SERVER_VM_VFCalc_H_
#define LSQL_SERVER_VM_VFCalc_H_

#include "vm.h"

class VFCalcScene : public VFScene
{
};

class VFCalc : public VFunction
{
public :
  virtual vfreturn_t Run(VProcess *process);
  virtual VFScene* CreateScene(VProcess *process);
  virtual void DestroyScene(VProcess *process);
};

#endif //LSQL_SERVER_VM_VFCalc_H_
