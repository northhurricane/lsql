#include "lsu.h"
#include "lfile.h"

/*
  lus
*/
LSU*
LSU::Create(const char* path, const char *name)
{
  LSU *su = new LSU();

  su->data_ = LSUData::Create(path, name);
  su->ctrl_ = LSUCtrl::Create(path, name);
  
  return su;
}

/*
  LSUData
*/
LSUData*
LSUData::Create(const char* path, const char *name)
{
  LSUData *data = new LSUData();

  data->Initialize(path, name);

  return data;
}

int
LSUData::Initialize(const char* path, const char *name)
{
  char full_path[1024];

  lfile_t file_create(full_path);

  return (0);
}

/*
  LSUCtrl
*/
LSUCtrl*
LSUCtrl::Create(const char* path, const char *name)
{
  LSUCtrl *ctrl = new LSUCtrl();

  ctrl->Initialize(path, name);

  return ctrl;
}

int
LSUCtrl::Initialize(const char* path, const char *name)
{
  char full_path[1024];

  lfile_t file_create(full_path);

  return (0);
}
