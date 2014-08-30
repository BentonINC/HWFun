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
#include <asf.h>
#include <delay.h>
#include <at25dfx.h>
#include <usart.h>
#include <stdio.h>
#include <stdio_serial.h>
#include <io.h>

struct usart_module usart_instance;

void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	while (usart_init(&usart_instance, EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}
	usart_enable(&usart_instance);
}

int main (void)
{
	system_init();
	configure_usart();
	
	if (at25dfx_chip_check_presence(FLASH_ADDR)==STATUS_OK); {
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		delay_ms(5000);
		uint8_t string[] = "Sweet! We can see Flash Memory!\r\n";
		usart_write_buffer_wait(&usart_instance, string, sizeof(string));
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
	}

	// Insert application code here, after the board has been initialized.

	// This skeleton code simply sets the LED to the state of the button.
	while (1) {
		// Is button pressed?
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			// Yes, so turn on LED.
				port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
				port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
				
				uint8_t string[] = "Button Pressed!\r\n";
				usart_write_buffer_wait(&usart_instance, string, sizeof(string));
		} else {
			// No, so turn LED off.
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}
}