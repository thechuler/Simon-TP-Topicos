#include "main.h"


//------Aumenta la cantidad de notas
void FuncionBotonSumarNota()
{
    Mix_PlayChannel(0, sonidos[1], 0); //<---Sonido de boton
    if(cantidad_notas<8) //<----Solo puede sumar si hay menos de 8 notas
    {
        char texto[10];
        cantidad_notas++;
        snprintf(texto, sizeof(texto), "Notas: %d",cantidad_notas);
        objetos[ID_NOTAS].texturas[0]= CombinarTexturaConTexto(   //<------------------Actualiza el render del boton
                                           juego.renderer,
                                           CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
                                           texto, "fnt/Symtext.ttf", 7, (SDL_Color){255, 0, 125, 255});
        printf("Sumando Notas %d \n",cantidad_notas);

        for(int i=0; i<8; i++)
        {
            if(notas_activas[i] == 0)
            {
                notas_activas[i]=1; //<---Avisa que notas estan activas actualmente
                break;
            }
        }


    }
}





void FuncionSlime()  //<---Funcion "Gordo Tony"
{
    if(easter_egg<15  ) //<--- Si easter egg es menor que 25 suma
    {
        easter_egg++;
    }
    else
    {
        easter_egg=0;  //<--- Si se pasa lo reinicia
    }
}




//Activa el modo Party !!!
void FuncionBotonParty()
{

    party = !party; //<---cambia el valor del modo party

    if(party)
    {
        Mix_PlayChannel(0, sonidos[1], 0); //<---Sonido feliz :D
        objetos[ID_PARTY].texturas[0] = CombinarTexturaConTexto(
                                            juego.renderer,
                                            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
                                            "Party: SI!", "fnt/Symtext.ttf", 7, (SDL_Color){255, 0, 125, 255});

        notas1[0] = cargarSonido("snd/do.wav");
        notas1[1] = cargarSonido("snd/re.wav");
        notas1[2] = cargarSonido("snd/mi.wav");
        notas1[3] = cargarSonido("snd/fa.wav");
        notas1[4] = cargarSonido("snd/sol.wav");
        notas1[5] = cargarSonido("snd/la.wav");
        notas1[6] = cargarSonido("snd/si.wav");       //<-----------------Sonido Criaturas (definitivamente mas divertido)
        notas1[7] = cargarSonido("snd/doa.wav");
        notas1[8] = cargarSonido("snd/fa#.wav");
        notas1[9] = cargarSonido("snd/la#.wav");
        notas1[10] = cargarSonido("snd/mib.wav");
        notas1[11] = cargarSonido("snd/lab.wav");
    }
    else
    {
        Mix_PlayChannel(0, sonidos[2], 0); //<---Sonido triste :(
        objetos[ID_PARTY].texturas[0] = CombinarTexturaConTexto(
                                            juego.renderer,
                                            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
                                            "Party: no :(", "fnt/Symtext.ttf", 7, (SDL_Color)
        {255, 0, 125, 255});

        notas1[0] = cargarSonido("snd/do1.wav");
        notas1[1] = cargarSonido("snd/re1.wav");
        notas1[2] = cargarSonido("snd/mi1.wav");
        notas1[3] = cargarSonido("snd/fa1.wav");
        notas1[4] = cargarSonido("snd/sol1.wav");       //<-------Sonido Notas (Aburrido pero promocionable)
        notas1[5] = cargarSonido("snd/la1.wav");
        notas1[6] = cargarSonido("snd/si1.wav");
        notas1[7] = cargarSonido("snd/doa1.wav");
        notas1[8] = cargarSonido("snd/fa#1.wav");
        notas1[9] = cargarSonido("snd/la#1.wav");
        notas1[10] = cargarSonido("snd/mib1.wav");
        notas1[11] = cargarSonido("snd/lab1.wav");
    }



}




//------Reduce la cantidad de notas--
void FuncionBotonRestarNota()
{
    Mix_PlayChannel(0, sonidos[2], 0); //<----Sonido boton
    if(cantidad_notas>1) //<---Solo si hay mas de 1 nota
    {
        char texto[10];
        cantidad_notas--;
        snprintf(texto, sizeof(texto), "Notas: %d",cantidad_notas);

        objetos[ID_NOTAS].texturas[0] = CombinarTexturaConTexto(
                                            juego.renderer,
                                            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
                                            texto, "fnt/Symtext.ttf", 7, (SDL_Color){255, 0, 125, 255});

        printf("Restando Notas %d \n",cantidad_notas);

        for(int i=8; i>0; i--)
        {
            if(notas_activas[i] ==1)
            {
                notas_activas[i]=0;// <---Avisa que notas estan activas
                break;
            }
        }

    }
}


//----Reduce la duracion de un sonido
void FuncionBotonRestarDuracion()
{
    Mix_PlayChannel(0, sonidos[2], 0); //<---Sonido boton
    if(duracion_sonido>2000){ //<---Mientras que la duracion sea al menos 2000
               char texto[12];
           duracion_sonido -= 100;
            snprintf(texto, sizeof(texto), "Dur: %dms",duracion_sonido);
            objetos[ID_DURACION].texturas[0] = CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            texto, "fnt/Symtext.ttf", 7, (SDL_Color){255, 0, 125, 255});
       printf("Restando Duracion %d \n",duracion_sonido);
    }
}




//---Aumenta la duracion de un sonido
void FuncionBotonSumarDuracion()
{
    Mix_PlayChannel(0, sonidos[1], 0); //<---Sonido Boton
    if(duracion_sonido<3000)   //<----Mientras duracion sea menor a 3000
    {
        char texto[12];
        duracion_sonido += 100;
        snprintf(texto, sizeof(texto), "Dur: %dms",duracion_sonido);
        objetos[ID_DURACION].texturas[0] = CombinarTexturaConTexto(
                                               juego.renderer,
                                               CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
                                               texto, "fnt/Symtext.ttf", 7, (SDL_Color){255, 0, 125, 255});
        printf("Sumando Duracion %d \n",duracion_sonido);
    }


}





//----Cierra el juego
void FuncionBotonSalir()
{
    corriendo = 0;
}






//----Abre la pantalla Modo de juego
void FuncionBotonModo()
{
    Mix_PlayChannel(0, sonidos[1], 0); //<---Sonido Boton
    SDL_Delay(200);
    PantallasModos();
}



//----Vuelve al menu principal
void FuncionBotonVolver()
{
    Mix_PlayChannel(0, sonidos[1], 0); //<---Sonido Boton
    if(modo==MODO_SCHONBERG){ //<---Si el modo es schonberg chequea la puntuacion maxima
           jugador_actual.puntuacion_maxima = puntuacion;
           JugadorInsertarEnTop(&jugador_actual);
           JugadorGuardarTop();
           objetos[ID_TOP].texturas[0] = CrearTexturaTopJugadores(juego.renderer, TTF_OpenFont("fnt/Symtext.ttf",34), jugadores_top, 5); //<---Actualiza top       //<--------Actualiza el render de puntuacion


    }

   modo = MODO_MENUS;
   PantallasMenuPrincipal();
}



//---Guarda la melodia
void FuncionBotonGuardar()
{
  Mix_PlayChannel(0, sonidos[1], 0);  //<---Sonido Boton
  MelodiaGuardar(&melodia_jugador,nombre_archivo);
}


//----Abre la pantalla Mozart
void FuncionBotonMozart()
{
    MelodiaInicializar(&melodia_jugador,5,8);
    printf("MODO MOZART \n");
    Mix_PlayChannel(0, sonidos[2], 0);  //<---Sonido Boton
    char* ruta = AbrirExploradorYRecuperarRuta(); //<----Busca la ruta
  if (ruta == NULL || ruta[0] == '\0')
        return;
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
    modo = MODO_SCHONBERG;
    PantallaBloquearBotones();
}


//--Abre la pantalla desafio
void FuncionBotonDesafio()
{
    MelodiaInicializar(&melodia_jugador, 3, 8);
    modo = MODO_DESAFIO; //<---Activa el modo desafio
    ventana_abierta = 1; //<---Activa la ventana auxiliar
}


//-Abre la pantalla configs
void FuncionBotonConfigs()
{
    Mix_PlayChannel(0, sonidos[1], 0);
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
        objetos[id].debe_Renderizar = 1;
        resultado = MelodiaComprobarIngreso(&melodia, id);
        break;
    }
}

