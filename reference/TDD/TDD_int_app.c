/*
 ============================================================================
 Name        : Teste_TDD.c
 Author      : Marco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#if EXECUTE_TDD

#define THIS_FILE   "TDD_int_app.c"

#include "defin.h"
#include "general.h"
//#include "provider.h"
#include "TDD_equals.h"


/*
 * ======================= INICIO TDD  =======================================
 */



/*
 * Teste_String_Valida
 * Verifica se uma string é Valida
 * NuLL é considerada Invalida
 */
int Teste_String_Valida(void)
{
 char stringTeste[APP_MAX_STR_DEFAULT];

 //Testes TRUE
 stringTeste[0]='X';
 stringTeste[1]='Y';
 stringTeste[2]=0;
 _assert_true2(isValid_str(&stringTeste));

 stringTeste[0]='1'; //Numero
 _assert_true2(isValid_str(&stringTeste));

 //Testes FALSE

 stringTeste[0]=0;//NULL
 _assert_false(isValid_str(&stringTeste));

 //stringTeste[0]='';//Vazio
 //_assert_false(isValid_str(&stringTeste));

 stringTeste[0]='ª';
 _assert_false(isValid_str(&stringTeste));

 stringTeste[0]='@';
 _assert_false(isValid_str(&stringTeste));

 return SUCCESS;
}


/*
 * Testa A includa de TECLAS NA LISTA
 */
int Test_IncludeKey()
{
  extern struct app App_ctrl;
  char newkey[APP_MAX_STR_DEFAULT];

  //Testes NULL
  newkey[0]=0;//NULL
  _assert_null( GetKey(&newkey) );

  newkey[0]='ª';
  _assert_null( GetKey(&newkey) );


  //Inicia Tabela
  list_init(&App_ctrl.Tab_BLF_key);
  _assert_true(list_empty(&App_ctrl.Tab_BLF_key));

  //Paga tecla se nao tiver Inclui na lista
  newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;
  _assert_not_null( GetKey(&newkey) );

  _assert_equals(list_size(&App_ctrl.Tab_BLF_key),1);
  _assert_false(list_empty(&App_ctrl.Tab_BLF_key));



  //Paga tecla QUE JA TEM NA LISTA
  newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;
  _assert_not_null( GetKey(&newkey) );
  _assert_equals(list_size(&App_ctrl.Tab_BLF_key), 1);


  //Pega SEGUNDA tecla se nao tiver Inclui na lista
  newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='2';
  newkey[4]=0;
  _assert_not_null( GetKey(&newkey) );

  _assert_equals(list_size(&App_ctrl.Tab_BLF_key), 2);
  return SUCCESS;

}

/*
 * Testa A includa de TECLAS NA LISTA
 */
int Test_IncludePort()
{
  TAG_SUBSCRIBE_BLF msgTx;

  app_syslog(LOG_DEBUG,"%s-><......TESTE.....>%s()", __THIS_FILE__ );

  msgTx.IndDNSDriverIP=0;
  _assert_equals( IncludeNewDNSInKey(&msgTx), EINVALID ) ;

  msgTx.IndDNSDriverIP=99;
  _assert_equals( IncludeNewDNSInKey(&msgTx), EINVALID ) ;

  msgTx.IndDNSDriverIP=65001;
  _assert_equals( IncludeNewDNSInKey(&msgTx), EINVALID ) ;


  msgTx.IndDNSDriverIP=1000;
  msgTx.BLF_TargetSubscriber[0]=0;
  _assert_equals( IncludeNewDNSInKey(&msgTx), EINVALID ) ;


  msgTx.IndDNSDriverIP=2000;
  strcpy(&msgTx.BLF_TargetSubscriber,"2001");
  msgTx.BLF_SubscriptionExpirationTime = 500;
  /*newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;*/
  _assert_success(  IncludeNewDNSInKey(&msgTx) ) ;

  msgTx.IndDNSDriverIP=2000;
  strcpy(&msgTx.BLF_TargetSubscriber,"2001");
  msgTx.BLF_SubscriptionExpirationTime = 500;
  /*newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;*/
  _assert_success(  IncludeNewDNSInKey(&msgTx) ) ;


  msgTx.IndDNSDriverIP=2000;
  strcpy(&msgTx.BLF_TargetSubscriber,"2001");
  msgTx.BLF_SubscriptionExpirationTime = 0;
  _assert_success(  IncludeNewDNSInKey(&msgTx) ) ;

  msgTx.IndDNSDriverIP=2000;
  strcpy(&msgTx.BLF_TargetSubscriber,"2001");
  msgTx.BLF_SubscriptionExpirationTime = ' ';
  _assert_success(  IncludeNewDNSInKey(&msgTx) ) ;

 return SUCCESS;

}



/*
 * Testa A includa de TECLAS NA LISTA
 */
int Test_ExcludePort()
{
  char newkey[APP_MAX_STR_DEFAULT];
  word indice;
  TKeys *aBlfKey ;

  indice=2000;
  newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;

  aBlfKey = FindKey(&newkey);
  _assert_success(  ExcludeDNSInKey(&aBlfKey->ListIndDNS, indice) ) ;

  _assert_equals(  ExcludeDNSInKey(&aBlfKey->ListIndDNS, indice), ENEXIST ) ;

  return SUCCESS;



}


/*
 * Testa A includa de TECLAS NA LISTA
 */
int Test_ExcludeKey()
{
  extern struct app App_ctrl;
  TKeys *aBlfKey ;

 _assert_equal_void( list_erase(&App_ctrl.Tab_BLF_key), App_ctrl.Tab_BLF_key.next,App_ctrl.Tab_BLF_key.prev);
  return SUCCESS;
}


/*
 * Testa A includa de TECLAS NA LISTA
 */
int Test_ChangeStatus()
{
  char newkey[APP_MAX_STR_DEFAULT];
  word status;
  enum DirChamada dir_call;

  status=LED_INVALIDO;
  dir_call = DIR_CALL_IN;

  app_syslog(LOG_DEBUG,"%s-><......TESTE.....>%s()", __THIS_FILE__ );

  _assert_equals( ChangeStatusInKey(&newkey, status,dir_call), EINVALID ) ;

  status=65001;
  _assert_equals( ChangeStatusInKey(&newkey, status,dir_call), EINVALID ) ;




  status=LED_APAGADO;
  newkey[0]=0;
  _assert_equals( ChangeStatusInKey(&newkey, status,dir_call), EINVALID ) ;

  //Testes NULL
  newkey[0]=0;//NULL
  _assert_equals( GetStatusKey(&newkey), LED_INVALIDO ) ;



  status=LED_VERMELHO_ACESO;
  newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;
  _assert_success(  ChangeStatusInKey(&newkey, status,dir_call) ) ;

  //Valida Estado que foi gravado
  _assert_equals( GetStatusKey(&newkey), LED_VERMELHO_ACESO ) ;


  status=LED_VERDE_ACESO;
  newkey[0]='2';
  newkey[1]='0';
  newkey[2]='0';
  newkey[3]='1';
  newkey[4]=0;
  _assert_success(  ChangeStatusInKey(&newkey, status,dir_call) ) ;

  //Valida Estado que foi gravado
  _assert_equals( GetStatusKey(&newkey), LED_VERDE_ACESO ) ;


  return SUCCESS;

}


#endif //ICIP_MOD_DEBUG

