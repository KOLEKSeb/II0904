#include "Dspic.h"

void _LED1init(void)
{
    TRISDbits.TRISD0=0; // configuration LED1 en sortie
    // initialisation INT1 sur SW1
    INTCON2bits.INT1EP=1; // interruption sur front descendant.
    IPC4bits.INT1IP=1; // priorit´e 1
    IFS1bits.INT1IF=0; // raz FLAG
    IEC1bits.INT1IE=1; // autorisation interruption INT1
    //Watchdog, esclave, 
}

void _LED2init(void)
{
    TRISDbits.TRISD1=0; // configuration LED2 en sortie
    INTCON2bits.INT2EP=1; // interruption sur front descendant.
    IPC5bits.INT2IP=1; // priorit´e 1
    IFS1bits.INT2IF=0; // raz FLAG
    IEC1bits.INT2IE=1; // autorisation interruption INT2
}

void _LED3init(void)
{
    TRISDbits.TRISD2=0; // configuration LED2 en sortie
    INTCON2bits.INT3EP=1; // interruption sur front descendant.
    IPC9bits.INT3IP=1; // priorit´e 1
    IFS2bits.INT3IF=0; // raz FLAG
    IEC2bits.INT3IE=1; // autorisation interruption INT2
}

void _LED4init(void)
{
    TRISDbits.TRISD3=0; // configuration LED2 en sortie
    INTCON2bits.INT4EP=1; // interruption sur front descendant.
    IPC9bits.INT4IP=1; // priorit´e 1
    IFS2bits.INT4IF=0; // raz FLAG
    IEC2bits.INT4IE=1; // autorisation interruption INT2
    //Watchdog, esclave, 
}