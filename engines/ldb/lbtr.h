#ifndef _LSQL_ENGINES_LDB_LBTR_H
#define _LSQL_ENGINES_LDB_LBTR_H


/*
  B+树对象
 */

class lsu;

class lbtr
{
public :
  enum rcode {
    SUCCESS =0,
  };

  rcode Search();
  rcode Insert();
  rcode Delete();
  rcode Update();

private:
  lsu *lsu_;  //对象所属的lsu
};

#endif //_LSQL_ENGINES_LDB_LBTR_H
