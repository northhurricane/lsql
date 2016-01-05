#include "vmexpr.h"

VMConstantExpr::VMConstantExpr(field_all_t *constant)
{
  data_ = *constant;
}

field_all_t
VMConstantExpr::Calc()
{
  return data_;
}


field_all_t
VMAddExpr::Calc()
{
  field_all_t left_val = left_->Calc();
  field_all_t right_val = right_->Calc();
  field_all_t val;

  //left_val + right_val
  return val;
}
