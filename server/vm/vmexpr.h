#ifndef LSQL_SERVER_VM_VMEXPR_H_
#define LSQL_SERVER_VM_VMEXPR_H_

#include <list>
#include "field.h"

#define MAX_SOURCE_COLUMN_NUMBER 32

enum vm_expr_type_enum
{
  CONSTANT = 1, //常量表达式。如：select 1
  COLUMN   = 2, //列表达式。如：select f1 from t1;的f1
  ADD      = 3,
  MINUS    = 4,
  MULTIPLY = 5,
  DIVID    = 6,
  FUNCTION = 7,
};
typedef enum vm_expr_type_enum vm_expr_type_t;

struct vm_expr_struct;

struct vm_expr_constant_struct
{
};

struct vm_expr_bo_struct
{
  struct vm_exprt_struct *expr1;
  struct vm_expr_struct *expr2;
};

/*
  用来说明各个虚拟函数（VF）是如何使用调用函数返回的数据的
  1、VF有多少列，就有多少个用于说明该列的生成的expr
 */
struct vm_expr_struct
{
  vm_expr_type_t type;  //

  //该表达式的输入
};
typedef struct vm_expr_struct vm_expr_t;

struct vm_exprs_struct
{
  uint16_t columns_amount;     //列的个数
  vm_expr_t *exprs;  //记录各列的使用情况
};
typedef struct vm_exprs_struct vm_exprs_t;

/*
  由于column的表达式类型的存在，所以在表达运行时
 */
struct vm_expr_env_struct
{
  uint16_t rowi;       //
};

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

class VMConstantExpr : public VMExpr
{
public :
  virtual field_all_t Calc();
  VMConstantExpr(field_all_t *constant);

private :
  field_all_t data_;
};

class VMColumnExpr : public VMExpr
{
public :
  virtual field_all_t Calc();
};

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
