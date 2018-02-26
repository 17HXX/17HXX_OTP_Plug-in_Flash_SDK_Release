/*
 * pwm_17H26.c
 *
 *  Created on: 2015-11-27
 *      Author: Administrator
 */

#include "../tl_common.h"
#include "../mcu/pwm.h"
#define		PHASE_TIME_BASE		0x800788
#define		CSC_VALUE_BASE		0x800794
#define		CYC_VALUE_BASE		0x800796
#define		SFN_VALUE_BASE		0x8007ac

//Enable the specified pwm, v is the PWMN
#define		EN_PWM(v)			(*(volatile unsigned char  *)0x800780 |= (1<<v))

//Disable the specified pwm, v is the PWMN
#define 	DIS_PWM(v)			(*(volatile unsigned char  *)0x800780 &= ~(1<<v))

//Set PWM clock frequency, v is the desired clock value, default to SYS_CLK
#define		SET_PWMCLK(v)		(*(volatile unsigned char  *)0x800781 = v)

//PWM output invert
#define		INVERT_PWM(v)		(*(volatile unsigned char  *)0x800783 |= (1<<v))



//Enable pwm output polarity
#define		EN_PWMPOL(v)		(*(volatile unsigned char  *)0x800785 |= (1<<v))

#define		DIS_PWMPOL(v)		(*(volatile unsigned char  *)0x800785 &= ~(1<<v))

//Enable pwm interrupt, v is the interrupt source
#define		EN_PWMINT(v)		(*(volatile unsigned char  *)0x8007b0 |= (1<<v))
#define		DIS_PWMINT(v)		(*(volatile unsigned char  *)0x8007b0 &= ~(1<<v))

//Enable PWM interrupt mask
#define		EN_PWMINTM			(*(volatile unsigned char  *)0x800640 |= 0x20)//////different from 8266,changed by chen
#define		DIS_PWMINTM			(*(volatile unsigned char  *)0x800640 &= 0xDF)//////changed by chen

//Clear interrupt status, v is the interrupt source
#define		CLR_PWMIRQS(v)	(*(volatile unsigned char  *)0x8007b1 |= (1<<v))

//Set Phase time, v is the PWM number, n is the desired value
#define		SET_PWMPT(v,n)		write_reg16((PHASE_TIME_BASE + v*2),n)

//PWM count status cycle value set function, v is the PWM numer, n is the desired value
#define		SET_PWMCSCV(v,n)	write_reg16((CSC_VALUE_BASE + v*4),n)

//PWM cycle value set function, v is the PWM numer, n is the desired value
#define		SET_PWMCYCV(v,n)	write_reg16((CYC_VALUE_BASE + v*4),n)

//Set number of signal frames, v can only be pwm0 and pwm1, n is the setting value
#define		SET_PWMSFN(v,n)		write_reg16((SFN_VALUE_BASE + v*2),n)


//Set pwm mode, v can only be pwm0 and pwm1, n is the mode
#define		SET_PWMMODE(v,n)	{\
								*(volatile unsigned char  *)0x800782 &= ~(n<<(v*2));\
								*(volatile unsigned char  *)0x800782 |= (n<<(v*2));\
								}

//PWM-INV output invert
#define		INVERT_PWMINV(v)	(*(volatile unsigned char  *)0x800784 |= (1<<v))
#define     INVERT_PWMCYC(v)    (*(volatile unsigned char  *)0x800785 |= (1<<v))

void sub_bit_set(int addr, char bit_pos)
{
	char v, bit_set_mask;
	v = read_reg8(addr);
	bit_set_mask = 1 << bit_pos;
	v = bit_set_mask | v;
	v = write_reg8(addr, v);
}

void sub_bit_clr(int addr, char bit_pos)
{
	char v, bit_set_mask;
	v = read_reg8(addr);
	bit_set_mask = 0xff ^ (1 << bit_pos);
	v = bit_set_mask & v;
	v = write_reg8(addr, v);
}



/************************************************************
*	@brief	Initiate the PWM function include seting and enabling the PWM clock.
*			For test pin number 22 - 27 is the PWM output pin.
*
*	@param	pwmCLKdiv - pwm clk divider
*
*	@return	None
*/
void pwm_Init(unsigned char pwmCLKdiv){
	SET_PWMCLK(pwmCLKdiv);//PWMCLK = SYSCLK/4
	sub_bit_set(0x800064,3);//PWM CLK Enable
	sub_bit_clr(0x800061,3);// disable PWM reset, wakeup
	//////SETB(0x800064,0x10);//PWM CLK Enable
    //////CLRB(0x800061,0x10);// disable PWM reset, wakeup
	//write_reg8(0x800586, 0xc0);	//GPIO disable, gp0, gp1, gp4,gp5
}
/********************************************************************************
*	@brief	open a pwm channel and setting the parameters
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmWorkM - enum variable of pwm work mode
*			phaseTime - delay time of the pwm channel before enter into the count status
*			cscValue - count status value
*			cycVlaue - cycle value
*			sfValue - signal frame value for the COUNT and IR mode
*
*	@return	'1' set success; '0' set error, if you set pwm2 - pwm5 to work on the other not normal mode, the function will return error.
*
*/
unsigned char pwm_Open(enum PWMN pwmNumber,enum PWMWM pwmWorkM,unsigned short phaseTime,unsigned short cscValue,unsigned short cycValue,unsigned short sfValue){
	unsigned long setValue = 0;
	unsigned char pwmN,pwmM;
	pwmN = (unsigned char)pwmNumber;
	pwmM = (unsigned char)pwmWorkM;
	if(pwmN>PWM0&& pwmM!=NORMAL){///only PWM0 has counting mode
		return 0;
	}
	SET_PWMPT(pwmN,phaseTime);/////same with 8266:phase
	setValue = (unsigned long)cscValue;
	setValue = setValue + ((unsigned long)cycValue<<16);
	write_reg32((CSC_VALUE_BASE + pwmN*4),setValue);/////same with 8266: count status value and cycle value
	/***set pwm work mode(only for pwm0)***/
	if (pwmN<1) {///only pwm0:normal mode,count mode
		write_reg8(0x800782, (read_reg8(0x800782)&0xfc)+pwmM);
	}

	if(pwmWorkM != NORMAL){
		SET_PWMSFN(pwmN,sfValue);
	}
	EN_PWM(pwmN);//Should be here, donot enable the PWM unitil all the settings done
	return 1;
}
/*******************************************************************************
*
*	@brief	close a pwm channel and reset the settings to default
*
*	@param	pwmNumber - enum variable of pwm channel number

*
*	@return	None
*/
void pwm_Close(enum PWMN pwmNumber){
	unsigned char pwmN;
	pwmN = (unsigned char)pwmNumber;
	SET_PWMPT(pwmN,0);////clear phase time
	write_reg32((CSC_VALUE_BASE + pwmN*4),0);////clear count status vale and cycle value
	SET_PWMMODE(pwmN,0);
	if(pwmN<1){
		SET_PWMSFN(pwmN,0);
	}
	DIS_PWM(pwmN);
}
/*******************************************************************************
*
*	@brief	set the duty cycle of a pwm channel
*
*	@param	pwmNumber - enum variable of pwm channel number
*			cscValue - count status value
*			cycVlaue - cycle value

*
*	@return	'1' set success; '0' set error, if csValue>cycValue
*/
unsigned char pwm_DutyCycleSet(enum PWMN pwmNumber,unsigned short csValue,unsigned short cycValue){
	unsigned char pwmN;
	pwmN = (unsigned char)pwmNumber;
	if(cycValue >csValue){
		write_reg16((CSC_VALUE_BASE + pwmN*4),csValue);
		write_reg16((CYC_VALUE_BASE + pwmN*4),cycValue);//////CYC_   not  CSC_
		return 1;
	}
	return 0;
}
/********************************************************
*	@brief	enable pwm interrupt
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmINTM - enum variable of pwm channel's interrupt mode
*
*	@return	None
*/
unsigned char pwm_InterruptEnable(enum PWMIRQSOURCE pwmIrqSrc){
	EN_PWMINT(pwmIrqSrc);
	EN_PWMINTM;
	*(volatile unsigned char  *)0x800643 |= 0x01;//EN_IRQ
	return 1;
}
/********************************************************
*	@brief	disable pwm interrupt
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmINTM - enum variable of pwm channel's interrupt mode
*
*	@return	None
*/
unsigned char pwm_InterruptDisable(enum PWMIRQSOURCE pwmIrqSrc){
	DIS_PWMINT(pwmIrqSrc);
	return 1;
}
/**********************************************************************
*
*	@brief	get interrupt source
*
*	@param	none
*
*	@return	irq_source - interrupt source, enum variable
*/
enum PWMIRQSOURCE pwm_InterruptSourceGet(void ){
	unsigned char IrqStatus = read_reg8(0x8007b1);
	int i = 0;

	if (IrqStatus == 0) {
        return NOIRQ;
	}
	else {
        for (i=PWM0PNUM; i<PWMIRQSOURCENUM; i++) {/////0x8007b1 default value is 0x00,so bit1 will be always 0,for bit1 is rsvd.reserved. by chen
        	if ((1<<i) & IrqStatus)
        		break;
        }
        return (enum PWMIRQSOURCE)i;
	}
}
unsigned char IsPWMn_Interr(enum PWMIRQSOURCE pwm_ir_src){
	unsigned char IrqStatus = read_reg8(0x8007b1);
	IrqStatus &= (1<<pwm_ir_src);
	if(IrqStatus != 0x00){
		return 0x01;///////pwm_ir_src  interrupt
	}
	return 0x00;	//////pwm_ir_src no interrupt
}

/********************************************************
*	@brief	clear interrupt status
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmINTM - enum variable of pwm channel's interrupt mode
*
*	@return	None
*/
void pwm_InterruptStatusClr(enum PWMIRQSOURCE irq_src){
	unsigned char irqS;
	irqS = (unsigned char)irq_src;
	CLR_PWMIRQS(irqS);
}

/********************************************************************
*
*	@brief	Invert PWM-INV output (would generate the same output waveform as PWMN)
*
*	@param	pwmNumber - enum variable of pwm number
*
*	@return	None
*/
void pwm_INVInvert(enum PWMN pwmNumber){
	INVERT_PWMINV((unsigned char)pwmNumber);
}
/********************************************************************
*   @brief  the polarity don't invert during phase time ,invert during the cout time and remaining time
*
*
*/
void pwm_CYCInvert(enum PWMN pwmNumber){
	INVERT_PWMCYC((unsigned char)pwmNumber);
}

void pwm_start(enum PWMN pwmNumber){
	EN_PWM(pwmNumber);
}

void pwm_stop(enum PWMN pwmNumber){
	DIS_PWM(pwmNumber);
}
