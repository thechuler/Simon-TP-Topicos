
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



SDL_Texture* CargarTexturaDesdeBinario(const char* ruta, SDL_Renderer* renderer)
{
    FILE* f = fopen(ruta, "rb");
    if (!f) { printf("No se pudo abrir %s\n", ruta); return NULL; }

    int ancho, alto;
    fread(&ancho, sizeof(int), 1, f);
    fread(&alto, sizeof(int), 1, f);

    int cantidad_pixeles = ancho * alto;
    unsigned char* pixels_rgb = malloc(cantidad_pixeles * 3);
    if (!pixels_rgb) { fclose(f); return NULL; }

    size_t leidos = fread(pixels_rgb, 3, cantidad_pixeles, f);
    fclose(f);
    if (leidos != cantidad_pixeles) { free(pixels_rgb); return NULL; }

    // Crear buffer RGBA
    unsigned char* pixels_rgba = malloc(cantidad_pixeles * 4);
    if (!pixels_rgba) { free(pixels_rgb); return NULL; }

    for (int i = 0; i < cantidad_pixeles; i++) {
        unsigned char r = pixels_rgb[i*3 + 0];
        unsigned char g = pixels_rgb[i*3 + 1];
        unsigned char b = pixels_rgb[i*3 + 2];

        pixels_rgba[i*4 + 0] = r;
        pixels_rgba[i*4 + 1] = g;
        pixels_rgba[i*4 + 2] = b;

        if (r == 0 && g == 0 && b == 0)
            pixels_rgba[i*4 + 3] = 0;
        else
            pixels_rgba[i*4 + 3] = 255;
    }

    free(pixels_rgb);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixels_rgba, ancho, alto, 32, ancho * 4, SDL_PIXELFORMAT_RGBA32
    );
    if (!surface) { free(pixels_rgba); return NULL; }

    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    free(pixels_rgba);

    SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);

    return textura;
}





imagen_t ImagenCrear(app_t *juego, int frames_totales,SDL_Texture **texturas,int alto, int ancho, int x, int y,int tipo_animacion, int id)
{
    imagen_t aux;
    aux.configs = (SDL_Rect){ x, y, ancho, alto };
    aux.debe_Renderizar = 1;
    aux.frame_actual = 0;
    aux.frames_totales = frames_totales;
    aux.debe_animar = tipo_animacion == 3 ? 0 : 1;
    aux.modo_reproduccion = tipo_animacion;
    aux.id = id;
    aux.texturas = texturas;

    return aux;
}








void ActualizarRender(app_t *video, imagen_t *objetos)
{
    SDL_RenderClear(video->renderer);

    for (int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        if (objetos[i].debe_Renderizar)
        {
            SDL_RenderCopy(video->renderer,
                           objetos[i].texturas[objetos[i].frame_actual],
                           NULL,
                           &objetos[i].configs);
    //    printf("RENDERIZANDO %d",i );
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










