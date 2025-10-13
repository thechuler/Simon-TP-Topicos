#ifndef VARIABLES_GLOBALES_H_INCLUDED
#define VARIABLES_GLOBALES_H_INCLUDED

#include "notas.h"
#include "video.h"
#include "gui.h"
#include "jugadores.h"

extern imagen_t objetos[CANTIDAD_OBJETOS];
extern  boton_t botones[CANTIDAD_BOTONES];
extern char corriendo;
extern int modo;
extern int resultado;
extern char ventana_abierta;
extern int puntuacion;
extern jugador_t jugadores_top[5];
extern jugador_t jugador_actual;
extern char animando_fin_ronda;
extern char esta_reproduciendo;
extern int cantidad_notas;
extern melodia_t melodia;
extern melodia_t melodia_jugador;
extern char nombre_archivo[200];
extern int duracion_sonido;


#endif // VARIABLES_GLOBALES_H_INCLUDED
