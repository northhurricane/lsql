#ifndef _LMSG_H
#define _LMSG_H

#include "lendian.h"

#define LMSG_HEAD_SIZE 64
#define LMSG_COMMON_HEAD_SIZE 16

#define LMSG_HEAD  0
#define LMSG_LEN   LMSG_HEAD
#define LMSG_CMD   (LMSG_LEN + sizeof(uint32_t))

//execute command
#define LMSG_REQ_EXEC LMSG_COMMON_HEAD_SIZE

inline uint32_t lmsg_read_len(uint8_t *m)
{
  return le_read_uint32(m + LMSG_LEN);
}

inline void lmsg_write_len(uint8_t *m, uint32_t len)
{
  le_write_uint32(m + LMSG_LEN, len);
}

inline uint16_t lmsg_read_cmd(uint8_t *m)
{
  return le_read_uint16(m);
}

inline void lmsg_write_cmd(uint8_t *m, uint16_t cmd)
{
  le_write_uint16(m, cmd);
}

#endif //_LMSG_H
