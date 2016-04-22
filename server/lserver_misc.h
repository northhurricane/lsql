#ifndef _LSERVER_MISC_H_
#define _LSERVER_MISC_H_

#include "lsql.h"

//那些不好归类函数都先放在此处，然后不断剥离

class LPort;

/*
  处理客户端连接
*/
lret
svr_do_connect(LPort *port);

#endif //_LSERVER_MISC_H_
