#ifndef SONIDOS_H_INCLUDED
#define SONIDOS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <math.h>



Mix_Chunk* cargarSonido(const char *path);


#endif // SONIDOS_H_INCLUDED
