#include "conn.h"

lmutex_t ConnectionManager::mutex_;
list<Connection*> ConnectionManager::connections_;

bool ConnectionManager::initialized_ = Construct();

bool ConnectionManager::Construct()
{
  lmutex_init(&mutex_);
  return true;
}
