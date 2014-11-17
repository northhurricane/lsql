#ifndef _STMT_H
#define _STMT_H

#include "common.h"

class DBConnection;

class Statement : public Head
{
public :
  DBConnection *dbc_;
};

#endif //STMT_H
