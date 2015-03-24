#ifndef _LSQL_ENGINES_LDB_LMPAGE_H
#define _LSQL_ENGINES_LDB_LMPAGE_H

/*
  lmpage : lsql page in memory
*/

class LMPage
{
public :
  uint2_t Locate();
  int Insert();

privave :
  uint4_t page_num_;
  uint2_t rec_num_;
};

#endif //_LSQL_ENGINES_LDB_LMPAGE_H
