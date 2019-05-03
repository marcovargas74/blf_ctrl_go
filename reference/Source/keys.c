/********************************************************************
 *    Descrição: Funções referentes a manipulações de Lista
 *    			 encadeadas.
 *
 *    Autor: Marco Antonio Vargas
 *
 *    Data:28/03/2018
 *******************************************************************/

#include "lists.h"
#include "keys.h"
#include "def_types.h"

#define THIS_FILE   "keys.c"


//Declaração de Váriaveis externas
extern Status_VoIP  StatusVoIP;
extern struct app App_ctrl;

//---------------CONFIGURAÇÂOES ENVIADAS PELO PABX -------------
TKeys     *NovaTeclaBLF;
TypePortDNS  *NovaPortaDNS;
//---------------------------------------------------------------

/*
 * compara tecla por nome
 */
int comparaKeysName(void *value, const void *nd)
{
  TKeys *reg1 = (TKeys *)nd;     //Este objeto esta na Lista
  //app_syslog(LOG_DEBUG, "%s->%s()<key_val>[%s]<key_list>[%s]<RESULT>[%d] ", __THIS_FILE__, value, reg1->key_name, strcmp(value, reg1->key_name) );
  //msleep_(100);
  return (  strcmp(value, reg1->key_name) );
}

/*
 * Compara Ramal/Junotr pelo DNS
 */
int ComparaDNSPort(void *value, const void *nd)
{
  TypePortDNS *reg1 = (TypePortDNS *)nd;     //Este objeto esta na Lista
  //icip_syslog(LOG_DEBUG, "%s->%s()<key_val>[%d]<port_rtp>[%d]", __THIS_FILE__, value, reg1->port_RTP );
  //msleep_(100);
  return ( (word)value == reg1->IndiceDNS ) ? SUCCESS : 1;
}


/*
 * Apesar de Void Retorna uma TKEY
 */
void *GetKey(char *nameKey)
{

  if ( !isValid_str(nameKey)  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){name Port is Invalid!}", __THIS_FILE__ );
      return NULL;
    }

  NovaTeclaBLF = findKey(nameKey);
  if(NovaTeclaBLF != NULL)
    {
      app_syslog(LOG_DEBUG,"%s->%s(){Key_exist}<index>[%d]", __THIS_FILE__, NovaTeclaBLF->Index );
      return ( (TKeys*)NovaTeclaBLF );
    }

  NovaTeclaBLF = malloc( sizeof(TKeys) );  //cria um novo objeto (aloca memória)
  if (NovaTeclaBLF == NULL)
    {
      StatusVoIP.ErrorAlloc++ ;   // Incrementa contador de erro
      app_syslog(LOG_ERR,"%s->%s(){ERROR_MALLOC}", __THIS_FILE__ );
      return NULL;
    }

//  memset(&NovaTeclaBLF,0, sizeof(TKeys));
  list_init(&NovaTeclaBLF->ListIndDNS);
  app_strncpy(&NovaTeclaBLF->key_name, nameKey, APP_MAX_NOME_PORTA);
  NovaTeclaBLF->status_blf = LED_VERDE_ACESO;
  NovaTeclaBLF->Index = ++App_ctrl.sizeKey;
  list_push_back(&App_ctrl.Tab_BLF_key, NovaTeclaBLF);

  app_syslog(LOG_DEBUG,"%s->%s(){KEY_INCLUDE!}<new_key>[%s]<list_size>[%d]", __THIS_FILE__, NovaTeclaBLF->key_name, list_size(&App_ctrl.Tab_BLF_key) );
  return ( (TKeys*)NovaTeclaBLF );
}//


/*
 * Só usar na Funcao GetKey
 * Pois ele nao faz Validacao do nome da TKEY
 */
void *findKey(char *nameKey)
{
 TKeys *find_node ;

 if(list_empty(&App_ctrl.Tab_BLF_key))
   return NULL;

 find_node = (TKeys*) list_search(&App_ctrl.Tab_BLF_key, (void*)(char*)nameKey, &comparaKeysName);
 return find_node;
}

/*
 * Apesar de Void Retorna uma TKEY
 */
void *FindKey(char *nameKey)
{
 TKeys *find_node ;

 if(list_empty(&App_ctrl.Tab_BLF_key))
   return NULL;

 if ( !isValid_str(nameKey)  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){name Port is Invalid!}", __THIS_FILE__ );
      return NULL;
    }

 find_node = (TKeys*) list_search(&App_ctrl.Tab_BLF_key, (void*)(char*)nameKey, &comparaKeysName);
 return find_node;
}


/*
 * SE nao È novo Reotrna TRUE
 */
int isNewBLFInList(char *nameKey)
{
 TKeys *find_node ;

 if(list_empty(&App_ctrl.Tab_BLF_key))
   return TRUE;

 if ( !isValid_str(nameKey)  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){name Port is Invalid!}", __THIS_FILE__ );
      return FALSE;
    }

 //app_syslog(LOG_DEBUG,"%s->%s()<find_key>[%s]", __THIS_FILE__, nameKey );
 find_node = (TKeys*) list_search(&App_ctrl.Tab_BLF_key, (void*)(char*)nameKey, &comparaKeysName);
 return (find_node != NULL) ? FALSE : TRUE;
}



/*
 * Inclui um Ramal/Juntor na Lista da Tecla
 * Isso srá usado para enviar o status da tecla
 * Quando mudar de STATUS
 */
int IncludeNewDNSInKey(TAG_SUBSCRIBE_BLF *ptr_blfdata)
{
  TKeys *aBlfKey ;

  /*This part already done previosly
  if ( (ptr_blfdata->IndDNSDriverIP < APP_MIN_INDEX ) || ( ptr_blfdata->IndDNSDriverIP > APP_MAX_INDEX  ) )
    {
      app_syslog( LOG_WARNING,"%s->%s(){index[%d] Invalid!}", __THIS_FILE__, ptr_blfdata->IndDNSDriverIP );
      return EINVALID;
    }*/

  aBlfKey = GetKey(&ptr_blfdata->BLF_TargetSubscriber);
  if ( aBlfKey == NULL  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){KEY Invalid!}<index>[%d]", __THIS_FILE__, ptr_blfdata->IndDNSDriverIP );
      return EINVALID;
    }

  if ( isInListPort(&aBlfKey->ListIndDNS, ptr_blfdata->IndDNSDriverIP)  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){DNS exist in KEY LIST!}<index>[%d]", __THIS_FILE__, ptr_blfdata->IndDNSDriverIP );
      if (!ptr_blfdata->BLF_SubscriptionExpirationTime)
        ExcludeDNSInKey(&aBlfKey->ListIndDNS, ptr_blfdata->IndDNSDriverIP);

      return SUCCESS;
    }

  NovaPortaDNS = malloc( sizeof(TypePortDNS) );  //cria um novo objeto (aloca memória)
   if (NovaPortaDNS == NULL)
     {
       StatusVoIP.ErrorAlloc++ ;   // Incrementa contador de erro
       app_syslog(LOG_ERR,"%s->%s(){ERROR_MALLOC}", __THIS_FILE__ );
       return NULL;
     }

  NovaPortaDNS->IndiceDNS = ptr_blfdata->IndDNSDriverIP;
  NovaPortaDNS->position = ptr_blfdata->Position;
  NovaPortaDNS->selelect = ptr_blfdata->Select;
  NovaPortaDNS->expiration= ptr_blfdata->BLF_SubscriptionExpirationTime;

  list_push_back(&aBlfKey->ListIndDNS, NovaPortaDNS);

  app_syslog(LOG_DEBUG,"%s->%s(){OK}<key>[%s]<dns>[%d]", __THIS_FILE__, aBlfKey->key_name, ptr_blfdata->IndDNSDriverIP );
  return SUCCESS;
}



/*
 * Porta está na Lista
 */
int isInListPort(void *list, word index)
{
  TypePortDNS *find_node ;

  if(list_empty(list))
    return FALSE;

  find_node = (TypePortDNS*) list_search(list, (void*)(word*)index, &ComparaDNSPort);
  return (find_node != NULL) ? TRUE : FALSE;
}


/*
 * Inclui um Ramal/Juntor na Lista da Tecla
 * Isso srá usado para enviar o status da tecla
 * Quando mudar de STATUS
  LED_APAGADO        = 0,     // off
  LED_VERMELHO_ACESO = 1,     // confirmed
  LED_VERDE_ACESO    = 2,     // terminated
  LED_VERMELHO_PISCA = 3,     // early
  LED_INVALIDO       = 0xFFFF   //Erro de Leitura
 */
int ChangeStatusInKey(char *nameKey,  word newStatus, enum  DirChamada directionCall)
{
  TKeys *aBlfKey ;

  if ( newStatus > LED_VERMELHO_PISCA  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){status[%d] Invalid!}", __THIS_FILE__, newStatus );
      return EINVALID;
    }

  aBlfKey = GetKey(nameKey);
  if ( aBlfKey == NULL  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){KEY Invalid!}<index>[%d]", __THIS_FILE__, newStatus );
      return EINVALID;
    }

  aBlfKey->status_blf=newStatus;
  aBlfKey->BLF_DirectionCall=directionCall;
  app_syslog(LOG_DEBUG,"%s->%s(){OK}<key>[%s]<status>[%d]", __THIS_FILE__, aBlfKey->key_name, aBlfKey->status_blf );
  SendToPortsChangeStatus(aBlfKey);

  return SUCCESS;
}

/*
 * Isso srá usado para enviar o status da tecla
 * Quando mudar de STATUS
 */
word GetStatusKey(char *nameKey)
{
  TKeys *aBlfKey ;

  aBlfKey = FindKey(nameKey);
  if ( aBlfKey == NULL  )
    {
      app_syslog( LOG_WARNING,"%s->%s(){KEY Invalid!}", __THIS_FILE__ );
      return LED_INVALIDO;
    }

  app_syslog(LOG_DEBUG,"%s->%s(){OK}<key>[%s]<status>[%d]", __THIS_FILE__, aBlfKey->key_name, aBlfKey->status_blf );
  return aBlfKey->status_blf;
}


/*
 * Vare Lista e envia mudanca de status para
 * As Portas(RAMAIS/JUNTORES).
 */
void SendToPortsChangeStatus(TKeys *pt_BlfKey)
{
  TypePortDNS *sendDNS_node ; //No principal
  TypePortDNS *next_node;
  if ( list_empty(&pt_BlfKey->ListIndDNS) )
     return;

  sendDNS_node = pt_BlfKey->ListIndDNS.next; //Pega o Primeiro no da lista
   while (sendDNS_node != (TypePortDNS*)&pt_BlfKey->ListIndDNS) //Enquanto O proximo nó for diferente do atual
     {
       next_node = sendDNS_node->next;
       if(sendDNS_node != NULL)
         FrmNotifySEND(sendDNS_node->IndiceDNS, pt_BlfKey);

       sendDNS_node = next_node;
     }

}


/*
 * Exclui um Ramal/Juntor da Lista da Tecla
 */
int ExcludeDNSInKey(void *list, word index)
{
  TypePortDNS *find_node ;

  /*if ( (index < APP_MIN_INDEX ) || ( index > APP_MAX_INDEX  ) )
    {
      app_syslog( LOG_WARNING,"%s->%s(){index[%d] Invalid!}", __THIS_FILE__, index );
      return EINVALID;
    }*/

  if(list_empty(list))
    return ENEXIST;

  find_node = (TypePortDNS*) list_search(list, (void*)(word*)index, &ComparaDNSPort);
  if (find_node != NULL)
    {
      app_syslog(LOG_DEBUG, "%s->%s()<port>[%d]<sizeList>[%d]", __THIS_FILE__, index, list_size(list) );
      list_erase(find_node);
      mem_free(find_node);
    }

  return SUCCESS;
}


/*
 * Faz uma vareedura e envia para o PABX
 * Para manter os estados ativos
 */
void Resfresh_status(void)
{
  TKeys *key_node ; //No principal
  TKeys *next_node;

  if(list_empty(&App_ctrl.Tab_BLF_key))
    return;

  key_node = App_ctrl.Tab_BLF_key.next; //Pega o Primeiro no da lista
  while (key_node != (TKeys*)&App_ctrl.Tab_BLF_key) //Enquanto O proximo nó for diferente do atual
    {
      next_node = key_node->next;
      if(key_node != NULL)
        {
          app_syslog(LOG_DEBUG, "%s->%s()<key>[%s]", __THIS_FILE__, key_node->key_name );
          FrmSubscribeRefresh_TOPABX (key_node);
          msleep_(200);
        }

      key_node = next_node;
    }

}

/*
 * Exclui ponteiro do sub na lista
 * /
BOOL excludeKey( char *nameKey)
{
  TKeys *key_node ; //No principal
  TKeys *next_node;

  if(list_empty(&App_ctrl.Tab_BLF_key))
    return SUCCESS;

  if ( !isValid_str(nameKey)  )
     {
       app_syslog( LOG_WARNING,"%s->%s(){name Port is Invalid!}", __THIS_FILE__ );
       return FALSE;
     }


  key_node = App_ctrl.Tab_BLF_key.next; //Pega o Primeiro no da lista
  while (key_node != (TKey*)&App_ctrl.Tab_BLF_key) //Enquanto O proximo nó for diferente do atual
    {
      TKeys *next_node = key_node->next;
      if(key_node != NULL)
         mem_free(key_node);

      key_node = next_node;
    }

  return SUCCESS ;
}
*/

