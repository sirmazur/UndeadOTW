#include <msp430x14x.h>
#include "portyLcd.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#define BUTTON0 (P4IN & BIT4)
#define BUTTON1 (P4IN & BIT5)
#define BUTTON2 (P4IN & BIT6)
#define BUTTON3 (P4IN & BIT7)
int licznik, i, test;
int zombie0[16];
int shieldman0[16];
int zombie_hp0[16];
int shieldman_hp0[16];
int zombie1[16];
int shieldman1[16];
int zombie_hp1[16];
int shieldman_hp1[16];
int player_row;
int randomizer;
int grenade=0;
int score = 0;
int check = 0;
int final_score;
int difficulty=20;
int player_hp=3;
void setButton() { P4DIR &= ~BIT4; P4DIR &= ~BIT5; }
void Clock(void);
void InitSpecial() {
    SEND_CMD(CG_RAM_ADDR);
    int spec[8][8] = { {0, 4, 15, 20, 4, 10, 10, 18}, {3, 3, 14, 2, 2, 6, 9, 9},
    {0, 20, 30, 21, 4, 10, 10, 9},{0, 6, 4, 14, 31, 31, 31, 14},{0, 4, 4, 14, 14, 14, 14, 14},{0, 0, 0, 14, 15, 14, 0, 0},{0, 25, 13, 6, 15, 10, 19, 1},{2, 5, 5, 9, 18, 17, 17, 31} };
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) {
            SEND_CHAR(spec[i][j]);
        }
    }
}
void main(void)
{
    setButton();
    {P2DIR |= BIT1;
    WDTCTL = WDTPW + WDTHOLD;
    InitPortsLcd();
    InitLCD();
    clearDisplay();
    BCSCTL1 |= XTS;
    do {
        IFG1 &= ~OFIFG;
        for (i = 0xFF; i > 0; i--);
    } while ((IFG1 & OFIFG) == OFIFG);
    BCSCTL1 |= DIVA_1;
    BCSCTL2 |= SELM0 | SELM1;
    TACTL = TASSEL_1 + MC_1 + ID_3;
    CCTL0 = CCIE;
    CCR0 = 50000;
    _EINT();
    InitSpecial();
    P1DIR |= BIT5;
    P1OUT &= ~BIT5;
	P1DIR |= BIT6;
	P1OUT &= ~BIT6;
	
    for (;;)
    {
        _BIS_SR(LPM3_bits);
        Clock();
    }}
}
void Clock(void)
{
    if (licznik % 10 == 0)
    {	if(score>50)
	  difficulty=15;
	  if(score>100)
		difficulty=10;
	  if(score>200)
		difficulty=5;
        if (shieldman_hp0[2] >=1)
        {shieldman0[2] = 0; shieldman_hp0[2] = 0; player_hp--; }
        if (shieldman_hp1[2] >=1)
        {shieldman1[2] = 0; shieldman_hp1[2] = 0; player_hp--; }
        if (shieldman_hp0[1] >=1)
        {shieldman0[1] = 0; shieldman_hp0[1] = 0; player_hp--; }
        if (shieldman_hp1[1] >=1)
        {shieldman1[1] = 0; shieldman_hp1[1] = 0; player_hp--; }

        if (zombie_hp0[2] >=1)
        {zombie0[2] = 0; zombie_hp0[2] = 0; player_hp--; }
        if (zombie_hp1[2] >=1)
        {zombie1[2] = 0; zombie_hp1[2] = 0; player_hp--; }
        if (zombie_hp0[1] >=1)
        {zombie0[1] = 0; zombie_hp0[1] = 0; player_hp--; }
        if (zombie_hp1[1] >=1)
        {zombie1[1] = 0; zombie_hp1[1] = 0; player_hp--; }
        if (player_hp <= 0)
        {if(check==0)
		{check=1; final_score=score;}
            SEND_CMD(DD_RAM_ADDR);
            for(int i=0;i<16;i++)
                SEND_CHAR(' ');
            SEND_CMD(DD_RAM_ADDR2);
            for (int i = 0; i < 16; i++)
                SEND_CHAR(' ');
            SEND_CMD(DD_RAM_ADDR);
            SEND_CHAR('y'); SEND_CHAR('o'); SEND_CHAR('u'); SEND_CHAR(' '); SEND_CHAR('l'); SEND_CHAR('o'); SEND_CHAR('s'); SEND_CHAR('t');SEND_CHAR(' ');
            SEND_CMD(DD_RAM_ADDR2);
            SEND_CHAR('s'); SEND_CHAR('c'); SEND_CHAR('o'); SEND_CHAR('r'); SEND_CHAR('e'); SEND_CHAR(' ');
            if (score < 100)
            {SEND_CHAR((final_score / 10)+48); SEND_CHAR((final_score%10)+48); }
			else
            if (score < 1000)
            {SEND_CHAR((final_score / 100)+48); SEND_CHAR(((final_score%100)/10)+48); SEND_CHAR((final_score%10)+48); }
        SEND_CHAR(' ');SEND_CHAR(7);SEND_CHAR(7);SEND_CHAR(7);
		}
		else
		{
		if(!BUTTON3 && grenade>20)
		{
		  if (player_row == 0)
            {
               
                for (int i = 1; i < 15; i++)
                {
                       
                        SEND_CMD(DD_RAM_ADDR);
                        SEND_CHAR(8);
                        for(int z=i;z>1;z--)
                        {
                            SEND_CHAR(' ');
                        }
                        if (zombie0[i] == 1)
                        {
                             shieldman_hp0[i]=0;
							zombie_hp0[i]=0;
							zombie0[i]=0;
							shieldman0[i]=0;
							shieldman_hp0[i+1]=0;
							zombie_hp0[i+1]=0;
							zombie0[i+1]=0;
							shieldman0[i+1]=0;
							shieldman_hp0[i+2]=0;
							zombie_hp0[i+2]=0;
							zombie0[i+2]=0;
							shieldman0[i+2]=0;
							SEND_CHAR(6);SEND_CHAR(6);SEND_CHAR(6);
							P1OUT ^= BIT6;
							for(unsigned int delay=0;delay<50000;delay++);
                            break;
                        }
                        else if (shieldman0[i] == 1)
                        {
                            shieldman_hp0[i]=0;
							zombie_hp0[i]=0;
							zombie0[i]=0;
							shieldman0[i]=0;
							shieldman_hp0[i+1]=0;
							zombie_hp0[i+1]=0;
							zombie0[i+1]=0;
							shieldman0[i+1]=0;
							shieldman_hp0[i+2]=0;
							zombie_hp0[i+2]=0;
							zombie0[i+2]=0;
							shieldman0[i+2]=0;
							SEND_CHAR(6);SEND_CHAR(6);SEND_CHAR(6);
							P1OUT ^= BIT6;
							for(unsigned int delay=0;delay<50000;delay++);
                            break;
                        }
                        else
                        {
                            SEND_CHAR(3);
                        }
                        for (unsigned int d = 0; d < 30000; d++);
                }
            }
            else
            {
               
                for (int i = 1; i < 15; i++)
                {
                    SEND_CMD(DD_RAM_ADDR2);
                    SEND_CHAR(8);
                    for (int z = i; z > 1; z--)
                    {
                        SEND_CHAR(' ');
                    }
                    if (zombie1[i] == 1)
                    {
                        shieldman_hp1[i]=0;
							zombie_hp1[i]=0;
							zombie1[i]=0;
							shieldman1[i]=0;
							shieldman_hp1[i+1]=0;
							zombie_hp1[i+1]=0;
							zombie1[i+1]=0;
							shieldman1[i+1]=0;
							shieldman_hp1[i+2]=0;
							zombie_hp1[i+2]=0;
							zombie1[i+2]=0;
							shieldman1[i+2]=0;
							SEND_CHAR(6);SEND_CHAR(6);SEND_CHAR(6);		
							P1OUT ^= BIT6;
							for(unsigned int delay=0;delay<50000;delay++);
                            break;
                    }
                    else if (shieldman1[i] == 1)
                    {
                         shieldman_hp1[i]=0;
							zombie_hp1[i]=0;
							zombie1[i]=0;
							shieldman1[i]=0;
							shieldman_hp1[i+1]=0;
							zombie_hp1[i+1]=0;
							zombie1[i+1]=0;
							shieldman1[i+1]=0;
							shieldman_hp1[i+2]=0;
							zombie_hp1[i+2]=0;
							zombie1[i+2]=0;
							shieldman1[i+2]=0;
							SEND_CHAR(6);SEND_CHAR(6);SEND_CHAR(6);		
							P1OUT ^= BIT6;
							for(unsigned int delay=0;delay<50000;delay++);
                            break;
                    }
                    else
                    {
                        SEND_CHAR(3);
                    }
                    for (unsigned int d = 0; d < 30000; d++);
                }
            }
		}
		else
        if (!BUTTON2)
        {
            if (player_row == 0)
            {
               
                for (int i = 1; i < 15; i++)
                {
                       
                        SEND_CMD(DD_RAM_ADDR);
                        SEND_CHAR(8);
                        for(int z=i;z>1;z--)
                        {
                            SEND_CHAR(' ');
                        }
                        if (zombie0[i] == 1)
                        {
                            zombie0[i] = 0;
                            zombie_hp0[i] = 0;
                            break;
                        }
                        else if (shieldman0[i] == 1)
                        {
                            shieldman_hp0[i] -= 1;
                            if (shieldman_hp0[i] == 0)
                                shieldman0[i] = 0;
                            break;
                        }
                        else
                        {
                            SEND_CHAR(5);
                        }
                        for (unsigned int d = 0; d < 30000; d++);
                }
            }
            else
            {
               
                for (int i = 1; i < 15; i++)
                {
                    SEND_CMD(DD_RAM_ADDR2);
                    SEND_CHAR(8);
                    for (int z = i; z > 1; z--)
                    {
                        SEND_CHAR(' ');
                    }
                    if (zombie1[i] == 1)
                    {
                        zombie1[i] = 0;
                        zombie_hp1[i] = 0;
                        break;
                    }
                    else if (shieldman1[i] == 1)
                    {
                        shieldman_hp1[i] -= 1;
                        if (shieldman_hp1[i] == 0)
                            shieldman1[i] = 0;
                        break;
                    }
                    else
                    {
                        SEND_CHAR(5);
                    }
                    for (unsigned int d = 0; d < 30000; d++);
                }
            }
        }
       
        {
            if (!BUTTON0)
            {
                player_row = 0;
            }
            else
                if (!BUTTON1)
                {
                    player_row = 1;
                }
            if (player_row == 0)
            {
                SEND_CMD(DD_RAM_ADDR2);
                for (int i = 0; i < 16; i++)
                {
                    SEND_CHAR(' ');
                }
                SEND_CMD(DD_RAM_ADDR);
                SEND_CHAR(8);
                randomizer = rand() % difficulty;
                for (int z = 2; z < 16; z++)
                {
                    if (zombie0[z + 1] == 1)
                    {
                        zombie0[z] = 1; zombie_hp0[z] = zombie_hp0[z + 1];
                        zombie0[z + 1] = 0; zombie_hp0[z + 1] == 0;
                        SEND_CHAR(1);
                    }
                    else
                        if (shieldman0[z + 1] == 1)
                        {
                            shieldman0[z] = 1; shieldman_hp0[z] = shieldman_hp0[z + 1];
                            shieldman0[z + 1] = 0; shieldman_hp0[z + 1] = 0;
                            SEND_CHAR(2);
                        }
                        else
                            SEND_CHAR(' ');


                }
                if (randomizer == 1)
                {
                    zombie0[15] = 1;
                    zombie_hp0[15] = 1;
                }
                if (randomizer == 2)
                {
                    shieldman0[15] = 1;
                    shieldman_hp0[15] = 2;
                }
                SEND_CMD(DD_RAM_ADDR2);
                randomizer = rand() % difficulty;
                for (int z = 1; z < 16; z++)
                {
                    if (zombie1[z + 1] == 1)
                    {
                        zombie1[z] = 1; zombie_hp1[z] = zombie_hp1[z + 1];
                        zombie1[z + 1] = 0; zombie_hp1[z + 1] == 0;
                        SEND_CHAR(1);
                    }
                    else
                        if (shieldman1[z + 1] == 1)
                        {
                            shieldman1[z] = 1; shieldman_hp1[z] = shieldman_hp1[z + 1];
                            shieldman1[z + 1] = 0; shieldman_hp1[z + 1] = 0;
                            SEND_CHAR(2);
                        }
                        else
                            SEND_CHAR(' ');


                }
                if (randomizer == 1)
                {
                    zombie1[15] = 1;
                    zombie_hp1[15] = 1;
                }
                if (randomizer == 2)
                {
                    shieldman1[15] = 1;
                    shieldman_hp1[15] = 2;
                }

            }
            else
            {
                SEND_CMD(DD_RAM_ADDR);
                for (int i = 0; i < 16; i++)
                {
                    SEND_CHAR(' ');
                }
                SEND_CMD(DD_RAM_ADDR2);
                SEND_CHAR(8);
                randomizer = rand() % difficulty;
                for (int z = 2; z < 16; z++)
                {
                    if (zombie1[z + 1] == 1)
                    {
                        zombie1[z] = 1; zombie_hp1[z] = zombie_hp1[z + 1];
                        zombie1[z + 1] = 0; zombie_hp1[z + 1] == 0;
                        SEND_CHAR(1);
                    }
                    else
                        if (shieldman1[z + 1] == 1)
                        {
                            shieldman1[z] = 1; shieldman_hp1[z] = shieldman_hp1[z + 1];
                            shieldman1[z + 1] = 0; shieldman_hp1[z + 1] = 0;
                            SEND_CHAR(2);
                        }
                        else
                            SEND_CHAR(' ');



                }
                if (randomizer == 1)
                {
                    zombie1[15] = 1;
                    zombie_hp1[15] = 1;
                }
                if (randomizer == 2)
                {
                    shieldman1[15] = 1;
                    shieldman_hp1[15] = 2;
                }
                SEND_CMD(DD_RAM_ADDR);
                randomizer = rand() % difficulty;
                for (int z = 1; z < 16; z++)
                {
                    if (zombie0[z + 1] == 1)
                    {
                        zombie0[z] = 1; zombie_hp0[z] = zombie_hp0[z + 1];
                        zombie0[z + 1] = 0; zombie_hp0[z + 1] == 0;
                        SEND_CHAR(1);
                    }
                    else
                        if (shieldman0[z + 1] == 1)
                        {
                            shieldman0[z] = 1; shieldman_hp0[z] = shieldman_hp0[z + 1];
                            shieldman0[z + 1] = 0; shieldman_hp0[z + 1] = 0;
                            SEND_CHAR(2);
                        }
                        else
                            SEND_CHAR(' ');


                }
                if (randomizer == 1)
                {
                    zombie0[15] = 1;
                    zombie_hp0[15] = 1;
                }
                if (randomizer == 2)
                {
                    shieldman0[15] = 1;
                    shieldman_hp0[15] = 2;
                }

            }


        }
        score++;grenade++;
		if(grenade==20)
		{P1OUT ^= BIT6;}
        for (int c = 0; c < player_hp * 2; c++)
        {
            P1OUT ^= BIT5;
            for(unsigned int delay=0;delay<60000;delay++);
        }
    }
	}}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void)
{
    ++licznik; _BIC_SR_IRQ(LPM3_bits);
}