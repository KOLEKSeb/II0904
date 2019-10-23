#include "LCD.h"
#include <xc.h>

#define WRITECHAR   0xA8
#define RESET       0x80
#define HOME        0x81
#define HOMECLEAR   0x82


void _LCDinit (void)
{
    LATGbits.LATG9=1;           //Select slave
    TRISGbits.TRISG9=0;         //RG9 => SDI2 (LCD)
    
    
    SPI2CONbits.MSTEN=1;        //Master mode enable
    SPI2CONbits.PPRE=1;         //Primary Prescale (Master Mode) bits
    SPI2CONbits.SPRE=7;         //Secondary Prescale (Master Mode) bits
    SPI2CONbits.CKE=0;          //SPI Clock Edge Select bit
    SPI2CONbits.CKP=0;          //Clock Polarity Select bit
    LATGbits.LATG9=0;
    
    SPI2STATbits.SPIEN=1;       //SPI Enable bit
}

void _LCDwritecmd(char c)
{
    SPI2BUF=c;                  //Transmit and Receive Buffer Address shared by SPI2TXB and SPI2RXB registers
    while(SPI2STATbits.SPITBF); //Transmit Buffer Full Status bit
}
void _LCDwritechar(char c)
{
    _LCDwritecmd(WRITECHAR);
    _LCDwritecmd(c);
}
void _LCDbitmap(int a)
{
    
}
void _LCDreset()
{
    _LCDwritecmd(RESET);
}
void _LCDhome()
{
    _LCDwritecmd(HOME);
}
void _LCDhomeclear()
{
    _LCDwritecmd(HOMECLEAR);
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
