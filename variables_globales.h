#ifndef VARIABLES_GLOBALES_H_INCLUDED
#define VARIABLES_GLOBALES_H_INCLUDED

#include "notas.h"
#include "video.h"
#include "gui.h"
#include "jugadores.h"

extern imagen_t objetos[CANTIDAD_OBJETOS];
extern  boton_t botones[CANTIDAD_BOTONES];
extern int corriendo;
extern int modo;
extern int resultado;
extern int ventana_abierta;
extern int puntuacion;
extern jugador_t jugadores_top[5];
extern jugador_t jugador_actual;
extern char animando_fin_ronda;
extern int esta_reproduciendo;
extern melodia_t melodia;
extern melodia_t melodia_jugador;
extern int pausa;
extern char nombre_archivo[200];


#endif // VARIABLES_GLOBALES_H_INCLUDED
