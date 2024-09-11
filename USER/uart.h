#ifndef __UART_H__
#define __UART_H__
#include "t5los8051.h"
#include "sys.h"

sbit TR5 = P0 ^ 1; //使能UART5_485
sbit TR4 = P0 ^ 0; //使能UART4_485

#define UART2_ENABLE
#define UART3_ENABLE
#define UART4_ENABLE
#define UART5_ENABLE

/********************************对外函数声明*********************************/

#define RX_FREE            (0x01)
#define RX_ING             (0x02)
#define RX_DONE            (0x03)
#define TX_FREE            (0x01)
#define TX_BUSY            (0x02)

#define UART2_RX_BYTE_SIZE 256
#define UART3_RX_BYTE_SIZE 256
#define UART4_RX_BYTE_SIZE 256
#define UART5_RX_BYTE_SIZE 256

typedef struct _S_UART
{
    u8 rxFlag;
    u16 rxLen;
    u16 rxCount;
}S_UART, *P_S_UART;

typedef enum
{
    UART2 = 2,
    UART3,
    UART4,
    UART5
} UartNum;

typedef enum
{
    MODE_8N1,
    MODE_8E1,
    MODE_8O1,
    MODE_8N2
} UartMode;

extern S_UART uart2;
extern S_UART uart3;
extern S_UART uart4;
extern S_UART uart5;
extern u8 uart2RxBuf[UART4_RX_BYTE_SIZE];
extern u8 uart3RxBuf[UART4_RX_BYTE_SIZE];
extern u8 uart4RxBuf[UART4_RX_BYTE_SIZE];
extern u8 uart5RxBuf[UART4_RX_BYTE_SIZE];
void uart_init(UartNum UARTx, u32 baud, UartMode mode);

void Analyze_8283(void);
void uartRun(P_S_UART pUart, void (*pUserApp)(void)) reentrant;
void Uart_timer(void);
/************************UART2_232_ENABLE*************************/
#ifdef UART2_ENABLE

void Uart2_Init(u32 baud, UartMode mode);
void Uart2_Sendbyte(u8 dat);
void Uart2_Sendstring(u8* pstr, u16 strlen);

#endif

/*******UART3_ENABLE********************************/
#ifdef UART3_ENABLE

void Uart3_Init(u32 baud, UartMode mode);
void Uart3_Sendbyte(u8 dat);
void Uart3_Sendstring(u8* pstr, u16 strlen);

#endif
 
/*******UART4_ENABLE********************************/
#ifdef UART4_ENABLE

void Uart4_Init(u32 baud, UartMode mode);
void Uart4_Sendbyte(u8 dat);
void Uart4_Sendstring(u8* pstr, u16 strlen);

#endif

/*******UART5_ENABLE********************************/
#ifdef UART5_ENABLE

void Uart5_Init(u32 baud, UartMode mode);
void Uart5_Sendbyte(u8 dat);
void Uart5_Sendstring(u8* pstr, u16 strlen);
#endif


#endif
