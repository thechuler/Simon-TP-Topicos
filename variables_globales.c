
#include "variables_globales.h"
imagen_t objetos[CANTIDAD_OBJETOS]; //<------Vector Principal de imagenes. Representa todos los objetos del juego
char corriendo = 1;  //<------- Si el juego esta o no corriendo
int modo = 0;    //<-----El modo de juego actual
char ventana_abierta = 0;  //<---Si hay o no una ventana auxiliar abierta
char esta_reproduciendo = 0;  //<---- Cuando se esta o no, reproduciendo la secuencia de la melodia.
int resultado = RESULTADO_EN_ESPERA; //<--- Resultado tras terminar una ronda
int puntuacion = 0;  //<-----Puntuacion del jugador
int cantidad_notas = 3; //<------Cantidad de notas activas (por defecto 3)
int duracion_sonido = 2000;  //<------- Duracion de cada nota (Por defecto 2sg)
char animando_fin_ronda = 0; //<-----Si esta o no animando el final de una ronda
char nombre_archivo[200]; //<-------Nombre del archivo que guardara la melodia.

jugador_t jugadores_top[5] = {
    {"DUM ->?",14},
    {"Compi",0},
    {"Cami",0},      //<----------Valores default del top 5 mejores jugadores
    {"ShuleTk",0},
    {"Jair17",0},
    };


jugador_t jugador_actual  = {"desconocido",0}; //<-----Jugador Actual, Default "Desconocido"
melodia_t melodia; //<-----Melodia Schonberg
melodia_t melodia_jugador; //<-----Melodia Mozart/ Desafio





    //-------Declaracion de Botones
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
        { &objetos[ID_BOTON_CONFIG], FuncionBotonConfigs, 0 ,ID_BOTON_CONFIG},
        { &objetos[ID_BOTON_VOLVER], FuncionBotonVolver,  0 ,ID_BOTON_VOLVER},

        { &objetos[ID_BOTON_SCHONBERG], FuncionBotonSchonberg,  0, ID_BOTON_SCHONBERG },
        { &objetos[ID_BOTON_MOZART], FuncionBotonMozart,  0 ,ID_BOTON_MOZART},
        { &objetos[ID_BOTON_DESAFIO], FuncionBotonDesafio, 0 ,ID_BOTON_DESAFIO},
        { &objetos[ID_BOTON_GUARDAR], FuncionBotonGuardar,  0 ,ID_BOTON_GUARDAR},

        { &objetos[ID_SUMAR_NOTAS], FuncionBotonSumarNota,  0 ,ID_SUMAR_NOTAS},
        { &objetos[ID_RESTAR_NOTAS], FuncionBotonRestarNota,  0 ,ID_RESTAR_NOTAS},

        { &objetos[ID_SUMAR_DURACION], FuncionBotonSumarDuracion,  0 ,ID_SUMAR_DURACION},
        { &objetos[ID_RESTAR_DURACION], FuncionBotonRestarDuracion,  0 ,ID_RESTAR_DURACION},
    };
    //-----------------------------------------------------------------------------------//


