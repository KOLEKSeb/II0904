/* 
 * File:   LCD.h
 * Author: tpeea
 *
 * Created on 16 octobre 2019, 16:33
 */

#ifndef LCD_H
#define	LCD_H

void _LCDinit(); //Initialisation LCD
void _LCDwritecmd(char); //Envoi de la commande c � l'afficheur
void _LCDwritechar(char); //Envoi du caractere c
void _LCDbitmap(int); //Envoi du bitmap index� par le int
void _LCDreset(); //Reset de l'afficheur
void _LCDhome(); //Reinitialisation du syst�me de coordon�es
void _LCDhomeclear(); //Reinitialisation du syst�me de coordon�es + Effacement de l'�cran
void _LCDgoto(int,int); //Deplacement du curseur aux coordonnees indiqu�s
void _LCDprintf(unsigned char*); //Ecrire une chaine de caractere jusqu'� 0

#endif	
