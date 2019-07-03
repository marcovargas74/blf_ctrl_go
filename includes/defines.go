package includes

const (
	//Version of application
	Version = "19.07.03"

	//SUCCESS return when a function is OK
	SUCCESS = 0 // Status está OK.

	//PRINTSYSLOG imprime print F
	PRINTSYSLOG = true

	//EXECUTETDD executa testes TDD
	EXECUTETDD = true

	/*Ficou definido casa dos 10 prioridade blf_ctrl
	 *QUANTO MAIS ALTO MAIOR PRIORIDADE*/

	//THREADPRIOBASE Prioridade BASE das threads da ICIP
	THREADPRIOBASE int = 10
	//THREADPRIOMAIN Prioridade BASE das threads da APPP
	THREADPRIOMAIN int = THREADPRIOBASE + 0
	//THREADPRIOPABXCOM Prioridade da thread  do socket de comunicação com o PABX
	THREADPRIOPABXCOM int = THREADPRIOBASE + 1

	//SERVERPATH é o caminho so Soquete
	SERVERPATH = "/tmp/server.sock"
	//SERVERTYPE é o caminho so Soquete
	SERVERTYPE = "unix"

	//TIMEEXEC10MIN Timer de 10 minutos
	TIMEEXEC10MIN = 10
)
