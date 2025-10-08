#include "main.h"




void FuncionBotonSalir(void *param1,void *param2)
{
    corriendo = 0;
}

void FuncionBotonModo(void *param1,void *param2)
{
    imagen_t *objetos =(imagen_t*)param1;
    boton_t *botones = (boton_t*)param2;
   PantallasModos(objetos,botones);
}


void FuncionBotonVolver(void *param1,void *param2)
{
    imagen_t *objetos =(imagen_t*)param1;
    boton_t *botones = (boton_t*)param2;
   PantallasMenuPrincipal(objetos,botones);
}




void FuncionBotonSchonberg(void *param1,void *param2)
{
    MelodiaInicializar(&melodia, 3, 8);
    MelodiaAgregarAleatoria(&melodia,3);
    MelodiaMostrarConsola(&melodia);
    imagen_t *objetos =(imagen_t*)param1;
    boton_t *botones = (boton_t*)param2;
    PantallasSchonberg(objetos,botones);
    modo = MODO_SCHONBERG;
   // SDL_Delay(1000);
    MelodiaAnimar(&melodia,objetos);
    esta_reproduciendo = 1;
}



void FuncionNota(void *param1,void *param2)
{
     int id = (int)param1;
    if(modo == MODO_MOZART)
    {
        MelodiaAgregarNota(&jugador,id);
    }
    resultado = MelodiaComprobarIngreso(&melodia, id);

}

