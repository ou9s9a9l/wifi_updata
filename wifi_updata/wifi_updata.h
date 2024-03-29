/*
 * wifi_updata.h
 *
 * Created: 2014/9/3 9:43:14
 *  Author: oyx
 */ 


#ifndef WIFI_UPDATA_H_
#define WIFI_UPDATA_H_


#include <avr/io.h>
#include "macr.h"
#include <avr/interrupt.h>
#include <AVR/sleep.h>
#include <avr/wdt.h>
#include "nRF24L01.h"
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>

//const char Set_TCP[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x52,0x54,0x3D,0x22,0x54,0x43,0x50,0x22,0x2C,
//	0x22,0x31,0x39,0x32,0x2E,0x31,0x36,0x38,0x2E,0x31,0x2E,/**/0x31,0x30,0x31,0x22,0x2C,0x35,0x30,0x35,0x30,0x0D,0x0A,0x00};
	//192.168.1.107 5050
const char Set_TCP[] ={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x52,0x54,0x3D,0x22,0x54,0x43,0x50,0x22,0x2C,
	0x22,0x31,0x38,0x32,0x2E,0x39,0x32,0x2E,0x31,0x39,0x30,0x2E,0x31,0x32,0x32,0x22,0x2C,0x35,0x30,0x35,0x30,0x0D,0x0A,0x00};
	//182.92.190.122 5050
const char Send_Comand[]={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x45,0x4E,0x44,0x3D,0x32,0x0D,0x0A,0x00};//send 2byte
const char RST[]=	{0x41,0x54,0x2B,0x52,0x53,0x54,0x0D,0x0A,0x00};
	
const char Prog[]={0x0C,0x94,0x2A,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,
	0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x49,0x00,0x0C,0x94,0x47,0x00,0x0C,
	0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,
	0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x0C,0x94,0x47,0x00,0x11,
	0x24,0x1F,0xBE,0xCF,0xE5,0xD4,0xE0,0xDE,0xBF,0xCD,0xBF,0x10,0xE0,0xA0,0xE6,0xB0,0xE0,0xE8,0xE7,0xF6,0xE0,0x02,
	0xC0,0x05,0x90,0x0D,0x92,0xA6,0x36,0xB1,0x07,0xD9,0xF7,0x10,0xE0,0xA6,0xE6,0xB0,0xE0,0x01,0xC0,0x1D,0x92};
	
#define XMODEM_NUL         0x00
#define XMODEM_SOH         0x01
#define XMODEM_STX         0x02
#define XMODEM_EOT         0x04
#define XMODEM_ACK         0x06
#define XMODEM_NAK         0x15
#define XMODEM_CAN         0x18
#define XMODEM_EOF         0x1A
#define XMODEM_RWC         'C'
#endif /* WIFI_UPDATA_H_ */