#include "vfdata.h"

VFData*
VFData::Create(uint16_t columns_amount, coldef_t *columns,
                        uint16_t row_array_size, Memory *memory)
{
  VFData *vfdata = NULL;
  vfdata->fields_ = NULL;

  return NULL;
}

void
VFData::Destroy(VFData *data)
{
  return;
}

void
VFData::FillField(uint16_t dest_fieldno, vffield_t *src_data, uint16_t amount)
{
}

void
VFData::FillField(uint16_t fieldno, uint16_t rowno
                  , field_type_t type, void *field)
{
}

void
VFData::FillField(uint16_t fieldno, uint16_t rowno
                  , sqltype_t type, void *data, uint16_t length)
{
  //获取field
  vffield_t *vffield = *(fields_ + fieldno);

  //获取行数据的位置
  lassert(rowno < vffield->amount);
  void *prow = NULL;
  if (vffield->type == FIELD_REF)
  {
    prow = ((uint8_t*)vffield->data) + FIELD_REF_SIZE * rowno;
  }
  else
  {
    prow = ((uint8_t*)vffield->data) + FIELD_ALL_SIZE * rowno;
  }

  field_set_data(vffield->type, prow, type, data, length);
  //进行数据填写
}

