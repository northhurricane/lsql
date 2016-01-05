#include "VFCalc.h"

vfreturn_t
VFCalc::Run(VProcess *process)
{
  //进行计算列的操作
  VMExprtIterator iter = exprs_.begin();
  for (; iter != exprs_.end(); iter++)
  {
    //计算表达式
    VMExpr *expr = *iter;
    expr->Calc();

    //计算结果写入VFCalc的VFScene中
  }

  return over_return();
}

VFScene*
VFCalc::CreateScene(VProcess *process)
{
  VFCalcScene *scene = new VFCalcScene();

  //根据函数的列信息创建数据
  VFData *data = VFData::Create(coldefs()->col_num,
                                coldefs()->coldefs,
                                process->rows_array_size(),
                                process->memory());

  scene->set_data(data);

  return scene;
}

void
VFCalc::DestroyScene(VProcess *process)
{
  VFCalcScene *scene = (VFCalcScene*)process->GetScene(serial());

  delete scene;
}

