package main

import (
	"fmt"

	"github.com/marcovargas74/blf_ctrl_go/general"
	"github.com/marcovargas74/blf_ctrl_go/includes"
)

const thisFile string = "blfctrl.go"

func init() {
	//define.App_ctrl App
	//LOOP_Main := TRUE
	//Pids_Threads tStatusPIDVoIP           //NUmro dos Pids das thread usados no debbuger
	fmt.Println("======== Start Aplication blf_control Version " + includes.Version + "========")

}

func testSucces(num int) int {
	return includes.SUCCESS
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

	fmt.Printf("\n%s APPLICATION BLF-STARTING  Iniciado\n\n", general.ThisFunction())
	fmt.Println(testSucces(3))
	fmt.Println(includes.Version)

	general.StartGeneral()
	// boost_priority(THREAD_PRIO_MAIN);
	general.StartLogger()

	/*
			TrataComandosVindoDoLinux(&sig_app);


			// Seta opções default da Aplicação
			init_parm_app();
			app_syslog( LOG_NOTICE, "%s->%s(){******APPLICATION BLF-STARTING*******}<version>[%s]",__THIS_FILE__, App_ctrl.version_software );

			Pids_Threads.Pid_Main = getpid();


			#if EXECUTE_TDD
			ExecutaTestesIniciais();
			#endif


			//=========================== INICIALIZAÇÃO DE COMUNICAÇÂO COM PABX ==================
			app_syslog( LOG_NOTICE, "%s->%s(){ Carrega a thread de comunicacao com oPABXCOMM_socket",__THIS_FILE__ );
			ret_thread = pthread_create(&App_ctrl.router_thread, NULL, &PABXCOMM_socket, NULL);
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
