#include "ui.h"
#include "encoder.h"

/*==============================================================================================
  Rutina para navegar en la pantalla principal que agrupa todos los parametros de configuracion, 
  inicialmente era la pantalla inicial de la interfaz
	==============================================================================================*/
void ppalConfigScreen(u8 pageNumber){
	u16 state;
	state=Encoder_recevie();
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
	Page_Change(pageNumber);
}	


/*==============================================================================================
  Rutina para cambiar el valor de los parametros de configuracion, el parametro a configurar se 
  pasa como argumento, al igual que los valores limite, el incremento y pagina relacionada
	==============================================================================================*/
void configScreen(u8 pageNumber, u16 parameterReg, parameterMin, parameterMax, parameterInc){
	u16 state;//Deben ser de 2 Bytes ya que es el tamano del VP en DWIN
	u16 num;//si se colocan de 1 Byte (u8) pone problemas la lectura/escritura
	state=Encoder_recevie();
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
		}break;
		default:
			break;
	}
	write_dgus_vp(parameterReg,(u8*)&num,1);//Siempre escribe aunque no haya cambio (no hubo giro de perilla)
	Page_Change(pageNumber);//Siempre cambia pagina aunque no haya cambio (no hubo presion de perilla)
}


/*==============================================================================================
  Rutina a la que solo deberia entrar cuando se encuentre en la pantalla de resumen (pagina 40)
  en la que se mantiene el CPAP durante su funcionamiento normal o en la de fugas (pagina 6) 
	==============================================================================================*/
void briefScreens(u8 pageNumber){
	u16 state;
	state=Encoder_recevie();
	switch(state){
		case 3:{//Presion simple de la perilla
				if(pageNumber==6){
					pageNumber=1;
				}else{
					pageNumber=50;
				}
		}break;
		default:
			break;
	}
	Page_Change(pageNumber);
}	


/*==============================================================================================
  Rutina para navegar en la pantalla de reportes
	==============================================================================================*/
void reportScreen(u16 pageNumber){
	u16 state;
	state=Encoder_recevie();
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
	Page_Change(pageNumber);
}	


/*==============================================================================================
  Rutina para navegar en la pantalla inicial de tres opciones:
      Iniciar terapia, Configuracion y reportes
	==============================================================================================*/
void initScreen(u16 pageNumber){
	u16 state;
	state=Encoder_recevie();
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
			pageNumber-=10;
		}break;
		default:
			break;
	}
	Page_Change(pageNumber);
}	


/*==============================================================================================
  Rutina principal de manejo de la interfaz que de acuerdo a la pagina actual
  llama a las otras rutinas
	==============================================================================================*/
void encoder_page_change(){
	u16 pageNumber;
	pageNumber=GetPageID();
	if( pageNumber>=0 && pageNumber<=4){
		ppalConfigScreen(pageNumber);
	}else if( pageNumber>=20 && pageNumber<=23){
		reportScreen(pageNumber);
	}else if( pageNumber==50 || pageNumber==10 || pageNumber==30){
		initScreen(pageNumber);
	}else if(pageNumber==BRILLO_PAG){
		configScreen(BRILLO_PAG, BRILLO_REG, BRILLO_MIN, BRILLO_MAX, BRILLO_INC);
	}else if(pageNumber==PRESION_PAG){
		configScreen(PRESION_PAG, PRESION_REG, PRESION_MIN, PRESION_MAX, PRESION_INC);
	}else if(pageNumber==TIEMPO_PAG){
		configScreen(TIEMPO_PAG, TIEMPO_REG, TIEMPO_MIN, TIEMPO_MAX, TIEMPO_INC);
	}else if(pageNumber==HUMEDAD_PAG){
		configScreen(HUMEDAD_PAG, HUMEDAD_REG, HUMEDAD_MIN, HUMEDAD_MAX, HUMEDAD_INC);
	}else{
		briefScreens(pageNumber);
	}
}