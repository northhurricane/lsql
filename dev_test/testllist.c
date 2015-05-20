#include "llist.h"
#include "llist_p.h"

typedef struct test1_item_struct test1_item_t;
struct test1_item_struct {
  int temp;

  LLIST_LINK_TEMPLATE(test1_item_t) link_for_test1_list;
  LLIST_LINK_TEMPLATE(test1_item_t) link_for_test1_2_list;
};

typedef LLIST_TEMPLATE(test1_item_t) test1_list_t;
typedef LLIST_TEMPLATE(test1_item_t) test1_2_list_t;

void test1()
{
  test1_list_t test1_list;
  test1_2_list_t test1_2_list;
  test1_item_t test1_item;
  test1_item_t test1_item2;

  LLIST_INIT(test1_list);
  LLIST_INIT(test1_2_list);

  LLIST_ADD_FIRST(test1_list, &test1_item, link_for_test1_list);
  LLIST_ADD_LAST(test1_list, &test1_item2, link_for_test1_list);

  LLIST_ADD_FIRST(test1_2_list, &test1_item2, link_for_test1_2_list);
  LLIST_ADD_LAST(test1_2_list, &test1_item, link_for_test1_2_list);

  {
    test1_item_t *item = LLIST_GET_FIRST(test1_list);
    test1_item_t *item2 = LLIST_GET_LAST(test1_list);
    test1_item_t *item_next = LLIST_GET_NEXT(item, link_for_test1_list);
    test1_item_t *item_prev = LLIST_GET_PREV(item2, link_for_test1_list);
  }
  
}

void test2()
{
  llist_p_t list;
  llist_pnode_t d1,d2,d3;
  llist_pnode_t first;
  llist_pnode_t *n1;

  llist_p_init(&list);
  llist_p_add_last(&list, &d1);
  llist_p_add_last(&list, &d2);
  llist_p_add_last(&list, &d3);
  llist_p_add_first(&list, &first);

  n1 = llist_p_get_first(&list);
  n1 = llist_p_get_next(n1);
  n1 = llist_p_get_prev(n1);
  n1 = llist_p_get_last(&list);

}

int main(int argc, char *argv[])
{
  test1();
  return 0;
}
