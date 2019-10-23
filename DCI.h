/* 
 * File:   DCI.h
 * Author: tpeea
 *
 * Created on 23 octobre 2019, 17:05
 */

#ifndef DCI_H
#define	DCI_H

void _DCIinit();                      //Initialisation DCI
void _DCIsinus();                     //Envoi sinus
void _DCIsend(unsigned int*, int);    //Envoi tableau de taille fini
void _wait ();                        //Fonction attente

#endif	/* DCI_H */

