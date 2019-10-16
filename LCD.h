/* 
 * File:   LCD.h
 * Author: tpeea
 *
 * Created on 16 octobre 2019, 16:33
 */

#ifndef LCD_H
#define	LCD_H

void _LCDinit(); //Initialisation LCD
void _LCDwritecmd(char); //Envoi de la commande c à l'afficheur
void _LCDwritechar(char); //Envoi du caractere c
void _LCDbitmap(int); //Envoi du bitmap indexé par le int
void _LCDreset(); //Reset de l'afficheur
void _LCDhome(); //Reinitialisation du système de coordonées
void _LCDhomeclear(); //Reinitialisation du système de coordonées + Effacement de l'écran
void _LCDgoto(int,int); //Deplacement du curseur aux coordonnees indiqués
void _LCDprintf(unsigned char*); //Ecrire une chaine de caractere jusqu'à 0

#endif	
