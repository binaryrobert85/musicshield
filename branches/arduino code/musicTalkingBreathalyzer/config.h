//  File config.h
//  Headers for configurating IOs,SPI to Music Shield
//  For more details about the product please check http://www.seeedstudio.com/depot/

//  Copyright (c) 2010 seeed technology inc.
//  Author: Icing Chang
//  Version: 1.0
//  Time: Oct 21, 2010
//  Changing records:
//    
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <avr/io.h>

#ifndef CONFIG_H
#define CONFIG_H


//////////////////////for SPI/////////////////////////////////////////
#if defined(__AVR_ATmega1280__)
#define SPIDO	PB2	// Port B bit 2 : data out (data to MSD and vs1053)
#define SPIDI	PB3	// Port B bit 3 : data in (data from MSD and vs1053)
#define SPICLK	PB1	// Port B bit 1 : clock for MSD and vs1053
#else
#define SPIDO	PB3	// Port B bit 3 : data out (data to MSD and vs1053)
#define SPIDI	PB4	// Port B bit 4 : data in (data from MSD and vs1053)
#define SPICLK	PB5	// Port B bit 5 : clock for MSD and vs1053
#endif

#define SPIPutCharWithoutWaiting(data) SPDR =data
#define SPIWait() while(!(SPSR & (1<<SPIF)))
void SPIPutChar(unsigned char data);
unsigned char SPIGetChar();
#define SPI8Clocks(nClocks)	{for(int i = 0; i < nClocks; i++){SPIPutChar(0xAA);}}

void InitSPI();



////////////////////////for MMC////////////////////////////////////
#if defined(__AVR_ATmega1280__)
#define SPICS	PB4	// Port B bit 2 (pin14): chip select for MSD
#define DeselectMSD()	PORTB |= (1 << SPICS)|(1<<PB0)
#define SelectMSD()	PORTB &= ~((1 << SPICS)|(1<<PB0))
#else
#define SPICS	PB2	// Port B bit 2 (pin14): chip select for MSD
#define DeselectMSD()	PORTB |= 1 << SPICS
#define SelectMSD()	PORTB &= ~(1 << SPICS)
#endif


#define READ_SPIDI()	PINB & (1 << SPIDI)

///////////////////////for vs10xx///////////////////////////////////
#if defined(__AVR_ATmega1280__)
#define VS_XRESET PF0
#define VS_DREQ PF1
#define VS_XDCS PF2
#define VS_XCS  PF3

#define VS_PORT PORTF
#define VS_PIN PINF
#define VS_DDR DDRF
#else

#define VS_XRESET PC0
#define VS_DREQ PC1
#define VS_XDCS PC2
#define VS_XCS  PC3


#define VS_PORT PORTC
#define VS_PIN PINC
#define VS_DDR DDRC
#endif

#define Mp3SelectControl()	VS_PORT&= ~(1<<VS_XCS)
#define Mp3DeselectControl()	VS_PORT |= (1<<VS_XCS) 	


#define Mp3PutInRest() VS_PORT &= ~(1<<VS_XRESET) 
#define Mp3ReleaseFromReset() VS_PORT |= (1<<VS_XRESET)
#define Mp3SelectData() VS_PORT &= ~(1<<VS_XDCS)
#define Mp3DeselectData() VS_PORT |= (1<<VS_XDCS)

#define MP3_DREQ (VS_PIN & (1<<VS_DREQ))



void InitIOForVs10xx();


/////////////////////for keys//////////////////////////////////////
#if defined(__AVR_ATmega1280__)
#define VD PH4
#define BK PH3
#define PS PE3
#define NT PG5
#define VU PE5


#define VDKey (PINH & (1<<VD))
#define BKKey (PINH & (1<<BK))
#define PSKey (PINE & (1<<PS))
#define NTKey (PING & (1<<NT))
#define VUKey (PINE & (1<<VU))
#else
#define VD PD7
#define BK PD6
#define PS PD5
#define NT PD4
#define VU PD3


#define VDKey (PIND & (1<<VD))
#define BKKey (PIND & (1<<BK))
#define PSKey (PIND & (1<<PS))
#define NTKey (PIND & (1<<NT))
#define VUKey (PIND & (1<<VU))

#endif

void InitIOForKeys();

//////////////////for LEDs///////////////////////////////////////
#if defined(__AVR_ATmega1280__)
#define RED_LED 		PH6
#define GREEN_LED 	PH5
#define LED_PORT	PORTH
#define LED_DDR		DDRH
#else
#define RED_LED 		PB1
#define GREEN_LED 	PB0
#define LED_PORT	PORTB
#define LED_DDR		DDRB
#endif

#define RED_LED_ON()	LED_PORT |=(1<<RED_LED)
#define RED_LED_OFF()	LED_PORT &=~(1<<RED_LED)
#define GREEN_LED_ON()	LED_PORT |=(1<<GREEN_LED)
#define GREEN_LED_OFF()	LED_PORT &=~(1<<GREEN_LED)

void InitIOForLEDs();

/** Generic temp variable for non-reentrant main routines */
union Temp {
  unsigned char c;
  unsigned int i;
  unsigned long l;
};
extern union Temp  temp;
#endif

