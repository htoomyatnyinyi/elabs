/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2011  Luis Claudio Gambôa Lopes

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

#include "atraso.h"
#include "lcd.h"
#include "i2c.h"
#include "eeprom.h"
#include "eeprom_ext.h"
#include "adc.h"
#include "itoa.h"
#include "teclado.h"
#include "rtc.h"


unsigned char cnt;
unsigned int t1cont;

void interrupt()
 {
  cnt--;
  if(!cnt)
  {
//executada a cada 1 segundo
     TMR1ON_bit=0;
     t1cont=(((unsigned int)TMR1H<<8)|(TMR1L))/7; //ventilador com 7 p�s
     cnt=125; 
     TMR1H=0;
     TMR1L=0;
     TMR1ON_bit=1;
  }
  T0IF_bit=0;
  TMR0H=0;
  TMR0L=6; //250
}


void main() 
{
  unsigned char i;
  unsigned char tmp;
  unsigned int tmpi;

  char str[6];

  ADCON1=0x06;
  TRISA=0xC3;
  TRISB=0x01;
  TRISC=0x01;
  TRISD=0x00;
  TRISE=0x00;

  RBPU_bit=0;

  lcd_init();
  i2c_init();
  adc_init();



//dip
  TRISB=0x03;
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Ligue todos DIP");
  lcd_cmd(L_L2);
  lcd_str("Press. RB1");
  while(RB1_bit);


//dip
  TRISB=0x03;
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Desligue RTC DIP");
  lcd_cmd(L_L2);
  lcd_str("Press. RB1");
  while(RB1_bit);

//dip
  TRISB=0x03;
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Desl. REL1 DIP");
  lcd_cmd(L_L2);
  lcd_str("Press. RB1");
  while(RB1_bit);


//teste TEMP
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("   Teste TEMP");
  
  TRISA=0x07;

  adc_init();

  for(i=0; i< 100; i++)
  {
    tmpi=(adc_amostra(2)*10)/2;
    lcd_cmd(L_L2+5);
    itoa(tmpi,str);
    lcd_dat(str[2]);
    lcd_dat(str[3]);
    lcd_dat(',');
    lcd_dat(str[4]);
    lcd_dat('C');
    atraso_ms(20);
  }


//teste Aquecimento
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("   Teste AQUEC");
  RC5_bit=1;
  for(i=0; i< 100; i++)
  {
    tmpi=(adc_amostra(2)*10)/2;
    lcd_cmd(L_L2+5);
    itoa(tmpi,str);
    lcd_dat(str[2]);
    lcd_dat(str[3]);
    lcd_dat(',');
    lcd_dat(str[4]);
    lcd_dat('C');
    atraso_ms(50);
  }
  RC5_bit=0;


//teste Resfriamento

  TRISC0_bit=1;
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("   Teste RESFR");

//timer0 temporizador

 T0CS_bit=0;
 PSA_bit=0;
 T08BIT_bit=1;
 T0PS0_bit=0; // divide por 32
 T0PS1_bit=0;
 T0PS2_bit=1;
 TMR0ON_bit=1;

 T0IE_bit=1;

//T = 32x250x125 = 1segundo;

//timer1 contador
 TMR1CS_bit=1;
 T1CKPS1_bit=0;
 T1CKPS0_bit=0;


 T0IF_bit=0;
 TMR0H=0;
 TMR0L=6; //250
 cnt=125; 
 GIE_bit=1;

 TMR1H=0;
 TMR1L=0;
 TMR1ON_bit=1;

  RC2_bit=1;
  for(i=0; i< 150; i++)
  {
    tmpi=(adc_amostra(2)*10)/2;
    lcd_cmd(L_L2+2);
    itoa(tmpi,str);
    lcd_dat(str[2]);
    lcd_dat(str[3]);
    lcd_dat(',');
    lcd_dat(str[4]);
    lcd_dat('C');

    lcd_cmd(L_L2+8);
    itoa(t1cont,str);
    lcd_dat(str[1]);
    lcd_dat(str[2]);
    lcd_dat(str[3]);
    lcd_dat(str[4]);
    lcd_dat('R');
    lcd_dat('P');
    lcd_dat('S');

    atraso_ms(10);
  }

  GIE_bit=0;
  RC2_bit=0;


ADCON1=0x06;


//teste RTC
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Teste RTC");
  
//ajuste  rtc_w();

//  rtc_w();
 
  rtc_r();
  lcd_cmd(L_L2);
  lcd_str(date);
   atraso_ms(2000);
  for(i=0;i<20;i++)
  {
    rtc_r();
    lcd_cmd(L_L2);;
    lcd_str(time);
    atraso_ms(500); 
  }


//dip
  TRISB=0x03;
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Des. DIS* e LED1");
  lcd_cmd(L_L2);
  lcd_str("Press. RB1");
  while(RB1_bit);



  TRISB=0xF8;
//teste Teclado
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1+2);
  lcd_str("Teste Teclado");

  lcd_cmd(L_L2+1);

  i=0;
  while(i<14)
  {
    TRISD=0x0F;
    tmp=tc_tecla(1500)+0x30;
    TRISD=0x00;
    lcd_dat(tmp);
    i++;
  }



  TRISB=0x03;
//teste EEPROM INT
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Teste EEPROM INT");
// testar ? 
  lcd_cmd(L_L2);
  lcd_str(" (s=RB0 n=RB1) ?");


  TRISB=0x03;

  while(RB0_bit && RB1_bit);

  if(RB0_bit == 0)
  {
    tmp=e2prom_r(10);
    lcd_dat(tmp);

    e2prom_w(10,0xA5);
    e2prom_w(10,0x5A);
    i=e2prom_r(10);

    e2prom_w(10,tmp);

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Teste EEPROM INT");
    lcd_cmd(L_L2);
    if(i == 0x5A) 
      lcd_str("       OK");
    else
      lcd_str("      ERRO");

    atraso_ms(1000);
  }
  else
  {
    while(RB1_bit == 0);
  }



//teste EEPROM EXT
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("Teste EEPROM EXT");
// testar ? 
  lcd_cmd(L_L2);
  lcd_str(" (s=RB0 n=RB1) ?");

  TRISB=0x03;

  while(RB0_bit && RB1_bit);

  if(RB0_bit == 0)
  {
    tmp=e2pext_r(10);
    lcd_dat(tmp);

    e2pext_w(10,0xA5);
    e2pext_w(10,0x5A);
    i=e2pext_r(10);

    e2pext_w(10,tmp);

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Teste EEPROM EXT");
    lcd_cmd(L_L2);
    if(i == 0x5A) 
      lcd_str("       OK");
    else
      lcd_str("      ERRO");

    atraso_ms(1000);
  }
  else
  {
    while(RB1_bit == 0);
  }

  TRISB=0x00;
  PORTB=0;


//fim teste 
  lcd_cmd(L_CLR);
  lcd_cmd(L_L1);
  lcd_str("      Fim");
  lcd_cmd(L_L2);
  lcd_str(" Pressione RST");



   while(1);

}