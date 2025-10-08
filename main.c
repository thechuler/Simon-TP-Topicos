#include "main.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));
    app_t juego;
    imagen_t objetos[CANTIDAD_OBJETOS]; //<------Vector Principal de imagenes. Representa todos los objetos del juego



    //----------------------------DECLARACION DE OBJETOS---------------------------------------------------//
    objetos[ID_FONDO] = ImagenCrear(1, "fondo", PANTALLA_ALTO, PANTALLA_ANCHO, 0, 0, ANIMACION_NO,ID_FONDO);

    objetos[ID_BOTON_MODO] = ImagenCrear(2, "boton", 100, 200, 0, 100, ANIMACION_RESET,ID_BOTON_MODO);
    objetos[ID_BOTON_CONFIG] = ImagenCrear(2, "boton", 100, 200, 0, 250, ANIMACION_RESET,ID_BOTON_CONFIG);
    objetos[ID_BOTON_VOLVER] = ImagenCrear(2, "boton", 50, 100, 500, 0, ANIMACION_RESET,ID_BOTON_VOLVER);
    objetos[ID_BOTON_SALIR] = ImagenCrear(2, "boton", 100, 200, 0, 400, ANIMACION_RESET,ID_BOTON_SALIR);

    objetos[ID_AZUL] = ImagenCrear(6, "rosa", 100, 50, 500, 100, ANIMACION_RESET,ID_AZUL);
    objetos[ID_VERDE] = ImagenCrear(6, "rosa", 100, 50, 550, 100, ANIMACION_RESET,ID_VERDE);
    objetos[ID_ROJO] = ImagenCrear(6, "rosa", 100, 50, 600, 100, ANIMACION_RESET,ID_ROJO);
    objetos[ID_AMARILLO] = ImagenCrear(6, "rosa", 100, 50, 650, 100, ANIMACION_RESET,ID_AMARILLO);
    objetos[ID_VIOLETA] = ImagenCrear(6, "rosa", 100, 50, 500, 150, ANIMACION_RESET,ID_VIOLETA);
    objetos[ID_NARANJA] = ImagenCrear(6, "rosa", 100, 50, 550, 150, ANIMACION_RESET,ID_NARANJA);
    objetos[ID_NEGRO] = ImagenCrear(6, "rosa", 100, 50, 600, 150, ANIMACION_RESET,ID_NEGRO);
    objetos[ID_BLANCO] = ImagenCrear(6, "rosa", 100, 50, 650, 150, ANIMACION_RESET,ID_BLANCO);

    objetos[ID_BOTON_SCHONBERG] = ImagenCrear(2, "boton", 100, 200, 0, 100, ANIMACION_RESET,ID_BOTON_SCHONBERG);
    objetos[ID_BOTON_MOZART] = ImagenCrear(2, "boton", 100, 200, 0, 250, ANIMACION_RESET,ID_BOTON_MOZART);
    objetos[ID_BOTON_DESAFIO] = ImagenCrear(2, "boton", 100, 200, 0, 400, ANIMACION_RESET,ID_BOTON_DESAFIO);


//-----------------------------------------------------------------------------------------------------------------//








//------------------------------------DECLARACION BOTONES--------------------------------//

    boton_t botones[CANTIDAD_BOTONES] =    //<--------Vector Principal de botones.
    {
        { &objetos[ID_AZUL], FuncionNota,(void*)ID_AZUL,NULL,0 },
        { &objetos[ID_ROJO], FuncionNota,(void*)ID_ROJO,NULL,0 },
        { &objetos[ID_VERDE], FuncionNota,(void*)ID_VERDE,NULL,0 },
        { &objetos[ID_AMARILLO], FuncionNota,(void*)ID_AMARILLO,NULL,0 },
        { &objetos[ID_NARANJA], FuncionNota,(void*)ID_NARANJA,NULL,0 },
        { &objetos[ID_VIOLETA], FuncionNota,(void*)ID_VIOLETA,NULL,0 },
        { &objetos[ID_NEGRO], FuncionNota,(void*)ID_NEGRO,NULL,0 },
        { &objetos[ID_BLANCO], FuncionNota,(void*)ID_BLANCO,NULL,0 },


        { &objetos[ID_BOTON_MODO], FuncionBotonModo,objetos,botones,0},
        { &objetos[ID_BOTON_SALIR], FuncionBotonSalir,NULL,NULL,0},
        { &objetos[ID_BOTON_CONFIG], FuncionBotonSalir,NULL,NULL,0},
        { &objetos[ID_BOTON_VOLVER], FuncionBotonVolver,objetos,botones,0},

        { &objetos[ID_BOTON_SCHONBERG], FuncionBotonSchonberg,objetos,botones,0},
        { &objetos[ID_BOTON_MOZART], FuncionBotonSalir,NULL,NULL,0},
        { &objetos[ID_BOTON_DESAFIO], FuncionBotonSalir,NULL,NULL,0},
    };

//-----------------------------------------------------------------------------------//



    SDL_Event e;
    IniciarGraficos(&juego);
    PantallasMenuPrincipal(objetos,botones); //<-------Coloca el juego en el menu principal


  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

        printf("[ERROR] No se pudo inicializar el audio: %s\n", Mix_GetError());
        corriendo = 0;
    }

    Mix_Chunk* sonidos[9] = {
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
        }






//--------------------FPS----------------------------//

switch(resultado){

case RESULTADO_GANO: //<--Si gano

if(objetos[melodia.p[melodia.ultima_nota]].debe_animar){ //<------Comprueba que el objeto se termine de animar
    printf("\n Esperando al objeto: %d",objetos[melodia.p[melodia.ultima_nota]].id);
    break;
}

//Si llega a este punto se supone que lo de arriba ya se animo

if(!animando_victoria){ //<---Si todavia no esta animando la victoria
printf("\n GO");
MelodiaGanoAnimacion(objetos); // <---- La marca para ser animada
}

else{  //<-----Si si se esta animando

if(!objetos[ID_ROJO].debe_animar){ //<-- comprueba si se termino de animar

animando_victoria = 0; //<------Se termina la animacion de victoria
SDL_Delay(200); //<------HACE UN DELAY
MelodiaGano(&melodia); //<------Activa la logica
resultado = RESULTADO_EN_ESPERA; //<------ Espera
}

}


break;
case RESULTADO_PERDIO:
Mix_PlayChannel(0,sonidos[0], 0); // (0, ...) reproduce en el canal 0
SDL_Delay(2000);
//melodia reset
resultado = RESULTADO_EN_ESPERA;
break;
}



if(esta_reproduciendo == 1){
    MelodiaAnimar(&melodia,objetos);
}



for(int i = ID_AZUL ; i<ID_BLANCO;i++){
    if(objetos[i].frame_actual == 3){
     Mix_PlayChannel(0,sonidos[i], 0); // (0, ...) reproduce en el canal 0
    }
}



        SDL_RenderClear(juego.renderer);
        ManejarAnimaciones(objetos);
        ActualizarRender(&juego,objetos);
        SDL_RenderPresent(juego.renderer);
        SDL_Delay(100); // Control de FPS
//---------------------------------------------------//
    }

    return 0;
}
