#include "lbtr.h"
#include "lpage.h"

void
LBTree::Insert()
{
  //定位插入点
  LPage *root = NULL;
  LPage *located_page = NULL;

  LocateForInsert(root);

  InsertResult r = TryInsert(locate_page);
  if (r == NeedSplit)
  {
    SplitInsert(located_pate);
  }
  if (r == KeyConflict)
  {
  }
}

void
LBTree::SplitInsert(LPage *page, LTuple *tuple)
{
  bool is_root = false;
  LPage *page = parent;
  if (is_root)
  {
    //分配两个新的页面
    //拷贝数据至页面
    return ;
  }

  //拆分页面，形成两个
  //构造插入父节点的索引记录

  //尝试插入记录
  TryInsert(parent);

  //判断插入情况
  if (r == NeedSplit)
  {
    SplitInsert(parent);
  }
  if (r == KeyConflict)
  {
    return;
  }
}

void
LBTree::TryInsert(LPage *page, LTuple *tuple)
{
}

void
LBTree::LocateForInsert()
{
}


