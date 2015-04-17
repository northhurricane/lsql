#include "VFDummyTableScan.h"

void
VFDummyTableScan::Run(VProcess *process)
{
  VFScene *scene = process->GetScene(serial());
  //判断是否运行过，如果运行过的则直接返回。对dummy table来说，只有一行记录，该记录也是内容固定的，所以在初始化的同时就可填入，在执行到该记录时直接返回
}

void
VFDummyTableScan::CreateScene(VFScene **pscene, Memory *memory)
{
  //创建函数运行现场
  VFDummyTableScene *scene = NULL;

  FillRow(scene);

  VFScene *tmp = NULL;

  *pscene = scene;
}

void
VFDummyTableScan::FillRow(VFDummyTableScene *scene)
{
}

