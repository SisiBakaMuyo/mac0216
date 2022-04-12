/*//////////////////////////////////////////////////////////////////////
Nome: Henrique Suzuki                 NUSP: 10297626
Nome: Raul dos Reis Soares            NUSP:  8535596
Nome: Isis Ardisson Logullo           NUSP:  7577410

Modulo que cria os objetos que vao ser utilizados no programa principal
//////////////////////////////////////////////////////////////////////*/

/*#include guards*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "graphic.h"
#include "spaceLib.h"
#include "control.h"



/*//////////////////////////////////////////////////////////////////////
	FUNÇÕES DE INICIALIZAÇÃO
//////////////////////////////////////////////////////////////////////*/

/*
Função que cria um cenario, depois aloca espaço e inicializa as variaveis
Parametros:
Retorna: o endereço do cenario criado
 */
Cenario* cria_cena()
{
	Cenario* cena=malloc(sizeof(Cenario));
	cena->massa_planeta=0;
	cena->raio_planeta=0;
	cena->num_projetil=0;
	cena->tempo=0;
	cena->dt=0;
 	cena->tempo_projetil=0;
	cena->nave1=NULL;
	cena->nave2=NULL;
	return cena;
}

/*Função que aloca espaço e cria um objeto
Parametros: massa do objeto(kg), posição no eixo x, posição no eixo y, velocidade no eixo x, velocidade no eixo y
Retorna: o endereço do objeto criado
*/
Objeto* cria_obj(double massa,double npos_x, double npos_y, double nvel_x, double nvel_y)
{	
	Objeto* obj=malloc(sizeof(Objeto));
	obj->massa_obj = massa;
	obj->pos_x = npos_x;
	obj->pos_y = npos_y;
	obj->vel_x = nvel_x;
	obj->vel_y = nvel_y;
 	obj->a_x = 0;
	obj->a_y= 0;
	return obj;
}

/*Função que aloca espaço e cria uma nave
Parametros: nome da nave, massa do objeto(kg), posição no eixo x, posição no eixo y, velocidade no eixo x, velocidade no eixo y
Retorna: o endereço da nave criada*/
Nave* cria_nave(char* nome,double massa,double npos_x, double npos_y, double nvel_x, double nvel_y)
{
	Nave* nav=malloc(sizeof(Nave));
	strcpy(nav->nome_nave,nome);
	nav->info_nave= cria_obj(massa,npos_x,npos_y,nvel_x,nvel_y);
  nav->rotacao = 10;
	return nav;
}

/*Função que insere um nó com um objeto que contém as propriedades dos parametro passados na lista ligada do cenário.
Parametros: o cenario, massa do objeto(kg), posição no eixo x, posição no eixo y, velocidade no eixo x, velocidade no eixo y
Função sem valor de retorno*/
void insere_node(Cenario* cena, double massa,double npos_x, double npos_y, double nvel_x, double nvel_y) {
    Node* node = malloc(sizeof(Node));

    node->obj = cria_obj( massa, npos_x, npos_y, nvel_x, nvel_y);
    node->tempo = cena->tempo_projetil;
    node->prox = cena->projeteis;
    cena->projeteis = node;
}


/*Função que remove um nó da lista ligada do cenário.
Parametros: o cenario, o endereço do nó a ser removido
Função sem valor de retorno*/
void remove_node (Cenario* cena, Node* node) {
    Node* p = cena->projeteis;

    //verificando se o primeiro nó é o node
    if (p == node) {
        cena->projeteis = p->prox;
    }else {
        // procurando o nó a ser removido
        while (p->prox != node) {
            if (p == NULL) {
                printf("Erro ao remover o projetil\n");
                break;
            }
            p = p->prox;
        }
        p->prox = node->prox;
    }
    cena->num_projetil+=-1;
    free(node);
}


/*Função que le o arquivo da entrada e retira as informações sobre o cenario
Parametros: o cenario inicializado e o nome do arquivo
Retorna: nada */
void ler_cena(Cenario* cena, char* txtName)
{
	FILE* cfgTxt= malloc(sizeof(FILE));
  	char* atLine = malloc(sizeof(char)*MAX);

  	/*primeiro passo é ler o arquivo de entrada pra conseguir as informçãoes sobre o jogo */
  	
  	/*Pergunta o dt*/
  	printf("Digite o intervalo de tempo: \n>>>> ");
  	scanf("%lf", &cena->dt);

  	/* Abre o arquivo */
  	cfgTxt= fopen(txtName, "r");
  	
  	/* Pega as informações do planeta*/
  	fgets(atLine, MAX, cfgTxt);
  	sscanf(atLine,"%lf %lf %lf", &cena->raio_planeta, &cena->massa_planeta, &cena->tempo);
  	
  	/* Pega as informações da Nave 1*/
  	char* nome_nave= malloc(sizeof(char)*MAX);
  	double massa,posx,posy,velx,vely;

  	fgets(atLine, MAX, cfgTxt);
  	sscanf(atLine,"%s %lf %lf %lf %lf %lf", nome_nave, &massa,&posx,&posy,&velx,&vely);
	  Nave* nave1=cria_nave(nome_nave,massa,posx,posy,velx,vely);
	  cena->nave1=nave1;

  	/* Pega as informações da Nave 2*/
  	fgets(atLine, MAX, cfgTxt);
  	sscanf(atLine,"%s %lf %lf %lf %lf %lf", nome_nave, &massa,&posx,&posy,&velx,&vely);
  	Nave* nave2=cria_nave(nome_nave,massa,posx,posy,velx,vely);
  	cena->nave2=nave2;

  	/* Pega o numero de projeteis e o tempo de duração*/  	
  	fgets(atLine, MAX, cfgTxt);
  	sscanf(atLine,"%i %i", &cena->num_projetil,&cena->tempo_projetil);

  	/*cria os projeteis*/
    for(int i=0;i<cena->num_projetil;i++){
        fgets(atLine, MAX, cfgTxt);
        sscanf(atLine,"%lf %lf %lf %lf %lf", &massa,&posx,&posy,&velx,&vely);
        insere_node(cena, massa, posx, posy, velx, vely);
    }

  	//free(txtName);
  	free(cfgTxt);
  	free(atLine);
  	
  	free(nome_nave);
}


/*//////////////////////////////////////////////////////////////////////
	FUNÇÕES DE CÁLCULO DA FÍSICA
//////////////////////////////////////////////////////////////////////*/



/*Função: Essa função calcula a aceleração causada pela gravidade do planeta
Parametros: o cenario inicializado e o nome do arquivo
Retorna: nada 
gravidade=G.M/d^2

*/
void calc_grav(Cenario* cena, Objeto* corpo) { 
  	double d, g, ax, ay;
 	d = distancia(0, 0, corpo->pos_x, corpo->pos_y);
  	g = (G * cena->massa_planeta/pow(d,2));

 	//calculando as componentes fx e fy
 	ax = -1*(corpo->pos_x * g)/d;
 	ay = -1*(corpo->pos_y * g)/d;

  	//atualizando a força resultante f_x e f_y do corpo
  	corpo->a_x = ax;
  	corpo->a_y = ay;
}



/*Função: Calcula a distancia entre dois pontos
Parametros: x1, y1, x2, y2
Retorna: a distancia
*/
double distancia(double pos_x1, double pos_y1, double pos_x2, double pos_y2)
{
	double dist=0;
	dist= sqrt(pow((pos_x1 - pos_x2),2) + pow((pos_y1 - pos_y2),2));
	return dist;
}


/*Função: Atualiza as informações do corpo com as formulas de euler pra espaço e velocidade
Parametros: o objeto que vai ser atualizado
Retorna: nada
*/
void euler_s(Objeto* corpo, double dt)
{
	/*atualiza a velocidade do corpo*/
	corpo->vel_x+=(corpo->a_x)*dt;
	corpo->vel_y+=(corpo->a_y)*dt;

	/*atualiza a posição do corpo*/
	corpo->pos_x+=(corpo->vel_x)*dt;
	corpo->pos_y+=(corpo->vel_y)*dt;

	//printf("%0.5e|%0.5e\n",corpo->pos_x,corpo->pos_y);
	
}

/*Função: Verifica se as naves bateram no planeta
Parametros: O cenário
Retorna: 1 caso sim e 0 caso não
*/
int bateu_planeta(Cenario* cena)
{
	double d=distancia(0, 0, cena->nave1->info_nave->pos_x, cena->nave1->info_nave->pos_y);
	if (d- cena->raio_planeta<1e-10)
	{

		printf("\n Nave: %s colidiu com o planeta.\n",cena->nave1->nome_nave);
		printf("\n distancia: %lf | raio: %lf \n",d,cena->raio_planeta);
		return 0;
	}
	d=distancia(0, 0, cena->nave2->info_nave->pos_x, cena->nave2->info_nave->pos_y);
	if (d- cena->raio_planeta<1e-10)
	{
		printf("\n Nave: %s colidiu com o planeta.\n",cena->nave2->nome_nave);
		printf("\n distancia: %lf | raio: %lf \n",d,cena->raio_planeta);
		return 0;
	}
	return 1;

}

/*Função: atualiza todo so elementos da cena
Parametros: O cenário
Não tem valor de retorno
*/

void atualiza(Cenario* cena) {
  PIC  nave1[16],  nave2[16], background, planeta, ball;
  WINDOW *w= cria_janela();
  MASK msks[18];

  InitKBD(w);
  

if(WCheckKBD(w)){
 	

  ler_img(w, nave1, nave2, &background, &planeta, &ball, msks);
  usleep(12500);
  
  WClear(w);
	for (double t0=0; t0<=cena->tempo;t0+=cena->dt)
	{

	usleep(25000);		
    //Calcula gravidade das naves
    calc_grav(cena, cena->nave1->info_nave);
    calc_grav(cena, cena->nave2->info_nave);
    //Verificar pressionamento de teclas
    if (WCheckKBD(w)) {
      WGetKey(w);
      atualiza_rotacao( cena, WLastKeySym());
    }

    //Atualiza posições gráficas
    atualiza_grafico(w, nave1, nave2, background, planeta, ball, cena, msks);
    usleep(25000);

    //Atualiza naves
		euler_s(cena->nave1->info_nave, cena->dt);
		euler_s(cena->nave2->info_nave, cena->dt);

		/*Atualiz os projéteis*/
		for(Node* p = cena->projeteis; p != NULL; p = p->prox)
		{
			calc_grav(cena,p->obj);
			euler_s(p->obj, cena->dt);
			p->tempo= p->tempo- cena->dt;
		}

		/*Remove os projéteis cujo tempo expirou*/
		int x=cena->num_projetil;
		Node* p = cena->projeteis;
		for(int i=0; i<x;i++)
		{	
			Node* at=p;
			p=p->prox;
			if (at->tempo-0< 1e-10){remove_node(cena,at);printf("Explodiu projetil|");}
		}

		//if(bateu_planeta(cena)==0){break;}
	}
  WDestroy(w);
  CloseGraph();
	printf("\n");
  }	
}

/*Algumas funções que começamos, podem acabar sendo uteis nas próximas fases */

/*Função: Calcula a forca resultante de cada elemento do cenário (exceto o planeta)
Parametros: o cenário
Função sem retorno
*/
/*
void calc_forcas(Cenario* cena) {
  Objeto* obj = NULL;
  //zerando todas as forças para recalculá-las
  zera_forcas();

  //calculando a força resultante da nave1
  obj = cena->nave1->info_nave;
  calc_grav(cena, obj);
  for (Node* p = cena->projeteis; p != NULL; p = p->prox) {
    calc_iteracao(obj, p->obj);
  }
  calc_iteracao(obj, cena->nave2->info_nave);

    //calculando a força resultante da nave2
  obj = cena->nave2->info_nave;
  calc_grav(cena, obj);
  for (Node* p = cena->projeteis; p != NULL; p = p->prox) {
    calc_iteracao(obj, p->obj);
  }

  //calculando a forca resultante de cada objeto
  for (obj = cena->projeteis; obj != NULL; obj = obj->prox)
    for (Node* p = obj->prox; p != NULL; p = p->prox) {
      calc_iteracao(obj, p->obj);
    }
}
*/

/*Função: Calcula a forca de iteraçao entre dois corpos
Parametros: corpo1, corpo2
Função sem retorno
F=G.M.m/d^2
*/
/*
void calc_iteracao(Objeto* corpo1, Objeto* corpo2) {
  double f, fx, fy, d, dx, dy;

  //calculando a força resultante
  d = distancia(corpo1->pos_x,  corpo1->pos_y, corpo2->pos_x, corpo2->pos_y);
  dx = absf(corpo1->pos_x - corpo2->pos_x);
  dy = absf(corpo2->pos_y - corpo2-> pos_y);
  f = (G * corpo1->massa_obj * corpo2->massa_obj);
  fx = (dx * f)/d;
  fy = (dy * f)/d;

  //atualizando a força resultante de cada corpo
  if (corpo1->pos_x > corpo2->pos_x) {
    corpo1->f_x += -fx;
    corpo2->f_x +=  fx; 
  }
  else {
    corpo1->f_x +=  fx;
    corpo2->f_x += -fx;
  }

  if (corpo1->pos_y > corpo2->pos_y) {
    corpo1->f_y += -fy;
    corpo2->f_y +=  fy; 
  }
  else {
    corpo1->f_y +=  fy;
    corpo2->f_y += -fy;
  }
}
*/

/*Função: Muda a força resultante de todos os objetos da cena para zero (a fim de calcular as novas forças)
Parametros: o cenário
Função sem retorno
*/
/*
void zera_forcas(Cenario* cena) {
  cena->nave1->info_nave->f_x = 0;
  cena->nave1->info_nave->f_y = 0;
  cena->nave2->info_nave->f_x = 0;
  cena->nave2->info_nave->f_x = 0;

  for (Node* p = cena->projeteis; p != NULL; p = p->prox) {
    p->obj->f_x = 0;
    p->obj->f_x = 0;
  }
}
*/
