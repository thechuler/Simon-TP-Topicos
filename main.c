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



    CrearVentana(&juego, "Simi-Simi-MON!", 700, 500);  //<---------Creacion de ventana





    // ------------------------- FUENTE ------------------------ //
    TTF_Font *font = TTF_OpenFont("Symtext.ttf",34);
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






    //-------------------------COLORES--------------------------//

    SDL_Color colores_notas[9] =
    {
        {255, 0, 125, 255}, // Rosa
        {60, 100, 200, 255},   // Azul
        {90, 170, 110, 255},   // verde
        {140, 25, 25, 255},   // Rojo
        {255, 255, 40, 255}, // amarillo
        {185, 40, 255, 255}, // violeta
        {255, 157, 40, 255}, // naranja
        {78, 78, 78, 255}, // negro
    };




//-----------------------------------------------------------//




//--------------------------------CREACION DE TEXTURAS-------------------------------//


    SDL_Texture *texturas_azul[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_AZUL],texturas_azul,juego.renderer);

    SDL_Texture *texturas_verde[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_VERDE],texturas_verde,juego.renderer);

    SDL_Texture *texturas_rojo[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_ROJO],texturas_rojo,juego.renderer);

    SDL_Texture *texturas_amarillo[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_AMARILLO],texturas_amarillo,juego.renderer);

    SDL_Texture *texturas_violeta[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_VIOLETA],texturas_violeta,juego.renderer);

    SDL_Texture *texturas_naranja[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_NARANJA],texturas_naranja,juego.renderer);

    SDL_Texture *texturas_negro[6];
    CargarAnimaciondesdeBinario("slime",&colores_notas[ID_NEGRO],texturas_negro,juego.renderer);

    SDL_Texture *texturas_blanco[6];
    CargarAnimaciondesdeBinario("slime",NULL,texturas_blanco,juego.renderer);


    SDL_Texture *botonJugar[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Jugar", "Symtext.ttf", 14, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };


    SDL_Texture *botonConfigs[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Configs", "Symtext.ttf", 11, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };

    SDL_Texture *botonSalir[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Salir", "Symtext.ttf", 14, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };


    SDL_Texture *botonSchonberg[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Schonberg", "Symtext.ttf", 8, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };


    SDL_Texture *botonMozart[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Mozart", "Symtext.ttf", 10, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };

    SDL_Texture *botonDesafio[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Desafio", "Symtext.ttf", 10, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };

    SDL_Texture *botonGuardar[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "Guardar", "Symtext.ttf", 10, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };


    SDL_Texture *botonSumar[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "+", "Symtext.ttf", 25, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };


    SDL_Texture *botonRestar[2] =
    {
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            "-", "Symtext.ttf", 25, colores_notas[0]
        ),
        CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer,NULL),
    };

    SDL_Texture *puntajeText =
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL), //<--- Textura puntaje
            "0", "Symtext.ttf", 10, colores_notas[0]);


    SDL_Texture *cant_notas =
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),    //<--- Textura config
            "NOTAS: 3", "Symtext.ttf", 7, colores_notas[0]);


    SDL_Texture *botonDuracion =
        CombinarTexturaConTexto(
            juego.renderer,
            CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),
            " ", "Symtext.ttf", 6, colores_notas[0]);



    SDL_Texture *fondo = CargarTexturaDesdeBinario("img/fondo1.bin", juego.renderer,NULL);
    SDL_Texture *home = CargarTexturaDesdeBinario("img/home1.bin", juego.renderer,NULL);



  //---------------------------------------------------------------------------------//







    // ------------------------- OBJETOS ------------------------ //
    objetos[ID_FONDO] = ImagenCrear(&juego, 1, &fondo, PANTALLA_ALTO, PANTALLA_ANCHO, 0, 0, ANIMACION_NO, ID_FONDO);
    objetos[ID_BOTON_MODO] = ImagenCrear(&juego, 2, botonJugar, 100, 200, 50, 150, ANIMACION_RESET, ID_BOTON_MODO);
    objetos[ID_BOTON_CONFIG] = ImagenCrear(&juego, 2, botonConfigs, 100, 200, 50, 250, ANIMACION_RESET, ID_BOTON_CONFIG);
    objetos[ID_BOTON_VOLVER] = ImagenCrear(&juego, 1, &home, 100, 100, 550, 360, ANIMACION_RESET, ID_BOTON_VOLVER);
    objetos[ID_BOTON_SALIR] = ImagenCrear(&juego, 2, botonSalir, 100, 200, 50, 350, ANIMACION_RESET, ID_BOTON_SALIR);

    objetos[ID_AZUL] = ImagenCrear(&juego, 6, texturas_azul, 160, 120, 125, 100, ANIMACION_RESET, ID_AZUL);
    objetos[ID_VERDE] = ImagenCrear(&juego, 6, texturas_verde, 160, 120, 235, 100, ANIMACION_RESET, ID_VERDE);
    objetos[ID_ROJO] = ImagenCrear(&juego, 6, texturas_rojo, 160, 120, 345, 100, ANIMACION_RESET, ID_ROJO);
    objetos[ID_AMARILLO] = ImagenCrear(&juego, 6, texturas_amarillo, 160, 120, 455, 100, ANIMACION_RESET, ID_AMARILLO);

    objetos[ID_VIOLETA] = ImagenCrear(&juego, 6, texturas_violeta, 160, 120, 125, 180, ANIMACION_RESET, ID_VIOLETA);
    objetos[ID_NARANJA] = ImagenCrear(&juego, 6, texturas_naranja, 160, 120, 235, 180, ANIMACION_RESET, ID_NARANJA);
    objetos[ID_NEGRO] = ImagenCrear(&juego, 6, texturas_negro, 160, 120, 345, 180, ANIMACION_RESET, ID_NEGRO);
    objetos[ID_BLANCO] = ImagenCrear(&juego, 6, texturas_blanco, 160, 120, 455, 180, ANIMACION_RESET, ID_BLANCO);

    objetos[ID_BOTON_SCHONBERG] = ImagenCrear(&juego, 2, botonSchonberg, 100, 200, 50, 150, ANIMACION_RESET, ID_BOTON_SCHONBERG);
    objetos[ID_BOTON_MOZART] = ImagenCrear(&juego, 2, botonMozart, 100, 200, 50, 250, ANIMACION_RESET, ID_BOTON_MOZART);
    objetos[ID_BOTON_DESAFIO] = ImagenCrear(&juego, 2, botonDesafio, 100, 200, 50, 350, ANIMACION_RESET, ID_BOTON_DESAFIO);
    objetos[ID_BOTON_GUARDAR] = ImagenCrear(&juego, 2, botonGuardar, 100, 200, 500, 0, ANIMACION_RESET, ID_BOTON_GUARDAR);

    objetos[ID_TOP] = ImagenCrear(&juego, 1, topJugadoresTex, 250, 200, 480, 150, ANIMACION_RESET, ID_TOP);
    objetos[ID_PUNTAJE] = ImagenCrear(&juego, 1, &puntajeText, 100, 150, 0, 0, ANIMACION_RESET, ID_PUNTAJE);

    objetos[ID_SUMAR_NOTAS] = ImagenCrear(&juego, 1, botonSumar, 100, 50, 570, 250, ANIMACION_RESET, ID_SUMAR_NOTAS);
    objetos[ID_RESTAR_NOTAS] = ImagenCrear(&juego, 1, botonRestar, 100, 50, 500, 250, ANIMACION_RESET, ID_RESTAR_NOTAS);

    objetos[ID_SUMAR_DURACION] = ImagenCrear(&juego, 1, botonSumar, 100, 50, 570, 150, ANIMACION_RESET, ID_SUMAR_DURACION);
    objetos[ID_RESTAR_DURACION] = ImagenCrear(&juego, 1, botonRestar, 100, 50, 500,150, ANIMACION_RESET, ID_RESTAR_DURACION);

    objetos[ID_DURACION] = ImagenCrear(&juego, 1,&botonDuracion, 100, 400, 50, 150, ANIMACION_RESET, ID_DURACION);
    objetos[ID_NOTAS] = ImagenCrear(&juego, 1, &cant_notas, 100, 400, 50, 250, ANIMACION_RESET, ID_NOTAS);
    objetos[ID_MARCO_PUNTAJE] = ImagenCrear(&juego, 1,&cant_notas, 100, 400, 50, 250, ANIMACION_RESET, ID_MARCO_PUNTAJE);


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
                        PantallasDesafio();
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
                objetos[ID_PUNTAJE].texturas[0] =  CombinarTexturaConTexto(juego.renderer,CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer,NULL),texto_puntaje, "arial.ttf", 10, colores_notas[0]);
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

/*
                if(cantidad_notas >1)  //<--- Si hay mas de 1 nota se aplica una reduccion en el tiempo total
                {
                    SDL_Delay(duracion_sonido - ((duracion_sonido*0.03))* melodia.cant_notas ); //<-- -3% por nota
                }
                else
                {
                    SDL_Delay(duracion_sonido); //<--- Si hay solo 1, simplemente no se aplica
                }
*/
            }

        }


        //-------------------------------------------------------------------------------------------//




        // ------------------------ CREAR VENTANA AUXILIAR ------------------------------------//
        if (ventana_abierta && modo == MODO_SCHONBERG)
        {
            CrearVentana(&ventana_auxiliar, "Cual es tu nombre?", 400, 200);
            ingresoTexto = 1;
            ventana_abierta = 0;
        }


        if (ventana_abierta && modo == MODO_DESAFIO)
        {
            CrearVentana(&ventana_auxiliar, "Ingresa el nombre del archivo", 400, 200);
            ingresoTexto = 1;
            ventana_abierta = 0;
        }


        //---Renderiza el texto que se esta ingresando
        if (ingresoTexto && ventana_auxiliar.ventana != NULL) //<----Si la ventana esta abierta
        {
            SDL_SetRenderDrawColor(ventana_auxiliar.renderer, 0, 0, 0, 255);
            SDL_RenderClear(ventana_auxiliar.renderer);

            SDL_Surface *superficieTexto = TTF_RenderText_Blended(font, texto, colores_notas[0]);
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
