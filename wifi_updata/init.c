/*
 * init.c
 *
 * Created: 2014/8/19 9:25:21
 *  Author: oyx
 */ 

#include <avr/io.h>
#include "macr.h"
#include <avr/interrupt.h>
void Mcu_Init(void)
{
	DDRA=0XFF;
	PORTA=0XFF;
	
	DDRB=0XFf;
	PORTB=0XFF;
	
	DDRC=0XFF;
	PORTC=0Xff;
	
	DDRD=0XfF;
	PORTD=0XFf;
	DDR_PA0=0;//adc 设为输入
}
void USART0_Init( void )
{
   UBRR0L=16;         //8m 51 1m  12 4800   8888 16是2x情况下57600
   UCSR0A =(1<<U2X0);
   UCSR0B = (1<<RXEN0)|(1<<TXEN0);
   UCSR0C =0x0e;// (1<<USBS0)|(3<<UCSZ0);
}
void USART1_Init( void )
{
	UBRR1L=51;         //8m 51 1m  12 4800   8888 16是2x情况下57600
	UCSR1A =(1<<U2X1);
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	UCSR1C =0x0e;// (1<<USBS0)|(3<<UCSZ0);
	
}

void Spi_Init(void)
{
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);   // 主机模式，fck/16, SPI方式0
	DDR_PB6=0;
	//	DDR_PB4=1;
}

void Timer_Init(void)
{
	cli();
	TCCR1B=0x03;// 1024  5devide
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	TIMSK1=0x01;//1开启中断
	sei();
}

