#include "video.h"






//-------------Crea una ventana nueva y su render usando SDL
void CrearVentana(app_t *aplicacion,const char *titulo,int ancho,int alto)
{
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




//---------Crea la textura del texto de los jugadores top
SDL_Texture* CrearTexturaTopJugadores(SDL_Renderer *renderer, TTF_Font *font, jugador_t *jugadores, int cantidad)
{

    SDL_Color colorBlanco = {255, 0, 125, 255};  //<--------Color de la textura
    char buffer[1024]; //<--------- Para juntar todo el texto
    buffer[0] = '\0';

    strcat(buffer, "TOP JUGADORES \n\n"); //<-------Titulo


    for (int i = 0; i < cantidad; i++)   //<------- Obtiene la lista de jugadores y su puntuacion
    {
        char linea[256];
        snprintf(linea, sizeof(linea), "  %d- %s : %d\n", i + 1, jugadores[i].nombre, jugadores[i].puntuacion_maxima);
        strcat(buffer, linea);
    }


    SDL_Surface *superficieTexto = TTF_RenderText_Blended_Wrapped(font, buffer, colorBlanco, 400);  //<------- Crear superficie con todo el texto
    if (!superficieTexto)
    {
        printf("Error al crear superficie de texto: %s\n", TTF_GetError());
        return NULL;
    }


    SDL_Texture *textoTex = SDL_CreateTextureFromSurface(renderer, superficieTexto);//<----- Crear textura desde la superficie
    SDL_FreeSurface(superficieTexto);

    if (!textoTex)
    {
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








//----Obtiene los valores RGB desde un archivo .Bin;
void CargarPixelesDesdeBinario(const char* ruta,imagen_cruda_t *img){

    FILE* f = fopen(ruta, "rb"); //<-----Abre el archivo por su ruta
    if (!f)
    {
        printf("No se pudo abrir %s\n", ruta);
        return ;
    }

    int ancho, alto; //<------Las primeras 2 posiciones del archivo son el alto y el ancho
    fread(&ancho, sizeof(int), 1, f);
    fread(&alto, sizeof(int), 1, f);

    int cantidad_pixeles = ancho * alto; //<----la cantidad de pixeles de la imagen

    unsigned char* pixels_rgb = malloc(cantidad_pixeles * 3); //<-----Reserva memoria para cada pixel (se multiplica por 3, por R,G,B)
    if (!pixels_rgb)
    {
        fclose(f);
        return;
    }

    size_t leidos = fread(pixels_rgb, 3, cantidad_pixeles, f);//<---------Comprueba si la cantidad esperada de pixeles es = a la cantidad leida
    fclose(f);

    if (leidos != cantidad_pixeles)
    {
        free(pixels_rgb);
        return;
    }


    img->pixeles = pixels_rgb;
    img->ancho = ancho;
    img->alto = alto;

}




//---Aplica un filtro de color a una imagen y la pasa a rgba
void AplicarFiltroYConvertir(imagen_cruda_t *imagen, SDL_Color color)
{
    int cantidad_pixeles = imagen->alto * imagen->ancho;
    unsigned char* pixels_rgba = malloc(cantidad_pixeles * 4);
    if (!pixels_rgba) return;

    for (int i = 0; i < cantidad_pixeles; i++) {
        unsigned char r = imagen->pixeles[i * 3 + 0];
        unsigned char g = imagen->pixeles[i * 3 + 1];
        unsigned char b = imagen->pixeles[i * 3 + 2];


        pixels_rgba[i * 4 + 0] = (r * color.r) / 255;
        pixels_rgba[i * 4 + 1] = (g * color.g) / 255;
        pixels_rgba[i * 4 + 2] = (b * color.b) / 255;

        pixels_rgba[i * 4 + 3] = (r == 0 && g == 0 && b == 0) ? 0 : 255; //<---El negro lo ignora
    }

    free(imagen->pixeles);
    imagen->pixeles = pixels_rgba;
}



//-------Pasa de rgb a rgba sin aplicar el filtro
void ConvertirRGBaRGBA(imagen_cruda_t *imagen)
{
    int cantidad_pixeles = imagen->alto * imagen->ancho;

    unsigned char* pixels_rgba = malloc(cantidad_pixeles * 4);
    if (!pixels_rgba) return ;

    for (int i = 0; i < cantidad_pixeles; i++) {
        unsigned char r = imagen->pixeles[i * 3 + 0];
        unsigned char g = imagen->pixeles[i * 3 + 1];
        unsigned char b = imagen->pixeles[i * 3 + 2];

        pixels_rgba[i * 4 + 0] = r;
        pixels_rgba[i * 4 + 1] = g;
        pixels_rgba[i * 4 + 2] = b;
        pixels_rgba[i * 4 + 3] = (r == 0 && g == 0 && b == 0) ? 0 : 255;
    }

    free(imagen->pixeles);
    imagen->pixeles = pixels_rgba;
}










//-------Carga una textura desde un binario
SDL_Texture* CargarTexturaDesdeBinario(const char* ruta, SDL_Renderer* renderer,SDL_Color *filtro)
{
    imagen_cruda_t img;
    CargarPixelesDesdeBinario(ruta,&img);
    if (!img.pixeles) return NULL;

    if(filtro == NULL){
    ConvertirRGBaRGBA(&img);
    }else{
    AplicarFiltroYConvertir(&img,*filtro);
    }


    if (!img.pixeles) return NULL;

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        img.pixeles, img.ancho, img.alto, 32, img.ancho * 4, SDL_PIXELFORMAT_RGBA32
    );

    if (!surface) {
        free(img.pixeles);
        return NULL;
    }

    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    free(img.pixeles);

    if (textura)
        SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);

    return textura;
}





//----Carga varias texturas desde un binario
void CargarAnimaciondesdeBinario(const char* nombre,SDL_Color *color,SDL_Texture **texturas,SDL_Renderer *renderer){

char ruta_completa[256];
for(int i=1; i<=6; i++){
     snprintf(ruta_completa, sizeof(ruta_completa), "img/%s%d.bin", nombre, i);
     texturas[i-1] = CargarTexturaDesdeBinario(ruta_completa, renderer, color);
}

return;
}











//--------Crea una nueva estructura que representa una imagen u objeto
imagen_t ImagenCrear(app_t *juego, int frames_totales,SDL_Texture **texturas,int alto, int ancho, int x, int y,int tipo_animacion, int id)
{
    imagen_t aux; //<---Auxiliar
    aux.configs = (SDL_Rect)
    {
        x, y, ancho, alto
    }; //<---- Rectangulo de sdl, en este caso representa la posicion y el tamaño de la imagen
    aux.debe_Renderizar = 1;
    aux.frame_actual = 0;
    aux.frames_totales = frames_totales;
    aux.debe_animar = tipo_animacion == 3 ? 0 : 1;
    aux.modo_reproduccion = tipo_animacion;
    aux.id = id;
    aux.texturas = texturas;

    return aux;
}







//------Se encarga de copiar todas las imagenes que deberan ser renderizadas al render de la ventana. Luego las muestra
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
        }
    }

    SDL_RenderPresent(video->renderer);
}





//------------Controla los cambios de fotograma en las animaciones para cada objeto
void ManejarAnimaciones(imagen_t *objetos)
{
    for (int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        if (objetos[i].debe_animar) //<-----Si debe animar
        {
            switch (objetos[i].modo_reproduccion)
            {
            case ANIMACION_BUCLE:    //<---------- Anima toda la secuencia una y otra vez
                if (objetos[i].frame_actual >= objetos[i].frames_totales-1)
                {
                    objetos[i].frame_actual = 0;
                }
                else
                {
                    objetos[i].frame_actual++;
                }
                break;

            case ANIMACION_RESET: //<-----------Anima la secuencia 1 vez y luego  vuelve al fotograma 0
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

            case ANIMACION_ULTIMO_FRAME://<---------Anima la secuencia 1 vez y se queda en el ultimo fotograma
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










