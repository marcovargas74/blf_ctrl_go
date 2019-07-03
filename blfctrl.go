package main

import (
	"fmt"
	"log/syslog"
	"os"
	"time"

	"github.com/marcovargas74/blf_ctrl_go/comm"
	"github.com/marcovargas74/blf_ctrl_go/general"
	"github.com/marcovargas74/blf_ctrl_go/includes"
)

//AppCtrl Variaveis Globais usados em todo o Aplicativo
var AppCtrl includes.TApp

func init() {
	AppCtrl.LOOPMain = true
	general.Clear()
	general.StartLogger(true)
	fmt.Println("======== Start Aplication blf_control Version " + includes.Version + "========")
	general.ClearContErros()

	//list_init(&App_ctrl.Tab_BLF_key);
	//App_ctrl.sizeKey=0;
	//App_ctrl.kill_application = KILL_NOT;

}

/* FUNCAO teste
fmt.Println(testSucces(3))
func testSucces(num int) int {
	return includes.SUCCESS
}
*/

/*
 * Quando receber o sinal SIGUSR1 executa a ação
 * determinada pela estrutura sig
 */
func trataComandosVindoDoLinux() {
	//  void icip_trata_seg_fault(int signum);

	/* Vincula o handler com uma função
	   sig_app->sa_handler = CloseApp_blf_ctrl;
	   //Comando veio do LInux ou outra aplicacao
	   //User-defined signal 1 (POSIX).
	   sigaction(SIGUSR1, &sig_app, 0);*/

	//Caso A aplicacao ocorra algum segment FAULT Causado por um NULL
	//runtimesignal(SIGSEGV, app_trata_seg_fault);

	//Caso A aplicacao ocorra algum Urgent condition on socket
	//signal(SIGURG, app_trata_cond_urgent_socket);

	//Caso A aplicacao receba um QUIT
	//signal(SIGQUIT, app_trata_quit);

}

/* Funcao Inivial
 */
func main() {
	//var count30s byte    //Contador de 30 segundos
	var countLOOP uint64 //Contador de minuto
	var count1MIN uint64 //Contador de minuto

	general.BoostPriority(includes.THREADPRIOMAIN)
	trataComandosVindoDoLinux()
	AppCtrl.PidMain = os.Getpid()
	/*if includes.EXECUTETDD {
		ExecutaTestesIniciais()
	}*/

	//=========================== INICIALIZAÇÃO DE COMUNICAÇÂO COM PABX ==================
	general.AppSyslog(syslog.LOG_INFO, "%s {Carrega a thread de comunicacao com oPABXCOMM_socket}\n", general.ThisFunction())

	//Chama a thread de comunicacao com o Remoto .
	go comm.RemoteCOMMsocket(&AppCtrl.PidRemoteSocket, &AppCtrl.PABXCOMMConnected, &AppCtrl.KillApplication)

	//Aguarda Se conectar com o Remoto
	retComm := comm.AguardaComunicacaoComRemoto(&AppCtrl.PABXCOMMConnected, &AppCtrl.LOOPMain)
	if retComm != 0 {
		general.AppSyslog(syslog.LOG_INFO, "%s {FATAL ERROR->Falha na comunicacao com Remoto}<error>[%d]\n", general.ThisFunction(), retComm)
		return //Termina Aplicação
	}

	general.AppSyslog(syslog.LOG_INFO, "%s {START LOOP_MAIN!!!}\n", general.ThisFunction())
	for {
		executaTimerControl(&countLOOP, &count1MIN)
		//Termina caso App mandou terminar
		if AppCtrl.LOOPMain == false {
			break
		}
	} //for

	general.AppSyslog(syslog.LOG_DEBUG, "%s {FINISH LOOP_MAIN }\n", general.ThisFunction())

}

/*
 *
 */
//func executaTimerControl(ptrCountLOOP *uint64, ptrCount30s *byte, ptrCount1MIN *uint64) {
func executaTimerControl(ptrCountLOOP *uint64, ptrCount1MIN *uint64) {
	/*time.Sleep(time.Second * 30)
	//a cada 30segundos
	general.AppSyslog(syslog.LOG_DEBUG, "%s LOOP 30seg..[%d]min\n", general.ThisFunction(), *ptrCount30s)

	*ptrCount30s ^= 1     //Alterana 0 e 1
	if *ptrCount30s > 0 { //Se 30 segundos igual a 1
		return
	}
	*/
	// 1 minuto
	time.Sleep(time.Minute)
	*ptrCount1MIN++ //Inclrementa 1 Minuto
	general.AppSyslog(syslog.LOG_DEBUG, "%s LOOP 1min..[%d]min\n", general.ThisFunction(), *ptrCount1MIN)

	if (*ptrCount1MIN % includes.TIMEEXEC10MIN) == 0 {
		general.AppSyslog(syslog.LOG_DEBUG, "%s LOOP 10 min..[%d]min\n", general.ThisFunction(), *ptrCount1MIN)
		//Resfresh_status();
		general.PrintContErros()
	}

} //Excuta_timer_control
