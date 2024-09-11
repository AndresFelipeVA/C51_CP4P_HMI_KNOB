#include "sys.h"
#include "timer.h"
#include "uart.h"

S_UART uart2;
u8 uart2RxBuf[UART2_RX_BYTE_SIZE];

S_UART uart3;
u8 uart3RxBuf[UART3_RX_BYTE_SIZE];

S_UART uart4;
u8 uart4RxBuf[UART4_RX_BYTE_SIZE];

S_UART uart5;
u8 uart5RxBuf[UART5_RX_BYTE_SIZE];

void uart_init(UartNum UARTx, u32 baud, UartMode mode)
{
    switch (UARTx)
    {
        case UART2:
            Uart2_Init(baud, mode);
            break;
        case UART3:
            Uart3_Init(baud, mode);
            break;
        case UART4:
            Uart4_Init(baud, mode);
            break;
        case UART5:
            Uart5_Init(baud, mode);
            break;
        default:
            break;
    }
}
/******************************************************** UART2 *******************************************************/
#ifdef UART2_ENABLE

/***********************************************************
* description: Uart2的初始化，主要包括引脚和中断初始化
* param {u32} baud 波特率
* return {void}
***********************************************************/
void Uart2_Init(u32 baud, UartMode mode)
{
    switch (mode)
    {
        case MODE_8N1:
            /* code */
            break;

        default:
            break;
    }
    MUX_SEL |= 0x40;                        //0100 0000，将第6bit置1，P0.4-0.5端口复用
    P0MDOUT &= 0xDF;                        //1101 1111，将第5bit清0，P0.5为输入模式 RXD
    P0MDOUT |= 0x10;                        //0001 0000，将第4bit置1，P0.4为输出模式 TXD
    ADCON = 0x80;                           //设置SREL0H:L产生波特率
    SCON0 = 0x50;                           //0101 0000，选择模式1，使能REN0允许接收
    PCON &= 0x7F;                           //SMOD置0
    baud = 1024 - (u16)(3225600.0f / baud); //SMOD=0，SREL0H:L=1024-主频/(64*波特率)
                                            //SMOD=1，SREL0H:L=1024-主频/(32*波特率)
    SREL0H = (baud >> 8) & 0xFF;
    SREL0L = baud & 0xFF;

    uart2.rxFlag = RX_FREE;

    ES0 = 1;
    EA = 1; //总中断使能
}

/***********************************************************
* description: Uart2接收中断函数
* param {void}
* return {void}
***********************************************************/
void UART2_ISR_PC(void) interrupt 4
{
    EA = 0;
    if (RI0) //串口接收中断
    {
        uart2.rxCount = 0;
        if (uart2.rxFlag == RX_FREE)
        {
            uart2.rxLen = 0;
            uart2.rxFlag = RX_ING;
        }
        if (uart2.rxFlag == RX_ING)
        {
            uart2RxBuf[uart2.rxLen] = SBUF0;
            uart2.rxLen++;
        }
        RI0 = 0;
    }
    EA = 1;
}

/***********************************************************
* description: Uart2发送字节
* param {u8} dat 字节数据
* return {void}
***********************************************************/
void Uart2_Sendbyte(u8 dat)
{
    SBUF0 = dat;
    while (TI0 == 0)
        ;
    TI0 = 0;
}

/***********************************************************
* description: Uart2发送字符串
* param {u8} *pstr 字符串指针
* param {u16} strlen
* return {*}
***********************************************************/
void Uart2_Sendstring(u8* pstr, u16 strlen)
{
    if ((NULL == pstr) || (0 == strlen))
        return;
    while (strlen--)
    {
        Uart2_Sendbyte(*pstr);
        pstr++;
    }
}

#endif

/******************************************************** UART3 *******************************************************/
#ifdef UART3_ENABLE

/***********************************************************
* description: Uart3的初始化
* param {u32} baud 波特率
* return {void}
***********************************************************/
void Uart3_Init(u32 baud, UartMode mode)
{
    u16 real_baud;
    switch (mode)
    {
        case MODE_8N1:
            /* code */
            break;

        default:
            break;
    }
    MUX_SEL |= 0x20;                             //0010 0000,将第5bit置1，P0.6-0.7端口复用
    P0MDOUT &= 0x7f;                             //0111 1111,将第7bit清零，P0.7为输入模式 RXD
    P0MDOUT |= 0x40;                             //0100 0000,将第6bit置1，P0.6为输出模式 TXD
    SCON1 = 0x90;                                //1001 0000, .7 1=8bit UART; .4 1=接收使能
    real_baud = 1024 - (u16)(6451200.0f / baud); //SMOD=1,SREL0H:L=1024-主频/(32*波特率)
    SREL1H = (real_baud >> 8) & 0xFF;
    SREL1L = real_baud & 0xFF;
    IEN2 = 0x01; //.0 (ES1) USRT3 中断使能控制位,其他位必须写0
    uart3.rxFlag = RX_FREE;
    EA = 1; //中断使能
}

/***********************************************************
* description: Uart3接收中断函数
* param {void}
* return {void}
***********************************************************/
void UART3_ISR_PC(void) interrupt 16
{
    EA = 0;
    if (SCON1 & 0x01) //串口接收中断
    {
        uart3.rxCount = 0;
        if (uart3.rxFlag == RX_FREE)
        {
            uart3.rxLen = 0;
            uart3.rxFlag = RX_ING;
        }
        if (uart3.rxFlag == RX_ING)
        {
            uart3RxBuf[uart3.rxLen] = SBUF1;
            uart3.rxLen++;
        }
        SCON1 = SCON1 & 0xFE;
    }
    EA = 1;
}

/***********************************************************
* description: Uart3发送字节
* param {u8} dat 字节数据
* return {void}
***********************************************************/
void Uart3_Sendbyte(u8 dat)
{
    SBUF1 = dat;
    while ((SCON1 & 0x02) == 0)
        ;
    SCON1 &= 0xfd;
    SCON1 &= 0xfd;
}

/***********************************************************
* description: Uart3发送字符串
* param {u8} *pstr 字符串指针
* param {u16} strlen
* return {*}
***********************************************************/
void Uart3_Sendstring(u8* pstr, u16 strlen)
{
    if ((NULL == pstr) || (0 == strlen))
        return;
    while (strlen--)
    {
        Uart3_Sendbyte(*pstr);
        pstr++;
    }
}

#endif

/******************************************************** UART4 *******************************************************/
#ifdef UART4_ENABLE

/***********************************************************
* description: Uart4的初始化
* param {u32} baud 波特率
* return {void}
***********************************************************/
void Uart4_Init(u32 baud, UartMode mode)
{
    u16 real_baud;
    switch (mode)
    {
        case MODE_8N1:
            /* code */
            break;

        default:
            break;
    }
    SCON2T = 0x80; //1000 0000
    SCON2R = 0x80;
    real_baud = 25804800.0f / baud;
    BODE2_DIV_H = (u8)(real_baud >> 8);
    BODE2_DIV_L = (u8)real_baud;
    IEN1 |= 0x0c; //0000 1100
    P0MDOUT |= 0x01;
    TR4 = 0; //使能Uart4_485控制器接收
    uart4.rxFlag = RX_FREE;
    EA = 1;
}

/***********************************************************
* description: Uart4发送中断函数
* param {void}
* return {void}
***********************************************************/
void Uart4t_Isr() interrupt 10
{
}

/***********************************************************
* description: Uart4接收中断函数
* param {void}
* return {void}
***********************************************************/
void UART4_RX_ISR_PC(void) interrupt 11
{
    EA = 0;
    if (SCON2R & 0x01) //串口接收中断
    {
        uart4.rxCount = 0;
        if (uart4.rxFlag == RX_FREE)
        {
            uart4.rxLen = 0;
            uart4.rxFlag = RX_ING;
        }
        if (uart4.rxFlag == RX_ING)
        {
            uart4RxBuf[uart4.rxLen] = SBUF2_RX;
            uart4.rxLen++;
        }
        SCON2R = SCON2R & 0xFE;
    }
    EA = 1;
}

/***********************************************************
* description: 串口4发送一个字节
* param {u8} dat 要发送的字节
* return {void}
***********************************************************/
void Uart4_Sendbyte(u8 dat)
{
    TR4 = 1;
    SBUF2_TX = dat;
    while ((SCON2T & 0x01) == 0)
        ;
    SCON2T &= 0xFE;
    TR4 = 0;
}

/***********************************************************
* description: 串口4发送一个字符串
* param {u8} *pstr 要发送的字符缓冲区
* param {u16} strlen 要发送的字符长度
* return {void}
***********************************************************/
void Uart4_Sendstring(u8* pstr, u16 strlen)
{
    if ((NULL == pstr) || (0 == strlen))
        return;

    while (strlen--)
    {
        Uart4_Sendbyte(*pstr);
        pstr++;
    }
}
#endif

/******************************************************** UART5 *******************************************************/
#ifdef UART5_ENABLE

/***********************************************************
* description: Uart5的初始化
* param {u32} baud 波特率
* return {void}
***********************************************************/
void Uart5_Init(u32 baud, UartMode mode)
{
    u16 real_baud;
    switch (mode)
    {
        case MODE_8N1:
            /* code */
            break;

        default:
            break;
    }
    SCON3T = 0x80;
    SCON3R = 0x80;
    real_baud = 25804800.0f / baud;
    BODE3_DIV_H = (u8)(real_baud >> 8);
    BODE3_DIV_L = (u8)real_baud;
    IEN1 |= 0x30;
    P0MDOUT |= 0x02;
    TR5 = 0; //使能UART5_485控制器接收
    uart5.rxFlag = RX_FREE;
    EA = 1;
}

/***********************************************************
* description: Uart5发送中断函数
* param {void}
* return {void}
***********************************************************/
void Uart5t_Isr() interrupt 12
{
}

/***********************************************************
* description: Uart5接收中断函数
* param {void}
* return {void}
***********************************************************/
void UART5_RX_ISR_PC(void) interrupt 13
{
    EA = 0;
    if (SCON3R & 0x01) //串口接收中断
    {
        uart5.rxCount = 0;
        if (uart5.rxFlag == RX_FREE)
        {
            uart5.rxLen = 0;
            uart5.rxFlag = RX_ING;
        }
        if (uart5.rxFlag == RX_ING)
        {
            uart5RxBuf[uart5.rxLen] = SBUF3_RX;
            uart5.rxLen++;
        }
        SCON3R = SCON3R & 0xFE;
    }
    EA = 1;
}

/***********************************************************
* description: 串口5发送一个字节
* param {u8} dat 要发送的字节
* return {void}
***********************************************************/
void Uart5_Sendbyte(u8 dat)
{
    TR5 = 1;
    SBUF3_TX = dat;
    while ((SCON3T & 0x01) == 0)
        ;
    SCON3T &= 0xFE;
    TR5 = 0;
}

/***********************************************************
* description: 串口5发送一个字符串
* param {u8} *pstr 要发送的字符缓冲区
* param {u16} strlen 要发送的字符长度
* return {void}
***********************************************************/
void Uart5_Sendstring(u8* pstr, u16 strlen)
{
    if ((NULL == pstr) || (0 == strlen))
        return;
    while (strlen--)
    {
        Uart5_Sendbyte(*pstr);
        pstr++;
    }
}

#endif

void Analyze_8283(void)
{
    u16 regAddr, regNumber;

    P_S_UART uart = &uart2;
    u8* pBuf = uart2RxBuf;
    void (*pSendFuc)(u8*, u16) = Uart2_Sendstring;

    if ((pBuf[0] != 0x5A) || (pBuf[1] != 0xA5))
        return;
    if (pBuf[3] == 0x83)
    {
        if (uart->rxLen != 7)
            return;
        if (pBuf[2] != 0x04)
            return;

        regAddr = ((u16)pBuf[4] << 8) | (u16)pBuf[5];
        regNumber = (u16)pBuf[6];
        read_dgus_vp(regAddr, &pBuf[7], regNumber);
        pBuf[2] = pBuf[2] + (regNumber << 1);
        pSendFuc(pBuf, uart->rxLen + (regNumber << 1));
    }
    else if (pBuf[3] == 0x82)
    {
        regAddr = ((u16)pBuf[4] << 8) | (u16)pBuf[5];
        write_dgus_vp(regAddr, (u8*)&pBuf[6], (pBuf[2] - 3) / 2);
        pBuf[2] = 3;
        pBuf[4] = 0x4F;
        pBuf[5] = 0x4B;
        pSendFuc(pBuf, 6);
    }
}


void uartRun(P_S_UART pUart, void (*pUserApp)(void)) reentrant
{
    if ((pUart->rxFlag == RX_ING) && (pUart->rxCount > 50))
    {
        pUart->rxFlag = RX_DONE;
    }
    if (pUart->rxFlag == RX_DONE)
    {
        pUserApp();
        pUart->rxFlag = RX_FREE;
    }
}
 
/***********************************************************
* description: 放到1ms定时器中判断一包数据接收完毕
* param {*}
* return {*}
***********************************************************/
void Uart_timer(void)
{
    uart2.rxCount++;
    uart3.rxCount++;
    uart4.rxCount++;
    uart5.rxCount++;
}

/***********************************************************
* description: printf重定向到串口2
***********************************************************/
char putchar(char c)
{
    Uart4_Sendbyte(c);
    return c;
}
