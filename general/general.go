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
	"log"
	"log/syslog"
	"os"
	"os/exec"
	"runtime"
	"strings"
	"syscall"

	"github.com/marcovargas74/blf_ctrl_go/includes"
)

//AppLog Variavel usado no syslog
var AppLog *syslog.Writer

//var AppLog io.Writer

//AppLevel onde armazenado o nivel do syslog
var AppLevel syslog.Priority

//AppLogProg se Log Programado True
var AppLogProg bool

//StatusApp mostra os Erros da aplicacao
var StatusApp includes.TstatusApp

//Clear Limpa a Tela
func Clear() {
	//fmt.Println("\033[2J")
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	cmd.Run()
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
func StartLogger(isProg bool) {
	var err error

	AppLogProg = isProg
	AppLevel = syslog.LOG_DEBUG | syslog.LOG_LOCAL7

	if isProg == false {
		return
	}

	AppLog, err = syslog.Dial("udp", "172.31.11.162:514", AppLevel, "app_blfctrl")
	if err != nil {
		log.Fatal(err)
	}
	defer AppLog.Close()
	AppSyslog(syslog.LOG_INFO, "%s sys/Log  Iniciado\n", ThisFunction())
}

//LoggerClose Finish the Logger
func LoggerClose() {
	AppSyslog(syslog.LOG_INFO, "%s {BLF_CTRL_FINISH}\n", ThisFunction())
	AppLog.Close()
}

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
func AppSyslog(syslogpri syslog.Priority, format string, a ...interface{}) {

	if syslogpri > AppLevel {
		return
	}

	//Imprime informacoes na tela como prints
	info := fmt.Sprintf(format, a...)
	if includes.PRINTSYSLOG {
		log.Printf("%v", info)
	}

	//SYSLOG INFO
	if syslogpri == syslog.LOG_INFO {
		AppLog.Info(info)
		return
	}

	//SYSLOG ERRO
	if syslogpri == syslog.LOG_ERR {
		AppLog.Err(info)
		return
	}

	//Nivel Debug
	fmt.Fprintf(AppLog, format, a...)
}

//BoostPriority Define Prioridade da Thread
func BoostPriority(priority int) {
	err := syscall.Setpriority(0, os.Getpid(), priority)
	if err != nil {
		//log.print(err)
		AppSyslog(syslog.LOG_ERR, "%s{FALHA NO ESCALADOR DE PRIORIDADE}<PID>[%d]<err>[%s]\n", ThisFunction(), os.Getpid(), err)
	}
	/*
	  struct sched_param param;
	  param.sched_priority = priority;
	  if(sched_setscheduler(0, SCHED_RR, &param) == -1)
	  {
	    app_syslog( LOG_ERR, "%s->%s(){FALHA NO ESCALADOR DE PRIORIDADE }<pid>[%d]", __THIS_FILE__, getpid() );
	    //exit(-1);
	  }*/
	AppSyslog(syslog.LOG_DEBUG, "%s{NOVO PROCESSO}<priority>[%d]<PID>[%d]\n", ThisFunction(), priority, os.Getpid())

} //void boost_priority(void)

// ClearContErros Limpa variaveis contadores de Erro
func ClearContErros() {
	//  memset(&StatusVoIP, 0, sizeof(Status_VoIP) );StatusVoIP
	StatusApp.ErrorAlloc = 0     //Erros de alocação de memóriStatusVoIPa;
	StatusApp.ErrorComSocket = 0 //Erros de cominicação com soStatusVoIPckets;
	StatusApp.GenericCont1 = 0
	StatusApp.GenericCont2 = 0
}

//PrintContErros IMprime os Erros do Applicativo
func PrintContErros() {
	if StatusApp.ErrorComSocket > 0 || StatusApp.ErrorAlloc > 0 {
		AppSyslog(syslog.LOG_ERR, "%s <alloc>[%d]<socket>[%d]\n", ThisFunction(),
			StatusApp.ErrorAlloc,     //Erros de alocação de memória;
			StatusApp.ErrorComSocket, //Erros de cominicação com sockets
		)

	}

} //void ClearContErros(void)

//------------------ FIM ARQUIVO GO --------------------------------------

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
