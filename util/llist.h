#ifndef LSQL_UTIL_LLIST_H_
#define LSQL_UTIL_LLIST_H_

#include <stdint.h>

/*
c下的链表实现，相对于c++的链表，在表达上存在复杂性。
当对象需要加入多个链表时，需要明确知道要加入哪些链表，并分别定义针对这些链表的链接定义
*/

#ifndef NULL
#define NULL 0
#endif

#define LLIST_TEMPLATE(NODE_TYPE)\
struct {\
uint32_t  amount;/**/\
NODE_TYPE *first;/**/\
NODE_TYPE *last; /**/\
}\

#define LLIST_LINK_TEMPLATE(NODE_TYPE)\
struct {\
NODE_TYPE *prev; /**/\
NODE_TYPE *next; /**/\
}\

#define LLIST_INIT(LIST)\
{\
  (LIST).amount = 0;\
  (LIST).first = NULL;\
  (LIST).last  = NULL;\
}\

/*
LIST:链表
ELEMENT:链表元素的指针
ELEMENT_LINK:链表元素中的连接对象
*/
#define LLIST_ADD_FIRST(LIST, ELEMENT, ELEMENT_LINK)\
{\
  ((LIST).amount)++;\
  ((ELEMENT)->ELEMENT_LINK).prev = NULL;                \
  ((ELEMENT)->ELEMENT_LINK).next = (LIST).first;        \
  if ((LIST).first != NULL) {                           \
    (((LIST).first)->ELEMENT_LINK).prev = (ELEMENT);    \
  }                                                     \
  (LIST).first = (ELEMENT);                             \
  if ((LIST).last == NULL) {                            \
    (LIST).last = ELEMENT;                              \
  }                                                     \
}

#define LLIST_ADD_LAST(LIST, ELEMENT, ELEMENT_LINK)     \
{\
  ((LIST).amount)--;                            \
  ((ELEMENT)->ELEMENT_LINK).prev = (LIST).last; \
  ((ELEMENT)->ELEMENT_LINK).next = NULL;        \
  if ((LIST).last != NULL){                             \
    (((LIST).last)->ELEMENT_LINK).next = (ELEMENT);     \
  }                                                     \
  (LIST).last = (ELEMENT);                              \
  if ((LIST).first == NULL) {                           \
    (LIST).first = ELEMENT;                             \
  }                                                     \
}

#define LLIST_GET_FIRST(LIST)                   \
  (LIST).first

#define LLIST_GET_LAST(LIST)                    \
  (LIST).last

#define LLIST_GET_NEXT(ELEMENT, ELEMENT_LINK)   \
  ((ELEMENT)->ELEMENT_LINK).next

#define LLIST_GET_PREV(ELEMENT, ELEMENT_LINK)   \
  ((ELEMENT)->ELEMENT_LINK).prev


#endif //LSQL_UTIL_LLIST_H_
