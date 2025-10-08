#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "macros.h"

#define PANTALLA_ANCHO   700      //1366
#define PANTALLA_ALTO    500    //768
#define TITULO "SIMON"

#define ANIMACION_BUCLE 0
#define ANIMACION_ULTIMO_FRAME 2
#define ANIMACION_RESET 1
#define ANIMACION_NO 3





typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *ventana;
} app_t;






typedef struct {
   SDL_Surface *surface;     //<-- Superficie de la imagen
   SDL_Texture *textura;     //<--- Textura de la imagen
   SDL_Rect configs;         //<-- Pos y tam de un rectangulo que representa la imagen
   char debe_Renderizar;     //<-- Si deberia o no renderizar
   char debe_animar;         //<-- Si deberia o no animar
   char **fotogramas;        //<--vector de string que representa los nombres de los archivos que forman cada frame
   int frame_actual;         //<--- En que frame se encuentra la animacion
   int frames_totales;       //<-- Cuantos frames hay
   int modo_reproduccion;    //<--- El modo en el que se van a animar
   int id;                   //<-- Id del objeto
} imagen_t;



void IniciarGraficos(app_t*);
void ManejarAnimaciones(imagen_t  *);
void ActualizarRender(app_t *, imagen_t *);
void ImagenCargar(imagen_t*,app_t*);

imagen_t ImagenCrear(int,const char *, int , int , int , int , int,int);



#endif
