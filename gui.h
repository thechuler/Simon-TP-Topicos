#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "video.h"
#include "variables_globales.h"





extern int corriendo;
extern int modo;
extern int resultado;
extern melodia_t melodia;
extern melodia_t jugador;

typedef void (*AccionBoton)(void *param1,void *param2);


typedef struct {
    imagen_t *imagen; //<-------Direccion de memoria de la imagen que tendra el boton
    AccionBoton accion;  //<-------Que va a hacer el boton
    void *param1;      //<--Parametro 1
    void *param2;      //<--Parametro 2
    char esta_activo;  //<-- si el boton esta o no activo.
} boton_t;



void BotonesActivosAgregar(boton_t *, imagen_t *,AccionBoton accion);
int BotonesActivosComprobarInteraccion(boton_t *, int, int);
int BotonesObtenerPorId(boton_t *,int );



void PantallasLimpiar(imagen_t*);
void PantallasMenuPrincipal(imagen_t*,boton_t *);
void PantallasModos(imagen_t *,boton_t *);
void PantallasSchonberg(imagen_t *,boton_t *);
void PantallaBloquearBotones(boton_t *botones);



void FuncionBotonSalir(void *param1, void *param2);
void FuncionNota(void *param1, void *param2);
void FuncionBotonModo(void *param1, void *param2);
void FuncionBotonSchonberg(void *param1,void *param2);
void FuncionBotonVolver(void *param1,void *param2);



#endif // GUI_H_INCLUDED
