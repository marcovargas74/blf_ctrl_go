/********************************************************************
 *    Descrição: Funções de uso Geral
 *
 *    Autor: Marco Antonio Vargas
 *
 *    Data:02/07/2019
 *******************************************************************/

package general

import (
	"fmt"
	"io"
	"log"
	"log/syslog"
	"runtime"
	"strings"

	"github.com/marcovargas74/blf_ctrl_go/includes"
)

//AppLog Variavel usado no syslog
var AppLog io.Writer

//StartGeneral é a mensagem de inicio do pacote General
func StartGeneral() {
	fmt.Println("genneral")
}

// ThisFunction return a string containing the file name, function name
// and the line number of a specified entry on the call stack
//func ThisFunction(depthList ...int) string {
func ThisFunction() string {
	/*var depth int
	if depthList == nil {
		depth = 1
	} else {
		depth = depthList[0]
	}
	function, file, line, _ := runtime.Caller(depth)*/
	function, file, line, _ := runtime.Caller(1)
	return fmt.Sprintf("%s->%s(%d)", chopPath(file), chopPath(runtime.FuncForPC(function).Name()), line)
}

// return the source filename after the last slash
func chopPath(original string) string {
	i := strings.LastIndex(original, "/")
	//if i == -1 {
	//return original
	//}
	return original[i+1:]
}

//============================= LOGGIN  ==================================

//StartLogger Inicia Login da aplicação
/*Formas de Imprimir Logs
 *fmt.Fprintf(AppLog, "%s sys/Log  Iniciado\n", ThisFunction())
 *sysLog.Debug("And this is a daemon emergency with demotag.")
 *log.Printf("%s sys/Log  Iniciado\n", ThisFunction())
 */
func StartLogger() {
	var err error
	//App_ctrl.Level_LOG_Prog := syslog.LOG_DEBUG | syslog.LOG_LOCAL7
	//App_ctrl.Is_LOG_Prog = true

	level := syslog.LOG_DEBUG | syslog.LOG_LOCAL7
	//var SysLog Write

	AppLog, err = syslog.Dial("udp", "172.31.11.162:514", level, "app_blfctrl")
	if err != nil {
		log.Fatal(err)
	}
	AppSyslog("%s sys/Log  Iniciado2\n", ThisFunction())
}

//LoggerClose Finish the Logger
func LoggerClose() {
	AppSyslog("%s {BLF_CTRL_FINISH}\n", ThisFunction())
	//closelog();
}

/*
func App_SetLogLevel(isProg bool, priority int) {
	//App_ctrl.Level_LOG_Prog = level
	//App_ctrl.Is_LOG_Prog = isProg
	//setlogmask (LOG_UPTO (level));
}*/

/* App_syslog
  *Aplicar o Padrao enm todas as Mensagens de LOG
  * Sintaxe da Mensagem de LOG
  * (funcao)    = Entre parenteses: Nome Da Funcao
  * {texto}    = Entre chaves: Texto qualquer
  * <variavel> = Entre Couchetes NOme da Variavel
  * [%x x] = Entre Couchetes Valor da Variavel

	icip_syslog( LOG_INFO ,"%s:(FUNC){Este eh umLOG de teste}<argument_1>[%d]:",THIS_FILE, arg1);
    int app_syslog(int syslogpri, char *format, ...)
*/

//AppSyslog mensagem de log Padrao
func AppSyslog(format string, a ...interface{}) {

	//SYSLOG
	fmt.Fprintf(AppLog, format, a...)
	info := fmt.Sprintf(format, a...)

	if includes.PRINTSYSLOG {
		log.Printf("%v", info)
	}

	//fmt.Fprintf(sysLog, "%s sys/Log  Iniciado\n", ThisFunction())
	/*
			va_list args;

		   if( (syslogpri > App_ctrl.Level_LOG_Prog) || (!App_ctrl.Is_LOG_Prog) )
			return ECANCELLED;

		   va_start(args, format);
		   vsyslog(syslogpri, format, args);
		   _storage_func(args);
		   va_end(args);


		 #if PRINT_SYSLOG
		   printf(format, args);
		 #endif

		   return SUCCESS;

		   func Debug(format string, a ...interface{}) {
		    _, file, line, _ := runtime.Caller(1)
		    info := fmt.Sprintf(format, a...)

		    log.Printf("[cgl] debug %s:%d %v", file, line, info)*/
}

/*
 #include "defin.h"
 #include "general.h"
 #include <stdio.h>
 #include <stdarg.h>
 #include <sched.h>
 #include <sys/resource.h>
 #include "ctype.h"




 //Declaração de Váriaveis externas
 extern struct app App_ctrl;

 //Variaveis Globais
 Status_VoIP  StatusVoIP;
 const char *NameArquivoGlobal;
 const char *NameFuncaoGlobal;


 #define _storage_func(args_x) NameArquivoGlobal = va_arg(args_x, char *); NameFuncaoGlobal = va_arg(args_x, char *) ;


 //Define Prioridade da Thread
 void boost_priority(int priority)
 {
   struct sched_param param;

   param.sched_priority = priority;
   if(sched_setscheduler(0, SCHED_RR, &param) == -1)
	 {
	   app_syslog( LOG_ERR, "%s->%s(){FALHA NO ESCALADOR DE PRIORIDADE }<pid>[%d]", __THIS_FILE__, getpid() );
	   //exit(-1);
	 }
   app_syslog( LOG_DEBUG, "%s->%s{NOVO PROCESSO}<_priority>[%d]<PID>[%d]", __THIS_FILE__, param.sched_priority, getpid() );

 }//void boost_priority(void)





 /*
  *
  * /
 void ClearContErros(void)
 {
   //  memset(&StatusVoIP, 0, sizeof(Status_VoIP) );
   StatusVoIP.ErrorAlloc = 0 ;          //Erros de alocação de memória;
   StatusVoIP.ErrorComSocket = 0;       //Erros de cominicação com sockets;
   StatusVoIP.Generic_cont1= 0;
   StatusVoIP.Generic_cont2= 0;
 }//void ClearContErros(void)

 /*
  *
  * /
 void PrintContErros(void)
 {
 //  memset(&StatusVoIP, 0, sizeof(Status_VoIP) );
   //Incrementa Erro Caso Tenha Perdido Registro incrementaErro.
   if ( StatusVoIP.ErrorComSocket || StatusVoIP.ErrorAlloc)
	 app_syslog(LOG_CRIT, "%s->%s()<alloc>[%d]<socket>[%d]", __THIS_FILE__,
		 StatusVoIP.ErrorAlloc,         //Erros de alocação de memória;
		 StatusVoIP.ErrorComSocket      //Erros de cominicação com sockets;
								   );
 }//void ClearContErros(void)



 //Quando Variavel for alocado pelo PJ não de deve dar free
 void mem_free(void *pt_var)
 {
  if (pt_var == NULL)
	return;

  free(pt_var);
  pt_var = NULL;
 }

 //Quando Variavel for alocado pelo PJ não de deve dar free
 void unnit_close(void *pt_fd)
 {
  if (pt_fd == NULL)
	return;

  close(pt_fd);
  pt_fd = NULL;
 }

 /*
  *
  * /
 void app_SetLogLevel(BOOL isProg, int level)
 {
  App_ctrl.Level_LOG_Prog = level;
  App_ctrl.Is_LOG_Prog    = isProg;
  setlogmask (LOG_UPTO (level));

 }
 /* Aplicar o Padrao enm todas as Mensagens de LOG
  * Sintaxe da Mensagem de LOG
  * (funcao)    = Entre parenteses: Nome Da Funcao
  * {texto}    = Entre chaves: Texto qualquer
  * <variavel> = Entre Couchetes NOme da Variavel
  * [%x x] = Entre Couchetes Valor da Variavel

	icip_syslog( LOG_INFO ,"%s:(FUNC){Este eh umLOG de teste}<argument_1>[%d]:",THIS_FILE, arg1);
  * /

 int app_syslog(int syslogpri, char *format, ...)
 {
   va_list args;

   if( (syslogpri > App_ctrl.Level_LOG_Prog) || (!App_ctrl.Is_LOG_Prog) )
	return ECANCELLED;

   va_start(args, format);
   vsyslog(syslogpri, format, args);
   _storage_func(args);
   va_end(args);


 #if PRINT_SYSLOG
   printf(format, args);
 #endif

   return SUCCESS;

   func Debug(format string, a ...interface{}) {
    _, file, line, _ := runtime.Caller(1)
    info := fmt.Sprintf(format, a...)

    log.Printf("[cgl] debug %s:%d %v", file, line, info)
 }


 void printLastFunc( char* name_func)
 {
   syslog(LOG_EMERG, "%s->%s()<!!!The Last FILE was>[%s()]", name_func, name_func,  NameArquivoGlobal);
   if ( *NameFuncaoGlobal==NULL )
	  return;

   syslog(LOG_EMERG, "%s->%s()<!!!The Last FUNCTION Exec>[was %s()]", name_func, name_func, NameFuncaoGlobal);

 }


 /*
  * icip_strncpy2
  *
  * Copia uma string para outra
  * Usado quando a string origem é uma ponteiro para char
  * /
 void app_strncpy(char *pchDst, char *pchSrc, int lenDst)
 {
   int lenSrc;

   if (pchSrc == NULL)
	 return;

   memset(pchDst ,0, lenDst);

   lenSrc = strlen(pchSrc);
   strncpy(pchDst, pchSrc, MIN_( lenSrc, lenDst));
   pchDst[POS_FIM_STRING_( lenSrc, lenDst)] = 0;
 }



 /*
  * icip_endstr
  *
  * poe caracter de fim de string(\0) na posição do caracter passado como parametro
  * Usado quando a string origem é uma ponteiro para char
  * /
 BOOL app_endstr(char *pt_str, char ch)
 {
  char *fim_str;

  fim_str = strchr(pt_str, ch);            //Acha o caracter
  if (fim_str)                             //e se existir
	{
	  *(fim_str) = 0;                          //poe Final de String
	  return TRUE;
	}

  return FALSE;

 }



 /*
  * icip_endstr
  *
  * Verificar se string é valida
  * /
 bool isValid_str(char *pt_str)
 {
  if( *pt_str==NULL)
	  return FALSE;

  return ( isalnum(*pt_str) );

 }

 /*
  * icip_endstr
  *
  * Verificar se string é valida
  * /
 bool isValid_str_ascii(char *pt_str)
 {
  if( *pt_str==NULL)
	 return FALSE;

  return ( isascii(*pt_str) );

 }


*/
