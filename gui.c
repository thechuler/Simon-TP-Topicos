#include "gui.h"



//-------Comprueba si un boton fue clickeado y activa su funcion asociada-----//
int BotonesActivosComprobarInteraccion(boton_t *botones, int x, int y)
{
    SDL_Point click = {x, y};

    for(int i = 0; i < CANTIDAD_BOTONES; i++)
    {
        if(botones[i].esta_activo)
        {
            if(SDL_PointInRect(&click,&botones[i].imagen->configs))
            {
                botones[i].imagen->frame_actual =0;
                botones[i].imagen->debe_animar = 1;
                botones[i].accion(botones[i].param1, botones[i].param2);

                return  0;
            }
        }
    }

    return -1;
}




//-------Limpia todos los objetos de la pantalla-----//
void PantallasLimpiar(imagen_t *objeto)
{
    for(int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        objeto[i].debe_Renderizar = 0;
    }
}


//----Bloquea todos los botones de la pantalla----//
void PantallaBloquearBotones(boton_t *botones)
{
    for(int i = 0; i < CANTIDAD_BOTONES; i++)
    {
        botones[i].esta_activo = 0;
    }
}


//------Obtiene un boton por su id asignada-----//
int BotonesObtenerPorId(boton_t *botones,int id)
{
    for(int i=0; i<CANTIDAD_BOTONES; i++)
    {
        if(botones[i].imagen->id == id)
        {
            return i;
        }
    }
    return -1;
}




//------------Setea el menu principal-----------------//
void PantallasMenuPrincipal(imagen_t *objeto,boton_t *botones){
PantallaBloquearBotones(botones);
PantallasLimpiar(objeto);

objeto[ID_BOTON_SALIR].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_SALIR)].esta_activo = 1;

objeto[ID_BOTON_CONFIG].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_CONFIG)].esta_activo = 1;

objeto[ID_BOTON_MODO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_MODO)].esta_activo = 1;

}




//------------Setea la pantalla modos-----------------//
void PantallasModos(imagen_t *objeto,boton_t *botones){
PantallaBloquearBotones(botones);
PantallasLimpiar(objeto);

objeto[ID_FONDO].debe_Renderizar = 1;

objeto[ID_BOTON_MOZART].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_MOZART)].esta_activo = 1;


objeto[ID_BOTON_DESAFIO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_DESAFIO)].esta_activo = 1;

objeto[ID_BOTON_SCHONBERG].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_SCHONBERG)].esta_activo = 1;


objeto[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_VOLVER)].esta_activo = 1;
}




//------------Setea la pantalla schonberg-----------------//
void PantallasSchonberg(imagen_t *objeto,boton_t *botones){
PantallaBloquearBotones(botones);
PantallasLimpiar(objeto);

objeto[ID_AZUL].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_AZUL)].esta_activo = 1;

objeto[ID_ROJO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_ROJO)].esta_activo = 1;

objeto[ID_VERDE].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_VERDE)].esta_activo = 1;

objeto[ID_AMARILLO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_AMARILLO)].esta_activo = 1;

objeto[ID_VIOLETA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_VIOLETA)].esta_activo = 1;

objeto[ID_NARANJA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_NARANJA)].esta_activo = 1;

objeto[ID_NEGRO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_NEGRO)].esta_activo = 1;

objeto[ID_BLANCO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BLANCO)].esta_activo = 1;


objeto[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(botones,ID_BOTON_VOLVER)].esta_activo = 1;
}


