#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "video.h"






typedef void (*AccionBoton)();


typedef struct {
    imagen_t *imagen; //<-------Direccion de memoria de la imagen que tendra el boton
    AccionBoton accion;  //<-------Que va a hacer el boton
    char esta_activo;  //<-- si el boton esta o no activo.
    int id;
} boton_t;



void BotonesActivosAgregar(boton_t *, imagen_t *,AccionBoton accion);
int BotonesActivosComprobarInteraccion( int, int);
int BotonesObtenerPorId(int );



void PantallasLimpiar();
void PantallasMenuPrincipal();
void PantallasModos();
void PantallasSchonberg();
void PantallasDesafio();
void PantallaBloquearBotones();
void PantallasMozart();




void FuncionNota(int);
void FuncionBotonModo();

void FuncionBotonVolver();
void FuncionBotonSalir();
void FuncionBotonGuardar();

void FuncionBotonMozart();
void FuncionBotonSchonberg();
void FuncionBotonDesafio();

char* AbrirExploradorYRecuperarRuta(void);


#endif // GUI_H_INCLUDED
