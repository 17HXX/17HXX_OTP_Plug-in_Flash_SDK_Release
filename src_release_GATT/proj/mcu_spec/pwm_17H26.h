/*
 * pwm_17H26.h
 *
 *  Created on: 2015-11-27
 *      Author: Administrator
 */

#ifndef PWM_17H26_H_
#define PWM_17H26_H_

/*************************************************************
*	@brief		enum variable, the number of PWM channels supported
*
*/
enum PWMN{
	PWM0 = 0,
	PWM1,
	PWM2,
	PWM3,
};


/*************************************************************
*	@brief		enum variable used for PWM work mode setting
*
*/
enum PWMWM{
	NORMAL,
	COUNT,
};


/*************************************************************
*	@brief		enum variable of interrupt source
*

enum INTSOURCE{
	SFNIRQ,//completed a pulse group IRQ, only counting mode and IR mode
	FDIRQ,//Frame done IRQ
};
*/
/********************************************************
*
*	pwm interrupt source
*/
/*enum PWMIRQSOURCE{
	NOIRQ = 0xff,
	PWM0PNUM = 0,
	PWM1PNUM,
	PWM0CYCLEDONE,
	PWM1CYCLEDONE,
	PWM2CYCLEDONE,
	PWM3CYCLEDONE,
	PWM4CYCLEDONE,
	PWM5CYCLEDONE,
	PWMIRQSOURCENUM,
};*/
enum PWMIRQSOURCE{
	NOIRQ = 0xff,
	PWM0PNUM = 0,
	PWM0CYCLEDONE=2,
	PWM1CYCLEDONE,
	PWM2CYCLEDONE,
	PWM3CYCLEDONE,
	PWMIRQSOURCENUM,
};



/************************************************************
*	@brief	Initiate the PWM function include seting and enabling the PWM clock.
*			For test pin number 22 - 27 is the PWM output pin.
*
*	@param	None
*
*	@return	None
*/
extern void pwm_Init(unsigned char pwmCLKdiv);

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
extern unsigned char pwm_Open(enum PWMN pwmNumber, enum PWMWM pwmWorkM, unsigned short phaseTime, unsigned short cscValue, unsigned short cycValue, unsigned short sfValue );

/*******************************************************************************
*
*	@brief	close a pwm channel and reset the settings to default
*
*	@param	pwmNumber - enum variable of pwm channel number

*
*	@return	None
*/
extern void pwm_Close(enum PWMN pwmNumber);

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
extern unsigned char pwm_DutyCycleSet(enum PWMN pwmNumber, unsigned short csValue,unsigned short cycValue);

/********************************************************
*	@brief	enable pwm interrupt
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmINTM - enum variable of pwm channel's interrupt mode
*
*	@return	None
*/
extern unsigned char pwm_InterruptEnable(enum PWMIRQSOURCE pwmIrqSrc);

/********************************************************
*	@brief	disable pwm interrupt
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmM - enum variable of pwm work mode
*
*	@return	None
*/
extern unsigned char pwm_InterruptDisable(enum PWMIRQSOURCE pwmIrqSrc);
/**********************************************************************
*
*	@brief	get interrupt source
*
*	@param	none
*
*	@return	irq_source - interrupt source, enum variable
*/
extern enum PWMIRQSOURCE pwm_InterruptSourceGet(void );

/********************************************************
*	@brief	clear interrupt status
*
*	@param	pwmNumber - enum variable of pwm channel number
*			pwmINTM - enum variable of pwm channel's interrupt mode
*
*	@return	None
*/
extern void pwm_InterruptStatusClr(enum PWMIRQSOURCE irq_src);

/********************************************************************
*
*	@brief	Invert PWM-INV output (would generate the same output waveform as PWMN)
*
*	@param	pwmNumber - enum variable of pwm number
*
*	@return	None
*/
extern void pwm_INVInvert(enum PWMN pwmNumber);
/*****************************************************************
*    @brief     when the cycle of pwm complete,the status register .i.e 0x8007b1 will set.
*	     	      so no matter whether interruption is occured,the set of the status register bits follow with the completion of cycle time
*/
unsigned char IsPWMn_Interr(enum PWMIRQSOURCE pwm_ir_src);
#endif /* PWM_17H26_H_ */
