#include "sys.h"
#include "timer.h"
#include "uart.h"
#include "ui.h"


void main()
{
	u16 pageNumber;
	T0_Init();
  T1_Init();
  StartTimer(0,60000);
  Uart2_Init(115200, MODE_8N1);
	pageNumber=50;//Para que empiece en esta pagina diferente al 0 por defecto
	Page_Change(pageNumber);
	while(1)
  {
		uartRun(&uart2, Analyze_8283);
		encoder_page_change();    
  }
}

