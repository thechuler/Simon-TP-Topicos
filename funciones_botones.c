#include "main.h"




void FuncionBotonSalir()
{
    corriendo = 0;
}

void FuncionBotonModo()
{
   PantallasModos(objetos,botones);
}


void FuncionBotonVolver()
{
   PantallasMenuPrincipal(objetos,botones);
}


void FuncionBotonGuardar()
{
  MelodiaGuardar(&melodia_jugador,nombre_archivo);
}



void FuncionBotonMozart()
{
    MelodiaInicializar(&melodia_jugador,5,8);
    printf("MODO MOZART \n");
    char* ruta = AbrirExploradorYRecuperarRuta();
    MelodiaCargar(&melodia_jugador,ruta);
    free(ruta);
    MelodiaMostrarConsola(&melodia_jugador);
    PantallasMozart();
    modo = MODO_MOZART;
    MelodiaAnimar(&melodia_jugador);
    esta_reproduciendo = 1;
}



void FuncionBotonSchonberg()
{
    MelodiaInicializar(&melodia, 3, 8);
    MelodiaAgregarAleatoria(&melodia,3);
    MelodiaMostrarConsola(&melodia);
    ventana_abierta = 1;
    PantallasSchonberg();
    PantallaBloquearBotones();
}

void FuncionBotonDesafio()
{
    MelodiaInicializar(&melodia_jugador, 3, 8);
    PantallasDesafio(objetos,botones);
    modo = MODO_DESAFIO;
    ventana_abierta = 1;
}


void FuncionNota(int id)
{
    switch(modo)
    {
    case MODO_DESAFIO:
        MelodiaAgregarNota(&melodia_jugador,id);
        break;

    case MODO_MOZART:
        resultado = MelodiaComprobarIngreso(&melodia_jugador, id);
        break;

    case MODO_SCHONBERG:
        resultado = MelodiaComprobarIngreso(&melodia, id);
        break;
    }
}

