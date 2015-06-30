#include "compile.h"
#include "autoheap.h"

void test1()
{
  AutoHeap *heap = AutoHeap::Create();

  //mock语法分析的结果
  int size = 0;

  parse_select_t *select =
  (parse_select_t*)heap->Allocate(sizeof(parse_select_t[1]));
  select->head.type = PARSE_SELECT;

  size = sizeof(parse_select_items_t[1]);
  parse_select_items_t *select_items =
  (parse_select_items_t*)heap->Allocate(size);
  llist_p_init(&select_items->items);

  parse_select_item_t *select_item =
  (parse_select_item_t*)heap->Allocate(sizeof(parse_select_item_t[1]));
  select_item->node.data = select_item;

  llist_p_add_last(&select_items->items, &select_item->node);
  select->from = NULL;
  select->items = select_items;

  //进行编译
  VProgram *prog = NULL;
  lsql_compile((parse_head_t*)select, &prog);
  //编译出的虚拟程序运行
}

int main(int argc, char *argv[])
{
  return 0;
}

