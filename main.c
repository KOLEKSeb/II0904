/* 
 
 

 */

// FOSC
#pragma config FPR = XT_PLL16           // Primary Oscillator Mode (XT w/PLL 16x)
#pragma config FOS = PRI                // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

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
#include "DCI.h"


int volume = 23;
short flagVolume = 0;
short flagLCD = 0;

int Sin[] = {0x0000, 0x2975, 0x4E73, 0x6AFA, 0x7BF9, 0x7F99, 0x7578, 0x5EAB, 0x3DA9,
    0x1601, 0xEBFB, 0xC41C, 0xA2B2, 0x8B59, 0x8093, 0x838B, 0x93EE, 0xAFF9, 0xD4A5, 0xFDFE};

int main() {
    //INITIALISATION MATERIELLE
    _LCDinit();
    _LED1init();
    _LED2init();
    _LED3init();
    _LED4init();
    _LCDhomeclear();
    _DCIinit();
    
    //INITIALISATION AFFICHAGE
    _LCDprintf("Volume = ");
    _LCDwritechar(0x30 + volume / 10); //Affichage dixaine
    _LCDwritechar(0x30 + volume % 10); //Affichage unité

    //PROGRAMME
    while (1) {
        if (flagLCD == 1) {
            _LCDhomeclear();
            _LCDprintf("Volume = ");
            _LCDwritechar(0x30 + volume / 10);
            _LCDwritechar(0x30 + volume % 10);
            flagLCD = 0;
        }
    }
}

void __attribute__((interrupt, auto_psv)) _INT1Interrupt(void) {
    if (volume > 0) {
        volume--;
        flagVolume = 1;
        flagLCD = 1;
    }

    IFS1bits.INT1IF = 0; // acquittement FLAG
}

void __attribute__((interrupt, auto_psv)) _INT2Interrupt(void) {
    if (volume < 31) {
        volume++;
        flagVolume = 1;
        flagLCD = 1;
    }
    IFS1bits.INT2IF = 0; // acquittement FLAG
}

void __attribute__((interrupt, auto_psv)) _INT3Interrupt(void) {
    PORTDbits.RD2 = ~PORTDbits.RD2;
    IFS2bits.INT3IF = 0; // acquittement FLAG
}

void __attribute__((interrupt, auto_psv)) _INT4Interrupt(void) {
    PORTDbits.RD3 = ~PORTDbits.RD3;
    IFS2bits.INT4IF = 0; // acquittement FLAG
}


void __attribute__((interrupt, auto_psv)) _DCIInterrupt(void) {
    static int k = 0; //Compteur
    int DACValue = Sin[k]&(~0x0001); //Valeur à émettre
    //~ : NOT
    //Bit poid faible != 0 car sinon demande de commande 
    int cmdValue = 0; 
    //Controle du volume
    if (flagVolume) {
        DACValue |= 1;
        //Bit de poid faible à 1 : Envoi de commande
        cmdValue = (0x0700 + (0x00ff & volume)*4);
        //0x7XX : Registre 7
        //_____________________________________
        //         XX 
        //bit 7 : 0
        //bit 6 -> bit 2 : Valeur volume (TXG)
        //bit 2 -> bit 0 : SLM/SRM = 0
        //______________________________________
        flagVolume = 0;
    }
    TXBUF0 = DACValue;
    TXBUF1 = cmdValue;
    //Envoi de la trame
    k = (k + 1) % 20; //Limite tableau sinus
    IFS2bits.DCIIF = 0; // raz flag;
}
