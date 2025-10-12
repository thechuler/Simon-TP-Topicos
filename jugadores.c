#include "jugadores.h"
#include "variables_globales.h"





int JugadorInsertarEnTop(jugador_t *jugador) {
    for (int i = 0; i < 5; i++) {
        if (jugador->puntuacion_maxima > jugadores_top[i].puntuacion_maxima) {

            for (int j = 4; j > i; j--) {
                jugadores_top[j] = jugadores_top[j - 1];
            }
            jugadores_top[i] = *jugador;
            return i;
        }
    }
    return -1;
}


void JugadorControlarPuntuacion(jugador_t *jugador,int result){

switch(result){

case RESULTADO_GANO:
jugador->puntuacion_maxima++;
break;


case RESULTADO_PERDIO:
if(JugadorInsertarEnTop(jugador) != -1){
    //NUEVO RECORD
}
break;
}



}



void JugadorGuardarTop(){

FILE *f = fopen("topJugadores.dat","wb");
if(!f){
    return;
}
fwrite(jugadores_top,sizeof(jugador_t),5,f);

fclose(f);
}


void JugadoresCargar() {
    FILE *f = fopen("topJugadores.dat", "rb");
    if (!f) {
        return;
    }
    fread(jugadores_top, sizeof(jugador_t), 5, f);
    fclose(f);
}



