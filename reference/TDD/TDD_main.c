/*
 ============================================================================
 Name        : Teste_TDD.c
 Author      : Marco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */



#define THIS_FILE   "TDD_main.c"

#include "defin.h"
#include "def_types.h"
#include "TDD_equals.h"


TDD_struct TDD_Struct;
BOOL IN_TEST=FALSE;

#if EXECUTE_TDD

int retorna_condicao(int condicao);
int retorna_soma(int primeiro_num, int segundo_num);

/*
 * Chamar este Funcao no Icicio da funcao MAIN()
 * Antes  de começar a Rodar ntro do Progrma para aplicar o TDD no codigo
*/
int ExecutaTestesIniciais(void)
{
  TDD_Struct.NumDeFuncoesTestadas   = 0;
  TDD_Struct.NumDeTestesRealizados  = 0;
  TDD_Struct.NumDeTestesFallhos     = 0;
  IN_TEST = TRUE;

  syslog( LOG_DEBUG,"-----------------------------INICIO do TDD------------------------------------------------------");

  if (ExecutaTodosOsPreTestes() == SUCCESS)
    syslog( LOG_INFO,"%s->%s(){TODOS OS [%d] TESTES PASSARAM}", THIS_FILE, __func__, TDD_Struct.NumDeTestesRealizados );
  else
    syslog( LOG_INFO,"%s->%s(){OCORRERAM [%d] FALHAS NOS [%d]TESTES REALIZADOS}", THIS_FILE, __func__, TDD_Struct.NumDeTestesFallhos, TDD_Struct.NumDeTestesRealizados );

  IN_TEST = FALSE;
  sleep(1);
  syslog( LOG_DEBUG,"-----------------------------FIM do TDD-----------------------------------------------------------");
  sleep(1);
  return SUCCESS;
}


//Chamar este Funcao dentro do Progrma para aplicar o TDD no codigo
int ExecutaTestesFinais(void)
{
  TDD_Struct.NumDeFuncoesTestadas   = 0;
  TDD_Struct.NumDeTestesRealizados  = 0;
  TDD_Struct.NumDeTestesFallhos     = 0;

  #if NOT_MAKE_TEST_RUN
  return SUCCESS ;
  #endif

  syslog( LOG_DEBUG,"-----------------------------INICIO do TDD-COM o SISTEMA RODANDO----------------------------------------------");


  if (ExecutaTodosOsPosTestes() == SUCCESS)
    syslog( LOG_INFO,"%s->%s(){TODOS OS [%d] TESTES PASSARAM}", THIS_FILE, __func__, TDD_Struct.NumDeTestesRealizados );
  else
    syslog( LOG_INFO,"%s->%s(){OCORRERAM [%d] FALHAS NOS [%d]TESTES REALIZADOS}", THIS_FILE, __func__, TDD_Struct.NumDeTestesFallhos, TDD_Struct.NumDeTestesRealizados );


  syslog( LOG_DEBUG,"----------------------------------------------------------------------------------------------------------------------");
  sleep(1);
  syslog( LOG_DEBUG,"-----------------------------FIM do TDD-COM o SISTEMA RODANDO-----------------------------------------------------------");
  sleep(1);
  return SUCCESS;
}

/*
 * REALIZA TODOS OS TESTES Antes da Aplicacao Rodar
 * Para um novo Teste Inclui aqui!!!!
 */
int ExecutaTodosOsPreTestes()
{
  //Teste 0 de Soma   
  ExecutaTestesBasicosPadrao();
  //ExecutaTestesDeFuncoesGerais();

  //-------------TESTES DA APLICAÇÂO---------------------------
  ExecutaTestesDoModApp();
  // Executa Testes MODULO NETWORK
  //ExecutaTestesDoMod_Network();
  sleep(1);
  syslog( LOG_INFO,"%s->%s()[%d]TESTES}", THIS_FILE, __func__, TDD_Struct.NumDeTestesRealizados );

  return TDD_Struct.NumDeTestesFallhos;
}

/*
 * Testes Basicos
 */
void ExecutaTestesBasicosPadrao(void)
{
  //Teste 0 de Soma
  _verify(Teste_Exemplo_soma_01);
  _verify(Teste_Exemplo_Boolean);
  _verify(Teste_Exemplo_NULL);
}


/*
 * Testes Gerais
 */
void ExecutaTestesDeFuncoesGerais(void)
{
  //Teste 0 de Soma
//  _verify(Teste_String_Valida);
//  _verify(Teste_String_includeInFile);
//  _verify(Teste_FormataStrToEndMAC);


}



/*
 * TESTES do MOdulo APP
 */
void ExecutaTestesDoModApp(void)
{
  //Teste MOdulo APP
  _verify(Teste_String_Valida);
  _verify(Test_IncludeKey);
  _verify(Test_IncludePort);
  _verify(Test_ChangeStatus);
  _verify(Test_ExcludePort);

}


/*
 * TESTES DA ICIP do Modulo Network
 * /
void ExecutaTestesDoMod_Network(void)
{
  // Executa Testes MODULO NETWORK
  _verify(Test_IPv4_IPv6);
  _verify(Test2_IPv4_IPv6);
  _verify(Test_IP_Privado);
//  _verify(Test_Refresh_DNS_NAT);
  _verify(Test_ValidaIP);
  _verify(Test_ValidaIP_2);
  _verify(Test_Qual_InterfaceDeSaidaUsar);
  _verify(Test_VLAN_load_IDs);

}


//========================== Testes a serem realizados com o Sistema rodando ===============================================



/*
 * REALIZA TODOS OS TESTES Depois que a Aplicacao Ja esta rodando
 * e Configucao Finalizada
 * Para um novo Teste Inclui aqui!!!!
 */
int ExecutaTodosOsPosTestes()
{
//  _verify(Test_Refresh_DNS_NAT_Run);
//  _verify(Test_Qual_InterfaceDeSaidaUsar_RUN);
//  _verify(Test_ValidaIP_dominio_RUN);
  sleep(1);
  return TDD_Struct.NumDeTestesFallhos;
}

/*
 * Teste Exemplo
 * Para servir de template
 */ 
int Teste_Exemplo_soma_01(void)
{
    //int x=5;
  _assert_equals(retorna_soma(-2,2), 0);
  _assert_equals(retorna_soma(2,2), 4);
  _assert_equals(retorna_soma(2,-22) , -20);
  //syslog( LOG_INFO,"%s->%s(){testa bits[0x%x] }", THIS_FILE, __func__, 512 );
  return SUCCESS;
}


/*
 * Teste Exemplo
 * Para servir de template
 */
int Teste_Exemplo_Boolean(void)
{
   //testes oks
  _assert_true(retorna_condicao(true));
  _assert_false(retorna_condicao(false));

  //testes NAO ok
  //_assert_true(retorna_condicao(false));
  //_assert_false(retorna_condicao(true));
return SUCCESS;
}


/*
 * Teste Exemplo
 * Para servir de template
 */
int Teste_Exemplo_NULL(void)
{
   //testes oks
  _assert_null(retorna_condicao(NULL));
  _assert_not_null(retorna_condicao(true));
  _assert_null(retorna_condicao(-1));
//  _assert_null(retorna_condicao(6));

return SUCCESS;
}


/*
 * Funceos usada para testar o template
 */
int retorna_soma(int primeiro_num, int segundo_num)
{
  return( primeiro_num + segundo_num );
}


/*
 * Funceos usada para testar o template
 */
int retorna_condicao(int condicao)
{
  return condicao;
}



/*
 * Testa mensagem de LOG De Falha==NULL  
 */
int TestaMensagemDeLogFalha()
{
  int result_test=0;
  //_assert(print_syslog_teste() == SUCCESS);
  _assert_equal_void( FAIL_SYSLOG(), SUCCESS, SUCCESS);
 return SUCCESS;
}


/*---------------------------------------------------------------------------
 * How to use
 *---------------------------------------------------------------------------/

*
#include <stdio.h>
#include <stdlib.h>
#include "TDD_equals.h"

#define THIS_FILE   "TDD_main.c"

*
 * main() - Entrada do programa - Processo VoIP
 * /
int main(void)
{
  int status, i;//, AcStatus;


  ExecutaTestesIniciais();

  //. Put your code's system here.....
  // .
  //.
  //.
  //. End code's system.
  //Executa TESTE

  ExecutaTestesFinais();


  //Daemonize();
  while (1)
    {
     //loop
    }

  return 1;
}
*/

#endif //ICIP_MOD_DEBUG
