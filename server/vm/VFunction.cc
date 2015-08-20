#include "VFunction.h"

#define SERIAL_UNDEFINE 0xFFFFFFFF
VFunction::VFunction()
{
  serial_ = SERIAL_UNDEFINE;
  first_ = NULL;
  second_ = NULL;
}
