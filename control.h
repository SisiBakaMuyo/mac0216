/*//////////////////////////////////////////////////////////////////////
Nome: Henrique Suzuki                 NUSP: 10297626
Nome: Raul dos Reis Soares            NUSP:  8535596
Nome: Isis Ardisson Logullo           NUSP:  7577410
//////////////////////////////////////////////////////////////////////*/
#ifndef CONTROL_H
#define CONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphic.h"
#include "spaceLib.h"
#include <X11/keysym.h>

#define rot1 cena->nave1->rotacao
#define rot2 cena->nave2->rotacao
#define acc 20*((2*cena->raio_planeta)/(185.0))
#define ang 22.5


/* Função que atualiza a rotação das naves de acordo com a tecla pressionada
Parâmetros: Cenário que será atualizado, e keysym da tecla pressionada */
void atualiza_rotacao( Cenario* cena, KeySym mov);

#endif