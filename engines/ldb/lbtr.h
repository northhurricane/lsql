#ifndef _LSQL_ENGINES_LDB_LBTR_H
#define _LSQL_ENGINES_LDB_LBTR_H


/*
  B+树对象
 */

class LSU;

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

  void LocatePosition();
  void TryInsert(LPage *page);
  void SplitInsert(LPage *page);
  
  LSU *lsu_;  //对象所属的lsu
};

#endif //_LSQL_ENGINES_LDB_LBTR_H
