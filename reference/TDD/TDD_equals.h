/*
 ============================================================================
 Name        : TDD_equals.c
 Author      : Marco
 Version     : 1.00.00
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef __TDD_MAIN_H__
#define __TDD_MAIN_H__

//Includes
#include "TDD_configs.h"

//Defines Structs
typedef struct
{
  const char* Func_name;
  int Line_code;
  int File_name;
  int NumDeTestesRealizados;
  int NumDeFuncoesTestadas;
  int NumDeTestesFallhos;

} TDD_struct;    //< Tipo de dados usados para Sinalização BLF dos ramais


extern TDD_struct TDD_Struct;

//int retorna_condicao(int condicao);

//FUNCOES
#define _() TDD_Struct.Func_name=__func__; TDD_Struct.Line_code=__LINE__ ;  TDD_Struct.File_name=THIS_FILE;


#if STOP_FIRST_ERROR
#define _verify(test) do { int result=test(); TDD_Struct.NumDeTestesRealizados++; if(result) {NumDeTestesFallhos++; return result;} } while(0)
#else //STOP_FIRST_ERROR
#define _verify(test) do { int result=test(); TDD_Struct.NumDeTestesRealizados++; if(result) TDD_Struct.NumDeTestesFallhos++; } while(0)
#endif


/*
 * Asserts Para Numeros Inteiros
 */

#define _assert_equals(test,retval) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) == retval) \
        OK_SYSLOG(); \
      else \
        { \
    	  FAIL_SYSLOG(); \
          return ERROR; \
        } \
     } while(0)



#define _assert_notEquals(test,retval) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) != retval) \
        OK_SYSLOG(); \
      else \
        { \
    	  FAIL_SYSLOG(); \
          return ERROR; \
        } \
     } while(0)


/*
 * Asserts Para BOOLEAN
 */
#define _assert_true(test) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) == TRUE) \
        OK_SYSLOG(); \
      else \
        { \
    	  FAIL_SYSLOG_BOOL(); \
          return ERROR; \
        } \
     } while(0)


#define _assert_false(test) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) == FALSE) \
        OK_SYSLOG(); \
      else \
        { \
    	  FAIL_SYSLOG_BOOL(); \
          return ERROR; \
        } \
     } while(0)

/*
 * Caso For maior Igual ou Maior que 1 (TRUE)
 * Tambem retorna TRUE
 */
#define _assert_true2(test) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) >= TRUE) \
        OK_SYSLOG(); \
      else \
        { \
    	  FAIL_SYSLOG_BOOL(); \
          return ERROR; \
        } \
     } while(0)


#define _assert_null(test) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) <= 0 ) \
        OK_SYSLOG(); \
      else \
        { \
          FAIL_SYSLOG(); \
          return result_test; \
        } \
     } while(0)


#define _assert_not_null(test) \
  do {\
      _(); \
      long result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) > NULL) \
        OK_SYSLOG(); \
      else \
        { \
          FAIL_SYSLOG(); \
          return result_test; \
        } \
     } while(0)

/*
 * Asserts Para Strings
 */

#define _assert_equals_strings(test,retval) \
  do {\
      _(); \
      int result_test=strcmp(test,retval); TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) == 0) \
        OK_SYSLOG(); \
      else \
        { \
          FAIL_SYSLOG(); \
          return result_test; \
        } \
     } while(0)


#define _assert_not_equals_strings(test,retval) \
  do {\
      _(); \
      int result_test=strcmp(test,retval); TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) != 0) \
        OK_SYSLOG(); \
      else \
        { \
          FAIL_SYSLOG(); \
          return result_test; \
        } \
     } while(0)



/*
 * Execute a void Function or a Procedure
 */
#define _assert_equal_void(run_func, comp_var, expected_val) \
  do {\
      _(); run_func;\
      int result_test=comp_var; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) == expected_val) \
        OK_SYSLOG(); \
      else \
        { \
          FAIL_SYSLOG(); \
          return ERROR; \
        } \
     } while(0)

/*
 * Execute a void Function or a Procedure
 */
#define _assert_notEqual_void(run_func, comp_var, expected_val) \
  do {\
      _(); run_func;\
      int result_test=comp_var; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) != expected_val) \
        OK_SYSLOG(); \
      else \
        { \
          FAIL_SYSLOG(); \
          return ERROR; \
        } \
     } while(0)

/*
 * OK se funç~ao retornart SUCCESS
 */
#define _assert_success(test) \
  do {\
      _(); \
      int result_test=test; TDD_Struct.NumDeTestesRealizados++; \
      if ( (result_test) == SUCCESS) \
        OK_SYSLOG(); \
      else \
        { \
    	  FAIL_SYSLOG(); \
          return ERROR; \
        } \
     } while(0)



#endif /* __TDD_MAIN_H__ */





