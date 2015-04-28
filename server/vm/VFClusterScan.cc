#include "VFClusterScan.h"

vfreturn_t
VFClusterScan::Run(VProcess *process)
{
  //进行计算列的操作
  return over_return();
}

VFScene*
VFClusterScan::CreateScene(VProcess *process)
{
  VFClusterScanScene *scene = new VFClusterScanScene();

  //根据函数的列信息创建数据
  VFData *data = VFData::Create(coldefs()->col_num,
                                coldefs()->coldefs,
                                process->rows_array_size(),
                                process->memory());

  scene->set_data(data);

  return scene;
}

void
VFClusterScan::DestroyScene(VProcess *process)
{
  VFClusterScanScene *scene = NULL;
  scene = (VFClusterScanScene*)process->GetScene(serial());

  delete scene;
}

