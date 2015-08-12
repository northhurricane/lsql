#ifndef _LSQL_ENGINES_LDB_LDB_H
#define _LSQL_ENGINES_LDB_LDB_H

#include <stdint.h>

/*初始化数据库*/
int ldb_init(char *path, uint32_t page_size);

#endif //_LSQL_ENGINES_LDB_LDB_H
