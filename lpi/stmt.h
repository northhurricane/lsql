#ifndef LSQL_LPI_STMT_H_
#define LSQL_LPI_STMT_H_

#include "common.h"

class DBConnection;

class Statement : public HandleHead
{
private :
  DBConnection *dbc_;

public :
  Statement(DBConnection *dbc);
};

lpi_return_t
lpi_allocate_stmt(DBConnection *dbc, lpi_hstmt_t *stmt);

lpi_return_t
lpi_execute_direct(Statement *stmt,
                   uint8_t *text, uint32_t length);

#endif //LSQL_LPI_STMT_H_
