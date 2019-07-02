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

type app struct {
	ThreadCount     int
	RouterThread    int // Thread de recepção e roteamento das mensagens vindas do PABX
	KillApplication byte
	//TABELAS DE Uso Geral
	TabBLFkey       []tKeys
	SizeKey         int
	LevelLOGProg    int
	IsLOGProg       bool
	VersionSoftware string //Versao da aplicação Default
}

//Estrutura de Contadores de Erro
type tStatusVoip struct {
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
