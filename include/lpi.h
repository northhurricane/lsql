#ifndef _LPI_H
#define _LPI_H

/*
  LPI interface defination reference ODBC/OCI/DM DPI, but it mainly follow ODBC style. I think it is easier to understand (at least for me :P).
*/

#include <stdint.h>

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
lpi_connect(lpi_hdbc_t connectino_handle,
            uint8_t *server, uint32_t server_length,
            uint8_t *user_name, uint32_t user_name_length,
            uint8_t *pass_word, uint32_t pass_word_length);

DllExport lpi_return_t lpi_disconnect(lpi_hdbc_t connectino_handle);

DllExport lpi_return_t
lpi_execute_direct(lpi_hstmt_t statement_handle,
                 uint8_t *statement_text, uint32_t text_length);

#ifdef __cplusplus
}                                    /* End of extern "C" { */
#endif  /* __cplusplus */

#endif //_LPI_H
