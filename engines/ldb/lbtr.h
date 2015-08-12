#ifndef _LSQL_ENGINES_LDB_LBTR_H
#define _LSQL_ENGINES_LDB_LBTR_H


/*
  B+树对象
 */

class LSU;
class LTuple;

class LBTree
{
public :
  void Search();
  void Insert();
  void Delete();
  void Update();

private:
  enum InsertResult
  {
    Success,
    NeedSplit,
    KeyConflict
  };

  /*插入定位，不光得到位置，还要得到搜索至该位置的路径，便于插入时的分裂操作*/
  void LocateForInsert();
  /*尝试是否可以直接插入*/
  void TryInsert(LPage *page, LTuple *tuple);
  /*分裂当前页的插入*/
  void SplitInsert(LPage *page, LTuple *tuple);
  
  LSU *lsu_;  //对象所属的lsu
};

#endif //_LSQL_ENGINES_LDB_LBTR_H
