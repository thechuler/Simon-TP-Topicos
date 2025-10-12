
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




SDL_Texture* CrearTexturaTopJugadores(SDL_Renderer *renderer, TTF_Font *font, jugador_t *jugadores, int cantidad) {
    SDL_Color colorBlanco = {255, 255, 255, 255};
    char buffer[1024]; // Para concatenar todo el texto
    buffer[0] = '\0';

    // Título
    strcat(buffer, "TOP JUGADORES\n\n");

    // Lista de jugadores
    for (int i = 0; i < cantidad; i++) {
        char linea[256];
        snprintf(linea, sizeof(linea), "%d- %s : %d\n", i + 1, jugadores[i].nombre, jugadores[i].puntuacion_maxima);
        strcat(buffer, linea);
    }

    // Crear superficie con todo el texto
    SDL_Surface *superficieTexto = TTF_RenderText_Blended_Wrapped(font, buffer, colorBlanco, 400); // 400 es el ancho máximo
    if (!superficieTexto) {
        printf("Error al crear superficie de texto: %s\n", TTF_GetError());
        return NULL;
    }

    // Crear textura desde la superficie
    SDL_Texture *textoTex = SDL_CreateTextureFromSurface(renderer, superficieTexto);
    SDL_FreeSurface(superficieTexto);

    if (!textoTex) {
        printf("Error al crear textura de texto: %s\n", SDL_GetError());
        return NULL;
    }

    return textoTex;
}






SDL_Texture* CombinarTexturaConTexto(SDL_Renderer* renderer, SDL_Texture* base, const char* texto, const char* fuente, int tam, SDL_Color color)
{
    // Obtener tamaño del texto
    TTF_Font* font = TTF_OpenFont(fuente, tam);
    SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font, texto, color);
    TTF_CloseFont(font);

    // Crear textura del texto
    SDL_Texture* texto_tex = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);

    // Crear una textura destino del mismo tamaño que la base
    int w, h;
    SDL_QueryTexture(base, NULL, NULL, &w, &h);
    SDL_Texture* destino = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    // Establecer como render target
    SDL_SetRenderTarget(renderer, destino);
    SDL_RenderCopy(renderer, base, NULL, NULL);

    // Renderizar el texto centrado
    SDL_Rect rect_texto = { w/2 - text_surface->w/2, h/2 - text_surface->h/2, text_surface->w, text_surface->h };
    SDL_RenderCopy(renderer, texto_tex, NULL, &rect_texto);

    // Volver al render target normal
    SDL_SetRenderTarget(renderer, NULL);

    SDL_DestroyTexture(texto_tex);
    return destino;
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










