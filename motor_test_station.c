#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "trace.h"
#include "contract.h"
#include "usart.h"

/*
CPU Ports Mapping for Atmega 32 and Atmega16

Port A
	PA0	(not connected)
	PA1 (not connected)
	PA2 (not connected)
	PA3 (not connected)
	PA4 (not connected)
	PA5 (not connected)
	PA6 (not connected)
	PA7 (not connected)

Port B
	PB0 (not connected)
	PB1 (not connected)
	PB2 (not connected) INT2
	PB3 (not connected) PWM
	PB4 (not connected)
	PB5 (connected) MOSI (SPI programmer)
	PB6 (connected) MISO (SPI programmer)
	PB7 (connected) SCK (SPI programmer)

Port C
	PC0 (not connected) I2C SCL 
	PC1 (not connected) I2C SDA
	PC2 (not connected)
	PC3 (not connected)
	PC4 (not connected)
	PC5 (not connected)
	PC6 (not connected)
	PC7 (not connected)

Port D
	PD0 (connected) RS232 RX 
	PD1 (connected) RS232 TX
	PD2 (not connected) INT0
	PD3 (not connected)
	PD4 (not connected)
	PD5 (not connected)
	PD6 (not connected)
	PD7 (not connected) PWM
*/


/*
// TODO
// Interrupt handler for line sensors
    //MCUCR = ((1<<ISC11)|(0<<ISC10)|(1<<ISC01)|(0<<ISC00)); // Set external interrupt on falling edge
	//  MCUCR = (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11); // Set external interrupt on rising edge
    //GICR  = ((1<<INT1)|(0<<INT0));                         // Activate INT1
*/

int g_INT0Counter;

SIGNAL(SIG_INTERRUPT0) 
{
	g_INT0Counter++;
	TRACE_RAW( "Count:%i\n\r", g_INT0Counter);
}


int main ( void)
{
	g_INT0Counter = 0;

    // init HW uart
    usart_init( 57600);

    // init trace subsystem
    traceInit();

	TRACE( "System Ready");

	// init interrupt
	DDRD &= ~(1<<PD2);
	MCUCR = ((1<<ISC11)|(0<<ISC10)|(1<<ISC01)|(0<<ISC00)); // Set external interrupt on falling edge
	GICR  = ((0<<INT1)|(1<<INT0)); // init INT0 
    PORTD |= _BV(PD2); //pin PD2 podci¹gniêty do plusa


	sei();

	while(1)
	{
		//TRACE_RAW( "Count:%i\n\r", g_INT0Counter);
	}
	return 0;
}
