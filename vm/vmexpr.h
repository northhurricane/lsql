#ifndef LSQL_SERVER_VM_VMEXPR_H_
#define LSQL_SERVER_VM_VMEXPR_H_

#include <list>
#include "field.h"

/*
  依赖与虚拟机运行的表达式
*/

using namespace std;

class VMExpr
{
public :
  virtual field_all_t Calc() = 0;
  enum TYPE
  {
    CONSTANT = 1, //常量表达式。如：select 1
    COLUMN   = 2, //列表达式。如：select f1 from t1;的f1
    ADD      = 3,
    MINUS    = 4,
    MULTIPLY = 5,
    DIVID    = 6,
    FUNCTION = 7,
  };
  typedef enum TYPE Type;

  Type type() { return type_; }
  sqltype_t sqltype() { return sqltype_; }

protected :
  Type type_;
  sqltype_t sqltype_;
};

typedef list<VMExpr*> VMExprList;
typedef VMExprList::iterator VMExprtIterator;

/*常量表达式*/
class VMConstantExpr : public VMExpr
{
public :
  virtual field_all_t Calc();
  VMConstantExpr(field_all_t *constant);

private :
  field_all_t data_;
};

/*列表达式，说明获取数据的来源*/
#define VM_COLUMN_SOURCE_FIRST 0
#define VM_COLUMN_SOURCE_SECONDE 1
struct vm_column_source_struct
{
  uint16_t vf_idx; //0表示first，1表示second
  uint16_t pos;    //vf返回的数据集的列编号。0-based，0表示第一列
};
typedef struct vm_column_source_struct vm_column_source_t;

class VMColumnExpr : public VMExpr
{
public :
  virtual field_all_t Calc();

  vm_column_source_t source() { return source_; }
  void set_source(vm_column_source_t source) { source_ = source; }
private :
  vm_column_source_t source_;
};

/*加法表达式*/
class VMAddExpr : public VMExpr
{
public :
  VMExpr *left() { return left_; }
  VMExpr *right() { return right_; }

  VMAddExpr(VMExpr *left, VMExpr *right)
  {
    left_ = left; right_ = right;
  }

  virtual field_all_t Calc();

private :
  VMExpr *left_;
  VMExpr *right_;
};


#endif //LSQL_SERVER_VM_VMEXPR_H_
