#include "main.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));
    app_t juego;
    app_t ventana_auxiliar;
    CrearVentana(&juego,"Simon",700,500);
    int ingresoTexto = 0;
    int ventana_abierta=0;


    SDL_Texture *rosa[6] ={
    CargarTexturaDesdeBinario("img/rosa1.bin", juego.renderer),
    CargarTexturaDesdeBinario("img/rosa2.bin", juego.renderer),
    CargarTexturaDesdeBinario("img/rosa3.bin", juego.renderer),
    CargarTexturaDesdeBinario("img/rosa4.bin", juego.renderer),
    CargarTexturaDesdeBinario("img/rosa5.bin", juego.renderer),
    CargarTexturaDesdeBinario("img/rosa6.bin", juego.renderer),
    };


    SDL_Texture *boton[2] ={
    CargarTexturaDesdeBinario("img/boton1.bin", juego.renderer),
    CargarTexturaDesdeBinario("img/boton2.bin", juego.renderer),
    };

    SDL_Texture *fondo[1] ={
    CargarTexturaDesdeBinario("img/fondo1.bin", juego.renderer),
    };

      SDL_Texture *home[1] ={
    CargarTexturaDesdeBinario("img/home1.bin", juego.renderer),
    };




    //----------------------------DECLARACION DE OBJETOS---------------------------------------------------//
   objetos[ID_FONDO] = ImagenCrear(&juego,1, fondo, PANTALLA_ALTO, PANTALLA_ANCHO, 0, 0, ANIMACION_NO, ID_FONDO);
    objetos[ID_BOTON_MODO] = ImagenCrear(&juego,2, boton, 100, 200, 0, 100, ANIMACION_RESET, ID_BOTON_MODO);
    objetos[ID_BOTON_CONFIG] = ImagenCrear(&juego,2, boton, 100, 200, 0, 250, ANIMACION_RESET, ID_BOTON_CONFIG);
    objetos[ID_BOTON_VOLVER] = ImagenCrear(&juego,1, home, 100, 100, 600, 400, ANIMACION_RESET, ID_BOTON_VOLVER);
    objetos[ID_BOTON_SALIR] = ImagenCrear(&juego,2, boton, 100, 200, 0, 400, ANIMACION_RESET, ID_BOTON_SALIR);

    objetos[ID_AZUL]     = ImagenCrear(&juego,6, rosa, 160, 120, 125, 180, ANIMACION_RESET, ID_AZUL);
    objetos[ID_VERDE]    = ImagenCrear(&juego,6, rosa, 160, 120, 235, 180, ANIMACION_RESET, ID_VERDE);
    objetos[ID_ROJO]     = ImagenCrear(&juego,6, rosa, 160, 120, 345, 180, ANIMACION_RESET, ID_ROJO);
    objetos[ID_AMARILLO] = ImagenCrear(&juego,6, rosa, 160, 120, 455, 180, ANIMACION_RESET, ID_AMARILLO);

    objetos[ID_VIOLETA]  = ImagenCrear(&juego,6, rosa, 160, 120, 125, 260, ANIMACION_RESET, ID_VIOLETA);
    objetos[ID_NARANJA]  = ImagenCrear(&juego,6, rosa, 160, 120, 235, 260, ANIMACION_RESET, ID_NARANJA);
    objetos[ID_NEGRO]    = ImagenCrear(&juego,6, rosa, 160, 120, 345, 260, ANIMACION_RESET, ID_NEGRO);
    objetos[ID_BLANCO]   = ImagenCrear(&juego,6, rosa, 160, 120, 455, 260, ANIMACION_RESET, ID_BLANCO);

    objetos[ID_BOTON_SCHONBERG] = ImagenCrear(&juego,2, boton, 100, 200, 0, 100, ANIMACION_RESET, ID_BOTON_SCHONBERG);
    objetos[ID_BOTON_MOZART]    = ImagenCrear(&juego,2, boton, 100, 200, 0, 250, ANIMACION_RESET, ID_BOTON_MOZART);
    objetos[ID_BOTON_DESAFIO]   = ImagenCrear(&juego,2, boton, 100, 200, 0, 400, ANIMACION_RESET, ID_BOTON_DESAFIO);
    objetos[ID_BOTON_GUARDAR]   = ImagenCrear(&juego,2, boton, 100, 200, 0, 400, ANIMACION_RESET, ID_BOTON_GUARDAR);
    //-----------------------------------------------------------------------------------------------------------------//







       if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error al iniciar video: %s\n", SDL_GetError());
        exit(1);
    }


    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    SDL_StartTextInput();
    char texto[256] = "";

    SDL_Event e;




    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("[ERROR] No se pudo inicializar el audio: %s\n", Mix_GetError());
        corriendo = 0;
    }



    Mix_Chunk* sonidos[9] =
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




    PantallasMenuPrincipal(objetos, botones); //<-------Coloca el juego en el menu principal

    //Bucle Principal
    while (corriendo)
    {



        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                corriendo = 0;



            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int x = e.button.x;
                int y = e.button.y;
                BotonesActivosComprobarInteraccion(botones, x, y);
            }




      //------------------------------DETECCION INGRESO DE TEXTO----------------------------------------------------------------//
        if(ingresoTexto == 1){

            if (e.type == SDL_TEXTINPUT) //<---Si detecta el input del teclado
                strcat(texto, e.text.text); //<--- agrega un caracter


            if (e.type == SDL_KEYDOWN) //<---- si detecta que aprietan una tecla
            {
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(texto) > 0) //<-- si es borrar y hay texto
                {
                    texto[strlen(texto) - 1] = '\0'; //<--- elimina el último caracter
                }
                else if (e.key.keysym.sym == SDLK_RETURN) //<--- si la tecla es enter printea
                {
                    printf("Texto ingresado: %s\n", texto);
                }
            }

        }
      //-------------------------------------------------------------------------------------------------------//

        }



        if(ingresoTexto == 1){
      //   PantallaBloquearBotones(botones);
        if(ventana_abierta == 0){
        CrearVentana(&ventana_auxiliar,"Simon",300,200);
        ventana_abierta = 1;
        }

        SDL_Color color = {255, 255, 255}; //<----- Color de la letra
        SDL_Surface *superficieTexto = TTF_RenderText_Blended(font, texto, color);
        SDL_Texture *textoTex = SDL_CreateTextureFromSurface(ventana_auxiliar.renderer, superficieTexto);

        int tw, th;
        SDL_QueryTexture(textoTex, NULL, NULL, &tw, &th); //<--- Obtiene tamaño del texto
        SDL_Rect destino = {50, 100, tw, th};

        SDL_SetRenderDrawColor(ventana_auxiliar.renderer, 0, 0, 0, 255);
        SDL_RenderClear(ventana_auxiliar.renderer);
        SDL_RenderCopy(ventana_auxiliar.renderer, textoTex, NULL, &destino); //<--- Dibuja el texto
        SDL_RenderPresent(ventana_auxiliar.renderer); //<--- Muestra en pantalla

        SDL_DestroyTexture(textoTex);
        SDL_FreeSurface(superficieTexto);

        }


        //--------------------FPS----------------------------//
        switch (resultado)
        {
            case RESULTADO_GANO: //<--Si gano
                if (objetos[melodia.p[melodia.ultima_nota]].debe_animar)
                    break;

                if (!animando_victoria)
                {
                    printf("\n GO");
                    MelodiaGanoAnimacion(objetos);
                }
                else
                {
                    if (!objetos[ID_ROJO].debe_animar)
                    {
                        animando_victoria = 0;
                        SDL_Delay(200);
                        MelodiaGano(&melodia);
                        resultado = RESULTADO_EN_ESPERA;
                    }
                }
                break;

            case RESULTADO_PERDIO:
                MelodiaReiniciar(&melodia, 5);
                MelodiaAgregarAleatoria(&melodia, 3);
                system("cls");
                MelodiaMostrarConsola(&melodia);
                esta_reproduciendo = 1;
                resultado = RESULTADO_EN_ESPERA;
                SDL_Delay(2000);
                break;
        }







        //------------------ANIMACION DE SECUENCIA MELODICA-------------------//
        if (esta_reproduciendo == 1)
        {
            if (modo == MODO_MOZART)
                MelodiaAnimar(&jugador, objetos);
            if (modo == MODO_SCHONBERG)
                MelodiaAnimar(&melodia, objetos);
        }

        for (int i = ID_AZUL; i < ID_BLANCO; i++)
        {
            if (objetos[i].frame_actual == 3)
            {
                Mix_PlayChannel(0, sonidos[i], 0); // (0, ...) reproduce en el canal 0
            }
        }
       //----------------------------------------------------------------------------//


/*
//SDL_Texture* miTextura =
objetos[ID_FONDO].texturas[0] =  CargarTexturaDesdeBinario("img/fondo1.bin", juego.renderer);
  SDL_RenderClear(juego.renderer);
  SDL_SetRenderDrawColor(juego.renderer, 255, 255, 255, 255);
if (objetos[ID_FONDO].texturas[0]) {
    SDL_Rect dest = {160, 120, 225, 280};
    SDL_RenderCopy(juego.renderer, miTextura, NULL, &dest);
}
*/


       ManejarAnimaciones(objetos);
        ActualizarRender(&juego, objetos);
        SDL_RenderPresent(juego.renderer);
        SDL_Delay(100); // Control de FPS
        //---------------------------------------------------//









    }




    return 0;
}
