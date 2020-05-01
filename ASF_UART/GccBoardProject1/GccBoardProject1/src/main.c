/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <stdio.h>
#include <board.h>
#include "stdio_serial.h"

#define MAX_RX_BUFFER_LENGTH 1
/*** Instance Structs and Configs ***/
struct usart_module usart_instance;
struct adc_module adc_instance;
struct tc_module tc_instance;


/***** GLOBAL VARIABLES *******/
uint8_t string[] = "Hello World!\r\n";
volatile bool guiReady = true;
volatile uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];
volatile u_int16_t adc_results;
volatile u_int16_t mul_results[200];
volatile u_int16_t trigger = 2048;  //
volatile u_int16_t del_s = 0;



/***** Function Prototypes ******/
void start(void);
void stop(void);
u_int32_t get_time(void);

/***** Interrupts, Peripherals, Drivers and the hard stuff *******/
void usart_read_callback(struct usart_module *const usart_module)
{
	 usart_write_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
	 guiReady = true;
}

void usart_write_callback(struct usart_module *const usart_module)
{
	//port_pin_toggle_output_level(LED_0_PIN);
}
void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	while (usart_init(&usart_instance,
	EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {}
	usart_enable(&usart_instance);
}
void configure_usart_callbacks(void)
{
	usart_register_callback(&usart_instance,
	usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_instance,
	usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_instance,
	USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);
}
void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}
void configure_tc(void)
{
	struct tc_32bit_config tc_config;
	tc_get_config_defaults(&tc_config);
	tc_init(&tc_instance, TC1, &tc_config);
}

int getNum(char ch)
{
	int num=0;
	if(ch>='0' && ch<='9')
	{
		num=ch-0x30;
	}
	else
	{
		switch(ch)
		{
			case 'A': case 'a': num=10; break;
			case 'B': case 'b': num=11; break;
			case 'C': case 'c': num=12; break;
			case 'D': case 'd': num=13; break;
			case 'E': case 'e': num=14; break;
			case 'F': case 'f': num=15; break;
			default: num=0;
		}
	}
	return num;
}
/*********** Main Entry Code **********************/

int main (void)
{
	system_init();
	configure_usart();
	configure_usart_callbacks();
	configure_adc();
	/* Insert application code here, after the board has been initialized. */
	system_interrupt_enable_global();
	usart_write_buffer_wait(&usart_instance, string, sizeof(string));	adc_start_conversion(&adc_instance);
	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {
		while(del_s >= 0){
		usart_read_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
		
		switch(*rx_buffer){
			case 'A':
			case 'a': usart_write_buffer_wait(&usart_instance, (uint8_t *) "NICE!", 5); start(); usart_write_buffer_wait(&usart_instance, (uint8_t *) "ACK!", 5); break;
			default: usart_write_buffer_wait(&usart_instance, (uint8_t *) "HELP!", 5); usart_write_buffer_wait(&usart_instance, (uint8_t *) rx_buffer, MAX_RX_BUFFER_LENGTH); break;

		}
		}
		usart_write_buffer_wait(&usart_instance, (uint8_t *) "Delay has gone negative! Press Button!", 25);
// 		/* Is button pressed? */
// 		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
// 			/* Yes, so turn LED on. */
// 			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
// 		} else {
// 			/* No, so turn LED off. */
// 			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
// 		}
	}
}

void start(void)
{
	while(*rx_buffer == 'a' || *rx_buffer == "A")
	{
		 usart_read_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
		 //adc_read(&adc_instance,adc_results);
		 //while(adc_results < trigger)
			//adc_read(&adc_instance, adc_results);
			//if(adc_results > trigger)
			{
				if(del_s == 0)
				{
					for (int i = 0; i < 200 ; i ++ )
					{
						adc_read(&adc_instance, mul_results[i]);
					}
					if(guiReady)
					{
						for(int j = 0 ; j < 200 ; j++)
						{
							guiReady = false;
								unsigned int x=0;
								x=(getNum(mul_results[j]))*16+(getNum(mul_results[j+1]));
							usart_write_buffer_wait(&usart_instance, (uint8_t *)mul_results[j], sizeof(mul_results[j]));
						}
					}
				}
			}
			//else
			{
// 				for (int k = 0; k < 200 ; k ++ )
// 				{
// 					adc_read(&adc_instance, mul_results[k]);
// 					delay_us(del_s);
// 				}
// 				if(guiReady)
// 				{
// 					for(int l = 0 ; l < 200 ; l++)
// 					{
// 						guiReady = false;
// 						//usart_write_buffer_wait(&usart_instance, (uint8_t *)mul_results[l], sizeof(mul_results[l]));
// 					}
// 				}		
			}
			usart_read_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
	}
}
void stop(void);
u_int32_t get_time(void);


