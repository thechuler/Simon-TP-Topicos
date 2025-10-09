
#include "video.h"





void CrearVentana(app_t *aplicacion,const char *titulo,int ancho,int alto){
 aplicacion->ventana = SDL_CreateWindow(    //<-----Creacion de la ventana
                              titulo,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              ancho,
                              alto,
                              SDL_WINDOW_SHOWN
                          );

    if (!aplicacion->ventana)   //<------Si no se creo la ventana cerrar.
    {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }


    //Creacion del render
    aplicacion->renderer = SDL_CreateRenderer(aplicacion->ventana, -1, SDL_RENDERER_ACCELERATED); //<-- Esta macro le avisa a sdl que hay que usar gpu en vez de cpu
    if (!aplicacion->renderer)
    {
        printf("Error al crear renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(aplicacion->ventana);
        SDL_Quit();
        exit(1);
    }

}



//-------Genera un struct del tipo imagen_t a partir de los parametros ingresados---//
imagen_t ImagenCrear(int frames_totales, const char *nombre, int alto, int ancho, int x, int y, int tipo_animacion,int id)
{

    //---Reservar memoria para los nombres de los archivos y aplicar nombre---//
    imagen_t aux;
    aux.fotogramas = malloc(frames_totales * sizeof(char*));
    if (aux.fotogramas == NULL)
    {
        printf("Error al reservar memoria para fotogramas\n");
        exit(2);
    }

    for (int i = 0; i < frames_totales; i++)
    {
        aux.fotogramas[i] = malloc(256);
        if (aux.fotogramas[i] == NULL)
        {
            printf("Error al reservar memoria para un fotograma\n");
            exit(1);
        }
        sprintf(aux.fotogramas[i], "%s%d.bmp", nombre, i+1);
    }
    //-----------------------------------------------------//



    aux.configs = (SDL_Rect)
    {
        x, y, ancho, alto
    };
    aux.debe_Renderizar = 1;
    aux.frame_actual = 0;
    aux.frames_totales = frames_totales;
    aux.debe_animar = tipo_animacion == 3 ? 0 : 1;
    aux.modo_reproduccion = tipo_animacion;
    aux.id = id;
    return aux;
}





// HAY QUE CAMBIAR EL MAPEADO DE ESTO
void ImagenCargar(imagen_t *imagen,app_t *applicacion)  //<--------Prepara una imagen para ser cargada en el Render
{
    // Cargar imagen en memoria
    char ruta[100];
    sprintf(ruta, "texturas/%s", imagen->fotogramas[imagen->frame_actual]);//<---Crea la ruta a base del nombre del frame actual y el path


    SDL_RWops *rw = SDL_RWFromFile(ruta, "rb"); //<--- Obtiene Datos tras la lectura del archivo y los guarda en una struct.
    imagen->surface = SDL_LoadBMP_RW(rw, 1);   //<---- Lee esos datos y los convierte en surface. Al terminar cierra el espacio en memoria si el int es != 0


    if (!imagen->surface)
    {
        printf("Error al cargar imagen '%s': %s\n", ruta, SDL_GetError());
        SDL_DestroyRenderer(applicacion->renderer);
        SDL_DestroyWindow(applicacion->ventana);
        SDL_Quit();
        exit(3);
    }



    //Crear Textura
    imagen->textura = SDL_CreateTextureFromSurface(applicacion->renderer, imagen->surface);
    SDL_FreeSurface(imagen->surface); //<-- Una vez la textura ya se crea, no hace falta seguir teniendo en memoria la imagen
    if (!imagen->textura)
    {
        printf("Error al crear textura: %s\n", SDL_GetError());
        SDL_DestroyRenderer(applicacion->renderer);
        SDL_DestroyWindow(applicacion->ventana);
        SDL_Quit();
        exit(3);
    }


    SDL_RenderCopy(applicacion->renderer, imagen->textura, NULL, &imagen->configs); //<-- COPIA AL RENDER TODA LA TEXTURA

}





void ActualizarRender(app_t *video, imagen_t *objetos)   //<--- Esta funcion "DEBERIA" de decidir si una imagen se renderiza o no
{
    SDL_RenderClear(video->renderer);                                   // En principio funciona bien, pero como carga todas las imagenes por cada frame no se que tan optimo es

    for (int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        if (objetos[i].debe_Renderizar)
        {
            ImagenCargar(&objetos[i],video);
        }
    }

    SDL_RenderPresent(video->renderer);
}







void ManejarAnimaciones(imagen_t *objetos)
{
    for (int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        if (objetos[i].debe_animar)
        {
            switch (objetos[i].modo_reproduccion)
            {
                case ANIMACION_BUCLE:
                    if (objetos[i].frame_actual >= objetos[i].frames_totales-1)
                    {
                        objetos[i].frame_actual = 0;
                    }
                    else
                    {
                        objetos[i].frame_actual++;
                    }
                    break;

                case ANIMACION_RESET:
                    if (objetos[i].frame_actual >= objetos[i].frames_totales-1)
                    {
                        objetos[i].frame_actual = 0;
                        objetos[i].debe_animar = 0;
                    }
                    else
                    {
                        objetos[i].frame_actual++;
                    }
                    break;

                case ANIMACION_ULTIMO_FRAME:
                    if (objetos[i].frame_actual >= objetos[i].frames_totales-1)
                    {
                        objetos[i].debe_animar = 0;
                    }
                    else
                    {
                        objetos[i].frame_actual++;
                    }
                    break;
            }
        }
    }
}










