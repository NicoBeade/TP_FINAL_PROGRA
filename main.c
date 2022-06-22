#include <stdio.h>

typededf struct {
    int x;
    int y;
}vector_t;

typedef struct ALIEN{
    vector_t pos;
    int type;
    int lives;
    struct ALIEN * next;
}


int main() {
    printf("hola mundo\n");
    return 0;
}




void move (ALIEN* alien, int direccion){
    int vx, vy;
    switch (direccion){
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

    for (i=0; alien->next!=NULL; i))
}