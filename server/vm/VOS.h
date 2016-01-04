#ifndef _LSQL_VOS_H_
#define _LSQL_VOS_H_

/*
模拟操作系统，完成操作系统的一些功能。
1、vm的维护。创建/销毁vm对象
2、虚拟进程的维护。创建/销毁进程，

设想功能:
1、可动态的增加/减少虚拟机，在线调节运行资源
*/

class VProgram;
class VProcess;

class VOS
{
public :
  static void Initialize();
  /*启动程序*/
  static int StartProgram(VProgram *program);
  /*当虚拟进程完成执行，通知VOS退出，由VOS回收资源*/
  static int ExitNotify(VProcess *process);

private :
  //设想功能
  static void AddVM() {}
  static void RemoveVM() {}

  //VM链表
  //运行中
  //空闲中
};

#endif //_LSQL_VOS_H_
