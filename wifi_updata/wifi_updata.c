/*
 * wifi_updata.c
 *
 * Created: 2014/9/3 9:41:33
 *  Author: oyx
 */ 

#include "wifi_updata.h"
unsigned int sendflag=0;
void get_mcusr(void)
{
	MCUSR = 0;
	wdt_disable();
}
void uart_sendB(unsigned char data)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0=data;
}
void uart1_sendB(unsigned char data)
{
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1=data;
}
void uart1_send128B(unsigned char *data)
{
	for (int a=0;a<128;a++)
	{
		while ( !( UCSR1A & (1<<UDRE1)) );
		UDR1=data[a];
	}
	
}
void Uart_SendString(unsigned char *data)
{
	volatile unsigned int a=0;
	while(data[a]!=0)
{uart_sendB(data[a]);a++;}
}
void Uart_SendSingle(unsigned char data)
{
	Uart_SendString(Send_Comand);
	_delay_ms(50);
	uart_sendB(data);
	uart_sendB(data);
	_delay_ms(50);
}
unsigned char ch,cl;
void crc16(unsigned char *buf)
{
	unsigned int j;
	unsigned char i;
	unsigned int t;
	unsigned int crc=0;

	for(j = 128; j > 0; j--)
	{
		//标准CRC校验
		crc = (crc ^ (((unsigned int) *buf) << 8));
		for(i = 8; i > 0; i--)
		{
			t = crc << 1;
			if(crc & 0x8000)
			t = t ^ 0x1021;
			crc = t;
		}
	
		buf++;
	}
	ch = crc / 256;
	cl = crc % 256;
}

void usart_send(void)
{
	if (sendflag==0)
	{
		uart1_sendB(0x64);
	}
	
	


	_delay_ms(500);
};
#define  rxlen 151
unsigned char rxbuffer[rxlen],rxbuffer1[rxlen];
unsigned int count=0,rxflag=0,packetlen=0;
unsigned int endflag=1,packNO,rxwifi=0;//0is not end  1 is end
ISR(USART1_RX_vect)
{
	volatile  unsigned int temp;
	
	if(UCSR1A & (1<<RXC1))
	temp=UDR1;
	if (temp==XMODEM_RWC)//开始进行
	{
		sendflag=1;endflag=0;
	}
	if (temp==XMODEM_ACK&&endflag==0)//request next 128 byte
	{
		sendflag=1;Uart_SendSingle(0x31);rxwifi=0;
		for (int a=0;a<rxlen;a++)
			{
				rxbuffer1[a]=0;
			}
			
	}
	if (temp==XMODEM_ACK&&endflag==1)//request next 128 byte
	{
		sendflag=1;Uart_SendSingle(0x30);rxwifi=0;
		for (int a=0;a<rxlen;a++)
			{
				rxbuffer1[a]=0;
			}
	}
	if (temp==XMODEM_NAK&&endflag==0)//request next 128 byte
	{
		sendflag=1;
		
	}				
}
void Mcu_Reset(void)
{
	_PA4=0;
	_delay_ms(2000);
	_PA4=1;
}
int main(void)
{
    //TODO:: Please write your application code
	volatile unsigned int a,b=0,c=0,d=0,e;
	volatile unsigned char temp;
	get_mcusr();
	Mcu_Init( );
	Spi_Init( );
//	Mcu_Reset();
	wdt_enable(WDTO_8S);
	
	Timer_Init();
	//	EEPROM_write(0xcd,0x2e);
	USART0_Init();
	USART1_Init();
	L01_CE_LOW( );
	L01_Init();
	L01_SetTRMode( TX_MODE );
	L01_WriteHoppingPoint( 0 );
	_PB2=0;
	_delay_ms(1000);
	Uart_SendString(RST);
	_delay_ms(2000);
	Uart_SendString(Set_TCP);
	_delay_ms(1000);
	UCSR0B |=(1<<RXCIE0);
	UCSR1B |=(1<<RXCIE1);
	wdt_reset();
while (1)
{
	
		if (sendflag==0&&rxwifi==1)//0 is send 64;1 is bootloder rxable;2 is idle
		{
			Mcu_Reset();
			_delay_ms(1000);
			uart1_sendB(0x64);
			_delay_ms(200);
			uart1_sendB(0x64);
			_delay_ms(200);
			uart1_sendB(0x64);
			_delay_ms(200);
		}
		if (sendflag==1&&rxwifi==1)
		{
			crc16(rxbuffer1);
			uart1_sendB(XMODEM_SOH);
			_delay_ms(10);
			uart1_sendB(packNO);
			uart1_sendB(~packNO);
			uart1_send128B(rxbuffer1);
			uart1_sendB(ch);
			uart1_sendB(cl);
			sendflag=3;
			
		}
		if (sendflag==2&&rxwifi==1)
		{
			uart1_sendB(XMODEM_EOT);
			endflag=1;	
			sendflag=1;
			rxwifi=0;
		}
		
}	
    return 0;
}
unsigned int rxflag1=0;
ISR(USART0_RX_vect)
{
	volatile int temp,a=0,b=0;
	if(UCSR0A & (1<<RXC0))
	temp=UDR0;
		
	if(rxflag&&temp==0x39)
	rxflag1=1;
	else rxflag=0;
	if(temp==0x32)
	{rxflag=1;
	wdt_reset();}
	if (rxflag1)
	{
		rxbuffer[count++]=temp;
	}

}

unsigned int everothersend=0;
ISR(TIMER1_OVF_vect)
{
/*	if (rxbuffer[145]==0&&rxbuffer[146]==0)//处理缓存多余的 144为加上模块附加之后的字节的最后一个为0a
	{
		for (int a=0;a<rxlen;a++)
		{
			rxbuffer[a]=0;
		}
		count=0;
	}*/
	if (everothersend++>=5)
	{
		Uart_SendSingle(0x33);
		everothersend=0;
		if (rxwifi==1)
		{
			sendflag=1;
		}
	}
	if (rxbuffer[0]!=0)
	{
	//if (packetlen==rxbuffer[11])
	{
		everothersend=0;
		for (int a=0;a<rxlen;a++)
		{
			rxbuffer1[a]=0;
		}
		if (rxbuffer[2]==0xFF)
		sendflag=2;// end 
		else
		packNO=rxbuffer[2]+1;
		for (int a=0;a<128;a++)
		{
			rxbuffer1[a]=rxbuffer[a+3];//1-9:+9 10-99:+10
		}
	
		for (int a=0;a<rxlen;a++)
		{
			rxbuffer[a]=0;
		}
		if(packNO==1)
		sendflag=0;
		count=0;
		rxflag1=0;
		rxwifi=1;
		
	}	
	}
	

	
	if (rxbuffer[149]!=0||rxbuffer[150]!=0)
	{
		for (int a=0;a<rxlen;a++)
		{
			rxbuffer[a]=0;
		}
		Uart_SendSingle(0x30);
	}	
}