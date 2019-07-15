package includes

/*
 *
 */
type tPortDNS struct {
	//DECL_LIST_MEMBER(struct TypePortDNS);    /**< Generic list member.   */
	Position   byte
	Selelect   byte
	IndiceDNS  uint8 // Índice DNS do driver/PABX  Usado Como Chave
	Expiration uint  // Para o serviço BLF: é o tempo em que a subscrição expira (em segundos; se zero cancela)
}

type tKeys struct {
	//DECL_LIST_MEMBER(struct TKeys);    /**< Generic list member.   */
	//enum  DirChamada    BLF_DirectionCall;
	Index      uint8
	StatusBlf  uint8
	KeyName    string
	ListIndDNS []tPortDNS
}

//TApp Tipo Aplicativo Variaveis Globais usados em todo o Aplicativo
type TApp struct {
	ThreadCount  int
	RouterThread int // Thread de recepção e roteamento das mensagens vindas do PABX
	//TABELAS DE Uso Geral
	TabBLFkey         []tKeys
	SizeKey           int
	LevelLOGProg      int
	IsLOGProg         bool
	VersionSoftware   string //Versao da aplicação Default
	PidMain           int
	PidRemoteSocket   int
	PABXCOMMConnected bool
	LOOPMain          bool
	KillApplication   bool
}

//Estrutura de Contadores de Erro

//TstatusApp tipo status do Aplicativo
type TstatusApp struct {
	ErrorAlloc     byte //Erros de alocação de memória;
	ErrorComSocket byte //Erros de cominicação com sockets;
	GenericCont1   uint64
	GenericCont2   uint64
}

//Estrutura de Pids Das Threads
type tStatusPIDVoIP struct {
	PidMain           int //Pid da Thread Principal;
	PidPABXCOMMsocket int //Pid da Thread de comunicação com o PABX;
}

//TsockCommandFromClient ESTRUTURAS SOCKET
type TsockCommandFromClient struct {
	Command byte
	Client  byte
	Vago    byte
}

//SIZEsockCommandFromClient tamanho da struct
const SIZEsockCommandFromClient = 3

// TsockStatusFromServer Tipo status do socket
type TsockStatusFromServer struct {
	Status byte
	Vago   byte
}

//SIZEsockStatusFromServer tamanho da struct
const SIZEsockStatusFromServer = 2

/*-----------------DEFINE ENUMS -----------------------------------------*/

type tEnum8 byte
type tEnum16 uint16

//ID dos clientes usado para se conectar no PBXCOM
const (
	VOIPMANAGER tEnum8 = iota
	CABLEMANAGER
	APPVOIP
	APPICTI
	BOARDCMD
	ICIPFAXVIRTUAL
	BLFCTRL
)

//Status do Socket do Cliente
const (
	SOCKETUNREGISTER tEnum8 = iota
	SOCKETREGISTER
	SOCKETSTATUS
)

//Tipo de clientes usado para rotiar mensagens entre processos
const (
	AddrServicos        tEnum16 = 0   // 0 endereço dos serviços 0001 a 0999
	AddrIPBoardManage   tEnum16 = 137 // gerencia da placa ICIP (lado PABX)
	AddrAPP             tEnum16 = 20000
	AddrAppVoipManager  tEnum16 = AddrAPP + 1 // Gerencia Voip
	AddrAppWeb          tEnum16 = AddrAPP + 2 // servidor web embarcado
	AddrAppEmail        tEnum16 = AddrAPP + 3 // cliente de email embarcado
	AddrAppSnmp         tEnum16 = AddrAPP + 4 // agente SNMP embarcado
	AddrAppCableManager tEnum16 = AddrAPP + 5 // agente SNMP embarcado
	AddrAppPbxComm      tEnum16 = AddrAPP + 6 //20006
	AddrAppIPMom        tEnum16 = AddrAPP + 7
	AddrAppFaxManager   tEnum16 = AddrAPP + 8
	AddrAppBlfCtrl      tEnum16 = AddrAPP + 9
)

// Tipo: tipos de mensagem do protocolo entre PABX e placa IP (1 byte)
const (
	TypeConfiguracao tEnum8 = iota
	TypeSinalizacaot tEnum8 = iota
	TypeDados        tEnum8 = iota
	TypeAlarme       tEnum8 = iota
)

/*
const (
      REGISTERFAILED tEnum8 =iota
      REGISTERSUCCESSSFULL
)*/

//TIPOS DE MENSAGEM TROCADAS ENTRE PROCESSOS
const (
	VoxFrmstartup   tEnum16 = 0
	VoxFrmSubscurbe tEnum16 = 12
	VoxFrmNotify
	VoxFrmNotifyBLF              tEnum16 = 20
	VoxFrmDesligaDevice          tEnum16 = 222
	VoxFrmSocketUnregisterClient tEnum16 = 500
	VoxFrmBroadCast              tEnum16 = 650
)
