#ifndef LSQL_FILE_LFILE_H_
#define LSQL_FILE_LFILE_H_

#ifndef NULL
#define NULL (0)
#endif

#include <stdint.h>

typedef int lfile_t;

lfile_t
lfile_create(const char *file);

lfile_t
lfile_open(const char *file);

void
lfile_expand(lfile_t lfile, uint64_t size);

void
lfile_write(lfile_t lfile, uint64_t offset, uint8_t *buff, uint32_t size);

#endif //LSQL_FILE_LFILE_H_
