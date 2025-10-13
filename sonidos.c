#include "sonidos.h"


//-----Carga un sonido a memoria desde archivo .wav
Mix_Chunk* cargarSonido(const char *path)
{
    Mix_Chunk *sonido;

    sonido = Mix_LoadWAV(path);
    if (!sonido)
    {
        printf("Error cargando sonido \"%s:\" %s\n", path, Mix_GetError());
    }

    return sonido;
}


