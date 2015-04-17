#ifndef LSQL_SERVER_VM_VFDummyTableScan_H_
#define LSQL_SERVER_VM_VFDummyTableScan_H_

#include "vm.h"

class VFDummyTableScene : public VFScene
{
  /*public :
    void Test() {return ;}*/
};

/*
  针对select 1这样的查询，虚拟一个表的搜索，返回一个只有一列的行记录，且该列的值为null。
*/
class VFDummyTableScan : VFunction
{
public :
  virtual void Run(VProcess *process);
  virtual void CreateScene(VFScene **pscene, Memory *memory);

private :
  void FillRow(VFDummyTableScene *scene);
};

#endif //LSQL_SERVER_VM_VFDummyTableScan_H_

