#ifndef _STMT_H
#define _STMT_H

#include "common.h"

class Connection;

class Statement : public Head
{
public :
  Connection *connection;
};

#endif //STMT_H
