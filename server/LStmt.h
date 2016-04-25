#ifndef _LSTMT_H_
#define _LSTMT_H_

#include <stdint.h>
#include <list>

using namespace std;

class LSession;

typedef list<LSession*> lsession_list_t;

class LStmt
{
private :
  uint64_t id_;
  LSession *session_;
};

#endif //_LSTMT_H_
