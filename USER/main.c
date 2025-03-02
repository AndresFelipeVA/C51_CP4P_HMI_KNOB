#include "sys.h"
#include "timer.h"
#include "uart.h"
#include "ui.h"

u8 initSring[9]={0x5A, 0xA5, 0x06, 0x83, 0x10, 0x00, 0x01, 0x00, 0x01};

void main()
{
	u16 pageNumber;
	T0_Init();
  T1_Init();
  StartTimer(0,60000);
  Uart2_Init(115200, MODE_8N1);
	pageNumber=50;//Para que empiece en esta pagina diferente al 0 por defecto
	Page_Change(pageNumber);
	//Se envia la secuencia que indica que la pantalla esta encendida y lista
	Uart2_Sendstring(initSring, 9);
	while(1)
  {
		uartRun(&uart2, Analyze_8283);
		encoder_page_change();    
  }
}

