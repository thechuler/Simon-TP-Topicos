#include "main.h"

int main(int argc, char *argv[])
{

    srand(time(NULL));          //<--- Semilla
    app_t juego;                // <---- Ventana principal
    app_t ventana_auxiliar;     //<--- Ventana auxiliar
    char ingresoTexto = 0;      //<---Cuando se esta o no ingresando texto
    char botones_activos = 1;   //<--- Cuando los botones se pueden clickear o no
    char texto[256] = "";       // <--- Variable auxiliar para ingreso de texto





    // ------------------------- INICIALIZACION SDL -------------------------- //
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Error al iniciar SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0)
    {
        printf("Error al iniciar TTF: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("[ERROR] No se pudo inicializar el audio: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }
    //-------------------------------------------------------------------------//







    CrearVentana(&juego, "Simon", 700, 500);  //<---------Creacion de ventana





    // ------------------------- FUENTE ------------------------ //
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (!font)
    {
        printf("Error al cargar fuente: %s\n", TTF_GetError());
        return 1;
    }
    //-----------------------------------------------------------//




    SDL_StartTextInput(); //<--- Inicia el input de texto








    // ------------------------- TEXTURAS ------------------------ //
    JugadoresCargar();
    SDL_Texture *topJugadoresTex[1] = { CrearTexturaTopJugadores(juego.renderer, font, jugadores_top, 5)}; //<--- Textura top


    SDL_Texture *rosa[6] =
    {
        CargarTexturaDesdeBinario("img/rosa1.bin", juego.renderer),
        CargarTexturaDesdeBinario("img/rosa2.bin", juego.renderer),
        CargarTexturaDesdeBinario("img/rosa3.bin", juego.renderer),     //<------Textura Notas
        CargarTexturaDesdeBinario("img/rosa4.bin", juego.renderer),
        CargarTexturaDesdeBinario("img/rosa5.bin", juego.renderer),
        CargarTexturaDesdeBinario("img/rosa6.bin", juego.renderer),
    };

    SDL_Texture *boton[2] =
    {
        CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer),    //<--- Textura boton basico
    };

    SDL_Color color = {255, 255, 255, 255};

    SDL_Texture *botonText[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer),
            "JUGAR", "arial.ttf", 10, color
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer),
    };


    SDL_Texture *puntajeText[1] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer), //<--- Textura puntaje
            "0", "arial.ttf", 10, color
        ),
    };



    SDL_Texture *cant_notas[1] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer),    //<--- Textura config
            "NOTAS: 3", "arial.ttf", 10, color
        ),
    };



    SDL_Texture *duracion[1] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer),
            "Duracion: 2000 ms", "arial.ttf", 10, color
        ),
    };


    SDL_Texture *fondo = CargarTexturaDesdeBinario("img/fondo1.bin", juego.renderer);
    SDL_Texture *home = CargarTexturaDesdeBinario("img/home1.bin", juego.renderer);
    //---------------------------------------------------------------------------------//







    // ------------------------- OBJETOS ------------------------ //
    objetos[ID_FONDO] = ImagenCrear(&juego, 1, &fondo, PANTALLA_ALTO, PANTALLA_ANCHO, 0, 0, ANIMACION_NO, ID_FONDO);
    objetos[ID_BOTON_MODO] = ImagenCrear(&juego, 2, botonText, 100, 200, 0, 100, ANIMACION_RESET, ID_BOTON_MODO);
    objetos[ID_BOTON_CONFIG] = ImagenCrear(&juego, 2, boton, 100, 200, 0, 250, ANIMACION_RESET, ID_BOTON_CONFIG);
    objetos[ID_BOTON_VOLVER] = ImagenCrear(&juego, 1, &home, 100, 100, 600, 400, ANIMACION_RESET, ID_BOTON_VOLVER);
    objetos[ID_BOTON_SALIR] = ImagenCrear(&juego, 2, boton, 100, 200, 0, 400, ANIMACION_RESET, ID_BOTON_SALIR);

    objetos[ID_AZUL] = ImagenCrear(&juego, 6, rosa, 160, 120, 125, 180, ANIMACION_RESET, ID_AZUL);
    objetos[ID_VERDE] = ImagenCrear(&juego, 6, rosa, 160, 120, 235, 180, ANIMACION_RESET, ID_VERDE);
    objetos[ID_ROJO] = ImagenCrear(&juego, 6, rosa, 160, 120, 345, 180, ANIMACION_RESET, ID_ROJO);
    objetos[ID_AMARILLO] = ImagenCrear(&juego, 6, rosa, 160, 120, 455, 180, ANIMACION_RESET, ID_AMARILLO);

    objetos[ID_VIOLETA] = ImagenCrear(&juego, 6, rosa, 160, 120, 125, 260, ANIMACION_RESET, ID_VIOLETA);
    objetos[ID_NARANJA] = ImagenCrear(&juego, 6, rosa, 160, 120, 235, 260, ANIMACION_RESET, ID_NARANJA);
    objetos[ID_NEGRO] = ImagenCrear(&juego, 6, rosa, 160, 120, 345, 260, ANIMACION_RESET, ID_NEGRO);
    objetos[ID_BLANCO] = ImagenCrear(&juego, 6, rosa, 160, 120, 455, 260, ANIMACION_RESET, ID_BLANCO);

    objetos[ID_BOTON_SCHONBERG] = ImagenCrear(&juego, 2, boton, 100, 200, 0, 100, ANIMACION_RESET, ID_BOTON_SCHONBERG);
    objetos[ID_BOTON_MOZART] = ImagenCrear(&juego, 2, boton, 100, 200, 0, 250, ANIMACION_RESET, ID_BOTON_MOZART);
    objetos[ID_BOTON_DESAFIO] = ImagenCrear(&juego, 2, boton, 100, 200, 0, 400, ANIMACION_RESET, ID_BOTON_DESAFIO);
    objetos[ID_BOTON_GUARDAR] = ImagenCrear(&juego, 2, boton, 100, 200, 0, 400, ANIMACION_RESET, ID_BOTON_GUARDAR);

    objetos[ID_TOP] = ImagenCrear(&juego, 1, topJugadoresTex, 200, 350, 400, 100, ANIMACION_RESET, ID_TOP);
    objetos[ID_PUNTAJE] = ImagenCrear(&juego, 1, puntajeText, 100, 150, 0, 0, ANIMACION_RESET, ID_PUNTAJE);

    objetos[ID_SUMAR_NOTAS] = ImagenCrear(&juego, 1, boton, 100, 50, 300, 250, ANIMACION_RESET, ID_SUMAR_NOTAS);
    objetos[ID_RESTAR_NOTAS] = ImagenCrear(&juego, 1, boton, 100, 50, 350, 250, ANIMACION_RESET, ID_RESTAR_NOTAS);

    objetos[ID_SUMAR_DURACION] = ImagenCrear(&juego, 1, boton, 100, 50, 300, 100, ANIMACION_RESET, ID_SUMAR_DURACION);
    objetos[ID_RESTAR_DURACION] = ImagenCrear(&juego, 1, boton, 100, 50, 350, 100, ANIMACION_RESET, ID_RESTAR_DURACION);

    objetos[ID_DURACION] = ImagenCrear(&juego, 1, duracion, 100, 200, 0, 100, ANIMACION_RESET, ID_DURACION);
    objetos[ID_NOTAS] = ImagenCrear(&juego, 1, cant_notas, 100, 200, 0, 250, ANIMACION_RESET, ID_NOTAS);

    //---------------------------------------------------------------------------------------------------------------//





    // ------------------------- SONIDOS ------------------------ //
    Mix_Chunk *sonidos[9] =
    {
        cargarSonido("snd/sonido.wav"),
        cargarSonido("snd/do.wav"),
        cargarSonido("snd/re.wav"),
        cargarSonido("snd/mi.wav"),
        cargarSonido("snd/fa.wav"),
        cargarSonido("snd/sol.wav"),
        cargarSonido("snd/la.wav"),
        cargarSonido("snd/si.wav"),
        cargarSonido("snd/doa.wav")
    };
    //------------------------------------------------------------//








    PantallasMenuPrincipal(); //<---Pone el juego en la pantalla principal
    SDL_Event e;               //<--- Eventos








    // ------------------------- BUCLE PRINCIPAL ------------------------ //
    while (corriendo)
    {


        while (SDL_PollEvent(&e))
        {



            if (e.type == SDL_QUIT)  //<---Cerrar el juego
                corriendo = 0;


            //--------------Si detecta un click-------------------------//
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int x = e.button.x;
                int y = e.button.y;
                BotonesActivosComprobarInteraccion(x, y);
            }

            //---------------------------------------------------------//



            //----------------------Si detecta entrada de texto---------------------------------//
            if (e.type == SDL_TEXTINPUT)
                strcat(texto, e.text.text);


            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(texto) > 0) //<----Borrar letras
                {
                    texto[strlen(texto) - 1] = '\0';
                }

                else if (e.key.keysym.sym == SDLK_RETURN) //<-----Ingresar Texto
                {


                    if(modo == MODO_SCHONBERG)       //<-------- En el modo SCHONBERG el texto es el nombre del jugador
                    {
                        strcpy(jugador_actual.nombre,texto);
                        printf("NUEVO JUGADOR: %s\n", texto);
                        modo = MODO_SCHONBERG;
                        MelodiaAnimar(&melodia);
                        esta_reproduciendo = 1;
                        PantallasSchonberg();
                    }



                    if(modo == MODO_DESAFIO)   //<-------- En el modo DESAFIO el texto es el nombre del archivo
                    {
                        printf("NUEVO ARCHIVO: %s\n", texto);
                        strcpy(nombre_archivo,texto);
                    }


                    ingresoTexto = 0; //<------Ya no se ingresa texto

                    if (ventana_auxiliar.ventana != NULL) //<-----Cierre de la ventana
                    {
                        SDL_DestroyRenderer(ventana_auxiliar.renderer);
                        SDL_DestroyWindow(ventana_auxiliar.ventana);
                        ventana_auxiliar.ventana = NULL;
                    }

                    texto[0] = '\0';  //<-------Reset del texto
                }
            }
            //--------------------------------------------------------------------//

        }







        // ---------------------------- LOGICA DE FIN DE RONDA --------------------------------------//
        switch (resultado)
        {


        case RESULTADO_GANO: //<--------Si gana la ronda
            if (modo == MODO_SCHONBERG)
            {

                char texto_puntaje[20];       //<--------Actualiza el render de puntuacion
                sprintf(texto_puntaje, "%d", puntuacion + 1);
                objetos[ID_PUNTAJE].texturas[0] =  CombinarTexturaConTexto(juego.renderer,CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer),texto_puntaje, "arial.ttf", 10, color);
                resultado = MelodiaFinalDeRonda(&melodia, RESULTADO_GANO); //<----Comprueba Siguiente estado
            }

            if (modo == MODO_MOZART)
                resultado = MelodiaFinalDeRonda(&melodia_jugador, RESULTADO_GANO);//<----Comprueba siguiente estado
            //Aca se podria haber una pantalla de victoria
            break;



        case RESULTADO_PERDIO://<-------Si pierde la ronda

            if (modo == MODO_SCHONBERG)
            {
                resultado = MelodiaFinalDeRonda(&melodia, RESULTADO_PERDIO);//<-------Comprueba siguiente estado
                objetos[ID_TOP].texturas[0] = CrearTexturaTopJugadores(juego.renderer, font, jugadores_top, 5); //<---Actualiza top
            }

            if (modo == MODO_MOZART)
                resultado = MelodiaFinalDeRonda(&melodia_jugador, RESULTADO_PERDIO);//<---Comprueba siguiente estado
            break;

        default:
            break;
        }
        //--------------------------------------------------------------------------------------------//










        // ----------------- ANIMACIONES Y BOTONES FIN DE RONDA -----------------------
        if (esta_reproduciendo)
        {

            if (botones_activos) //<---Si los botones estan activos los bloquea durante la secuencia
            {
                botones_activos = 0;
                PantallaBloquearBotones();
            }


            if (modo == MODO_MOZART)
                MelodiaAnimar(&melodia_jugador);
            if (modo == MODO_SCHONBERG)
                MelodiaAnimar(&melodia);
        }
        else
        {
            if (!botones_activos) //<---Si la secuencia ya termino y los botones no estan activos, los activa y recarga la pantalla
            {
                botones_activos = 1;
                if (modo == MODO_MOZART)
                    PantallasMozart();
                if (modo == MODO_SCHONBERG)
                    PantallasSchonberg();
            }
        }
        //------------------------------------------------------------------------//







        // ------------------------------------ SONIDOS --------------------------------------------//
        for (int i = ID_AZUL; i <= ID_BLANCO; i++) //<---Sonidos para cada nota
        {
            if (objetos[i].frame_actual == 3 && !animando_fin_ronda)  //<---Si no esta animando el fin de la ronda y tiene la boca abierta
            {
                Mix_PlayChannel(0, sonidos[i], 0); //<--- Reproduce su sonido


                if(cantidad_notas >1)  //<--- Si hay mas de 1 nota se aplica una reduccion en el tiempo total
                {
                    SDL_Delay(duracion_sonido - ((duracion_sonido*0.03))* melodia.cant_notas ); //<-- -3% por nota
                }
                else
                {
                    SDL_Delay(duracion_sonido); //<--- Si hay solo 1, simplemente no se aplica
                }

            }

        }


        //-------------------------------------------------------------------------------------------//




        // ------------------------ CREAR VENTANA AUXILIAR ------------------------------------//
        if (ventana_abierta && modo == MODO_SCHONBERG)
        {
            CrearVentana(&ventana_auxiliar, "Cual es tu nombre?", 200, 200);
            ingresoTexto = 1;
            ventana_abierta = 0;
        }


        if (ventana_abierta && modo == MODO_DESAFIO)
        {
            CrearVentana(&ventana_auxiliar, "Ingresa el nombre del archivo", 200, 200);
            ingresoTexto = 1;
            ventana_abierta = 0;
        }


        //---Renderiza el texto que se esta ingresando
        if (ingresoTexto && ventana_auxiliar.ventana != NULL) //<----Si la ventana esta abierta
        {
            SDL_SetRenderDrawColor(ventana_auxiliar.renderer, 0, 0, 0, 255);
            SDL_RenderClear(ventana_auxiliar.renderer);

            SDL_Surface *superficieTexto = TTF_RenderText_Blended(font, texto, color);
            if (superficieTexto)
            {
                SDL_Texture *textoTex = SDL_CreateTextureFromSurface(ventana_auxiliar.renderer, superficieTexto);
                int tw, th;
                SDL_QueryTexture(textoTex, NULL, NULL, &tw, &th);
                SDL_Rect destino = {50, 100, tw, th};
                SDL_RenderCopy(ventana_auxiliar.renderer, textoTex, NULL, &destino);
                SDL_DestroyTexture(textoTex);
                SDL_FreeSurface(superficieTexto);
            }

            SDL_RenderPresent(ventana_auxiliar.renderer);
        }

        //----------------------------------------------------------------------------------------//







        // ------------ RENDER PRINCIPAL ----------//
        ManejarAnimaciones(objetos);
        ActualizarRender(&juego, objetos);
        SDL_Delay(100); //<--- Pequeño delay entre frame y frame para las animaciones
    }
    //---------------------------------------------//



    // ------------------------- LIMPIEZA ------------------------ //
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    //-------------------------------------------------------------//
    return 0;
}
