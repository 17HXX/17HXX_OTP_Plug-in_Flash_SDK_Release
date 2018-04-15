#include "iqs_led.h"

#include "../../tl_common.h"
#include "../../../proj_lib/rf_drv.h"
#include "../../../proj_lib/pm.h"
#include "../../../proj/mcu/clock.h"
#include "../../../proj/mcu/clock_i.h"


#define  IQS_LED_INDICATE			0

#if(IQS_LED_INDICATE)

#define GPIO_IQS_LED1		GPIO_PA0
#define GPIO_IQS_LED2		GPIO_PA1
#define GPIO_IQS_LED3		GPIO_PA2
#define GPIO_IQS_LED4		GPIO_PA3
#define GPIO_IQS_LED5		GPIO_PA4

void leds_init(void)
{
	/*LED1 Initial*/
	gpio_set_func(GPIO_IQS_LED1,AS_GPIO);
	gpio_set_input_en(GPIO_IQS_LED1,0);
	gpio_set_output_en(GPIO_IQS_LED1,1);
	gpio_write(GPIO_IQS_LED1,1);

	gpio_set_func(GPIO_IQS_LED2,AS_GPIO);
	gpio_set_input_en(GPIO_IQS_LED2,0);
	gpio_set_output_en(GPIO_IQS_LED2,1);
	gpio_write(GPIO_IQS_LED2,1);

	gpio_set_func(GPIO_IQS_LED3,AS_GPIO);
	gpio_set_input_en(GPIO_IQS_LED3,0);
	gpio_set_output_en(GPIO_IQS_LED3,1);
	gpio_write(GPIO_IQS_LED3,1);

	gpio_set_func(GPIO_IQS_LED4,AS_GPIO);
	gpio_set_input_en(GPIO_IQS_LED4,0);
	gpio_set_output_en(GPIO_IQS_LED4,1);
	gpio_write(GPIO_IQS_LED4,1);

	gpio_set_func(GPIO_IQS_LED5,AS_GPIO);
	gpio_set_input_en(GPIO_IQS_LED5,0);
	gpio_set_output_en(GPIO_IQS_LED5,1);
	gpio_write(GPIO_IQS_LED5,1);
}

void leds_all_on(void)
{
    led1_on();
    led2_on();
    led3_on();
    led4_on();
    led5_on();
}

void leds_all_off(void)
{
	led1_off();
    led2_off();
    led3_off();
    led4_off();
    led5_off();
}

void leds_all_twinkle(void)
{
	led1_twinkle();
    led2_twinkle();
    led3_twinkle();
    led4_twinkle();
    led5_twinkle();
}

void led1_on(void)
{
	gpio_write(GPIO_IQS_LED1, 0);
}

void led1_off(void)
{
	gpio_write(GPIO_IQS_LED1, 1);
}

void led1_twinkle(void)
{
	BM_FLIP(reg_gpio_out(GPIO_IQS_LED1), GPIO_IQS_LED1&0xff);
}

void led2_on(void)
{
	gpio_write(GPIO_IQS_LED2, 0);
}

void led2_off(void)
{
	gpio_write(GPIO_IQS_LED2, 1);
}

void led2_twinkle(void)
{
	BM_FLIP(reg_gpio_out(GPIO_IQS_LED2), GPIO_IQS_LED2&0xff);
}


void led3_on(void)
{
	gpio_write(GPIO_IQS_LED3, 0);
}

void led3_off(void)
{
	gpio_write(GPIO_IQS_LED3, 1);
}

void led3_twinkle(void)
{
	BM_FLIP(reg_gpio_out(GPIO_IQS_LED3), GPIO_IQS_LED3&0xff);
}

void led4_on(void)
{
	gpio_write(GPIO_IQS_LED4, 0);
}

void led4_off(void)
{
	gpio_write(GPIO_IQS_LED4, 1);
}

void led4_twinkle(void)
{
	BM_FLIP(reg_gpio_out(GPIO_IQS_LED4), GPIO_IQS_LED4&0xff);
}

void led5_on(void)
{
	gpio_write(GPIO_IQS_LED5, 0);
}

void led5_off(void)
{
	gpio_write(GPIO_IQS_LED5, 1);
}

void led5_twinkle(void)
{
	BM_FLIP(reg_gpio_out(GPIO_IQS_LED5), GPIO_IQS_LED5&0xff);
}




#else

void leds_init(void)
{

}

void leds_all_on(void)
{

}

void leds_all_off(void)
{

}

void leds_all_twinkle(void)
{

}

void led1_on(void)
{

}

void led1_off(void)
{

}

void led1_twinkle(void)
{

}

void led2_on(void)
{

}

void led2_off(void)
{

}

void led2_twinkle(void)
{

}

void led3_on(void)
{

}

void led3_off(void)
{

}

void led3_twinkle(void)
{

}

void led4_on(void)
{

}

void led4_off(void)
{

}

void led4_twinkle(void)
{

}

void led5_on(void)
{

}

void led5_off(void)
{

}

void led5_twinkle(void)
{

}
#endif
