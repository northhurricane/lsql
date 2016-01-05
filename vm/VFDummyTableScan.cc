#include "VFDummyTableScan.h"
#include "vfdata.h"
#include "autoheap.h"

/*虚拟表的内容是固定的，所以不需要再每次sql执行时创建，只需要创建一次，在每次使用虚拟表时使用*/

class VFDummyTableData
{
public :
  VFDummyTableData();
  ~VFDummyTableData();
  VFData *data() { return data_; }

private:
  VFData *data_;
  AutoHeap *memory_;

  void BuildData(Memory *memory);
  coldef_t* BuildColdef(Memory *memory);
  void FillData(VFData *data);
};

VFDummyTableData::VFDummyTableData()
{
  memory_ = AutoHeap::Create();
  BuildData(memory_);
}

VFDummyTableData::~VFDummyTableData()
{
  VFData::Destroy(data_);
  AutoHeap::Destroy(memory_);
}

void
VFDummyTableData::BuildData(Memory *memory)
{
  uint16_t column_amounts = 1;
  uint16_t row_array_size = 1;

  coldef_t *coldefs = BuildColdef(memory);
  data_ = VFData::Create(column_amounts, coldefs, row_array_size, memory);
  FillData(data_);
}

coldef_t *
VFDummyTableData::BuildColdef(Memory *memory)
{
  uint32_t size = sizeof(coldef_t[1]);
  coldef_t *coldef = (coldef_t*)(memory->Allocate(size));

  coldef->type = LSQL_TYPE_INT;
  coldef->precision = LSQL_TYPE_INT_PREC;
  coldef->scale = LSQL_TYPE_INT_SCALE;
  coldef->nullable = false;
}

void
VFDummyTableData::FillData(VFData *data)
{
  int32_t val = 1;
  data->FillField(0, 0, LSQL_TYPE_INT, &val, 0);
}

static VFDummyTableData dummy_table_data;

/********************************/
VFDummyTableScene::VFDummyTableScene()
{
  data_ = dummy_table_data.data();
}

/********************************/
vfreturn_t
VFDummyTableScan::Run(VProcess *process)
{
  VFScene *scene = process->GetScene(serial());
  //判断是否运行过，如果运行过的则直接返回。对dummy table来说，只有一行记录，该记录也是内容固定的，所以在初始化的同时就可填入，在执行到该记录时直接返回
  if (scene->over())
    return over_return();

  vfreturn_t ret;
  ret.error = false;
  ret.over = false;
  ret.data = scene->data();

  scene->set_over(true);

  return ret;
}

VFScene* 
VFDummyTableScan::CreateScene(VProcess *process)
{
  //创建函数运行现场
  VFDummyTableScene *scene = new VFDummyTableScene();

  return scene;
}


void
VFDummyTableScan::DestroyScene(VProcess *process)
{
}
