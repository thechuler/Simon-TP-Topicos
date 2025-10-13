#include "notas.h"
#include "variables_globales.h"
#include "main.h"



//---Setea la melodia a un valor inicial
void MelodiaInicializar(melodia_t *melodia, int capacidad_inicial,unsigned nivel)
{
    melodia->p= malloc(sizeof(int) * capacidad_inicial); //<----Reserva memoria para la melodia
    if(!melodia->p)
    {
        printf("Error al inicializar Melodia\n");
        exit(3);
    }
    melodia->cant_notas = 0;
    melodia->cant_total_notas = capacidad_inicial;
    melodia->nivel = nivel;
}




//-----Agrega una nota a la melodia
void MelodiaAgregarNota(melodia_t *melodia,int nota)
{
    if(melodia->cant_notas >= melodia->cant_total_notas) //<-------Si la cantidad de notas supera la capacidad se reserva mas memoria
    {
        melodia->cant_total_notas += 5;
        int *p = realloc(melodia->p, sizeof(int) * melodia->cant_total_notas);
        if(!p)
        {
            printf("Error al redimensionar la melodia n");
            exit(1);
        }
        melodia->p = p;
    }

    melodia->p[melodia->cant_notas] = nota; //<---Se agrega la nota
    melodia->cant_notas++; //<---Se suma a la cantidad
}



//---Reinicia la malodia a un estado inicial
void MelodiaReiniciar(melodia_t *melodia,int capacidad_inicial)
{
    if (melodia->p != NULL)
    {
        free(melodia->p); //<---Libera memoria
    }
    MelodiaInicializar(melodia,capacidad_inicial,melodia->nivel); //<-----Inicializa nuevamente
}



//---Agrega una nota Aleatoria entre 1 y el nivel
void MelodiaAgregarAleatoria(melodia_t *melodia, int cantidad)
{

    for (int i = 0; i < cantidad; i++) //<------- Repite la cantidad una cantidad de veces como notas a agregar
    {
        int nota = 1 + rand() % melodia->nivel;//<----- Una nueva nota es un valor entre 1 y el nivel te la melodia (de 1 a 8)
        MelodiaAgregarNota(melodia, nota); //<---Agrega la nota
    }

    melodia->nota_actual = 0; //<--- Vuelve a iniciar la secuencia
}



//--------Muestra la melodia en consola
void MelodiaMostrarConsola(melodia_t *melodia)
{
    for(int i=0; i<melodia->cant_notas ; i++)
    {
        printf("(%d)",melodia->p[i]);
    }
}





//--------Comprueba 1 x 1 las notas de una melodia y devuelve un resultado
int MelodiaComprobarIngreso(melodia_t *melodia,int input)
{

    if (melodia->p[melodia->nota_actual] == input) //<----Si la nota actual de la secuencia es = a la que ingreso el usuario
    {
        melodia->ultima_nota = melodia->nota_actual; //<--- Se guarda la ultima nota comprobada (Esto se usa para evitar problemas en animacion)
        melodia->nota_actual++;// <--- Siguiente nota

        if (melodia->nota_actual >= melodia->cant_notas)//<---Si la melodia acabo
        {
            printf("\n\n GANASTE!\n");
            return RESULTADO_GANO;
        }
        else
        {
            printf("\n\n BIEN!\n");
            return RESULTADO_ACERTO;
        }
    }
    else
    {
        printf("\n\n PERDISTE!\n");
        return RESULTADO_PERDIO;
    }

}



//-----Activa todas las notas para el efecto de ronda ganada
void MelodiaGanoAnimacion()
{
    animando_fin_ronda = 1; //<----Empieza la animacion fin de ronda
    esta_reproduciendo = 0; //<--- ya no esta reproduciendo secuencia

    for(int i= 1 ; i<9; i++)
    {
        objetos[i].debe_animar = 1; //<--- Anima todas las notas
    }

}


//-----Activa todas las notas para el efecto de ronda perdida
void MelodiaPerdioAnimacion()
{
    animando_fin_ronda = 1;//<----Empieza la animacion fin de ronda
    esta_reproduciendo = 0;//<--- ya no esta reproduciendo secuencia

    for(int i= 1 ; i<9; i++)
    {
        objetos[i].debe_animar = 1;//<--- Anima todas las notas
    }

}




//------Logica de ronda ganada
void MelodiaGano(melodia_t *melodia)
{
    if(modo == 1)
    {
        // corriendo =0; //VICTORIA MOZART
    }

    if(modo == MODO_SCHONBERG)
    {
        puntuacion++; //<----Aumenta la puntuacion
        MelodiaAgregarAleatoria(melodia, 1); //<---Agrega una nota al aleatoria
        MelodiaMostrarConsola(melodia); //<---Muestra en consola
        esta_reproduciendo = 1; //<-----Comienza a reproducir secuencia
    }

}



//-----Logica ronda perdida
void MelodiaPerdio(melodia_t *melodia)
{
    if(modo == MODO_SCHONBERG)
    {
        jugador_actual.puntuacion_maxima = puntuacion; //<----Guarda la puntuacion maxima del jugador
        JugadorControlarPuntuacion(&jugador_actual,RESULTADO_PERDIO);//<-----Controla si la puntuacion deberia ser aumentada
        JugadorGuardarTop(); //<------Guarda  el top
        puntuacion = 0; //<--- Reset puntuacion
        MelodiaReiniciar(melodia,melodia->cant_notas); //<---Reset melodia
        MelodiaAgregarAleatoria(melodia,3); //<--------Agrega 3 notas
    }
    melodia->nota_actual = 0; //<----- Reinicia nota actual
    MelodiaMostrarConsola(melodia); //<---Muestra en consola
    esta_reproduciendo = 1;    //<------Comienza a reproducir secuencia
}




//-----Guarda una melodia en un archivo de texto
void MelodiaGuardar(melodia_t *melodia,char *nombre)
{
    char ruta[200];
    sprintf(ruta, "saves/%s.dat", nombre);
    FILE *f = fopen(ruta,"wb");//<---Crea un File en la carpeta saves
    if(!f) return;

    fwrite(melodia->p, sizeof(int), melodia->cant_notas, f); //<-------Guarda la melodia
    fclose(f); //<--- Cierra
}




//----------Carga la melodia de un archivo de texto
void MelodiaCargar(melodia_t *melodia,const char* ruta)
{
    FILE *f = fopen(ruta, "rb"); //<---Carga desde la ruta
    if (!f)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    int nota; //<--Auxiliar

    while (fread(&nota, sizeof(int), 1, f) == 1) //<---Mientras que existan notas
    {
        MelodiaAgregarNota(&melodia_jugador,nota); //<---Las agrega a la melodia
    }

    fclose(f);//<--- Cierra
}




//------Amima la secuencia de la melodia
void MelodiaAnimar(melodia_t *melodia)
{

    if (melodia->animacion_actual >= melodia->cant_notas)//<-----Si la nota que se esta animando es >= a la cantidad, termino la secuencia
    {
        melodia->animacion_actual = 0; //<---Reset de la nota a animar
        esta_reproduciendo = 0;  //<--- Ya no esta reproduciendo secuencia
        return;
    }


    imagen_t *img = &objetos[melodia->p[melodia->animacion_actual]]; //<--- Auxiliar para entender mejor el codigo, representa a la imagen que de debe animar


    if (img->debe_animar == 0) //<-- Si no se esta animando
    {
        img->debe_animar = 1; //<--Inicia la animacion
        img->frame_actual = 0;//<--Reinicia su frame
        return;
    }


    if(img->frame_actual >= img->frames_totales - 1 ) //<------Si ya se termino de animar
    {
        melodia->animacion_actual++;//<---Pasa a la siguiente nota a ser animada
    }



}








int MelodiaFinalDeRonda(melodia_t *melodia,int resultado)
{

    if (objetos[melodia->p[melodia->ultima_nota]].debe_animar)
    {
        return resultado;
    }

    if (!animando_fin_ronda)
    {
        printf("\n GO");
        if (resultado == RESULTADO_GANO)
            MelodiaGanoAnimacion();
        else
            MelodiaPerdioAnimacion();
        return resultado;
    }
    else
    {
        if (!objetos[ID_ROJO].debe_animar)
        {
            animando_fin_ronda = 0;
            SDL_Delay(200);
            if (resultado == RESULTADO_GANO)
                MelodiaGano(melodia);
            else
                MelodiaPerdio(melodia);
            return RESULTADO_EN_ESPERA;
        }
        return resultado;
    }

}



