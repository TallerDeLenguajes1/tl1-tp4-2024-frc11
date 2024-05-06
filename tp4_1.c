#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
}Tarea;
typedef struct Nodo{
Tarea T;
struct Nodo *Siguiente;
}Nodo;

/*Cada empleado tiene un listado de tareas a realizar y debe indicar en el sistema si fueron
realizadas o no. Para ello deberá crear dos listas enlazadas: una para las tareas pendientes y
otra para las tareas realizadas. Cada vez que se marque una tarea como realizada deberá
mover la tarea de la lista de tareas pendientes a la lista de tareas realizadas.
*/
//DECLARACION FUNCIONES
Nodo *crearNodo(Tarea *t);
Nodo *crearListaVacia();
Tarea *crearTarea(int TareaID);
void insertarNodoP(Nodo **Start, Nodo *nuevoNodo);
void insertarNodoF(Nodo *Start, Nodo *nuevoNodo);
void moverPorID(Nodo **Start1, Nodo **Start2, int TareaID);
void mostrarLista(Nodo *Start);
void formaParte(Nodo **Start1,Nodo **Start2,int IDbuscado,char *palabraClave);
int main(){
    Nodo *StartTPendientes=crearListaVacia();
    Nodo *StartTRealizadas=crearListaVacia();
    printf("Ingrese la primera Tarea \n");
    int TareaID=1000;
        Tarea *TareaNuevo=crearTarea(TareaID);
        Nodo *NodoNuevo=crearNodo(TareaNuevo);
        insertarNodoP(&StartTPendientes,NodoNuevo);
    int sigue;
    fflush(stdin);
    printf("Desea ingresar otra tarea? SI=1 NO=0 \n");
    scanf("%d",&sigue);
    while (sigue==1){
        TareaID++;
        Tarea *TareaNuevo=crearTarea(TareaID);
        fflush(stdin);
        Nodo *NodoNuevo=crearNodo(TareaNuevo);
        insertarNodoF(StartTPendientes,NodoNuevo);
        fflush(stdin);
        printf("Desea ingresar otra tarea? SI=1 NO=0 \n");
        scanf("%d",&sigue);
    }
    mostrarLista(StartTPendientes);
    int sigue2, idMov;
    printf("Desea mover un elemento a las tareas relizadas? SI=1 NO=0 \n");
    scanf("%d",&sigue2);
    while(sigue2==1){
        printf("Ingrese el ID de la tarea: \n");
        scanf("%d",&idMov);
        moverPorID(&StartTPendientes,&StartTRealizadas,idMov);
        printf("Desea ingresar otra tarea? SI=1 NO=0 \n");
        scanf("%d",&sigue2);
    }
    mostrarLista(StartTRealizadas);
    int sigue3;
    printf("Desea buscar un elemento por ID o Palabra clave? SI=1 NO=0 \n");
    scanf("%d",&sigue3);
    if(sigue3==1){
        char palabraClave[100];
        int IDbuscado;
        printf("Ingrese la palabra clave \n");
        fgets(palabraClave,sizeof(palabraClave),stdin);
        printf("Ingrese el ID a buscar \n");
        scanf("%d",&IDbuscado);
        formaParte(&StartTPendientes,&StartTRealizadas,IDbuscado,&palabraClave);
    }



    


}
//IMPLEMENTACION FUNCIONES
Nodo *crearNodo(Tarea *t){
    Nodo *nuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T=*t;
    nuevoNodo->Siguiente=NULL;
    return nuevoNodo;
}
Nodo *crearListaVacia(){
    return NULL;
}
Tarea *crearTarea(int TareaID){
    int duracion;
    char descripcion[100];
    Tarea *TareaNueva = (Tarea*)malloc(sizeof(Tarea));
    TareaNueva->TareaID = TareaID++;
    fflush(stdin);
    printf("Ingrese la descripcion de la tarea: \n");
    fgets(descripcion, sizeof(descripcion), stdin);
    TareaNueva->Descripcion = strdup(descripcion); // Duplica la cadena
    fflush(stdin);
    printf("Ingrese la duracion: \n");
    scanf("%d", &duracion);
    TareaNueva->Duracion = duracion;
    return TareaNueva;
}

void insertarNodoP(Nodo **Start, Nodo *nuevoNodo){
    nuevoNodo->Siguiente=*Start;
    *Start=nuevoNodo;
}
void insertarNodoF(Nodo *Start, Nodo *nuevoNodo){
    Nodo *aux=Start;
    while(aux->Siguiente){
        aux=aux->Siguiente;
    }
    aux->Siguiente=nuevoNodo;
}
void moverPorID(Nodo **Start1, Nodo **Start2, int TareaID) {
    Nodo *temp = *Start1, *prev;
    if (temp != NULL && temp->T.TareaID == TareaID) {
        *Start1 = temp->Siguiente;
    } else {
        while (temp != NULL && temp->T.TareaID != TareaID) {
            prev = temp;
            temp = temp->Siguiente;
        }
        if (temp == NULL) return;
        prev->Siguiente = temp->Siguiente;
    }
    temp->Siguiente = NULL;
    if (*Start2 == NULL) {
        *Start2 = temp;
    } else {
        Nodo *last = *Start2;
        while (last->Siguiente != NULL) {
            last = last->Siguiente;
        }
        last->Siguiente = temp;
    }
}
void mostrarLista(Nodo *Start) {
    Nodo *temp = Start;
    while(temp != NULL) {
        printf("Tarea ID: %d\n", temp->T.TareaID);
        printf("Descripcion: %s\n", temp->T.Descripcion);
        printf("Duracion: %d\n", temp->T.Duracion);
        printf("-----------------\n");
        temp = temp->Siguiente;
    }
}
void formaParte(Nodo **Start1,Nodo **Start2,int IDbuscado,char *palabraClave){
    Nodo *aux=Start1;
    printf("Buscando en la lista de Pendientes... \n");
    while(aux!=NULL){
        if(aux->T.TareaID== TareaID || strstr(aux->Descripcion,palabraClave)!=NULL){
            printf("Tarea ID: %d\n", temp->T.TareaID);
            printf("Descripcion: %s\n", temp->T.Descripcion);
            printf("Duracion: %d\n", temp->T.Duracion);
            printf("-----------------\n");
        }
        aux=aux->Siguiente;
    }
    aux=Start2;
    printf("Buscando en la lista de Realizados... \n");
    while(aux!=NULL){
        if(aux->T.TareaID== TareaID || strstr(aux->Descripcion,palabraClave)!=NULL){
            printf("Tarea ID: %d\n", temp->T.TareaID);
            printf("Descripcion: %s\n", temp->T.Descripcion);
            printf("Duracion: %d\n", temp->T.Duracion);
            printf("-----------------\n");
        }
        aux=aux->Siguiente;
    }



}
