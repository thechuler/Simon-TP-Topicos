#include "notas.h"
#include "variables_globales.h"


//----------------Genera una nueva melodia y la inicializa-----------------//
void MelodiaInicializar(melodia_t *melodia, int capacidad_inicial,unsigned nivel)
{
    melodia->p= malloc(sizeof(int) * capacidad_inicial);
    if(!melodia->p)
    {
        printf("Error al inicializar Melodia\n");
        exit(3);
    }
    melodia->cant_notas = 0;
    melodia->cant_total_notas = capacidad_inicial;
    melodia->nivel = nivel;
}




//----------Agrega una nota a la melodia --------------//
void MelodiaAgregarNota(melodia_t *melodia,int nota)
{
    if(melodia->cant_notas >= melodia->cant_total_notas)
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
    melodia->p[melodia->cant_notas] = nota;
    melodia->cant_notas++;
}




//----------Agrega una nota Aleatoria entre 1 y el nivel ----------//
void MelodiaAgregarAleatoria(melodia_t *melodia, int cantidad)
{

    for (int i = 0; i < cantidad; i++)
    {
        int nota = 1 + rand() % melodia->nivel;
        MelodiaAgregarNota(melodia, nota);
    }

    melodia->nota_actual = 0;
}



//--------Muestra la melodia en consola-------//
void MelodiaMostrarConsola(melodia_t *melodia)
{
    for(int i=0; i<melodia->cant_notas ; i++)
    {
        printf("(%d)",melodia->p[i]);
    }
}





//--------Comprueba 1 x 1 las notas de una melodia y devuelve un resultado---------//
int MelodiaComprobarIngreso(melodia_t *melodia,int input)
{

    if (melodia->p[melodia->nota_actual] == input)
    {
         melodia->ultima_nota = melodia->nota_actual;
         melodia->nota_actual++;

        if (melodia->nota_actual >= melodia->cant_notas)
        {

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
        // Mostrar Pantalla de reinciar o volver al menu
        printf("\n\n PERDISTE!\n");
        return RESULTADO_PERDIO;
    }

}




void MelodiaGanoAnimacion(imagen_t *objetos){

 printf("\n\n GANASTE!\n");
 animando_victoria = 1;
 esta_reproduciendo = 0;

for(int i= 1 ;i<9;i++){
    objetos[i].debe_animar = 1;
}


}

void MelodiaGano(melodia_t *melodia){
MelodiaAgregarAleatoria(melodia, 1);
//system("cls");
MelodiaMostrarConsola(melodia);
esta_reproduciendo = 1;
}





void MelodiaGuardar(melodia_t *melodia)
{
    FILE *f = fopen("guardado.dat","wb");
    if(!f) return;

    fwrite(melodia->p, sizeof(int), melodia->cant_notas, f);
    fclose(f);
}


void MelodiaCargar(melodia_t *melodia)
{
    FILE *f = fopen("guardado.dat","rb");
    if(!f) return;
    melodia->cant_notas = 0;
    int leidos = fread(melodia->p, sizeof(int), melodia->cant_total_notas, f);
    melodia->cant_notas = leidos;

    fclose(f);
}



void MelodiaAnimar(melodia_t *melodia, imagen_t *objetos)
{

    if (melodia->animacion_actual >= melodia->cant_notas) {
        melodia->animacion_actual = 0;
        esta_reproduciendo = 0;
        return;
    }

    int nota = melodia->p[melodia->animacion_actual];
    imagen_t *img = &objetos[nota];


    if (img->debe_animar == 0) {
        img->debe_animar = 1;
        img->frame_actual = 0;
        return;
    }


if(img->frame_actual >= img->frames_totales - 1 ){
     melodia->animacion_actual++;
     SDL_Delay(300);
}



}




