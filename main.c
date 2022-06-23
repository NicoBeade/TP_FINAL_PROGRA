#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*******************************************************************************************************************************************
 * 
                                 _____   _                          _           ___           _              
                                |_   _| (_)  _ __   ___   ___    __| |  ___    |   \   __ _  | |_   ___   ___
                                  | |   | | | '_ \ / _ \ (_-<   / _` | / -_)   | |) | / _` | |  _| / _ \ (_-<
                                  |_|   |_| | .__/ \___/ /__/   \__,_| \___|   |___/  \__,_|  \__| \___/ /__/
                                            |_|                                                          
 * 
 ******************************************************************************************************************************************/
typedef struct{//Esta estructura define un vector para las coordenadas
    int x;
    int y;
}vector_t;

typedef struct ALIEN{//Cada uno de los aliens sera una estructura de este tipo. Todos los aliens estan en una lista
    vector_t pos;//Posicion del alien
    int type;//Tipo de nave
    int lives;//Cantidad de vidas del alien (Distintos tipos de alien pueden tener mas o menos vidas)
    struct ALIEN * next;//Puntero al siguiente alien de la lista.
}alien_t;
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/


/*******************************************************************************************************************************************
 * 
                                     ___                     _                   _              
                                    / __|  ___   _ _    ___ | |_   __ _   _ _   | |_   ___   ___
                                   | (__  / _ \ | ' \  (_-< |  _| / _` | | ' \  |  _| / -_) (_-<
                                    \___| \___/ |_||_| /__/  \__| \__,_| |_||_|  \__| \___| /__/
                                                                                                                                                            
 * 
 ******************************************************************************************************************************************/
#define IZQUIERDA -1
#define DERECHA 1
#define ABAJO 1

#define DIST_INICIAL_X 6
#define DIST_INICIAL_Y 4
#define ESP_ALIENS_X 1
#define TAM_ALIENS_X 3
#define ESP_ALIENS_Y 1
#define TAM_ALIENS_Y 3

enum alienTypes {nodriza, superior, medio, inferior};
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/


/*******************************************************************************************************************************************
 * 
                                 ___               _           _     _                   
                                | _ \  _ _   ___  | |_   ___  | |_  (_)  _ __   ___   ___
                                |  _/ | '_| / _ \ |  _| / _ \ |  _| | | | '_ \ / _ \ (_-<
                                |_|   |_|   \___/  \__| \___/  \__| |_| | .__/ \___/ /__/
                                                                        |_|                                                            
 * 
 ******************************************************************************************************************************************/
alien_t* createListAlien(int aliensTotales, alien_t* listAlien);     //Crea la lista de los aliens.
void removeAlienList(int aliensTotales, alien_t* listAlien);    //Elimina de heap la lista creada.

//void moveAlien (alien_t* alien, int direccion); //Se encarga de modificar la posicion de los aliens.
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/


/*******************************************************************************************************************************************
 * 
                                __   __                  ___   _         _             _            
                                \ \ / /  __ _   _ _     / __| | |  ___  | |__   __ _  | |  ___   ___
                                 \ V /  / _` | | '_|   | (_ | | | / _ \ | '_ \ / _` | | | / -_) (_-<
                                  \_/   \__,_| |_|      \___| |_| \___/ |_.__/ \__,_| |_| \___| /__/
                                                                                                                                                            
 * 
 ******************************************************************************************************************************************/
//int timerTick;  //Esta variable es un "contador" que se decrementa cada cierto tiempo y con ella se controla cada cuanto tiempo se
                //ejecuta cada accion del programa.

//int velAliens;  //Determina que tan rapido se moveran los aliens

//int direccion;  //Determina la direccion en la que se tienen que mover los aliens en el proximo tick

//int vidas;      //Indica las vidas restantes del usuario

//int xMax;       //Ancho maximo de la pantalla
//int yMax;       //Alto maximo de la pantalla

int aliensTotales;  //Indica con cuantos aliens comienza el juego
//int aliensRestantes;    //Indica cuantos aliens quedan en la partida
int filasAliens; //Cantidad total de filas de aliens
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/


int main(void) {
    
    aliensTotales = 12;
    filasAliens = 4;

    alien_t* listAlien;

    listAlien = createListAlien(aliensTotales, listAlien);

    removeAlienList(aliensTotales, listAlien);

    return 0;
}


alien_t* createListAlien(int aliensTotales, alien_t* listAlien){
/* Esta funcion se encarga de crear la lista de los aliens. Recibe como parametros la cantidad de aliens totales y el puntero al que se desea que
    se devuelva el primer elemento de la lista.
*/
    int i;
    int despX = DIST_INICIAL_X;
    int despY = DIST_INICIAL_Y;   //Se utilizan para desplazar en x e y al crear los aliens.
    alien_t* auxiliar;
    int colAliens = aliensTotales / filasAliens;    //Cantidad de aliens por fila

    auxiliar = listAlien;

    for(i = 0 ; i < aliensTotales ; i++){//Se crea la lista
        auxiliar = malloc(sizeof(alien_t));

        if(auxiliar == NULL){
            printf("No se ha podido ampliar la lista\n");
        }

        auxiliar->pos.x = despX;//Posicion del alien
        auxiliar->pos.y = despY;
        
        switch(despY){//Tipo de alien y cantidad de vidas
            case DIST_INICIAL_Y://Si esta en la primera fila de aliens es de tipo superior y tiene 2 vidas
                auxiliar->type = superior;
                auxiliar->lives = 2;
                break;
            case DIST_INICIAL_Y + ESP_ALIENS_Y + TAM_ALIENS_Y://Si esta en la segunda o tercera fila es de tipo medio con una vida
                auxiliar->type = medio;
                auxiliar->lives = 1;
                break;
            case DIST_INICIAL_Y + 2*ESP_ALIENS_Y + 2*TAM_ALIENS_Y:
                auxiliar->type = medio;
                auxiliar->lives = 1;
                break;   
            case DIST_INICIAL_Y + 3*ESP_ALIENS_Y + 3*TAM_ALIENS_Y://Si esta en la cuarta o quina fila es de tipo inferior con una vida
                auxiliar->type = inferior;
                auxiliar->lives = 1;
                break;
            case DIST_INICIAL_Y + 4*ESP_ALIENS_Y + 4*TAM_ALIENS_Y:
                auxiliar->type = inferior;
                auxiliar->lives = 1;
                break;
            default:
                break;
        }

        auxiliar = auxiliar->next;//Siguiente elemento

        if(despX == DIST_INICIAL_X + colAliens*ESP_ALIENS_X + colAliens*TAM_ALIENS_X){//SI ya es el ultimo de la fila
            despX = DIST_INICIAL_X;//Regresa el desplazamiento en X al inicio
            despY += ESP_ALIENS_X + TAM_ALIENS_Y;//E incrementa el desplazamiento en Y a la siguiente fila
        }
        else{//Sino nos movemos a la siguiente columna.
            despX += ESP_ALIENS_X + TAM_ALIENS_X;
        }
    }

    auxiliar->next = NULL;//Al ultimo elemento se le asigna NULL.

    return listAlien;
}

void removeAlienList(int aliensTotales, alien_t* listAlien){
/*Esta funcion se encarga de liberar del heap la lista creada de los aliens*/

    if(aliensTotales > 1){
        removeAlienList(aliensTotales - 1, listAlien->next);
    }
    free(listAlien);
}

/*
void moveAlien (alien_t* alien, int direccion){
/* Este thread se encarga de mover la posicion de los aliens teniendo en cuenta la variable direccion para ello. Ademas, cuando se toca alguno
    de los bordes puede modificar el valor de direccion si se toca uno de los laterales o poner en 0 la variable vidas si se llega al borde
    inferior.
*
    while(1){
        if( !(timerTick % velAliens)){
            int vx, vy;//Variables temporales utilizadas para incrementar o decrementar las componentes x e y del vector coordenadas.

            switch (direccion){//Primero detecta en que sentido debemos mover las naves.
                case IZQUIERDA:
                    vx=-1;
                    vy=0;
                    break;
                case DERECHA:
                    vx=1;
                    vy=0;
                    break;
                case ABAJO:
                    vx=0;
                    vy=-1;
                    break;
            }
            int i = 1;
            while(i){//Mueve los aliens uno por uno

                alien->pos.x += vx;//Modifica su posicion en x e y
                alien->pos.y += vy;

                if( (alien->pos.x == 0) && (direccion == IZQUIERDA)){//Todos los casos posibles de que las naves toquen alguno de los bordes.
                    direccion = ABAJO;
                }
                else if( (alien->pos.x == 0) && (direccion == ABAJO)){
                    direccion = DERECHA;
                }
                else if( (alien->pos.x == xMax) && (direccion == DERECHA)){
                    direccion = ABAJO;
                }
                else if( (alien->pos.x == xMax) && (direccion == ABAJO)){
                    direccion = IZQUIERDA;
                }
                else if(alien->pos.y == yMax){
                    vidas = 0;
                }

                if(alien->next == NULL){//Si el puntero next es NULL quiere decir que es el ultimo elemento de la lista, entonces debe salir del loop.
                    i = 0;
                }
                else{//Sino termino apunta al siguiente elemento.
                    alien = alien->next;
                }
            }
        }
    }
}
*/
