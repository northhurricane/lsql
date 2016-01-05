#include "vm.h"
#include "vmsql.h"
#include "VFCalc.h"
#include "VFDummyTableScan.h"
#include "vmexpr.h"
#include "VFClusterScan.h"

/*
插入测试
*/
void testInsert()
{
  //insert into t1 values (1);
  //构造运行程序
  VProgram program;
  VInsert ins;
  program.Bind(&ins);

  //构造运行环境
  VProcess process;
  process.Initialize(&program);
  process.Run();
  process.Deinitialize();
}

/*测试进行常量查询*/
void testSelectConst()
{
  //select 1, 2+3;
  //构造program部分
  VProgram program;

  VFDummyTableScan dummyTable;
  //构造表达式部分
  uint32_t v = 1;
  //第一个表达式
  field_all_t val_1;
  field_set_data(FIELD_ALL, &val_1, LSQL_TYPE_INT, &v, 0);
  VMConstantExpr expr1(&val_1);
  //第二个表达式
  field_all_t val_2;
  v = 2;
  field_set_data(FIELD_ALL, &val_2, LSQL_TYPE_INT, &v, 0);
  field_all_t val_3;
  v = 3;
  field_set_data(FIELD_ALL, &val_3, LSQL_TYPE_INT, &v, 0);
  VMConstantExpr expr2_left(&val_2);
  VMConstantExpr expr2_right(&val_3);
  VMAddExpr expr2(&expr2_left, &expr2_right);

  VMExprList list;
  list.push_back(&expr1);
  list.push_back(&expr2);

  VFCalc calc(list);

  calc.set_first(&dummyTable);

  VSeelect select;

  bool success = program.Bind(&select);

  //虚拟进程运行
  VProcess process;
  process.Initialize(&program);
  process.Run();
  process.Deinitialize();
}

void testSelectConst2()
{
  //select 1, 2+3;
  //构造program部分
  VProgram program;
  VMSelect vm_select;

  VFDummyTableScan dummyTable;
  //构造表达式部分
  uint32_t v = 1;
  //第一个表达式
  field_all_t val_1;
  field_set_data(FIELD_ALL, &val_1, LSQL_TYPE_INT, &v, 0);
  VMConstantExpr expr1(&val_1);
  //第二个表达式
  field_all_t val_2;
  v = 2;
  field_set_data(FIELD_ALL, &val_2, LSQL_TYPE_INT, &v, 0);
  field_all_t val_3;
  v = 3;
  field_set_data(FIELD_ALL, &val_3, LSQL_TYPE_INT, &v, 0);
  VMConstantExpr expr2_left(&val_2);
  VMConstantExpr expr2_right(&val_3);
  VMAddExpr expr2(&expr2_left, &expr2_right);

  VMExprList list;
  list.push_back(&expr1);
  list.push_back(&expr2);

  VFCalc calc(list);

  calc.set_first(&dummyTable);

  vm_select.set_entrance(&calc);
  program.BindSql(&vm_select);

  //虚拟进程运行
  VProcess process;
  process.Initialize(&program);
  process.Run();
  process.Deinitialize();
}

/*测试进行列查询*/
void testSelectColumn()
{
  //select f1 from t1;
  VFClusterScan cluster_scan(NULL);

  VProgram program;

  bool success = program.Link(&cluster_scan);
}

void testSelectColumn2()
{
  //select f1,f1 + 1 from t1;
}

int main(int argc, char* argv[])
{
  testSelectConst();

  return 0;
}
