#include "main.h"

//------Aumenta la cantidad de notas
void FuncionBotonSumarNota()
{
    if(cantidad_notas<8)
        cantidad_notas++;
    printf("Sumando Notas %d \n",cantidad_notas);
   // objetos[ID_NOTAS].texturas[0] =
}


//------Reduce la cantidad de notas
void FuncionBotonRestarNota()
{
    if(cantidad_notas>1)
        cantidad_notas--;
    printf("Restando Notas %d \n",cantidad_notas);
   // objetos[ID_NOTAS].texturas[0] =
}


//----Reduce la duracion de un sonido
void FuncionBotonRestarDuracion()
{
    if(duracion_sonido>2000)
        duracion_sonido -= 100;
    printf("Restando Duracion %d \n",duracion_sonido);

}

//---Aumenta la duracion de un sonido
void FuncionBotonSumarDuracion()
{
      if(duracion_sonido<3000)
        duracion_sonido += 100;
    printf("Sumando Duracion %d \n",duracion_sonido);
}





//----Cierra el juego
void FuncionBotonSalir()
{
    corriendo = 0;
}


//----Abre la pantalla Modo de juego
void FuncionBotonModo()
{
    PantallasModos();
}

//----Vuelve al menu principal
void FuncionBotonVolver()
{
   PantallasMenuPrincipal();
}

//---Guarda la melodia
void FuncionBotonGuardar()
{
  MelodiaGuardar(&melodia_jugador,nombre_archivo);
}


//----Abre la pantalla Mozart
void FuncionBotonMozart()
{
    MelodiaInicializar(&melodia_jugador,5,8);
    printf("MODO MOZART \n");
    char* ruta = AbrirExploradorYRecuperarRuta(); //<----Busca la ruta
    MelodiaCargar(&melodia_jugador,ruta);
    free(ruta);//<---Libera la memoria de la ruta
    MelodiaMostrarConsola(&melodia_jugador);
    PantallasMozart();
    modo = MODO_MOZART;
    MelodiaAnimar(&melodia_jugador);
    esta_reproduciendo = 1;
}


//-- Abre la pantalla Schonberg
void FuncionBotonSchonberg()
{
    MelodiaInicializar(&melodia, 3, cantidad_notas); //<--Inicia la melodia
    MelodiaAgregarAleatoria(&melodia,3);
    MelodiaMostrarConsola(&melodia);
    ventana_abierta = 1; //<--Abre ventana auxiliar
    PantallasSchonberg();
    PantallaBloquearBotones();
}


//--Abre la pantalla desafio
void FuncionBotonDesafio()
{
    MelodiaInicializar(&melodia_jugador, 3, 8);
    PantallasDesafio();
    modo = MODO_DESAFIO; //<---Activa el modo desafio
    ventana_abierta = 1; //<---Activa la ventana auxiliar
}


//-Abre la pantalla configs
void FuncionBotonConfigs()
{
    PantallasConfigs();
}



//-----Maneja el sistema de input de las notas
void FuncionNota(int id)
{
    switch(modo)
    {
    case MODO_DESAFIO://<-------Si esta en modo desafio, la nota clickeada se agrega a la melodia
        MelodiaAgregarNota(&melodia_jugador,id);
        break;

    case MODO_MOZART://<-----Si esta en modo mozart, comprueba que la nota clickeada sea = a la melodia del jugador
        resultado = MelodiaComprobarIngreso(&melodia_jugador, id);
        break;

    case MODO_SCHONBERG://<-----Si esta ne modo schonberg comprueba que la nota clickeada sea = a la melodia del sistema (Aleatoria)
        resultado = MelodiaComprobarIngreso(&melodia, id);
        break;
    }
}

