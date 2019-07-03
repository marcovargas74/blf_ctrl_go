package main

import (
	"fmt"
	"log/syslog"
	"os"

	"github.com/marcovargas74/blf_ctrl_go/general"
	"github.com/marcovargas74/blf_ctrl_go/includes"
)

//AppCtrl Variaveis Globais usados em todo o Aplicativo
var AppCtrl includes.TApp

func init() {
	//define.App_ctrl App
	//LOOP_Main := TRUE
	//Pids_Threads tStatusPIDVoIP           //NUmro dos Pids das thread usados no debbuger
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
	//extern BOOL PABXCOMMConnected;
	//	status int ;
	//	struct sigaction sig_app;
	//int count_LOOP = 0;
	//byte count_30s  = 0;  //Contador de 30 segundos
	//uLong count_1MIN = 0; //Contador de minuto
	//int ret_thread;
	general.BoostPriority(includes.THREADPRIOMAIN)
	trataComandosVindoDoLinux()
	AppCtrl.PidMain = os.Getpid()
	/*if includes.EXECUTETDD {
		ExecutaTestesIniciais()
	}*/

	//=========================== INICIALIZAÇÃO DE COMUNICAÇÂO COM PABX ==================
	general.AppSyslog(syslog.LOG_INFO, "%s {Carrega a thread de comunicacao com oPABXCOMM_socket}\n", general.ThisFunction())
	//ret_thread = pthread_create(&App_ctrl.router_thread, NULL, &PABXCOMM_socket, NULL);
	/*
		if (ret_thread)
			  {
				app_syslog(LOG_ERR,"%s->%s(){FATAL ERROR->pthread_create}<error>[%d]", __THIS_FILE__, ret_thread );
				return ERROR;       //Termina Aplicação
			  }

				 if( Aguarda_comunicacao_com_PABX() != SUCCESS)
				   return ERROR;       //Termina Aplicação

			  #if ICIP_MOD_DEBUG && EXECUTE_TDD
				 //Executa TESTE
				  ExecutaTestesFinais();
			  #endif
				  app_syslog(LOG_DEBUG,"%s->%s(){LOOP_MAIN!!!}", __THIS_FILE__ );
				  while (LOOP_Main)
					 {
						//Executa Timer
						Executa_Timer_Control(&count_LOOP, &count_30s, &count_1MIN);
					 }
				   return SUCCESS;
	*/

}
