
//  RUN_ALL_IN_RAM 必须从工程参数设置，因为有几个地方依赖, // @ 同时要修改  boot.link 最后 bss 映射的地方.  时钟可能要更改 32M,  32M 更快， 8M 功耗更低
	#define RUN_ALL_IN_RAM		0				// @ 同时要修改  boot.link 最后 bss 映射的地方.  时钟可能要更改 32M,  32M 更快， 8M 功耗更低
	#define _BURN_PROOF_		0				// 每次重新上电，延迟 1 秒，提供机会重新烧写, not tested

	.code	16

	.equ RAM_SIZE,				0x1800			// 0x4000 是 16K,  根据芯片实际大小调整

	#define REMOVE_IRQ			1				//  check app_config.h,  必须一致
	#define HIGH_OTP_SPEED		1
	#define HIGH_SPI_SPEED		0
	#define RSV_RAM_FOR_APP		116				// 17H26, 与 cstartup.s 共享内存,  rf_rx_buff要128 bytes, 保证cstartup.s大于 128 bytes
	.equ IRQ_STK_SIZE,			0x40			// 根据实际需要修改， 如果 ram 不紧张 0x200 是一个好选择, 对于 17H26 不用中断，可以用 0x40

	.section	.vectors,"ax"
	.global 	__start
	.extern  main
	
	.extern  _ramcode_size_div_16_align_256_
	.extern  _ramcode_size_div_256_
	.extern  _ramcode_size_align_
	
__start:									@ MUST,  referenced by boot.link

	.org 0x0
	tj	__reset								@ two bytes
	.byte	0x01,0x11,0x59,0x4B,0x51,17	@ self MAC
	.org 0x8
	.word	(0x544c4e4b)					@ must !!!!
#if RUN_ALL_IN_RAM
	.word	(0x00880000 + 0x380)			@ !!!!! should be (_end_data16_ / 16)
#else	
	.word	(0x00880000 + _ramcode_size_div_16_align_256_)
#endif
	.org 0x10								@ irq fix address
#if(!REMOVE_IRQ)
__irq:
	tpush    	{r14}
	tpush    	{r0-r7}
	tmrss    	r0
	
	tmov		r1, r8
	tmov		r2, r9
	tmov		r3, r10
	tmov		r4, r11
	tmov		r5, r12
	tpush		{r0-r5}
	
	tjl      	irq_handler

	tpop		{r0-r5}
	tmov		r8, r1
	tmov		r9, r2
	tmov		r10,r3
	tmov		r11,r4
	tmov		r12,r5

	tmssr    	r0
	tpop		{r0-r7}
	treti    	{r15}
#endif	

__reset:
#if(0)
     tmov		r0, #4					@ Test FW ready flag at 0x40000 == 256K
     tshftl		r0, r0, #16				@ 0x4 << 16 == 256K
     tloadrb	r1, [r0, #8]
     tcmp		r1, #75					@ 0x4b is the fixed byte for all bin-file (that is 0x544c4e4b)
     tjne		NORMAL_START

     tloadr		r3, COPY_CODE_DAT
     tloadr		r0, COPY_CODE_DAT + 4
COPY_CODE_START:
     tloadm		r2!, {r1}
     tstorem	r3!, {r1}
     tcmp		r3, r0
     tjne		COPY_CODE_START

     tloadr		r3, COPY_CODE_DAT + 8
     tmov		r2, #136		@0x88
     tstorerb	r2, [r3, #0]

COPY_CODE_END:
     tj		COPY_CODE_END

NORMAL_START:
#endif

#if _BURN_PROOF_
	tmovs	r0, #63
	tjl		analog_read
	tshftl	r0, r0, #31
	tjmi	CONT
	tloadr	r0, DELAY_C
DELAY_N:
	tsub	r0, #1
	tjge	DELAY_N
	tj		CONT
	.balign	4
DELAY_C:	
	.word   32000000						@ delay  2 seconds at 32MHz clk
CONT:
#endif

	tloadr	r0, DAT1+8
	tloadr	r1, DAT1+4
	tloadr	r2, DAT0+4
FLL_STK:
	tcmp	r1, r2
	tjge	FLL_STK_END
	tstorer r0, [r1, #0]
	tadd    r1, #4
	tj		FLL_STK
FLL_STK_END:

#if(!REMOVE_IRQ)
	tloadr	r0, DAT0+8
	tmcsr	r0			
	tloadr	r0, DAT0+12
	tmov	r13, r0
#endif
	tloadr	r0, DAT0
	tmcsr	r0	
	tloadr	r0, DAT0+4
	tmov	r13, r0

	tmov	r0, #0
	tloadr	r1, DAT1
	tloadr	r2, DAT1 + 4
ZERO:
	tcmp	r1, r2
	tjge	ZERO_END
	tstorer	r0, [r1, #0]
	tadd    r1, #4
	tj		ZERO
ZERO_END:

#if(HIGH_SPI_SPEED)
	tloadr    	r1, SPISPEED
	tmov		r0, #0x3b			@0xbb for dual address/data mode; 0x3b for dual data mode
	tstorerb	r0, [r1, #0]
	tmov		r0, #1				@0x03 for dual address/data mode; 0x01 for dual data mode
	tstorerb	r0, [r1, #1]
#endif
#if(HIGH_OTP_SPEED)
	tloadr    	r1, OTPSPEED
	tmov		r0, #1
	tstorerb	r0, [r1, #0]
#endif

#if !RUN_ALL_IN_RAM
	tloadr    r1, DAT2					@ set cache
	tloadr    r0, DAT2 + 4
	tstorerb	r0, [r1, #0]
	tadd     	r0, #1
	tstorerb	r0, [r1, #1]
#endif

	tjl	main
END:	tj	END

	.balign	4
DAT0:
	.word	0x13			    						@SVC    @4
	.word	(0x808000 + RAM_SIZE)			@program stack
#if(!REMOVE_IRQ)
	.word	0x12			    		@IRQ    @0
	.word	(irq_stk + IRQ_STK_SIZE)	@irq stack, @8
#endif
#if(HIGH_SPI_SPEED)
SPISPEED:
	.word	(0x80000e)
#endif	
#if(HIGH_OTP_SPEED)
OTPSPEED:
	.word	(0x800603)
#endif
	
DAT1:
#if RUN_ALL_IN_RAM
	.word	(_start_bss_)
	.word	(_end_bss_)
#else	
	.word	(0x808000 + _ramcode_size_align_)
	.word	(_end_bss_)
#endif	
	.word	0xcdcdcdcd

#if !RUN_ALL_IN_RAM
DAT2:
	.word	(0x80060c)
	.word   _ramcode_size_div_256_
#endif

@  使得启动代码在第一扇区。修改 tcdb 的模式， 升级的时候， 不要写第一扇区	
#if _BURN_PROOF_
	.org 256
#elif(RSV_RAM_FOR_APP > 0)
	.org RSV_RAM_FOR_APP			//  !!!!!  这是为了预留给应用程序
#endif
	.section .bss
	.align 4
#if(!REMOVE_IRQ)
	.lcomm irq_stk, IRQ_STK_SIZE
#endif	
	.end

