#include "ldb.h"

static
int ldb_init_systables_storage(const char *path)
{
}

static
int ldb_init_systables_insert_record()
{
  return 0;
}

static
int ldb_init_systables(const char *path)
{
  //初始化存储空间
  ldb_init_systables_storage(path);

  //初始化存储内容
  ldb_init_systables_insert_record();

  return 0;
}

static
int ldb_init_syscolumns_storage(const char *path)
{
  return 0 ;
}

static
int ldb_init_syscolumns_insert_record()
{
  return 0;
}

static
int ldb_init_syscolumns(const char *path)
{
  return 0;
}

int ldb_init(const char *path)
{
  //初始化系统schema下的系统表

  //systables
  ldb_init_systables(path);

  //syscolumns
  ldb_init_syscolumns(path);

  return 0;
}

