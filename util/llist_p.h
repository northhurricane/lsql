#ifndef LSQL_UTIL_LIST_P_H_
#define LSQL_UTIL_LIST_P_H_

/*
*/

#include "llist.h"

typedef struct llist_pnode_struct llist_pnode_t;
struct llist_pnode_struct
{
  LLIST_LINK_TEMPLATE(llist_pnode_t) link;
  void * data;
};

typedef LLIST_TEMPLATE(llist_pnode_t) llist_p_t;

inline void
llist_p_init(llist_p_t *list)
{
  LLIST_INIT(*list);
}

inline void
llist_p_add_first(llist_p_t *list, llist_pnode_t *pnode)
{
  LLIST_ADD_FIRST(*list, pnode, link);
}

inline void
llist_p_add_last(llist_p_t *list, llist_pnode_t *pnode)
{
  LLIST_ADD_LAST(*list, pnode, link);
}

inline llist_pnode_t*
llist_p_get_first(llist_p_t *list)
{
  return LLIST_GET_FIRST(*list);
}

inline llist_pnode_t*
llist_p_get_last(llist_p_t *list)
{
  return LLIST_GET_LAST(*list);
}

inline llist_pnode_t*
llist_p_get_next(llist_pnode_t *pnode)
{
  return LLIST_GET_NEXT(pnode, link);
}

inline llist_pnode_t*
llist_p_get_prev(llist_pnode_t *pnode)
{
  return LLIST_GET_PREV(pnode, link);
}

#endif //LSQL_UTIL_LIST_P_H_
