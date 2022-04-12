/*//////////////////////////////////////////////////////////////////////
Nome: Henrique Suzuki                 NUSP: 10297626
Nome: Raul dos Reis Soares            NUSP:  8535596
Nome: Isis Ardisson Logullo           NUSP:  7577410
//////////////////////////////////////////////////////////////////////*/

#include "control.h"

void atualiza_rotacao( Cenario* cena, KeySym mov) {
    switch (mov) 
    {
        case XK_Right :
            rot1 = rot1 - 1;
            if (rot1 < 0)
                rot1 = 15;
        break;

        case XK_Left :
            rot1 = rot1 + 1;
            if (rot1 > 15)
                rot1 = 0;
        break;

        case XK_Up :
            cena->nave1->info_nave->a_x += (cos((M_PI*(rot1 * ang))/180.0) * acc);
            cena->nave1->info_nave->a_y -= (sin((M_PI*(rot1 * ang))/180.0) * acc);
        break;

        case 0x64 :
            rot2 = rot2 - 1;
            if (rot2 < 0)
                rot2 = 15;
        break;

        case 0x61 :
            rot2 = rot2 + 1;
            if (rot2 > 15)
                rot2 = 0;
        break;

        case 0x77 :
            cena->nave2->info_nave->a_x += (cos((M_PI*(rot2 * ang))/180.0) * acc);
            cena->nave2->info_nave->a_y -= (sin((M_PI*(rot2 * ang))/180.0) * acc);
        break;

        //default :
        //FAZER NADA
    }
}