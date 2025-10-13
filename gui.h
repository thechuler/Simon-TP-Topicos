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
    imagen_t *imagen; //<-------Imagen del boton
    AccionBoton accion;  //<-------Que va a hacer el boton
    char esta_activo;  //<-- si el boton esta o no activo.
    int id;      //<----Id del boton
} boton_t;



void BotonesActivosAgregar(boton_t *, imagen_t *,AccionBoton accion);
void BotonesActivosComprobarInteraccion( int, int);
int BotonesObtenerPorId(int );

void PantallasLimpiar();
void PantallasMenuPrincipal();
void PantallasModos();
void PantallasSchonberg();
void PantallasDesafio();
void PantallasConfigs();
void PantallaBloquearBotones();
void PantallasMozart();




void FuncionNota(int);
void FuncionBotonModo();
void FuncionBotonVolver();
void FuncionBotonSalir();
void FuncionBotonGuardar();
void FuncionBotonConfigs();
void FuncionBotonMozart();
void FuncionBotonSchonberg();
void FuncionBotonDesafio();
void FuncionBotonSumarNota();
void FuncionBotonRestarNota();
void FuncionBotonSumarDuracion();
void FuncionBotonRestarDuracion();
char* AbrirExploradorYRecuperarRuta();


#endif // GUI_H_INCLUDED
