#ifndef LSQL_SERVER_VM_VFDummyTableScan_H_
#define LSQL_SERVER_VM_VFDummyTableScan_H_

#include "vm.h"
#include "vfdata.h"

class VFDummyTableScene : public VFScene
{
public :
  VFDummyTableScene();
};

/*
  针对select 1这样的查询，虚拟一个表的搜索，返回一个只有一列的行记录，且该列的值为null。
*/
class VFDummyTableScan : public VFunction
{
public :
  virtual vfreturn_t Run(VProcess *process);
  virtual VFScene* CreateScene(Memory *memory);
  virtual void DestroyScene();
};

#endif //LSQL_SERVER_VM_VFDummyTableScan_H_

