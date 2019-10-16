#include "LCD.h"
#include <xc.h>

#define WRITECHAR   0xA8
#define RESET       0x80
#define HOME        0x81
#define HOMECLEAR   0x82


void _LCDinit (void)
{
    
    SPI2CONbits.MSTEN=1; //Master mode enable
    SPI2CONbits.PPRE=1; //Primary Prescale (Master Mode) bits
    SPI2CONbits.SPRE=7; //Secondary Prescale (Master Mode) bits
    SPI2CONbits.CKE=1; //SPI Clock Edge Select bit
    SPI2CONbits.CKP=1; //Clock Polarity Select bit
    
    TRISGbits.TRISG9=0; //RG9 => SDI2 (LCD)
    LATGbits.LATG9=0;
    SPI1STATbits.SPIEN=1; //SPI Enable bit
}

void _LCDwritecmd(char c)
{
    SPI2BUF=c;
    while(SPI2STATbits.SPITBF);
}
void _LCDwritechar(char c)
{
    SPI2BUF=WRITECHAR;
    while(SPI2STATbits.SPITBF);
    SPI2BUF=c;
    while(SPI2STATbits.SPITBF);
    
}
void _LCDbitmap(int a)
{
    
}
void _LCDreset()
{
    SPI2BUF=RESET;
    while(SPI2STATbits.SPITBF);
}
void _LCDhome()
{
    SPI2BUF=HOME;
    while(SPI2STATbits.SPITBF);
}
void _LCDhomeclear()
{
    SPI2BUF=HOMECLEAR;
    while(SPI2STATbits.SPITBF);
}
void _LCDgoto(int l, int c)
{
    
}


void _LCDprintf(unsigned char* a)
{
    int k=0;
    while (a[k] != 0)
    {
        _LCDwritechar(a[k]);
        k++;
    }
}
