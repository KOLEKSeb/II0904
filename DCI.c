#include "DCI.h"
#include <xc.h>


void _DCIinit()
{
    //a) Pour éviter d'imposer un niveau sur le reset, placer F6 en entrée :
    TRISFbits.TRISF6=1 ;
    
    //b) Réglage de la taille et du nombre de slots
    DCICON2bits.COFSG=0xF ; // 16 slots par trame
    DCICON2bits.WS=0xF ; // 16 bits par slot
    
    /*c) Réglage fréquence (Baus rate Generator)
    On souhaite Fs=8000Hz soit une horloge Fsck=256*Fs=2.048e6Hz
    BCG=Fcy/2/Fsck-1=6*/
    DCICON3=6 ; //En fait, on atteint 8.2kHz ainsi
    
    /*d) Paramétrage du fonctionnement du bus
    Cela règle l'horloge et la génération Frame synchro en sortie pour un mode maitre sur le dsPIC
    (CSCKD=0 et COFSD=0).
    On utilise le mode Multichannel+ frame synchro (COFSM=00), CSCKE=0 (calage des fronts
    d'hologe), DJST : TX à FS+1 (page 8 SI3000). Pas de contrôleur multiple sur le bus donc CSDO=0)*/
    DCICON1=0x0000 ;
    
    //e) réglage des slots utilisés en émission et réception
    TSCON=0x101 ; // 0 et 8 en émission
    RSCON= 0x101 ; // idem en réception
    
    //f) paramétrage des buffers
    DCICON2bits.BLEN=0x1 ; // utilisation de buffers de taille 2 entre interruptions
    
    //g) préparation de l'écriture des premières données d'initialisation dans les buffers
    TXBUF0=0x0001 ; //secondary frame
    //TXBUF1=0x0nXX ; // n : index registre, XX valeur à transmettre
    
    // h) reset du SI3000
    // positionnement en non reset
    //PORTF6bits.RF6=1 ;
    //programmation en sortie
    TRISFbits.TRISF6=0 ;
    // application d'un reset
    PORTFbits.RF6=0 ;
    _wait(1) ; //>250ns
    //Fin du reset
    PORTFbits.RF6=1 ;
    
    //i) validation du module DCI et configuration des registres SI3000
    DCICON1bits.DCIEN=1 ;

    //j) attente de fin d'émission et envoi des données suivantes
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x0300;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x0413;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x0200;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x010A;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x0547;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x065E;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x075C;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    
    TXBUF0=0x0001;
    TXBUF1=0x0900;
    while(DCISTATbits.TMPTY==0); // attente TXBUF vidé
    _wait(10000); // attente 100ms pour l'établissement du calibrage

    
    //k) configuration interruptions
    IFS2bits.DCIIF=0; // raz flag;
    IEC2bits.DCIIE=1; // autorise l'interruption DCI
    
}

void _DCIsend(unsigned int* a, int TAILLE)
{ 
    int k=0;
    while(a[k] != TAILLE)
    {
    TXBUF0=0x0001;
    TXBUF1=a[k];
    while(DCISTATbits.TMPTY==0);
    k++;
    }
}

void _DCIsinus()
{
    int Sin[]={0x0000,0x2975,0x4E73,0x6AFA,0x7BF9,0x7F99,0x7578,0x5EAB,0x3DA9,
    0x1601,0xEBFB,0xC41C,0xA2B2,0x8B59,0x8093,0x838B,0x93EE,0xAFF9,0xD4A5,0xFDFE};
    int k=0;
    for (k=0; k<20; k++)
    {
    TXBUF0=0x0001;
    TXBUF1=Sin[k];
    while(DCISTATbits.TMPTY==0);
    }
}

void _wait(unsigned int time10mus)
{
    unsigned int l;
    for(l=0;l<time10mus;l++)
    {
       asm("REPEAT #295"); // 295x34ns = 10µs
       asm("NOP");
    }
}

