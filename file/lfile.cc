#include "lfile.h"

//linux header
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

lfile_t
lfile_create(const char *file)
{
  lfile_t lfile = open(file, O_CREAT|O_WRONLY, 0644);

  return lfile;
}

void
lfile_expand(lfile_t file, uint64_t size)
{
  char buff[1] = {0};
  lseek(file, size - 1, SEEK_SET);
  write(file, buff, 1);
}

void
lfile_write(lfile_t lfile, uint64_t offset, uint8_t *buff, uint32_t size)
{
}
