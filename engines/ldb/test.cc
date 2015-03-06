#include "lsu.h"


void test_create_lsu()
{
  LSU lsu = LSU::Create("/home/jiangyx/test", "testlsu");
  page = lsu->GetRoot();
}

int main(int argc, char *argv[])
{
  /*
    用于测试存储引擎的使用
   */
  return (0);
}
