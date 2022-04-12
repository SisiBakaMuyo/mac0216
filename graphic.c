/* /\*\////////////////////////////////////////////////////////////////////// */
/* Nome: Henrique Suzuki                 NUSP: 10297626 */
/* Nome: Raul dos Reis Soares            NUSP:  8535596 */
/* Nome: Isis Ardisson Logullo           NUSP:  7577410 */

/* //////////////////////////////////////////////////////////////////////\*\/ */

/* /\*\////////////////////////////////////////////////////////////////////// */
/* comando pra compilar */
/* gcc graphic.c xwc.h xwc.c -Wall -O -lX11 -lXpm -lm */
/* //////////////////////////////////////////////////////////////////////\*\/ */

/*
Função que cria uma janela, depois aloca espaço imprime o fundo e o planeta na janela
Parametros:
Retorna: o endereço da janela criada
*/

#include "graphic.h"

WINDOW* cria_janela(){
    PIC background;
    WINDOW *w=malloc(sizeof(WINDOW));
    w = InitGraph(LARG, ALT, "SpaceWar");
    background = ReadPic(w, "images/abertura.xpm", NULL);
    PutPic(w, background, 0,0, 1139, 673, 0, 0);

    return w;
    }

    

void atualiza_grafico(WINDOW *w, PIC nave1[], PIC nave2[], PIC background, PIC planeta, PIC ball, Cenario* cena, MASK msks[]) {
    //WClear(w);
    PutPic(w, background, 0,0, 1139, 673, 0, 0);

    SetMask(w,msks[16]);
    PutPic(w, planeta, 0, 0, 185, 185, 477, 244);
    UnSetMask(w);

    SetMask(w,msks[cena->nave1->rotacao]);
    PutPic(w, nave1[cena->nave1->rotacao], 0, 0, 100, 100, (int) (((92.5)*((cena->nave1->info_nave->pos_x)/(cena->raio_planeta))) + (527.0)), (int) (((92.5)*((cena->nave1->info_nave->pos_y)/(cena->raio_planeta))) + (294.0)));
    UnSetMask(w);

    SetMask(w,msks[cena->nave2->rotacao]);
    PutPic(w, nave2[cena->nave2->rotacao], 0, 0, 100, 100, (int) (((92.5)*((cena->nave2->info_nave->pos_x)/(cena->raio_planeta))) + (527.0)), (int) (((92.5)*((cena->nave2->info_nave->pos_y)/(cena->raio_planeta))) + (294.0)));
    UnSetMask(w);

    SetMask(w, msks[17]);
    for(Node* p = cena->projeteis; p != NULL; p = p->prox) {
        PutPic(w, ball, 0, 0, 32, 32, (int) (((92.5)*((p->obj->pos_x)/(cena->raio_planeta))) + (552.0)), (int) (((92.5)*((p->obj->pos_y)/(cena->raio_planeta))) + (319.0)));
    }
    UnSetMask(w);
}

void ler_img(WINDOW *w,PIC nave1[], PIC nave2[], PIC *background, PIC *planeta, PIC *ball, MASK msks[]) {
  PIC basenave, baseplaneta, baseball;
  basenave = ReadPic(w, "images/basenave.xpm", NULL);
  baseplaneta = ReadPic(w,"images/baseplaneta.xpm", NULL);
  baseball = ReadPic(w, "images/baseball.xpm", NULL);
  for (int i = 0; i < 16; i++)
    msks[i] = NewMask(basenave, 100, 100);
  msks[16] = NewMask(baseplaneta, 185, 185);
  msks[17] = NewMask(baseball, 32, 32);

  *background = ReadPic(w, "images/fundo.xpm", NULL);
  nave1[0] = ReadPic(w, "images/Ship6-1.xpm", msks[0]);
  nave1[1] = ReadPic(w, "images/Ship6-2.xpm", msks[1]);
  nave1[2] = ReadPic(w, "images/Ship6-3.xpm", msks[2]);
  nave1[3] = ReadPic(w, "images/Ship6-4.xpm", msks[3]);
  nave1[4] = ReadPic(w, "images/Ship6-5.xpm", msks[4]);
  nave1[5] = ReadPic(w, "images/Ship6-6.xpm", msks[5]);
  nave1[6] = ReadPic(w, "images/Ship6-7.xpm", msks[6]);
  nave1[7] = ReadPic(w, "images/Ship6-8.xpm", msks[7]);
  nave1[8] = ReadPic(w, "images/Ship6-9.xpm", msks[8]);
  nave1[9] = ReadPic(w, "images/Ship6-10.xpm", msks[9]);
  nave1[10] = ReadPic(w, "images/Ship6-11.xpm", msks[10]);
  nave1[11] = ReadPic(w, "images/Ship6-12.xpm", msks[11]);
  nave1[12] = ReadPic(w, "images/Ship6-13.xpm", msks[12]);
  nave1[13] = ReadPic(w, "images/Ship6-14.xpm", msks[13]);
  nave1[14] = ReadPic(w, "images/Ship6-15.xpm", msks[14]);
  nave1[15] = ReadPic(w, "images/Ship6-16.xpm", msks[15]);
  nave2[0] = ReadPic(w, "images/Ship2-1.xpm", msks[0]);
  nave2[1] = ReadPic(w, "images/Ship2-2.xpm", msks[1]);
  nave2[2] = ReadPic(w, "images/Ship2-3.xpm", msks[2]);
  nave2[3] = ReadPic(w, "images/Ship2-4.xpm", msks[3]);
  nave2[4] = ReadPic(w, "images/Ship2-5.xpm", msks[4]);
  nave2[5] = ReadPic(w, "images/Ship2-6.xpm", msks[5]);
  nave2[6] = ReadPic(w, "images/Ship2-7.xpm", msks[6]);
  nave2[7] = ReadPic(w, "images/Ship2-8.xpm", msks[7]);
  nave2[8] = ReadPic(w, "images/Ship2-9.xpm", msks[8]);
  nave2[9] = ReadPic(w, "images/Ship2-10.xpm", msks[9]);
  nave2[10] = ReadPic(w, "images/Ship2-11.xpm", msks[10]);
  nave2[11] = ReadPic(w, "images/Ship2-12.xpm", msks[11]);
  nave2[12] = ReadPic(w, "images/Ship2-13.xpm", msks[12]);
  nave2[13] = ReadPic(w, "images/Ship2-14.xpm", msks[13]);
  nave2[14] = ReadPic(w, "images/Ship2-15.xpm", msks[14]);
  nave2[15] = ReadPic(w, "images/Ship2-16.xpm", msks[15]);
  *planeta = ReadPic(w, "images/planeta.xpm", msks[16]);
  *ball = ReadPic(w, "images/ball.xpm", msks[17]);
}