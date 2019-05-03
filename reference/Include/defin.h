/******************************************************************* *
 *    Descrição: Defines para ICIP - Aplicação VoIP
 *
 *    Autor: Marco Antonio Vargas
 *
 *    Data:22/07/2008
 *******************************************************************/

#ifndef DEFIN_H_
#define DEFIN_H_


// Includes.
#include <syslog.h>
#include <sys/socket.h>
#include "def_enum.h"

//static const char STR_COMMAND_NEW_STATUS[] = { "Command: new_status\r\n" };


#define         MAX_TYPE_ACCEPT         3 //Numero maximo de Tipos de suscribe

#define  SIZE_NIBBLE_BIT  4

#define  SIZE_BOOL      1
#define  SIZE_BYTE      1
#define  SIZE_WORD      2
#define  SIZE_DWORD     4

#define  NUM_BITS_BYTE   8
#define  NUM_BITS_WORD   16

//---------------------- DEFINES ----------------------------------
//Defines de Versao
#define _VER_SOFT    "18"     //Versao da Aplicação VOIP - ANO
#define _REV_SOFT    "07"     //Revisao da Aplicação VOIP - MES
#define _REL_SOFT    "04"    //RELEASE Aplicação VOIP - DIA
//#define _V_DBG_SOFT  "DBG"  //Versao da Aplicação ICIP Modo DEBUG

#if MOD_DEBUG
  #define LEVEL_LOG   3
#else //MODO RELEASE
  #define LEVEL_LOG   1
#endif //ICIP_MOD_DEBUG

#define   SUCCESS       0               // Status está OK.
#define   ERROR	       -1               // ERRO

#define ERRNO_START      20000
#define ECANCELLED       (ERRNO_START + 14)/* 20014 */
#define EINVALID         (ERRNO_START + 15)/* 20014 */
#define ENEXIST          (ERRNO_START + 16)/* 20014 */

//Usado em váriaveis Bool
#define   true          1               //Verdadeiro
#define   false         0               //Falso
#define   TRUE	        1               //Verdadeiro
#define   FALSE         0               //Falso
#define   ON	        1               //Ligado
#define   OFF	        0               //Desligado
#define   LOOP	        1               //Loop
#define   FAIL          0xFA            //FALHA

#define   INVALID_RTP_PORT 0xFFFF


//Ficou definido casa dos 10 prioridade blf_ctrl
//QUANTO MAIS ALTO MAIOR PRIORIDADE
#define   THREAD_PRIO_BASE         10  //Prioridade BASE das threads da ICIP
#define   THREAD_PRIO_MAIN         THREAD_PRIO_BASE+0  //Prioridade BASE das threads da ICIP
#define   THREAD_PRIO_PABXCOM THREAD_PRIO_BASE+1  //Prioridade da thread  do socket de comunicação com o PABX
//Defines de compilação do Código
#define   SHOW_PID_THERAD                   0    //Mostra Numero do PID da THREAD

//.................. DEFINICOES DE TESTE DE IP ..............................................
  //1 Ativa o novo modo de definir o IP que será Usado pela placa ICIP em cada Chamada
#define   TESTE_IP_NOK                       0    //Teste NOK
#define   TESTE_IP_OK                        1    //Teste OK
#define   TESTE_IP_TESTANDO                  2    //Teste OK

#define KILL_NOT   0
#define KILL_NOW   1
#define KILL_WAIT  2

//1% - 450
#define MAX_MEMO_TO_KILL_WAIT   15000//(30*500)  //30%
#define MAX_MEMO_TO_KILL_NOW    17500//(35*500)  //35%

//Defines de Log
//#define   SHOW_LOGGER                       1    // ATIVA LOGGER 1 SHOW LOGGER copia dados para o syslog
#define   LOG_PRINTF                        0    // 1 Modo mostra os printf do syslog Para Tudo
#define   SHOW_FRM_TO_PABXCOMM              0    // Mostra Log de mensgens enviadas pelo socket PABXCOMM
#define   SHOW_FRM_FROM_PABXCOMM            0    // Mostra mensagens recebidas do pabxcomm via socket


//#define   IP_LOCAL_HOST                 "127.0.0.1"
//#define   SIP_DEFAULT_PORT	        5060
#define   ERR_ADDR_IN_USE                 120098       //Address Already In USe


//  Defines das TAGS das Mensagens
#define   APP_MAX_NOME_VERSAO            16
#define   APP_MAX_DATA_BROADCAST          10
#define   APP_MAX_STATUS_DEVICE          52
#define   APP_MAX_NOME_PORTA             11
#define   APP_MAX_NOME_PORTA_2           12
#define   APP_MAX_STR_DEFAULT            50
#define   APP_MIN_INDEX                  100
#define   APP_MAX_INDEX                  65000
#define   EXPIRATION_DEFAULT             690
/*
#define   ICIP_MAX_NOME_OP                20
#define   ICIP_MAX_SENHA_LOGIN            52
#define   ICIP_MAX_CANAL                  80
#define   ICIP_MAX_CANAL_HIGHWAY          4
#define   ICIP_HIGHWAY_SLOTS              32

#define   ICIP_MAX_IP_DOMAIN              51
#define   ICIP_MAX_IP_DOMAIN_1            48
#define   ICIP_MAX_IP_DOMAIN_2            52
#define   ICIP_MAX_CODEC_OPT              16
#define   ICIP_MAX_SENHA_PROXY            65 //27
//#define   ICIP_MAX_SENHA_PROXY2           14
#define   ICIP_MAX_SIST_NOME              20
#define   ICIP_TAM_VOIP_REG_STATUS        33
#define   ICIP_MAX_NOME_EXTERNO           20
#define   ICIP_MAX_NOME_DISCADO           25
#define   ICIP_MAX_NUM_OP_CODEC           7+1  //Mais 1 Referente ao rmap do ruido de conforto
#define   ICIP_MAX_CAPACIDADE_REQ         4
#define   ICIP_MAX_NOME_DEVICE_TYPE       22
#define   UNNIT_TAM_STR_AUX_TMP           6
//#define   ICIP_MAX_STR_ENDERECO_MAC       22
#define   UNNITI_MAX_STR_ENDERECO_MAC     18
#define   ICIP_MAX_NUM_IPS_VAL            16
#define   ICIP_UM_MINUTO                  60
#define   SIZE_MAX_URI                    120//8080
#define   SIZE_MAX_URI_ADDR               60
#define   SIZE_MAX_HEADER                 120
#define   SIZE_MAX_BODY                   350
#define   SIZE_STR_DEFAULT                20
#define   ICIP_VAGO_43                    43
#define   ICIP_VAGO_26                    26
#define   ICIP_VAGO_3                     3
#define   ICIP_VAGO_38                    38
#define   ICIP_MAX_PEER_STUN              1
#define   ICIP_MAX_NOME_TYPE              10
#define   ICIP_MAX_STR_WRITER             500
//Defines Usados no BLF
#define   ICIP_MAX_STR_BLF                21
//Defines Usados na VLANs
#define   ICIP_MAX_VLANS                  5
#define   ICIP_MAX_ID_VLAN                8
#define   ICIP_MAX_NAME_VLAN              20
#define   MAX_SIZE_LINE_FILE              120
#define   SIZE_ADDR_IPV4_MIN              8               // tamanho minimo de um endereço IPv4 válido

#define   APP_MAX_DATA_BROADCAST          10

#define   ICIP_MAX_SMS_TEXT               161
#define   ICIP_MD5_RESULT_SIZE            16
#define   ICIP_MAX_CRITIC_ERROR           10
#define   ICIP_ACQUIRE_CALL_TIMEOUT       2000  //2000 milisegundos

#define   DEF_STATUS_NULL                  0
#define   DEF_STATUS_SEM_CAT               1
#define   DEF_STATUS_ENVIADA               2
#define   DEF_STATUS_SEM_CANAL_DISPONIVEL  3

#define   VOIPGEN_VOIP_FAX_DISABLE        0
#define   VOIPGEN_VOIP_FAX_T38            1
#define   VOIPGEN_VOIP_FAX_BYPASS         2
#define   VOIPGEN_VOIP_DATA_BYPASS        3//100

#define   VOIPGEN_JITTER_BUFFER_STATIC    TRUE

#define   ICIP_DOMINIO_DEFAULT            "unniti"
#define   ICIP_DESPERTADOR                "DESPERTADOR"
#define   ICIP_PABX                       "PABX"
#define   ICIP_INIT_REG                   "Init_Register"
#define   ICIP_INIT_REG_STS               " sts=Init_Register\x0"
static   const pj_str_t STR_INIT_REG = { ICIP_INIT_REG, strlen(ICIP_INIT_REG) };
*/

/*
//Define tipos de Caracteres
#define CARACTER_FLASH          '§'
#define CARACTER_FLASH_HEX      0xA7
#define CARACTER_FIMDISC         '#'
#define CARACTER_SEP_BINA_TRANSF '#' // separador para Bina em transferencia (Numero Externo  #  Ramal)

#define STR_SEP_PORT     ":" // separador de IP e Porta UDP/TCP(10.0.0.3:5060)
#define CHAR_SEP_PORT    ':' // separador de IP e Porta UDP/TCP(10.0.0.3:5060)
#define TAG_IP6_CHAR     ':'
#define TAG_END_URI      '>'
*/

//#define CARACTER_SEP_NAME_NUMBER ':' // separador para Nome e Numero de apt Para o Poerteiro Remote(nome:NUmero)

//#define PJMEDIA_RTP_PT_NULL     0x0FF
//#define ICIP_RTP_PT_G726_16   23
//#define ICIP_RTP_PT_G726_24   22
//#define ICIP_RTP_PT_G726_32   2
//#define ICIP_RTP_PT_G726_40   21

//#define SET_DATA_FW_SOCKET              40041620
//#define CLOSE_DATA_FW_SOCKET            40041621

#define   EMPTY                        -1
#define   CANAL_VAGO                   0xFF
#define   OFFSET_EST                   0

#define   SWAP_BYTE(Data) 	      ((Data >> 8) & 0xFF) | ((Data & 0xFF) << 8);

#define MIN_(var,val)    ((int)val < (int)var) ? val : var
#define msleep_(mseg)    usleep(mseg*1000)


//a Variavel var-max sempre é o limiteSe
//#define POS_FIM_STRING_( var, var_max) ((int)var_max <= (int)var) ? (var_max-1) : var
#define POS_FIM_STRING_( var, var_max) ((int)var < (int)var_max) ? var : (var_max-1)

//Cuidado este define vai pagar o nome do arquivo e funcao aonde for chamado
#define __THIS_FILE__ THIS_FILE, __func__

#endif /*DEFIN_H_*/

