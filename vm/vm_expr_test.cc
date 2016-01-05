#include "vmexpr.h"

void test1()
{
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
  expr2.Calc();
}

int main(int argc, char *argv[])
{
  test1();

  return 0;
}
