#ifndef LSQL_FILE_LFILE_H_
#define LSQL_FILE_LFILE_H_

#ifndef NULL
#define NULL (0)
#endif

typedef FILE *lfile_t;

lfile_t
lfile_create(const char *fullpath);

lfile_t
lfile_open(const char *fullpaht);

#endif //LSQL_FILE_LFILE_H_
