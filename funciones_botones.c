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
  MelodiaGuardar(&jugador);
}



void FuncionBotonMozart()
{
    MelodiaInicializar(&jugador,5,8);
    printf("MODO MOZART \n");
    char* ruta = AbrirExploradorYRecuperarRuta();
    MelodiaCargar(&jugador,ruta);
    free(ruta);
    printf("aaa");
    MelodiaMostrarConsola(&jugador);
    PantallasMozart(objetos,botones);
    modo = MODO_MOZART;
    MelodiaAnimar(&jugador,objetos);
    esta_reproduciendo = 1;
}



void FuncionBotonSchonberg()
{
    MelodiaInicializar(&melodia, 3, 8);
    MelodiaAgregarAleatoria(&melodia,3);
    MelodiaMostrarConsola(&melodia);
    PantallasSchonberg(objetos,botones);
    modo = MODO_SCHONBERG;
    MelodiaAnimar(&melodia,objetos);
    esta_reproduciendo = 1;
}

void FuncionBotonDesafio()
{
    MelodiaInicializar(&jugador, 3, 8);
    PantallasDesafio(objetos,botones);
    modo = MODO_DESAFIO;
}


void FuncionNota(int id)
{
    switch(modo)
    {
    case MODO_DESAFIO:
        MelodiaAgregarNota(&jugador,id);
        break;

    case MODO_MOZART:
        resultado = MelodiaComprobarIngreso(&jugador, id);
        break;

    case MODO_SCHONBERG:
        resultado = MelodiaComprobarIngreso(&melodia, id);
        break;
    }
}

