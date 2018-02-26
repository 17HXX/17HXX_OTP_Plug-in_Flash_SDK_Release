/**************************************************************************************************
  Filename:       	uart.h
  Author:			
  Created Date:	2016/06/05

  Description:    This file contains the details of enum variables and functions used in the uart.c file


**************************************************************************************************/
#ifndef 	uart_H
#define 	uart_H

#include "../mcu/register.h"
#include "../common/compatibility.h"
#include "../common/utility.h"

enum HARDWARECONTROL{
	CTSWODDPARITY = 0x0e,
	CTSWEVENPARITY = 0x06,
	CTSONLY = 0x02,
	ODDPARITY = 0x0C,
	EVENPARITY = 0x04,
	NOCONTROL = 0x00,
};
enum UARTIRQSOURCE{
	UARTRXIRQ,
	UARTTXIRQ,
};

#define CLK32M_UART9600			uart_Init(237,13,1,1,NOCONTROL)
#define	CLK32M_UART115200		uart_Init(19,13,1,1,NOCONTROL)
#define	CLK16M_UART115200		uart_Init(9,13,1,1,NOCONTROL)
#define	CLK16M_UART9600			uart_Init(103,15,1,1,NOCONTROL)

//UART_TX/UART_RX gpio pin config
#define	   UART_GPIO_CFG_PA6_PA7()  do{\
										*(volatile unsigned char  *)0x800586 &= 0x3f;\
										*(volatile unsigned char  *)0x8005b0 |= 0x80;\
								    }while(0)
#define	   UART_GPIO_CFG_PB2_PB3()  do{\
										*(volatile unsigned char  *)0x80058e &= 0xf3;\
										*(volatile unsigned char  *)0x8005b1 |= 0x0c;\
								    }while(0)
#define	   UART_GPIO_CFG_PC2_PC3()  do{\
										*(volatile unsigned char  *)0x800596 &= 0xf3;\
										*(volatile unsigned char  *)0x8005b2 |= 0x0c;\
								    }while(0)

/**********************************************************
*
*	@brief	reset uart module
*
*	@param	none
*
*	@return	none
*/
extern void uart_Reset(void );


/**********************************************************
*
*	@brief	clear error state of uart rx, maybe used when application detected UART not work
*
*	@parm	none
*
*	@return	'1' RX error flag rised and cleard success; '0' RX error flag not rised
*
*/
unsigned char uart_ErrorCLR(void);


/*******************************************************
*
*	@brief	uart initiate, set uart clock divider, bitwidth and the uart work mode
*
*	@param	uartCLKdiv - uart clock divider
*			bwpc - bitwidth, should be set to larger than 2
*			en_rx_irq - '1' enable rx irq; '0' disable.
*			en_tx_irq - enable tx irq; '0' disable.
*			hdwC - enum variable of hardware control functions
*
*	@return	'1' set success; '0' set error probably bwpc smaller than 3.
*
*		BaudRate = sclk/((uartCLKdiv+1)*(bwpc+1))
*		SYCLK = 16Mhz
		115200		9			13
		9600		103			15
*
*		SYCLK = 32Mhz
*		115200		19			13
		9600		237			13
*/
extern unsigned char uart_Init(unsigned short uartCLKdiv, unsigned char bwpc,unsigned char en_rx_irq,unsigned char en_tx_irq,enum HARDWARECONTROL hdwC);



/********************************************************************************
*	@brief	uart send data function, this  function tell the DMA to get data from the RAM and start
*			the DMA send function
*
*	@param	sendBuff - send data buffer
*
*	@return	'1' send success; '0' DMA busy
*/
extern unsigned char uart_Send(unsigned char* addr);


/********************************************************************
*
*	@brief	uart receive function, call this function to get the UART data
*
*	@param	userDataBuff - data buffer to store the uart data
*
*	@return	'0' rx error; 'rxLen' received data length
*/
//extern unsigned short uart_Rec(unsigned char* addr);

/******************************************************************************
*
*	@brief		get the uart IRQ source and clear the IRQ status, need to be called in the irq process function
*
*	@return		uart_irq_src- enum variable of uart IRQ source, 'UARTRXIRQ' or 'UARTTXIRQ'
*
*/
extern enum UARTIRQSOURCE uart_IRQSourceGet(void);

/****************************************************************************************
*
*	@brief	data receive buffer initiate function. DMA would move received uart data to the address space, uart packet length
*			needs to be no larger than (recBuffLen - 4).
*
*	@param	*recAddr:	receive buffer's address info.
*			recBuffLen:	receive buffer's length, the maximum uart packet length should be smaller than (recBuffLen - 4)
*
*	@return	none
*/

extern void uart_RecBuffInit(unsigned char *recAddr, unsigned short recBuffLen);

#endif
