#ifndef LSQL_SERVER_VM_VFClusterScan_H_
#define LSQL_SERVER_VM_VFClusterScan_H_

#include "vm.h"

class VFClusterScanScene : public VFScene
{
};

class VFClusterScan : public VFunction
{
public :
  virtual vfreturn_t Run(VProcess *process);
  virtual VFScene* CreateScene(VProcess *process);
  virtual void DestroyScene(VProcess *process);

  VFClusterScan(void *cluster_index)
  {
  }

private :
  void *cluster_index_; //聚集索引
};

#endif //LSQL_SERVER_VM_VFClusterScan_H_

