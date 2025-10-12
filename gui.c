#include "gui.h"
#include "variables_globales.h"

char* AbrirExploradorYRecuperarRuta(void) {
    OPENFILENAME ofn;       //z----- Estructura del dialogo, esta en windows.h
    char szFile[260];       //<---- Buffer donde guardaria la ruta

    ZeroMemory(&ofn, sizeof(ofn));
    ZeroMemory(szFile, sizeof(szFile));      //<------ Limpia para evitar basura

    ofn.lStructSize = sizeof(ofn); //<-----Tamaño de la structura
    ofn.hwndOwner = NULL;   // Ventana padre (NULL = consola)
    ofn.lpstrFile = szFile; //<----donde guarda la ruta
    ofn.lpstrFile[0] = '\0'; //<--- Lo inicializa vacio
    ofn.nMaxFile = sizeof(szFile);  //<--- tam maximo
    ofn.lpstrFilter =
        "Archivos DAT (*.dat)\0*.dat\0"
        "Todos los archivos (*.*)\0*.*\0";   //<----Este filtro hace que aparezcan los binarios en la busqueda


    ofn.nFilterIndex = 1;       //<--- orden de los filtros

    ofn.lpstrFileTitle = NULL;  //<--- No me interesa guardar solo el nombre del archivo
    ofn.nMaxFileTitle = 0;

    ofn.lpstrInitialDir = NULL; //<----  Empieza en el directorio actual

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //<------- condicional, el archivo debe existir al igual que la ruta


    if (GetOpenFileName(&ofn)) {   //<--- Abre la ventana y si el user eligio un archivo lo guarda
        char* ruta = (char*)malloc(strlen(ofn.lpstrFile) + 1);
        if (ruta) strcpy(ruta, ofn.lpstrFile);
        return ruta;
    } else {
        return NULL;
    }

}


//-------Comprueba si un boton fue clickeado y activa su funcion asociada-----//
int BotonesActivosComprobarInteraccion( int x, int y)
{
    SDL_Point click = {x, y};

    for(int i = 0; i < CANTIDAD_BOTONES; i++)
    {
        if(botones[i].esta_activo)
        {
            if(SDL_PointInRect(&click,&botones[i].imagen->configs))
            {
                botones[i].imagen->frame_actual =0;
                botones[i].imagen->debe_animar = 1;
                if(i>=ID_FONDO && i<=ID_BLANCO){
                botones[i].accion(botones[i].id);
                }else{
                botones[i].accion();
                }
                return  0;
            }
        }
    }

    return -1;
}




//-------Limpia todos los objetos de la pantalla-----//
void PantallasLimpiar()
{
    for(int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        objetos[i].debe_Renderizar = 0;
        objetos[i].debe_animar = 0;
    }
}


//----Bloquea todos los botones de la pantalla----//
void PantallaBloquearBotones()
{
    for(int i = 0; i < CANTIDAD_BOTONES; i++)
    {
        botones[i].esta_activo = 0;
    }
}


//------Obtiene un boton por su id asignada-----//
int BotonesObtenerPorId(int id)
{
    for(int i=0; i<CANTIDAD_BOTONES; i++)
    {
        if(botones[i].imagen->id == id)
        {
            return i;
        }
    }
    return -1;
}




//------------Setea el menu principal-----------------//
void PantallasMenuPrincipal(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_BOTON_SALIR].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_SALIR)].esta_activo = 1;

objetos[ID_BOTON_CONFIG].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_CONFIG)].esta_activo = 1;

objetos[ID_BOTON_MODO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_MODO)].esta_activo = 1;

}




//------------Setea la pantalla modos-----------------//
void PantallasModos(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_FONDO].debe_Renderizar = 1;

objetos[ID_BOTON_MOZART].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_MOZART)].esta_activo = 1;


objetos[ID_BOTON_DESAFIO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_DESAFIO)].esta_activo = 1;

objetos[ID_BOTON_SCHONBERG].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_SCHONBERG)].esta_activo = 1;


objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}




//------------Setea la pantalla schonberg-----------------//
void PantallasSchonberg(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_AZUL].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_AZUL)].esta_activo = 1;

objetos[ID_ROJO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_ROJO)].esta_activo = 1;

objetos[ID_VERDE].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_VERDE)].esta_activo = 1;

objetos[ID_AMARILLO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_AMARILLO)].esta_activo = 1;

objetos[ID_VIOLETA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_VIOLETA)].esta_activo = 1;

objetos[ID_NARANJA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_NARANJA)].esta_activo = 1;

objetos[ID_NEGRO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_NEGRO)].esta_activo = 1;

objetos[ID_BLANCO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BLANCO)].esta_activo = 1;


objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}


//------------Setea la pantalla schonberg-----------------//
void PantallasDesafio(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_AZUL].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_AZUL)].esta_activo = 1;

objetos[ID_ROJO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_ROJO)].esta_activo = 1;

objetos[ID_VERDE].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_VERDE)].esta_activo = 1;

objetos[ID_AMARILLO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_AMARILLO)].esta_activo = 1;

objetos[ID_VIOLETA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_VIOLETA)].esta_activo = 1;

objetos[ID_NARANJA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_NARANJA)].esta_activo = 1;

objetos[ID_NEGRO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_NEGRO)].esta_activo = 1;

objetos[ID_BLANCO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BLANCO)].esta_activo = 1;


objetos[ID_BOTON_GUARDAR].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_GUARDAR)].esta_activo = 1;

objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}


void PantallasMozart(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_AZUL].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_AZUL)].esta_activo = 1;

objetos[ID_ROJO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_ROJO)].esta_activo = 1;

objetos[ID_VERDE].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_VERDE)].esta_activo = 1;

objetos[ID_AMARILLO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_AMARILLO)].esta_activo = 1;

objetos[ID_VIOLETA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_VIOLETA)].esta_activo = 1;

objetos[ID_NARANJA].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_NARANJA)].esta_activo = 1;

objetos[ID_NEGRO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_NEGRO)].esta_activo = 1;

objetos[ID_BLANCO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BLANCO)].esta_activo = 1;

objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}





