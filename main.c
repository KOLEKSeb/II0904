/* 
 
 

*/

#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF             // Watchdog Timer (Enabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = NONE            // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>

#include "LCD.h"
#include "Dspic.h"

int main()
{
    _LCDinit();
    _LED1init();
    _LED2init();
    _LED3init();
    _LED4init();
    _LCDhomeclear();
    _LCDwritechar('o');
    while(1);
    
     
}

void __attribute__((interrupt,auto_psv)) _INT1Interrupt(void)
{
PORTDbits.RD0=~PORTDbits.RD0;
IFS1bits.INT1IF=0; // acquittement FLAG
}

void __attribute__((interrupt,auto_psv)) _INT2Interrupt(void)
{
PORTDbits.RD1=~PORTDbits.RD1;
IFS1bits.INT2IF=0; // acquittement FLAG
}
void __attribute__((interrupt,auto_psv)) _INT3Interrupt(void)
{
PORTDbits.RD2=~PORTDbits.RD2;
IFS2bits.INT3IF=0; // acquittement FLAG
}
void __attribute__((interrupt,auto_psv)) _INT4Interrupt(void)
{
PORTDbits.RD3=~PORTDbits.RD3;
IFS2bits.INT4IF=0; // acquittement FLAG
}
