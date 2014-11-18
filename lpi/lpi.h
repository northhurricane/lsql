#ifndef LSQL_LPI_H_
#define LSQL_LPI_H_

/*
  LPI interface defination reference ODBC/OCI/DM DPI, but it mainly follow ODBC style. I think it is easier to understand (at least for me :P).
*/

#include <stdint.h>
#include <lpidef.h>

#ifdef __WINDOWS__
#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )
#else
#define DllImport
#define DllExport
#endif

typedef int32_t lpi_return_t;
typedef void *lpi_handle_t;
typedef void *lpi_henv_t;
typedef void *lpi_hdbc_t;
typedef void *lpi_hstmt_t;
typedef void *lpi_hdesc_t;

typedef uint8_t lpi_char_t;
typedef int32_t lpi_length_t;
typedef void*   lpi_pointer_t;

#define LPI_SUCCESS                0
#define LPI_SUCCESS_WITH_INFO      1
#define LPI_NO_DATA                100
#define LPI_ERROR                  (-1)
#define LPI_INVALID_HANDLE         (-2)

#define LPI_NULL     (0)

#define LPI_HANDLE_ENV             1
#define LPI_HANDLE_DBC             2
#define LPI_HANDLE_STMT            3
#define LPI_HANDLE_DESC            4

#ifdef __cplusplus
extern "C" { /* Assume C declarations for C++   */
#endif  /* __cplusplus */

DllExport lpi_return_t
lpi_allocate_handle(int16_t handle_type, lpi_handle_t input_handel,
                  lpi_handle_t *output_handle);

DllExport lpi_return_t
lpi_alloc_env(lpi_henv_t* env);

DllExport lpi_return_t
lpi_alloc_dbc(lpi_henv_t env, lpi_hdbc_t *dbc);

DllExport lpi_return_t
lpi_alloc_stmt(lpi_hdbc_t dbc, lpi_hstmt_t *stmt);

DllExport lpi_return_t
lpi_set_dbc_attr(lpi_hdbc_t dbc, int32_t attr, lpi_pointer_t value, int32_t length);

DllExport lpi_return_t
lpi_connect(lpi_hdbc_t dbc,
            lpi_char_t *server, int32_t server_length,
            lpi_char_t *user_name, int32_t user_name_length,
            lpi_char_t *pass_word, int32_t password_length);

DllExport lpi_return_t lpi_disconnect(lpi_hdbc_t dbc);

DllExport lpi_return_t
lpi_exec_direct(lpi_hstmt_t stmt,
                 lpi_char_t *text, int32_t length);

#ifdef __cplusplus
}                                    /* End of extern "C" { */
#endif  /* __cplusplus */

#endif //LSQL_LPI_H_
