/*--------------------------------------------------------------------------
T5L1.H

Header file for T5L Embedded 8051 microcontroller.
--------------------------------------------------------------------------*/

#ifndef __M5_H__
#define __M5_H__

/* Byte Register */
/*Register Location     Reset value     Description */
sfr P0     				= 0x80;    //    FFh         Port 0         				
sfr SP     				= 0x81;    //    07h         Stack Pointer
sfr DPL    				= 0x82;    //    00h         Data Pointer Low
sfr DPH    				= 0x83;    //    00h         Data Pointer High
sfr DPL1   				= 0x84;    //    00h         Data Pointer 1 Low  
sfr DPH1   				= 0x85;    //    00h         Data Pointer 1 High 
sfr WDTREL 				= 0x86;    //    00h         Watchdog Timer Reload register
sfr PCON   				= 0x87;    //    00h         Power Control
sfr TCON   				= 0x88;    //    00h         Timer/Counter Control Register
sfr TMOD   				= 0x89;    //    00h         Timer Mode Register
sfr TL0    				= 0x8A;    //    00h         Timer 0, low byte
sfr TL1    				= 0x8B;    //    00h         Timer 1, low byte
sfr TH0    				= 0x8C;    //    00h         Timer 0, high byte
sfr TH1    				= 0x8D;    //    00h         Timer 1, high byte
sfr CKCON  				= 0x8E;    //    71h         Clock Control Register
sfr CAN_CR  			= 0x8F;

sfr P1     				= 0x90;    //    FFh         Port 1
sfr CAN_IR  			= 0x91;           				                 
sfr DPSEL  				= 0x92;    //    00h         Data Pointer Select Register                      
sfr DPC    				= 0x93;    //    00h         Data Pointer Control Register                     
sfr PAGESEL				= 0x94;    //    01h         Program Memory Page selector                    
sfr D_PAGESEL			= 0x95;    //    01h         External Data Memory Page selector 
sfr SCON2T				= 0x96;                       
sfr SCON2R  			= 0x97;         
sfr SCON0  				= 0x98;    //    00h         Serial Port 0, Control Register                
sfr SBUF0  				= 0x99;    //    00h         Serial Port 0, Data Buffer        
sfr IEN2   				= 0x9A;    //    00h         Interrupt Enable Register 2                     
sfr SCON1  				= 0x9B;    //    00h         Serial Port 1, Control Register        
sfr SBUF1  				= 0x9C;    //    00h         Serial Port 1, Data Buffer                 
sfr SREL1L 				= 0x9D;    //    00h         Serial Port 1, Reload Register, low byte    
sfr SBUF2_TX  			= 0x9E;    //    00h         Serial Port 1, Data Buffer                 
sfr SBUF2_RX 			= 0x9F;

sfr P2     				= 0xA0;    //    FFh         Port 2           				                       
sfr DMAS0  				= 0xA1;    //    00h         DMA Source Address Register 0 
sfr DMAS1  				= 0xA2;    //    00h         DMA Source Address Register 1  
sfr DMAS2  				= 0xA3;    //    00h         DMA Source Address Register 2  
sfr DMAT0  				= 0xA4;    //    00h         DMA Source Target Register 0  
sfr DMAT1  				= 0xA5;    //    00h         DMA Source Target Register 1  
sfr DMAT2  				= 0xA6;    //    00h         DMA Source Target Register 2  
sfr SCON3T  			= 0xA7;                    
sfr IEN0   				= 0xA8;    //    00h         Interrupt Enable Register 0                    
sfr IP0    				= 0xA9;    //    00h         Interrupt Priority Register 0                   
sfr SREL0L 				= 0xAA;    //    D9h         Serial Port 0, Reload Register, low byte                   
sfr SCON3R   			= 0xAB;    //    00h         I2C source and fixed or user IO select                     
sfr SBUF3_TX 			= 0xAC;    //    00h         In System Configuration Data[7:0]                     
sfr SBUF3_RX 			= 0xAD;    //    00h         In System Configuration Data[15:8]                      
sfr BODE3_DIV_H 		= 0xAE;    //    00h         In System Configuration Data[23:16]                      
sfr BODE3_DIV_L			= 0xAF;    //    00h         In System Configuration Data[31:24] 
 
sfr P3     				= 0xB0;    //    FFh         Port 3    
sfr DMAC0  				= 0xB1;    //    00h         DMA Byte Counter Register 0   
sfr DMAC1  				= 0xB2;    //    00h         DMA Byte Counter Register 1  
sfr DMAC2  				= 0xB3;    //    00h         DMA Byte Counter Register 2  
sfr DMASEL 				= 0xB4;    //    00h         DMA Channel Select Register 
sfr DMAM0  				= 0xB5;    //    00h         DMA Mode Register 0  
sfr DMAM1  				= 0xB6;    //    1Fh         DMA Mode Register 1  
sfr P0MDOUT        		= 0xB7;
sfr IEN1   				= 0xB8;    //    00h         Interrupt Enable Register 1         
sfr IP1    				= 0xB9;    //    00h         Interrupt Priority Register 1         
sfr SREL0H 				= 0xBA;    //    03h         Serial Port 0, Reload Register, high byte
sfr SREL1H 				= 0xBB;    //    03h         Serial Port 1, Reload Register, high byte  
sfr P1MDOUT        		= 0xBC;    
sfr P2MDOUT        		= 0xBD;
sfr P3MDOUT        		= 0xBE;
sfr IRCON2 				= 0xBF;    //    00h         Interrupt Request Control 2 Register  
           				
sfr IRCON  				= 0xC0;    //    00h         Interrupt Request Control Register                  
sfr CCEN   				= 0xC1;    //    00h         Compare/Capture Enable Register                    
sfr CCL1   				= 0xC2;    //    00h         Compare/Capture Register 1, low byte                  
sfr CCH1   				= 0xC3;    //    00h         Compare/Capture Register 1, high byte               
sfr CCL2   				= 0xC4;    //    00h         Compare/Capture Register 2, low byte                         
sfr CCH2   				= 0xC5;    //    00h         Compare/Capture Register 2, low byte                        
sfr CCL3   				= 0xC6;    //    00h         Compare/Capture Register 3, low byte
sfr CCH3   				= 0xC7;    //    00h         Compare/Capture Register 3, high byte                 
sfr T2CON  				= 0xC8;    //    00h         Timer 2 Control Register  
sfr MUX_SEL   			= 0xC9;
sfr TRL2L   			= 0xCA;    //    00h         Compare/Reload/Capture Register, low byte      
sfr TRL2H   			= 0xCB;    //    00h         Compare/Reload/Capture Register, high byte          
sfr TL2    				= 0xCC;    //    00h         Timer 2, low byte                                                                     
sfr TH2    				= 0xCD;    //    00h         Timer 2, high byte

sfr PSW    				= 0xD0;    //    FFh         Program Status Word   				
sfr IEN4  				= 0xD1;    //    00h         Interrupt Enable Register 4             				
sfr ADCON  				= 0xD8;    //    00h         Serial Port 0 Baud Rate Select register (only adcon.7 bit used)  
sfr BODE2_DIV_H  		= 0xD9;
sfr I2CDAT 				= 0xDA;    //    00h         I2C Data Register      
sfr I2CADR 				= 0xDB;    //    00h         I2C Address Register      
sfr I2CCON 				= 0xDC;    //    00h         I2C Control Register             
sfr I2CSTA 				= 0xDD;    //    00h         I2C Status Register 

sfr ACC    				= 0xE0;    //    FFh         Accumulator           				          
sfr SPSTA  				= 0xE1;    //    00h         Serial Peripheral(SPI) Status Register                          
sfr SPCON  				= 0xE2;    //    14h         Serial Peripheral(SPI) Control Register                     
sfr SPDAT  				= 0xE3;    //    00h         Serial Peripheral(SPI) Data Register
sfr SPSSN  				= 0xE4;    //    FFh         Serial Peripheral(SPI) Slave Select Register  
sfr MAC_MODE			= 0xE5;    //    00h         RTC Command Register      
sfr DIV_MODE			= 0xE6;    //    00h         RTC Select Register      
sfr BODE2_DIV_L			= 0xE7;    //    00h         RTC Data Register    
sfr CAN_ET  			= 0xE8;
sfr MD0    				= 0xE9;    //    00h         Multiplication/Division Register 0                     
sfr MD1    				= 0xEA;    //    00h         Multiplication/Division Register 1                      
sfr MD2    				= 0xEB;    //    00h         Multiplication/Division Register 2
sfr MD3    				= 0xEC;    //    00h         Multiplication/Division Register 3     
sfr MD4    				= 0xED;    //    00h         Multiplication/Division Register 4                 
sfr MD5    				= 0xEE;    //    00h         Multiplication/Division Register 5                    
sfr ARCON  				= 0xEF;    //    00h         Arithmetic Control Register

sfr B      				= 0xF0;    //    FFh         B Register 
sfr ADR_H				= 0xF1;              		       
sfr ADR_M   			= 0xF2;    
sfr ADR_L        	    = 0xF3;     
sfr ADR_INC     	    = 0xF4;        
sfr ISCHEADER2  	    = 0xF5;        
sfr ISCHEADER3  	    = 0xF6;                		           
sfr SRST   				= 0xF7;           		           
sfr RAMMODE				= 0xF8;        		           
sfr PORTDRV 			= 0xF9;          		           
sfr DATA3   			= 0xFA;       		           
sfr DATA2   		    = 0xFB;    
sfr DATA1   			= 0xFC;       		           
sfr DATA0   		    = 0xFD;  
sfr EXADR   			= 0xFE;       		           
sfr EXDATA   		    = 0xFF; 

/* BIT Register */

/* PSW:Program Status Word->Byte Address:0xD0,bit Address:0xD0~0xD7 */
sbit CY    		= 0xD7; 
sbit AC    		= 0xD6; 
sbit F0    		= 0xD5; 
sbit RS1   		= 0xD4; 
sbit RS0   		= 0xD3; 
sbit OV    		= 0xD2; 
sbit F1    		= 0xD1;
sbit P     		= 0xD0; 

/* TCON:Timer/Counter Control Register->Byte Address:0x88,bit Address:0x88~0x8F */
sbit TF1   		= 0x8F; 
sbit TR1   		= 0x8E;
sbit TF0   		= 0x8D;
sbit TR0   		= 0x8C;
sbit IE1   		= 0x8B;
sbit IT1   		= 0x8A;
sbit IE0   		= 0x89;
sbit IT0   		= 0x88;

/* T2CON:Timer 2 Control Register->Byte Address:0xC8,bit Address:0xC8~0xCF */
sbit T2PS  		= 0xCF; 
sbit I3FR  		= 0xCE;
sbit I2FR  		= 0xCD;
sbit T2R1  		= 0xCC;
sbit T2R0  		= 0xCB;
sbit T2CM  		= 0xCA;
sbit T2I1  		= 0xC9;
sbit T2I0  		= 0xC8;

/* S0CON:Serial Port 0,Control Register->Byte Address:0x98,bit Address:0x98~0x9F */
sbit SM0   		= 0x9F; 
sbit SM1   		= 0x9E;
sbit SM20  		= 0x9D;
sbit REN0  		= 0x9C;
sbit TB80  		= 0x9B;
sbit RB80  		= 0x9A;
sbit TI0   		= 0x99;
sbit RI0   		= 0x98;

/* IEN0:Interrupt Enable Register 0->Byte Address:0xA8,bit Address:0xA8~0xAF */
sbit EA   		= 0xAF; 
sbit WDT   		= 0xAE;
sbit ET2   		= 0xAD;
sbit ES0   		= 0xAC;
sbit ET1   		= 0xAB;
sbit EX1   		= 0xAA;
sbit ET0   		= 0xA9;
sbit EX0   		= 0xA8;

/* IEN1:Interrupt Priority Register/Enable Register 1 */
sbit EXEN2 		= 0xBF; 
sbit SWDT  		= 0xBE;
sbit ES3R   	= 0xBD;
sbit ES3T   	= 0xBC;
sbit ES2R   	= 0xBB;
sbit ES2T   	= 0xBA;
sbit ECAN   	= 0xB9;
sbit EX7   		= 0xB8;

/* IRCON:Interrupt Request Control Register->Byte Address:0xC0,bit Address:0xC0~0xC7 */
sbit EXF2  		= 0xC7;
sbit TF2   		= 0xC6;
sbit IEX6  		= 0xC5;
sbit IEX5  		= 0xC4;
sbit IEX4  		= 0xC3;
sbit IEX3  		= 0xC2;
sbit IEX2  		= 0xC1;
sbit IADC  		= 0xC0;

/* ADCON:Serial Port 0 Baud Rate Select register (only adcon.7 bit used) */
sbit BD    		= 0xDF;

/* P0:Port 0->Byte Address:0x80,bit Address:0x80~0x87 */
sbit P00 		= 0x80;
sbit P01 		= 0x81;
sbit P02 		= 0x82;
sbit P03 		= 0x83;
sbit P04 		= 0x84;
sbit P05 		= 0x85;
sbit P06 		= 0x86;
sbit P07 		= 0x87; 

/* P1:Port 1->Byte Address:0x90,bit Address:0x90~0x97 */
sbit P10 		= 0x90;
sbit P11 		= 0x91;
sbit P12 		= 0x92;
sbit P13 		= 0x93;
sbit P14 		= 0x94;
sbit P15 		= 0x95;
sbit P16 		= 0x96;
sbit P17 		= 0x97; 

/* P2:Port 2->Byte Address:0xA0,bit Address:0xA0~0xA7 */
sbit P20 		= 0xA0;
sbit P21 		= 0xA1;
sbit P22 		= 0xA2;
sbit P23 		= 0xA3;
sbit P24 		= 0xA4;
sbit P25 		= 0xA5;
sbit P26 		= 0xA6;
sbit P27 		= 0xA7; 

/* P3:Port 3->Byte Address:0xB0,bit Address:0xB0~0xB7 */
sbit P30 		= 0xB0;
sbit P31 		= 0xB1;
sbit P32 		= 0xB2;
sbit P33 		= 0xB3;
sbit P34 		= 0xB4;
sbit P35 		= 0xB5;
sbit P36 		= 0xB6;
sbit P37 		= 0xB7; 

/* RAMMODE:Misc Control Register->Byte Address:0xF8,bit Address:0xF8~0xFF */
//sbit ISCEN 		= 0xF8;
//sbit DPRAMWP	= 0xF9;
//sbit PLLLOCK	= 0xFA;
//sbit PLLPWD		= 0xFB;
sbit APP_ACK	= 0xFC;
sbit APP_RW 	= 0xFD;
sbit APP_EN 	= 0xFE;
sbit APP_REQ 	= 0xFF; 
#endif