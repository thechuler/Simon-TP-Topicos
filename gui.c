#include "gui.h"
#include "variables_globales.h"


//-----Abre el explorador de archivos de windows y recupera la ruta seleccionada
char* AbrirExploradorYRecuperarRuta(void) {
    OPENFILENAME ofn;       //<----- Estructura del dialogo, esta en windows.h
    char szFile[260];       //<----donde se guardaria la ruta

    ZeroMemory(&ofn, sizeof(ofn));
    ZeroMemory(szFile, sizeof(szFile));  //<------ Limpia para evitar basura

    ofn.lStructSize = sizeof(ofn); //<-----Tamaño de la structura
    ofn.hwndOwner = NULL;   // Ventana padre (NULL = consola)
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0'; //<--- Lo inicializa vacio
    ofn.nMaxFile = sizeof(szFile);  //<--- tam maximo
    ofn.lpstrFilter =
        "Archivos DAT (*.dat)\0*.dat\0"
        "Todos los archivos (*.*)\0*.*\0";   //<----Este filtro hace que aparezcan los binarios en la busqueda


    ofn.nFilterIndex = 1;       //<--- orden de los filtros

    ofn.lpstrFileTitle = NULL;  //<--- No me interesa guardar solo el nombre del archivo
    ofn.nMaxFileTitle = 0;

    ofn.lpstrInitialDir = "saves"; //<----  Empieza en la carpeta saves

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //<------- condicional, el archivo debe existir al igual que la ruta


    if (GetOpenFileName(&ofn)) {   //<--- Abre la ventana y si el user eligio un archivo lo guarda
        char* ruta = (char*)malloc(strlen(ofn.lpstrFile) + 1); //<---Reserva memoria, se liberaria cuando se llame a la func
        if (ruta) strcpy(ruta, ofn.lpstrFile);
        return ruta;
    } else {
        return NULL;
    }

}


//-------Comprueba si un boton fue clickeado y activa su funcion asociada
void BotonesActivosComprobarInteraccion( int x, int y)
{
    SDL_Point click = {x, y};

    for(int i = 0; i < CANTIDAD_BOTONES; i++) //<---Comprueba todos los botones 1 por 1
    {
        if(botones[i].esta_activo) //<-- Solo si el boton esta activo
        {
            if(SDL_PointInRect(&click,&botones[i].imagen->configs)) //<-- Si el click fue en la misma pos que el boton
            {
                botones[i].imagen->frame_actual =0; //<--se reinicia su frame
                botones[i].imagen->debe_animar = 1; //<--- Anima el boton
                if(i>=ID_FONDO && i<=ID_BLANCO){ //<---Si son las notas,
                botones[i].accion(botones[i].id); //<--Les pasa como parametro su id
                }else{
                botones[i].accion(); //<--Si no simplemente llama a su funcion
                }
                return ;
            }
        }
    }

}




//-------Limpia todos los objetos de la pantalla
void PantallasLimpiar()
{
    for(int i = 0; i < CANTIDAD_OBJETOS; i++)
    {
        objetos[i].debe_Renderizar = 0; //<---Desactiva render
        objetos[i].debe_animar = 0;  //<---Y animacion
    }
}


//--------Bloquea todos los botones de la pantalla
void PantallaBloquearBotones()
{
    for(int i = 0; i < CANTIDAD_BOTONES; i++)
    {
        botones[i].esta_activo = 0; //<---Desactiva la funcionalidad de los botones
    }
}


//--------Obtiene un boton por su id asignada
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




//-------------Setea el menu principal
void PantallasMenuPrincipal(){
PantallaBloquearBotones(); //<--- Bloquea botones
PantallasLimpiar();   //<---Limpia render

//Objetos en pantalla:
objetos[ID_BOTON_SALIR].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_SALIR)].esta_activo = 1;

objetos[ID_BOTON_CONFIG].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_CONFIG)].esta_activo = 1;

objetos[ID_BOTON_MODO].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_MODO)].esta_activo = 1;

objetos[ID_SLIME].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_SLIME)].esta_activo = 1;

objetos[ID_TOP].debe_Renderizar = 1;
objetos[ID_FONDO].debe_Renderizar = 1;

}




//-----Setea la pantalla configs
void PantallasConfigs(){
PantallaBloquearBotones();
PantallasLimpiar();

//Objetos en pantalla:
objetos[ID_FONDO].debe_Renderizar = 1;

objetos[ID_DURACION].debe_Renderizar = 1;
objetos[ID_NOTAS].debe_Renderizar = 1;


objetos[ID_SUMAR_NOTAS].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_SUMAR_NOTAS)].esta_activo = 1;


objetos[ID_RESTAR_NOTAS].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_RESTAR_NOTAS)].esta_activo = 1;


objetos[ID_SUMAR_DURACION].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_SUMAR_DURACION)].esta_activo = 1;


objetos[ID_RESTAR_DURACION].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_RESTAR_DURACION)].esta_activo = 1;





objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;

}



//---Setea la pantalla Modos de juego
void PantallasModos(){
PantallaBloquearBotones();
PantallasLimpiar();


//Objetos en pantalla:
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

objetos[ID_FONDO].debe_Renderizar = 1;
//Objetos en pantalla:


for(int i = 0; i<8;i++){
    if(notas_activas[i] == 1){
    botones[BotonesObtenerPorId(i+1)].esta_activo = 1;
    }
}

objetos[ID_AZUL].debe_Renderizar = 1;
objetos[ID_ROJO].debe_Renderizar = 1;
objetos[ID_VERDE].debe_Renderizar = 1;
objetos[ID_AMARILLO].debe_Renderizar = 1;
objetos[ID_VIOLETA].debe_Renderizar = 1;
objetos[ID_NARANJA].debe_Renderizar = 1;
objetos[ID_NEGRO].debe_Renderizar = 1;
objetos[ID_BLANCO].debe_Renderizar = 1;
objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
objetos[ID_PUNTAJE].debe_Renderizar = 1;
}


//------------Setea la pantalla Desafio
void PantallasDesafio(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_FONDO].debe_Renderizar = 1;
for(int i = 0; i<8;i++){
    if(notas_activas[i] == 1){
    botones[BotonesObtenerPorId(i+1)].esta_activo = 1;
    }
}


//Objetos en pantalla:
objetos[ID_AZUL].debe_Renderizar = 1;


objetos[ID_ROJO].debe_Renderizar = 1;


objetos[ID_VERDE].debe_Renderizar = 1;


objetos[ID_AMARILLO].debe_Renderizar = 1;


objetos[ID_VIOLETA].debe_Renderizar = 1;


objetos[ID_NARANJA].debe_Renderizar = 1;


objetos[ID_NEGRO].debe_Renderizar = 1;


objetos[ID_BLANCO].debe_Renderizar = 1;



objetos[ID_BOTON_GUARDAR].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_GUARDAR)].esta_activo = 1;

objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}



//---------Setea la pantalla Mozart
void PantallasMozart(){
PantallaBloquearBotones();
PantallasLimpiar();
objetos[ID_FONDO].debe_Renderizar =1;

for(int i = 0; i<8;i++){
    if(notas_activas[i] == 1){
    botones[BotonesObtenerPorId(i+1)].esta_activo = 1;
    }
}


//Objetos en pantalla:
objetos[ID_AZUL].debe_Renderizar = 1;


objetos[ID_ROJO].debe_Renderizar = 1;


objetos[ID_VERDE].debe_Renderizar = 1;


objetos[ID_AMARILLO].debe_Renderizar = 1;


objetos[ID_VIOLETA].debe_Renderizar = 1;


objetos[ID_NARANJA].debe_Renderizar = 1;


objetos[ID_NEGRO].debe_Renderizar = 1;


objetos[ID_BLANCO].debe_Renderizar = 1;

objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;
botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}


//---------Setea la pantalla Mozart
void PantallasMozartWin(){
PantallaBloquearBotones();
PantallasLimpiar();

objetos[ID_FONDO].debe_Renderizar =1;
objetos[ID_WIN].debe_Renderizar = 1;
objetos[ID_BOTON_VOLVER].debe_Renderizar = 1;

botones[BotonesObtenerPorId(ID_BOTON_VOLVER)].esta_activo = 1;
}






