#include <atmel_start.h>

uint32_t address = 1;
int idx = -1;
uint8_t data[512];
struct io_descriptor* usart_io;

void usart_read_callback(const struct usart_async_descriptor *const usart_module)
{
	gpio_set_pin_level(toggle2, 1);
	uint8_t temp;
	io_read(usart_io, &temp, 1);
	if(idx >= 0)
	{
		data[idx++]	= temp;
	}
	
	if(idx > 512)
	{
		gpio_set_pin_level(toggle3, 1);
		TCC0->CC[0].reg = 255 - data[address+0];
		TCC0->CC[1].reg = 255 - data[address+1];
		TCC0->CC[2].reg = 255 - data[address+2];
		idx = -1;
		gpio_set_pin_level(toggle3, 0);
	}
	gpio_set_pin_level(toggle2, 0);
}

void usart_error_callback(const struct usart_async_descriptor *const usart_module)
{
	gpio_set_pin_level(toggle1, 1);
	idx = 0;
	gpio_set_pin_level(toggle1, 0);
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	usart_async_get_io_descriptor(&USART_0, &usart_io);
	usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, usart_read_callback);
	usart_async_register_callback(&USART_0, USART_ASYNC_ERROR_CB, usart_error_callback);
	usart_async_enable(&USART_0);
	pwm_enable(&PWM_2);
	TCC0->CC[0].reg = 255;
	TCC0->CC[1].reg = 255;
	TCC0->CC[2].reg = 255;
	TCC0->PER.reg = 255;
	
	TCC0->CTRLA.bit.ENABLE = true;
	
	
	/* Replace with your application code */
	while (1) {
		__WFI();
	}
}
