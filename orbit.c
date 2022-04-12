/*//////////////////////////////////////////////////////////////////////
Nome: Henrique Suzuki                 NUSP: 10297626
Nome: Raul dos Reis Soares            NUSP:  8535596
Nome: Isis Ardisson Logullo           NUSP:  7577410

//////////////////////////////////////////////////////////////////////*/

/*//////////////////////////////////////////////////////////////////////
comando pra compilar
gcc orbit.c spaceLib.h spaceLib.c -Wall -o spaceWar
execute com um arquivo como argumento
//////////////////////////////////////////////////////////////////////*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "spaceLib.h"
#include <unistd.h>
#include "graphic.h"


int main(int argc, char *argv[])
{	
	/*Variaveis*/
	Cenario* cena=cria_cena();
	char* txtName= argv[1];
 	ler_cena(cena,txtName);


 	/* Prints pra mostrar q funciona*/
 	printf("ANTES\n");
  	printf("%0.2e|%0.2e|%0.2e\n",cena->raio_planeta, cena->massa_planeta, cena->tempo);
	printf("%s|%0.2e|%lf|%lf|%0.2e|%0.2e\n",cena->nave1->nome_nave,cena->nave1->info_nave->massa_obj,cena->nave1->info_nave->pos_x,cena->nave1->info_nave->pos_y,cena->nave1->info_nave->vel_x,cena->nave1->info_nave->vel_y);
	printf("%s|%0.2e|%0.10e|%0.10e|%0.2e|%0.2e\n",cena->nave2->nome_nave,cena->nave2->info_nave->massa_obj,cena->nave2->info_nave->pos_x,cena->nave2->info_nave->pos_y,cena->nave2->info_nave->vel_x,cena->nave2->info_nave->vel_y);
    
	int i=1;
    for(Node* p = cena->projeteis; p != NULL; p = p->prox)
	{
		printf("%i|%lf|%lf|%lf|%lf|%lf\n",i,p->obj->massa_obj,p->obj->pos_x,p->obj->pos_y,p->obj->vel_x,p->obj->vel_y);
        i++;
	}

 	printf("\n+-----+-----+-----+ ATUALIZA +-----+-----+-----+\n\n");

	
	atualiza(cena);

	/* Prints pra mostrar q funciona*/
	printf("DEPOIS\n");
	printf("%0.2e|%0.2e|%0.2e\n",cena->raio_planeta, cena->massa_planeta, cena->tempo);
	printf("%s|%0.2e|%lf|%lf|%0.2e|%0.2e\n",cena->nave1->nome_nave,cena->nave1->info_nave->massa_obj,cena->nave1->info_nave->pos_x,cena->nave1->info_nave->pos_y,cena->nave1->info_nave->vel_x,cena->nave1->info_nave->vel_y);
	printf("%s|%0.2e|%lf|%lf|%0.2e|%0.2e\n",cena->nave2->nome_nave,cena->nave2->info_nave->massa_obj,cena->nave2->info_nave->pos_x,cena->nave2->info_nave->pos_y,cena->nave2->info_nave->vel_x,cena->nave2->info_nave->vel_y);
		
	i=1;
	for(Node* p = cena->projeteis; p != NULL; p = p->prox)
	{
		printf("%i|%lf|%lf|%lf|%0.2e|%0.2e\n",i,p->obj->massa_obj,p->obj->pos_x,p->obj->pos_y,p->obj->vel_x,p->obj->vel_y);
		i++;
	}
	
	return 0;
}
