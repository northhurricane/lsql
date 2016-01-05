#ifndef _LSQL_VOS_H_
#define _LSQL_VOS_H_

#include <list>
/*
模拟操作系统，完成操作系统的一些功能。
1、vm的维护。创建/销毁vm对象
2、虚拟进程的维护。创建/销毁进程，

记录的信息
1、进程信息
*/

using namespace std;

class VProgram;
class VProcess;

class VOS
{
public :
  /*启动VOS，初始化VOS*/
  static void Initialize();

  /*启动程序*/
  static int StartProgram(VProgram *program);

  /*当虚拟进程完成执行，通知VOS退出，由VOS回收资源*/
  static int ExitNotify(VProcess *process);

  /*释放vm资源，进入等待模式*/
  static int Yield(VProcess *process);

private :
  //设想功能
  static void AddVM() {}
  static void RemoveVM() {}

  //VM链表
  //运行中
  //空闲中
};

#endif //_LSQL_VOS_H_
