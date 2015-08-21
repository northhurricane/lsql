#ifndef LSQL_SERVER_VM_VFUNCTION_H_
#define LSQL_SERVER_VM_VFUNCTION_H_

struct vfreturn_struct
{
  bool error; //调用是否出错
  bool over;  //函数是否结束。true表示函数执行结束，不再返回数据；false表示data成员变量中包含数据。

  VFData *data; //返回的数据
};
typedef struct vfreturn_struct vfreturn_t;

inline vfreturn_t over_return()
{
  vfreturn_t ret;
  ret.error = false;
  ret.over = true;
  ret.data = NULL;
}

/*函数运行现场。函数运行时，需要保存变量信息，执行的位置信息等*/
class VFScene
{
public :
  VFData *data() { return data_; }
  void set_data(VFData *data) { data_ = data; }
  bool over() { return over_; }
  void set_over(bool over) { over_ = over; }
  bool first_over() { return first_over_; }
  void set_first_over(bool over) { first_over_ = over; }
  bool second_over() { return second_over_; }
  void set_second_over(bool over) { second_over_ = over; }

protected :
  VFData  *data_;      //在函数执行时填写数据的地方，和VF的coldef一致

  bool over_;          //该函数是否取完数据。true表示所有数据都已经返回，false表示还可以继续返回数据。在first函数执行后，如果over被设置，则说明无需后续的函数执行（更多细节待定）
  bool first_over_;    //第一函数是否结束
  bool second_over_;   //第二函数是否结束
};

#define VF_SERIAL_UNDEFINE 0xFFFFFFFF

/*函数*/
class VFunction
{
public :
  //函数运行
  virtual vfreturn_t Run(VProcess *process) = 0;

  /*函数执行*/
  void Execute(VProcess *process);

  //创建函数运行时所需的运行现场，在虚拟进程的函数运行前，被调用
  virtual VFScene *CreateScene(VProcess *process) = 0;

  //销毁函数运行时所需的运行现场，在虚拟进程结束时，进行销毁
  virtual void DestroyScene(VProcess *process) = 0;
  VFunction() ;

protected:
  //
  virtual void ActionAfterFirstFunc() = 0;
  vritual void ActionAfterSecondFunc() = 0;

private:
  /*serail_的值在program生成时产生，每个program下的function的serial是唯一的。
    可将其看作C中的函数地址，C中每个函数的地址在某个确定的program中都是唯一的。*/
  uint32_t serial_; 
  VFunction *first_;   //第一个被执行
  VFunction *second_;  //第二个被执行
  coldef_array_t *coldefs_; //函数返回行集的元信息
  //用于定义如何使用first_/second_的行集的信息。也就是从子函数的行集到当前函数的行集的转化。比如abs(f1), cos(f1)，f1+f2这样的计算列，或者直接将行集的某些列的数据拷贝到当前行集

public :
  VFunction *first() { return first_; }
  void set_first(VFunction *first) { first_ = first; }
  VFunction *second() { return second_; }
  void set_second(VFunction *second) { second_ = second; }
  uint32_t serial() { return serial_; }
  void set_serial(uint32_t serial) { serial_ = serial; }
  coldef_array_t *coldefs() { return coldefs_; }
};

#ifndef // LSQL_SERVER_VM_VFUNCTION_H_

