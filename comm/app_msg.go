package comm

import (
	"log/syslog"

	"github.com/marcovargas74/blf_ctrl_go/general"
	"github.com/marcovargas74/blf_ctrl_go/includes"
)

/* Formato da mensagem enviada pela aplicação Roteadora
 *
 * +----------------+
 * -  APLICACAO (H) -
 * +----------------+
 * -  APLICACAO (L) -
 * +----------------+
 * -  PAYLOADSIZE(H)-
 * +----------------+
 * -  PAYLOADSIZE(L)-
 * +----------------+
 * -      TIPO      -
 * +----------------+
 * -    N_MSG (L)   -
 * +----------------+
 * -    N_MSG (H)   -
 * +----------------+
 * -     SELECT     -
 * +----------------+
 * -    POSITION    -
 * +----------------+
 * -     DADOS      -
 * +----------------+
 *
 * APLICACAO - identificação da aplicação destino da mensagem;
 *
 * PAYLOADSIZE - número de bytes contidos no Payload da mensagem
 *
 * TIPO - Tipo de mensagem recebida - Mensagem de configuração, sinalização, dados e alarme
 *
 * ID_DESTINO - Identificador do destino da mensagem (antigo CANAL do protocolo)
 *
 * N_MSG - Número da mensagem
 *
 * Dados - Informação contida na mensagem
 */

//TAGMESSAGEVOIP  Mensagem do Serviço Voip.
type TAGMESSAGEVOIP struct {
	//AplicHigh       byte //parte mais significativa, da identificação da aplicação destino da mensagem;
	//AplicLowh       byte //parte menos significativa, da identificação da aplicação destino da mensagem;
	Aplic uint16 //parte mais significativa, da identificação da aplicação destino da mensagem;
	//PayloadSizeH byte   //parte mais significativa,  do número de bytes contidos no Payload da mensagem;
	//PayloadSizeL byte   //parte mais significativa,  do número de bytes contidos no Payload da mensagem;
	PayloadSize uint16 //parte mais significativa,  do número de bytes contidos no Payload da mensagem;

	Tipo byte // TIPO - Tipo de mensagem recebida - Mensagem de configuração, sinalização, dados e alarme
	//NMsgLow  byte // N_MSG - Número da mensagem - Parte Menos Significativa
	//NMsgHigh byte // N_MSG - Número da mensagem - Parte Mais Significativa
	NMsg     uint16 // N_MSG - Número da mensagem - Parte Menos Significativa
	Select   byte   // parte integrante do endereço de hardware dos ramais e juntores IP, no PABX.
	Position byte   // parte integrante do endereço de hardware dos ramais e juntores IP, no PABX.

	//Dados [includes.APPMAXTAMPAYLOAD]byte //Dados - Informação contida na mensagem
	Dados []byte //Dados - Informação contida na mensagem

}

/*****************************************************************************************************
  VOX_FRM_BROADCAST (650 )
*****************************************************************************************************/

//TAGBROADCAST  TAg usada ma mensagem VOX_FRM_BROADCAST (650 )
type TAGBROADCAST struct {
	MotivoBroadCast byte //Motivo da desconexão
	data            [includes.APPMAXDATABROADCAST]byte
	//unsigned char data[APP_MAX_DATA_BROADCAST];
	//enum typeBroadcast MotivoBroadCast;  //Motivo da desconexão
	//unsigned char data[APP_MAX_DATA_BROADCAST];
}

//SIZETAGBROADCAST tamanho da struct
const SIZETAGBROADCAST = includes.APPMAXDATABROADCAST + 1

//SendFrmBroadCast Envia status da Rede para as aplicacoes
func SendFrmBroadCast(state byte) {
	//char *msg;
	var frmBroadcast TAGBROADCAST

	// Estado
	frmBroadcast.MotivoBroadCast = state
	general.AppSyslog(syslog.LOG_DEBUG, "%s<State>[%d] [%d] [%d]\n", general.ThisFunction(), frmBroadcast.MotivoBroadCast, includes.AddrAPP, includes.AddrAppVoipManager)

	msgToSend := []byte{frmBroadcast.MotivoBroadCast}

	//CreateMessageSEND(ADDR_ICIP_PBXCOM, TYPE_SINALIZACAO, VOX_FRM_BROADCAST, (char *)&frmBroadcast, SIZE_TAG_BROADCAST );
	FormataFrameSEND(uint16(includes.AddrAppPbxComm), byte(includes.TypeSinalizacao), uint16(includes.VoxFrmBroadCast), includes.VOIDPOSITION, includes.VOIDSELECT, msgToSend, len(msgToSend))

	//return SUCCESS
}

/*
 * Envia Mensagem de NOtify com estado da Tecla para APP_VOIP
 * Passa o DNS do Ramal e a tecla
 * /
 void  FrmNotifySEND ( word aplicDest, TKeys *aBlfKey)
 {
   TAG_NOTIFY_BLF msg_notify_blf;

   memset(&msg_notify_blf,0, SIZE_TAG_NOTIFY_BLF);

   //MONTA ESTADO
   msg_notify_blf.BLF_DirectionCall=aBlfKey->BLF_DirectionCall;
   msg_notify_blf.BLF_status=aBlfKey->status_blf;

   memcpy(&msg_notify_blf.BLF_TargetSubscriber, aBlfKey->key_name, APP_MAX_NOME_PORTA);
   app_syslog( LOG_DEBUG,"%s->%s()<status>[%d]<dir>[%d]<key>[%s]<dest>[%d]", __THIS_FILE__,
	   msg_notify_blf.BLF_status,
	   msg_notify_blf.BLF_DirectionCall,
	   msg_notify_blf.BLF_TargetSubscriber,
	   aplicDest
									   );
   (aplicDest, TYPE_SINALIZACAO, VOX_FRM_NOTIFY_BLF, VOID_POSITION, VOID_SELECT, &msg_notify_blf, SIZE_TAG_NOTIFY_BLF );
 }



/******************************************************************************************
        Function: SendFrmDesligarPorta
        Description: Envia a mensagem VOX_FRM_BROADCAST para o PBXCOM, que este por sua vez
                                 envia por broadcast para os outros aplicativos interessados.
******************************************************************************************* /



*/
