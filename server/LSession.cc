#include <list>
#include <map>
#include "LSession.h"
#include "lmutex.h"

using namespace std;

typedef map<uint64_t , LSession*>  session_id_map_t;
typedef session_id_map_t::iterator  session_id_map_it_t;
typedef map<LPort* , LSession*>  session_port_map_t;
typedef session_port_map_t::iterator  session_port_map_it_t;

class LSessionManager
{
public :
  LSessionManager();
  ~LSessionManager();

  void Add(LSession *session)
  {
    lmutex_lock(&map_mutex_);
    session_id_map_[session->get_id()] = session;
    session_port_map_[session->get_port()] = session;
    lmutex_unlock(&map_mutex_);
  }

  void Remover(LSession *session)
  {
    lmutex_lock(&map_mutex_);
    session_id_map_it_t it1 = session_id_map_.find(session->get_id());
    session_id_map_.erase(it1);
    session_port_map_it_t it2 = session_port_map_.find(session->get_port());
    session_port_map_.erase(it2);
    lmutex_unlock(&map_mutex_);
  }

private :
  session_id_map_t session_id_map_;
  session_port_map_t session_port_map_;
  lmutex_t map_mutex_;
};

LSessionManager::LSessionManager()
{
  lmutex_init(&map_mutex_);
}

LSessionManager::~LSessionManager()
{
  lmutex_destroy(&map_mutex_);
}

static LSessionManager session_manager;

LSession *session_create(LPort *port)
{
  LSession *session = new LSession();

  if (session == NULL)
    return NULL;

  return session;
}

void session_destroy(LSession *session)
{
}

LSession *session_find_by_port(LPort *port)
{
  return NULL;
}

LSession *session_find_by_id(uint64_t id)
{
  return NULL;
}


/////////////////////

