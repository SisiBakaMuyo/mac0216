/*//////////////////////////////////////////////////////////////////////
Nome: Henrique Suzuki                 NUSP: 10297626
Nome: Raul dos Reis Soares            NUSP:  8535596
Nome: Isis Ardisson Logullo           NUSP:  7577410
//////////////////////////////////////////////////////////////////////*/

/*#include guards*/
#ifndef spacelib_h
#define spacelib_h

/*/////////////////////////////////////////////////////////////////////*/
/*Tipo de dados*/
/*/////////////////////////////////////////////////////////////////////*/

#define MAX 128
#define G 6.67E-11

/* Objeto 
Pode ser nave ou um projétil 
    massa_obj — massa do objeto
    pos_x — coordenada x
    pos_y — coordenada y
    vel_x — componente x
    vel_y — componente y
    a_x — aceleração no eixo x
    a_y — aceleração no eixo y
*/
typedef struct
{
	double massa_obj;
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	double a_x;
	double a_y;
} Objeto;

/* Nave
Uma espécie de objeto q contém nome 
	nome_nave - nome da nave
	info_nave - objeto q contem as informações da nave
*/
typedef struct{
	Objeto* info_nave;
	int rotacao;
	char nome_nave[MAX];
} Nave;

/* Node
Um nó da lista ligada de projeteis
    obj - ponteiro para um objeto para um objeto (projétil)
    prox - ponteiro para o próximo nó da lista
*/
typedef struct NODE Node;
struct NODE {
    Objeto* obj;
    double tempo;
    Node* prox;
};

/*cenario
contem todas as informações do planeta, as naves e a lista de projeteis
	massa_planeta - massa do planeta
	raio_planeta - raio do planeta
	tempo - tempo de simulação
	tempo_projetil - tempo de duração dos projeteis
	nave1 - a primeira nave
	nave2 - a segunda nave
	projeteis - o primeiro node da lista ligada de projeteis
*/
typedef struct{
	double massa_planeta;
	double raio_planeta;
	double tempo;
	double dt;
	int tempo_projetil;
	int num_projetil;
	Nave* nave1;
	Nave* nave2;
	Node* projeteis;
} Cenario;

/*/////////////////////////////////////////////////////////////////////*/
/*Prototipos de funcoes*/
/*/////////////////////////////////////////////////////////////////////*/

/*Funções já implementadas e testadas*/

Cenario* cria_cena();

Objeto* cria_obj(double massa,double pos_x, double pos_y, double vel_x, double vel_y);

Nave* cria_nave(char* nome,double massa,double pos_x, double pos_y, double vel_x, double vel_y);

void insere_node(Cenario* cena, double massa,double npos_x, double npos_y, double nvel_x, double nvel_y);

void remove_node (Cenario* cena, Node* node);

void ler_cena(Cenario* cena, char* txtName);

double distancia(double pos_x1, double pos_y1, double pos_x2, double pos_y2);

void calc_grav(Cenario* cena, Objeto* corpo);

void atualiza(Cenario* cena) ;

void euler_s(Objeto* corpo, double dt);

int bateu_planeta(Cenario* cena);

/*Funções ainda não implementadas*/

/*Não sei se precisa dessa função*/
void calc_iteracao(Objeto* corpo1, Objeto* corpo2); 

/*Não sei se precisa dessa função*/
void calc_forcas(Cenario* cena);

/*Não sei se precisa dessa função*/
void zera_forcas(Cenario* cena);

#endif /* spacelib_h */

