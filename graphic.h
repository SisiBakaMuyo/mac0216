/*//////////////////////////////////////////////////////////////////////
Nome: Henrique Suzuki                 NUSP: 10297626
Nome: Raul dos Reis Soares            NUSP:  8535596
Nome: Isis Ardisson Logullo           NUSP:  7577410
//////////////////////////////////////////////////////////////////////*/

/*#include guards*/
#ifndef graphic_h
#define graphic_h
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <X11/keysym.h>
#include "xwc.h"
#include "spaceLib.h"


/*/////////////////////////////////////////////////////////////////////*/
/*Tipo de dados*/
/*/////////////////////////////////////////////////////////////////////*/

#define ALT 673
#define LARG 1139

/*/////////////////////////////////////////////////////////////////////*/
/*Prototipos de funcoes*/
/*/////////////////////////////////////////////////////////////////////*/

/*Funções já implementadas e testadas*/

WINDOW* cria_janela();

void atualiza_grafico(WINDOW *w, PIC nave1[], PIC nave2[], PIC background, PIC planeta, PIC ball, Cenario* cena, MASK msks[]);

void ler_img(WINDOW *w,PIC nave1[], PIC nave2[], PIC *background, PIC *planeta, PIC *ball, MASK msks[]);

#endif /* graphic_h */

