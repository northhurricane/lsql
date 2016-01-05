#ifndef LSQL_SERVER_VM_VFCalc_H_
#define LSQL_SERVER_VM_VFCalc_H_

#include "vm.h"
#include "vmexpr.h"

class VFCalcScene : public VFScene
{
};

/*
  计算函数中的表达式链表的元素个数就是VFCalcScene返回的结果列的个数。
*/
class VFCalc : public VFunction
{
public :
  virtual vfreturn_t Run(VProcess *process);
  virtual VFScene* CreateScene(VProcess *process);
  virtual void DestroyScene(VProcess *process);

  VFCalc(VMExprList exprs)
  {
    exprs_ = exprs;
  }

private :
  VMExprList exprs_;
};

#endif //LSQL_SERVER_VM_VFCalc_H_
