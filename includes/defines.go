package includes

const (
	//Version of application
	Version = "19.07.12"

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
	SERVERPATH = "/tmp/server"
	//SERVERTYPE é o caminho so Soquete
	SERVERTYPE = "unix"

	//TIMEEXEC10MIN Timer de 10 minutos
	TIMEEXEC10MIN = 10

	//SERVERLOG é o caminho onde será enviado o syslog
	SERVERLOG = "10.0.0.129:514"

	//APPMAXDATABROADCAST numero de bytes usado na mensagem de broadcast
	APPMAXDATABROADCAST = 10

	//VOIDSELECT Posicao da tabela hash usado pelo PABX
	VOIDSELECT = 0XFE
	//VOIDPOSITION Posicao da tabela hash usado pelo PABX
	VOIDPOSITION = 0xFE

	//APPMAXTAMPAYLOAD numero de bytes usado na mensagem geral
	APPMAXTAMPAYLOAD = 1500

	//SIZEHEADERSOCKET tamanho do cabeçalho da socket da mensagem
	SIZEHEADERSOCKET = 4

	//SIZEHEADERMSG tamanho do cabeçalho da mensagem
	SIZEHEADERMSG = 5

	//SIZEHEADER tamanho do header
	SIZEHEADER = SIZEHEADERSOCKET + SIZEHEADERMSG

	//SIZETAGMESSAGEAPP tamanho total da mensagem
	SIZETAGMESSAGEAPP = SIZEHEADER + APPMAXTAMPAYLOAD
)
