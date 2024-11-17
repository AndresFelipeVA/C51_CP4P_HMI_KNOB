#include "ui.h"
#include "encoder.h"
#include "uart.h"

/*Arreglo predefinido para enviar informacion al uC externo cuando se presione la perilla, las 
  posiciones 4 y 5 se llenaran con el numero del registro que se modifico y las 7 y 8 con el valor 
	que tomo dicho registro */
u8 sendingBuffer[9]={0x5A, 0xA5, 0x06, 0x83, 0x00, 0x00, 0x01, 0x00, 0x00};

u16 state;//Almacena de manera global el estado de la perilla


/*==============================================================================================
  Rutina para comunicar via serial con el uC externo, se indica el parametro (parameterReg) que
  se modifico y el valor del mismo (num)
  El arreglo de byte enviado es el mismo a cuando se ejecuta una lectura en la pantalla por
  medio del comando 83
	==============================================================================================*/
void sendMsgByUart2(u16 parameterReg, num){
	//Se almacena el numero del registro
	sendingBuffer[4] = (parameterReg >> 8) & 0xFF; // Byte alto
  sendingBuffer[5] = parameterReg & 0xFF;        // Byte bajo

	//Se almacena valor que tomo
	sendingBuffer[7] = (num >> 8) & 0xFF; // Byte alto
  sendingBuffer[8] = num & 0xFF;        // Byte bajo
	
	//Se envia la secuencia
	Uart2_Sendstring(sendingBuffer, 9);
}


/*==============================================================================================
  Rutina para navegar en la pantalla principal que agrupa todos los parametros de configuracion, 
  inicialmente era la pantalla inicial de la interfaz
	==============================================================================================*/
u16 ppalConfigScreen(u8 pageNumber){
	switch(state){
		case 1:{//Giro en direccion de las manecillas del reloj-Contrario a perilla pequena
			if(pageNumber==4){
				pageNumber=0;
			}else{
				pageNumber++;
			}
		}break;
		case 2:{//Giro en CONTRA de las manecillas del reloj-Contrario a perilla pequena
			if(pageNumber==0){
				pageNumber=4;
			}else{
				pageNumber--;
			}
		}break;
		case 3:{//Presion simple de la perilla
			if(pageNumber==0){
				pageNumber=10;
			}else{
				pageNumber=pageNumber+5;
				if(pageNumber==6){//Se inicia prueba de fugas
					sendMsgByUart2(FUGAS_REG, 1);
				}
			}
		}break;
		case 4:{//Presion sostenida
			if(pageNumber==0){
				pageNumber=5;
			}
		}break;
		default:
			break;
	}
	return pageNumber;
}	


/*==============================================================================================
  Rutina para cambiar el valor de los parametros de configuracion, el parametro a configurar se 
  pasa como argumento, al igual que los valores limite, el incremento y pagina relacionada
	==============================================================================================*/
u16 configScreen(u8 pageNumber, u16 parameterReg, parameterMin, parameterMax, parameterInc){
	u16 num;//Deben ser de 2 Bytes ya que es el tamano del VP en DWIN
	//si se colocan de 1 Byte (u8) pone problemas la lectura/escritura

	read_dgus_vp(parameterReg,(u8*)&num,1);
	switch(state){
		case 1:{//Giro en direccion de las manecillas del reloj-Contrario a perilla pequena
			if(num<parameterMax){
				num+=parameterInc;
			}
		}break;
		case 2:{//Giro en CONTRA de las manecillas del reloj-Contrario a perilla pequena
			if(num>parameterMin){
				num-=parameterInc;
			}
		}break;
		case 3:{//Presion simple de la perilla
			pageNumber=pageNumber-5;
			sendMsgByUart2(parameterReg, num);
		}break;
		default:
			break;
	}
	write_dgus_vp(parameterReg,(u8*)&num,1);
	return pageNumber;
}


/*==============================================================================================
  Rutina a la que solo deberia entrar cuando se encuentre en la pantalla de resumen (pagina 40)
  en la que se mantiene el CPAP durante su funcionamiento normal o en la de fugas (pagina 6) 
	==============================================================================================*/
u16 briefScreens(u8 pageNumber){
	switch(state){
		case 3:{//Presion simple de la perilla
				if(pageNumber==6){
					pageNumber=1;//Se detiene prueba de fugas
					sendMsgByUart2(FUGAS_REG, 0);
				}else{
					pageNumber=50;//Se detiene la terapia
					sendMsgByUart2(RUNNING, 0);
				}
		}break;
		default:
			break;
	}
	return pageNumber;
}	


/*==============================================================================================
  Rutina para navegar en la pantalla de reportes
	==============================================================================================*/
u16 reportScreen(u16 pageNumber){
	switch(state){
		case 1:{//Giro en direccion de las manecillas del reloj-Contrario a perilla pequena
			if(pageNumber==23){
				pageNumber=20;
			}else{
				pageNumber++;
			}
		}break;
		case 2:{//Giro en CONTRA de las manecillas del reloj-Contrario a perilla pequena
			if(pageNumber==20){
				pageNumber=23;
			}else{
				pageNumber--;
			}
		}break;
		case 3:{//Presion simple de la perilla
				if(pageNumber==20){
					pageNumber=30;
				}
		}break;
		default:
			break;
	}
	return pageNumber;
}	


/*==============================================================================================
  Rutina para navegar en la pantalla inicial de tres opciones:
      Iniciar terapia, Configuracion y reportes
	==============================================================================================*/
u16 initScreen(u16 pageNumber){
	switch(state){
		case 1:{//Giro en direccion de las manecillas del reloj-Contrario a perilla pequena
			if(pageNumber==50){
				pageNumber=10;
			}else{
				pageNumber+=20;
			}
		}break;
		case 2:{//Giro en CONTRA de las manecillas del reloj-Contrario a perilla pequena
			if(pageNumber==10){
				pageNumber=50;
			}else{
				pageNumber-=20;
			}
		}break;
		case 3:{//Presion simple de la perilla
			if(pageNumber==50){//Se va a iniciar la terapia
				sendMsgByUart2(RUNNING, 1);
			}
			pageNumber-=10;
		}break;
		default:
			break;
	}
	return pageNumber;
}	


/*==============================================================================================
  Rutina principal de manejo de la interfaz que de acuerdo a la pagina actual
  llama a las otras rutinas
	==============================================================================================*/
void encoder_page_change(){
	u16 pageNumber, newPage;
	state=Encoder_recevie();
	if(state!=0){	
		pageNumber=GetPageID();
		if( pageNumber>=0 && pageNumber<=4){
			newPage=ppalConfigScreen(pageNumber);
		}else if( pageNumber>=20 && pageNumber<=23){
			newPage=reportScreen(pageNumber);
		}else if( pageNumber==50 || pageNumber==10 || pageNumber==30){
			newPage=initScreen(pageNumber);
		}else if(pageNumber==BRILLO_PAG){
			newPage=configScreen(BRILLO_PAG, BRILLO_REG, BRILLO_MIN, BRILLO_MAX, BRILLO_INC);
		}else if(pageNumber==PRESION_PAG){
			newPage=configScreen(PRESION_PAG, PRESION_REG, PRESION_MIN, PRESION_MAX, PRESION_INC);
		}else if(pageNumber==TIEMPO_PAG){
			newPage=configScreen(TIEMPO_PAG, TIEMPO_REG, TIEMPO_MIN, TIEMPO_MAX, TIEMPO_INC);
		}else if(pageNumber==HUMEDAD_PAG){
			newPage=configScreen(HUMEDAD_PAG, HUMEDAD_REG, HUMEDAD_MIN, HUMEDAD_MAX, HUMEDAD_INC);
		}else{
			newPage=briefScreens(pageNumber);
		}
		Page_Change(newPage);
	}
}