#ifndef __PAGE_H__
#define __PAGE_H__
#include "sys.h"

#define FUGAS_REG 0x1001
#define RUNNING 0x1005//Como tal no es un registro que se use en la pantalla
										//Es solo para indicar al uC externo de que corra la terapia

#define BRILLO_PAG 5
#define BRILLO_REG 0x0082//0x1000
#define BRILLO_MIN 0x0000//0
#define BRILLO_MAX 0x6400//100
#define BRILLO_INC 0x0A00//10

#define PRESION_PAG 7
#define PRESION_REG 0x1002
#define PRESION_MIN 4
#define PRESION_MAX 22
#define PRESION_INC 1 

#define TIEMPO_PAG 8
#define TIEMPO_REG 0x1004
#define TIEMPO_MIN 0
#define TIEMPO_MAX 50//Para permitir automatico-Antes era 45
#define TIEMPO_INC 5

#define HUMEDAD_PAG 9
#define HUMEDAD_REG 0x1006
#define HUMEDAD_MIN 0
#define HUMEDAD_MAX 9
#define HUMEDAD_INC 1


void encoder_page_change(void);
#endif

