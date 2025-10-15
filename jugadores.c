#include "jugadores.h"
#include "variables_globales.h"




//---Comprueba si un jugador puede ser agregado al top.
int JugadorInsertarEnTop(jugador_t *jugador) {
    for (int i = 0; i < 5; i++) { //<---Recorre los 5

        if (jugador->puntuacion_maxima > jugadores_top[i].puntuacion_maxima) { //<--Si su puntuacion es mayor

            for (int j = 4; j > i; j--) { //<---Recorre desde el final hasta el principio
                jugadores_top[j] = jugadores_top[j - 1]; //<---Envia cada valor 1 hacia atras pisando el ultimo
            }
            jugadores_top[i] = *jugador;//<---Guarda al jugador
            return i;
        }
    }
    return -1;
}


//-----Controla la puntuacion del jugador
void JugadorControlarPuntuacion(jugador_t *jugador,int result){

switch(result){

case RESULTADO_GANO:
jugador->puntuacion_maxima++; //<---Si gano la ronda aumenta
break;


case RESULTADO_PERDIO:
if(JugadorInsertarEnTop(jugador) != -1){
    //NUEVO RECORD  //<--Si perdio nada
}
break;
}



}


//-----Guarda el top de jugadores en un archivo
void JugadorGuardarTop(){

FILE *f = fopen("topJugadores.dat","wb");
if(!f){
    return;
}

fwrite(jugadores_top,sizeof(jugador_t),5,f);

fclose(f);
}


//---Carga el top de jugadores desde un archivo
void JugadoresCargar() {
    FILE *f = fopen("topJugadores.dat", "rb");
    if (!f) {
        return;
    }
    fread(jugadores_top, sizeof(jugador_t), 5, f);
    fclose(f);
}



