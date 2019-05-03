/*
 ============================================================================
 Name        : TDD_configs.c
 Author      : Marco
 Version     :
 Copyright   : Your copyright notice
 Description : Editar este arquivo para se tornar compativel
               com o sistema onde os teste iram ser executados
 ============================================================================
 */

#ifndef __TDD_CONFIGS_H__
#define __TDD_CONFIGS_H__

//Includes exclusicas do sistemas
//#include "defin.h"
///#include "general.h"
//#include "provider.h"
//#include <stdio.h>
//#include <stdlib.h>


//Declaracao de variaveis  exclusicas do sistemas
//extern const char* func;
//extern int line;
//extern int File_name;
//extern int NumDeTestesRealizados;


//Definicoes de configuracoes Dos testes
#define DEFIN_DEFAULT     0    //Definicoes padrao do TDD_
#define PRINT_MENSAGEM_OK 0
#define PRINT_SYSLOG      1    //Tipo de Print Syslog ou Print
#define STOP_FIRST_ERROR  0    //Para na Primeira ocorrencia de falha
#define NOT_MAKE_TEST_RUN 1    // NAo roda os teste quando sistema estiver Rodando
#define ERROR             1    //Retorna ERRO no Caso dos Bollean ou valores igual a zero
#define SUCCESS           0    //Retorna SUCCESSO


#if DEFIN_DEFAULT
//Definicoes exclusivas do sistema
//MENSAGENS DE LOG PADRAO
#define FAIL_SYSLOG()       printf("!!!!Teste Failure_FUNC!!!! in [%s->%s()] line[%d] return[%d]",  TDD_Struct.File_name, TDD_Struct.Func_name, TDD_Struct.Line_code, result_test)
#define FAIL_SYSLOG_BOOL()  printf("!!!!Teste BOOLEAN Failure!!!! in [%s->%s()] line[%d] return[%s]",  TDD_Struct.File_name, TDD_Struct.Func_name, TDD_Struct.Line_code, result_test ? "TRUE": "FALSE")

#if PRINT_MENSAGEM_OK
#define OK_SYSLOG()  printf("\n%s() line %d : Test_OK", TDD_Struct.Func_name, TDD_Struct.Line_code)
#else
#define OK_SYSLOG()  continue
#endif //DEFIN_DEFAULT


#else //#if DEFIN_DEFAULT



// DEFINICOES DE SAIDA DO RESULTADO DOS TESTES
#if PRINT_MENSAGEM_OK
#define OK_SYSLOG()  syslog( LOG_DEBUG,"[%s->%s()] line %d : Test_OK", TDD_Struct.File_name, TDD_Struct.Func_name, TDD_Struct.Line_code)
#else
#define OK_SYSLOG()  continue
#endif

#define FAIL_SYSLOG()      syslog( LOG_CRIT,"!!!!Teste Failure_FUNC!!!! in [%s->%s()] line[%d] return[%d]",  TDD_Struct.File_name, TDD_Struct.Func_name, TDD_Struct.Line_code, result_test)
#define FAIL_SYSLOG_BOOL() syslog( LOG_CRIT,"!!!!Teste BOOLEAN Failure!!!! in [%s->%s()] line[%d] return[%s]",  TDD_Struct.File_name, TDD_Struct.Func_name, TDD_Struct.Line_code, result_test ? "TRUE": "FALSE")


#endif //#if DEFIN_DEFAULT



#endif /* __TDD_CONFIGS_H__ */





