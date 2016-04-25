#include "lserver_misc.h"
#include "LSession.h"

lret
svr_do_connect(LPort *port)
{
  lassert(port != NULL);

  //创建会话（session）
  LSession *session = session_create(port);

  return LSQL_SUCCESS;
}
