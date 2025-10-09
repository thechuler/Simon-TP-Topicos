#ifndef NOTAS_H
#define NOTAS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "video.h"


#define RESULTADO_GANO 1
#define RESULTADO_PERDIO 2
#define RESULTADO_ACERTO 3
#define RESULTADO_EN_ESPERA 4






typedef struct{
int *p;    //<---------Puntero del vector que guardara las notas.
int nota_actual;      //<-----La nota a chequear actualmente
int animacion_actual; // <---- La nota que se animara al mostrar la secuencia
int ultima_nota;
int cant_notas;       //<--  cantidad actual de notas
int cant_total_notas;  //<-------- Capacidad total de notas en el vect dinamico
unsigned nivel; // <--------- Nivel de la melodia (este unsigned despues lo usamos para generar numeros aleatorios desde 0 a nivel)
}melodia_t;



void MelodiaAgregarNota(melodia_t *,int);
void MelodiaAgregarAleatoria(melodia_t *,int);
int MelodiaComprobarIngreso(melodia_t *,int);
void MelodiaInicializar(melodia_t *, int ,unsigned );
void MelodiaMostrarConsola(melodia_t *);
void MelodiaGuardar(melodia_t *);
void MelodiaCargar(melodia_t *,const char* );
void MelodiaAnimar(melodia_t *,imagen_t *);
void MelodiaGano(melodia_t *);
void MelodiaGanoAnimacion(imagen_t *);
void MelodiaReiniciar(melodia_t *,int);



#endif
