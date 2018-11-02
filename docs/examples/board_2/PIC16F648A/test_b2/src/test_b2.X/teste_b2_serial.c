/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2010  Luis Claudio Gamb�a Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

/* ----------------------------------------------------------------------- */
/* Template source file generated by piklab */
#include "config_628A.h"

#include "atraso.h"
#include "lcd.h"
#include "teclado.h"
#include "serial.h"

/* ----------------------------------------------------------------------- */

/*
void isr() interrupt 0 {

}
*/
void main() {
  unsigned char i,tmp;

  CMCON=0x07; 
  TRISA=0x30;
  TRISB=0xE7;
  
  PORTA=0;
  PORTB=0;

  lcd_init();

  serial_init();

//teste serial
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Teste Serial TX");
  lcd_cmd(L_L2+2);
  lcd_str("9600 8N1");

  serial_tx_str("\r\n Picsimlab\r\n Teste Serial TX\r\n");

  for(i=0;i<4;i++)
  {
    serial_tx(i+0x30);
    serial_tx_str(" PicsimLab\r\n");
  }
  atraso_ms(1000);

  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Teste Serial RX");
  serial_tx_str(" Digite!\r\n");
  for(i=0;i<32;i++)
  {
    if(!(i%16))
    {
       lcd_cmd(L_L2);
       serial_tx_str("\r\n");
    }
    tmp=serial_rx(2000);
    lcd_dat(tmp);
    serial_tx(tmp);
  }
  atraso_ms(100);

  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Teste Teclado TX");
  serial_tx_str("\r\n Aguarde!\r\n");
  for(i=0;i<32;i++)
  {
    if(!(i%16))
    {
      lcd_cmd(L_L2);
      serial_tx_str("\r\n");
    }
    tmp=tc_tecla(2000)+0x30;
    lcd_dat(tmp);
    serial_tx(tmp);
  }
  atraso_ms(100);


//fim teste 
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1+4);
  lcd_str("Fim");
  lcd_cmd(L_L2+1);
  lcd_str("Pressione RST");

  serial_tx_str("\r\n FIM!\r\n");

  while(1);


}
