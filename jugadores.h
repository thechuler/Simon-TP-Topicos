#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED



typedef struct{
char nombre[50]; //<---Nombre del jugador
int puntuacion_maxima; //<----Puntuacion del jugador
}jugador_t;


void JugadorControlarPuntuacion(jugador_t *,int);
int JugadorInsertarEnTop(jugador_t *);
void JugadorGuardarTop();
void JugadoresCargar();

#endif // JUGADORES_H_INCLUDED
