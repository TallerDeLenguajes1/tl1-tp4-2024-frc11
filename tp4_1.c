#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; // Numérico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

// FUNCIONES
Nodo *crearListaVacia() {
    return NULL;
}

Nodo *crearNodo(Tarea valor) {
    Nodo *NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    NuevoNodo->T = valor;
    NuevoNodo->Siguiente = NULL;
    return NuevoNodo;
}

void insertarNodoPrincipio(Nodo **Start, Nodo *NuevoNodo) {
    NuevoNodo->Siguiente = *Start;
    *Start = NuevoNodo;
}

void insertarNodoFinal(Nodo *Start, Nodo *NuevoNodo) {
    Nodo *aux = Start;
    while(aux->Siguiente != NULL) {
        aux = aux->Siguiente;
    }
    aux->Siguiente = NuevoNodo;
}

Nodo *buscarNodo(Nodo *Start, int IDbuscado) {
    Nodo *aux = Start;
    while(aux && aux->T.TareaID != IDbuscado) {
        aux = aux->Siguiente;
    }
    return aux;
}

void EliminarNodo(Nodo **Start, int IDbuscado) {
    Nodo **aux = Start;

    while (*aux != NULL && (*aux)->T.TareaID != IDbuscado) {
        aux = &(*aux)->Siguiente;
    }

    if (*aux) {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        free(temp);
    }
}

void cargarTarea(Tarea *valor, int *TareaIDanterior) { // Corrección: Pasar un puntero a TareaIDanterior para modificar el valor original.
    valor->TareaID = (*TareaIDanterior)++;
    int NumerodeTarea = *TareaIDanterior - 999;
    char *BUFF = (char *)malloc(100 * sizeof(char));
    printf("Ingrese la descripcion de la tarea nro %d:", NumerodeTarea);
    fgets(BUFF, 100, stdin);
    BUFF[strcspn(BUFF, "\n")] = 0;
    valor->Descripcion = (char *)malloc((strlen(BUFF) + 1) * sizeof(char));
    strcpy(valor->Descripcion, BUFF);
    valor->Duracion = rand() % 89 + 10;
    free(BUFF);
}

int main() {
    srand(time(NULL));
    printf("Ingrese la cantidad de tareas a realizar: \n");
    int cantidad = 0, ID = 1000;
    scanf("%d", &cantidad);
    Nodo *ListaTareasPendientes = crearListaVacia();
    Nodo *ListaTareasRealizadas = crearListaVacia();
    Tarea *tareas = malloc(cantidad * sizeof(Tarea)); // Corrección: Cambiar el nombre de la variable a "tareas" para evitar la confusión con el tipo de datos "Tarea".
    Nodo **nodos = malloc(cantidad * sizeof(Nodo *));
    for(int i = 0; i < cantidad; i++) {
        cargarTarea(&tareas[i], &ID); // Corrección: Pasar la dirección de ID para modificar el valor original.
        nodos[i] = crearNodo(tareas[i]);
        insertarNodoFinal(ListaTareasPendientes, nodos[i]);
    }

    // No olvides liberar la memoria que has asignado con malloc.
    for(int i = 0; i < cantidad; i++) {
        free(tareas[i].Descripcion);
    }
    free(tareas);
    free(nodos);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int TareaID;
    char Descripcion[100];
    int Duracion;
} Tarea;

typedef struct Nodo {
    Tarea tarea;
    struct Nodo *siguiente;
} Nodo;

Nodo* crearNodo(Tarea tarea) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->tarea = tarea;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void insertarNodoFinal(Nodo** cabeza, Tarea tarea) {
    Nodo* nuevoNodo = crearNodo(tarea);
    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        Nodo* actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

void moverTareaRealizada(Nodo** pendientes, Nodo** realizadas, int TareaID) {
    Nodo* actual = *pendientes;
    Nodo* previo = NULL;
    while (actual != NULL && actual->tarea.TareaID != TareaID) {
        previo = actual;
        actual = actual->siguiente;
    }
    if (actual != NULL) {
        if (previo == NULL) {
            *pendientes = actual->siguiente;
        } else {
            previo->siguiente = actual->siguiente;
        }
        actual->siguiente = NULL;
        insertarNodoFinal(realizadas, actual->tarea);
        free(actual);
    }
}

void listarTareas(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("Tarea ID: %d, Descripcion: %s, Duracion: %d\n", actual->tarea.TareaID, actual->tarea.Descripcion, actual->tarea.Duracion);
        actual = actual->siguiente;
    }
}

void buscarTarea(Nodo* cabeza, int TareaID) {
    Nodo* actual = cabeza;
    while (actual != NULL && actual->tarea.TareaID != TareaID) {
        actual = actual->siguiente;
    }
    if (actual != NULL) {
        printf("Tarea encontrada: ID: %d, Descripcion: %s, Duracion: %d\n", actual->tarea.TareaID, actual->tarea.Descripcion, actual->tarea.Duracion);
    } else {
        printf("Tarea no encontrada.\n");
    }
}

int main() {
    Nodo* tareasPendientes = NULL;
    Nodo* tareasRealizadas = NULL;

    // Aquí puedes agregar el código para interactuar con el usuario, por ejemplo:
    // - Solicitar al usuario que ingrese tareas pendientes.
    // - Permitir al usuario mover tareas de la lista de pendientes a la lista de realizadas.
    // - Listar todas las tareas pendientes y realizadas.
    // - Permitir al usuario buscar tareas por ID.

    return 0;
}
