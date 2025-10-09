
#include "variables_globales.h"
imagen_t objetos[CANTIDAD_OBJETOS]; //<------Vector Principal de imagenes. Representa todos los objetos del juego
int corriendo = 1;
int modo = 0;
int esta_reproduciendo = 0;
int resultado = RESULTADO_EN_ESPERA;
char animando_victoria = 0;
melodia_t melodia;
melodia_t jugador;

    //------------------------------------DECLARACION BOTONES--------------------------------//
    boton_t botones[CANTIDAD_BOTONES] = //<--------Vector Principal de botones.
    {
        { &objetos[ID_AZUL], FuncionNota,0,ID_AZUL },
        { &objetos[ID_ROJO], FuncionNota, 0,ID_ROJO },
        { &objetos[ID_VERDE], FuncionNota,  0 ,ID_VERDE},
        { &objetos[ID_AMARILLO], FuncionNota,  0 ,ID_AMARILLO},
        { &objetos[ID_NARANJA], FuncionNota,  0 ,ID_NARANJA},
        { &objetos[ID_VIOLETA], FuncionNota,  0 ,ID_VIOLETA},
        { &objetos[ID_NEGRO], FuncionNota,  0 ,ID_NEGRO},
        { &objetos[ID_BLANCO], FuncionNota,  0 ,ID_BLANCO},

        { &objetos[ID_BOTON_MODO], FuncionBotonModo,  0 ,ID_BOTON_MODO},
        { &objetos[ID_BOTON_SALIR], FuncionBotonSalir, 0 ,ID_BOTON_SALIR},
        { &objetos[ID_BOTON_CONFIG], FuncionBotonSalir, 0 ,ID_BOTON_CONFIG},
        { &objetos[ID_BOTON_VOLVER], FuncionBotonVolver,  0 ,ID_BOTON_VOLVER},

        { &objetos[ID_BOTON_SCHONBERG], FuncionBotonSchonberg,  0, ID_BOTON_SCHONBERG },
        { &objetos[ID_BOTON_MOZART], FuncionBotonMozart,  0 ,ID_BOTON_MOZART},
        { &objetos[ID_BOTON_DESAFIO], FuncionBotonDesafio, 0 ,ID_BOTON_DESAFIO},
        { &objetos[ID_BOTON_GUARDAR], FuncionBotonGuardar,  0 ,ID_BOTON_GUARDAR},
    };
    //-----------------------------------------------------------------------------------//

