#ifndef _LSQL_ENGINES_LDB_LSU_H
#define _LSQL_ENGINES_LDB_LSU_H


/*
  lsu:lsql storage unit
  lsql数据存储单元，实现了页存储部分，可以简单的看待，一个lsu就是一个索引，一个索引就是一个B+树。
  数据存储在单独的文件，当需要管理多个页时，类似mysql的segment管理信息存储在控制文件中
  仅进行页面的存储和使用管理，页面内的内容无需了解，将有lpage针对页面进行操作定义
 */

class LSUData;
class LSUCtrl;
class LPage;

class LSU
{
public :
  /*
    创建一个存储单元。
   */
  static LSU* Create(const char* path, const char *name);

public :
  LPage* GetRootNode();
  LPage* GetNode();

private :
  LSUData *data_;
  LSUCtrl *ctrl_;

  LSU();
};

/*
  数据存储。用于存储数据页
 */
class LSUData
{
public :
  static LSUData *Create(const char* path, const char *name);

public :
  LPage *ReadPage();
  LPage *WritePage();

private :
  LSUData();
  int Initialize(const  char* path, const char *name);
};

/*
  控制存储。在数据超过一页的情况下，记录数据页的控制信息，类似mysql的fseg和xdes
 */
class LSUCtrl
{
public :
  static LSUCtrl *Create(const char* path, const char *name);

private:
  LSUCtrl();
  int Initialize(const char* path, const char *name);
};

#endif //_LSQL_ENGINES_LDB_LSU_H
