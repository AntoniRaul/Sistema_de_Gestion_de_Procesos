#include <iostream>
#include <string>
#include <fstream>

#define MAX 5

using namespace std;



// Lista enlazada para almacenar los procesos

struct Proceso { // Estructura que representa un proceso
    // Atributos del proceso
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente; // Puntero al siguiente proceso en la lista

    // Constructor para inicializar un nuevo proceso
    Proceso(int ID, string Nombre, int Prioridad) {
        id = ID;
        nombre = Nombre;
        prioridad = Prioridad;
        siguiente = NULL; // Inicializa el puntero siguiente como NULL
    }
};


// Pila de memoria para los procesos

Proceso* pila[MAX]; // Arreglo que representa la pila de memoria
int tope = -1; // Variable que indica el índice del último elemento en la pila

// Funcion para agregar elementos a la pila

void insertar(Proceso*& listaProcesos){
    if (tope == MAX - 1) {
        cout << "Memoria llena. No se puede insertar mas elementos." << endl;
    } else {
        int id2;
        cout << "Ingrese el ID del proceso a asignar a la memoria: "; cin >> id2;
        Proceso* temp = listaProcesos; // Crea un puntero temporal para recorrer la lista de procesos
        while (temp != NULL) { // Recorre la lista de procesos
            if (temp->id == id2) { // Verifica si el ID del proceso coincide con el ID ingresado
                pila[++tope] = temp; // Agrega el proceso a la pila
                cout << "Proceso con ID " << id2 << " agregado a la memoria." << endl;
                return; // Sale de la función una vez que se ha agregado el proceso
            }
            temp = temp->siguiente; // Avanza al siguiente proceso en la lista
        }
        cout << "No se encontró un proceso con ese ID." << endl;
    }
}

// Funcion para eliminar procesos de la pila

void eliminarDePila() {
    if (tope == -1) {
        cout << "La pila de memoria está vacía. No se puede eliminar ningún proceso." << endl;
        return;
    }
    cout << "Procesos en la pila de memoria:" << endl;
    for (int i = 0; i <= tope; i++) {
        cout << "ID: " << pila[i]->id << ", Nombre: " << pila[i]->nombre << ", Prioridad: " << pila[i]->prioridad << endl;
    }
    int idEliminar;
    cout << "Ingrese el ID del proceso que desea quitar de la pila: ";
    cin >> idEliminar;

    int pos = -1;
    for (int i = 0; i <= tope; i++) {
        if (pila[i]->id == idEliminar) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        cout << "No se encontró un proceso con ese ID en la pila." << endl;
        return;
    }
    Proceso* procesoEliminado = pila[pos];
    // Desplazar los elementos para llenar el hueco
    for (int i = pos; i < tope; i++) {
        pila[i] = pila[i + 1];
    }
    tope--;
    cout << "Proceso con ID " << procesoEliminado->id << " eliminado de la memoria." << endl;
}

// Funcion para liberar la memoria de los procesos en la pila

void liberarMemoria() {
    if (tope == -1) {
        cout << "La pila de memoria está vacía. No hay procesos para liberar." << endl;
        return;
    }
    // Solo vacía la pila, no elimina los procesos de la lista enlazada
    tope = -1;
    cout << "Todos los procesos han sido quitados de la memoria (pila) exitosamente." << endl;
}

// Funcion para visualizar los procesos en la pila

void visualizarPila() {
    if (tope == -1) { // Verifica si la pila está vacía
        cout << "La pila de memoria está vacía." << endl; // Mensaje si la pila está vacía
    } else {
        cout << "Procesos en la pila de memoria:" << endl;
        for (int i = 0; i <= tope; i++) { // Recorre la pila e imprime los IDs de los procesos
            cout << "ID: " << pila[i]->id << ", Nombre: " << pila[i]->nombre << ", Prioridad: " << pila[i]->prioridad << endl;
        }
    }
}

// Función para agregar un nuevo proceso al final de la lista

void agregarAlFinal(Proceso*& listaProcesos, int ID, string Nombre, int Prioridad) {
    Proceso *nuevoProceso = new Proceso(ID, Nombre, Prioridad); // Crea un nuevo proceso con los datos proporcionados

    if (listaProcesos == NULL) { // Verifica si la lista está vacía
        listaProcesos = nuevoProceso; // Si está vacía, el nuevo proceso se convierte en el primer elemento de la lista
    } else {
        Proceso* temp = listaProcesos; // Crea un puntero temporal para recorrer la lista
        while (temp->siguiente) { // Recorre la lista hasta el final
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoProceso; // Asigna el nuevo proceso al final de la lista
        cout << "Proceso agregado al final de la lista.\n";
    }
}

// Funcion para imprimir todos los procesos en la lista

void imprimirProcesos(Proceso* listaProcesos) {
    Proceso* temp = listaProcesos; // Crea un puntero temporal para recorrer la lista

    if (!temp) { // Verifica si la lista está vacía
        cout << "No hay procesos registrados.\n"; // Mensaje si la lista está vacía
        return;
    }
    cout << "Lista de procesos:\n";
    while (temp != NULL) { // Recorre la lista e imprime los datos de cada proceso
        cout << "ID: " << temp->id << ", Nombre: " << temp->nombre << ", Prioridad: " << temp->prioridad << endl;
        temp = temp->siguiente; // Avanza al siguiente proceso
    }
    cout << endl;
}

void eliminarProceso(Proceso*& listaProcesos, int id) {
    Proceso* temp = listaProcesos;
    // Creamos un puntero que buscara el proceso que indiquemos
    Proceso* anterior = NULL;
    // Creamos otro puntero que guardará el nodo anterior que deseqamos eliminar 
    while (temp && temp->id != id) {
        anterior = temp;
        temp = temp->siguiente;
    }
    // Con esto podemos eliminar un proceso de la lista cuando el ID coincide
    if (!temp) {
        cout << "Proceso no encontrado.\n";
        return;
    }
    // Esto informa cuando no se encuentre ningun proceso con ese ID y termina la función
    if (!anterior) listaProcesos = temp->siguiente;
    else anterior->siguiente = temp->siguiente;
    delete temp;
    // Esto hace que libere la memoria del proceso eliminado
    cout << "Proceso eliminado.\n";
}
void buscarProceso(Proceso*& listaProcesos, int id) {
    Proceso* temp = listaProcesos;
    // Indicamos que comienza desde el inicio de la lista
    while (temp) {
        if (temp->id == id) {
            cout << "ID: " << temp->id << ", Nombre: " << temp->nombre << ", Prioridad: " << temp->prioridad << endl;
            return;
        }
        temp = temp->siguiente;
    }
    // Cuando encuentre el ID que busquemos lo imprimirá
    cout << "Proceso no encontrado.\n";
    // Nos informará si no lo encuentra
}

void modificarProceso(Proceso*& listaProcesos, int id) {
    Proceso* temp = listaProcesos;
    // Creamos un puntero que buscara el proceso que indiquemos
    while (temp) { // Recorremos la lista de procesos
        if (temp->id == id) { // Verificamos si el ID del proceso coincide con el ID buscado
            // Si encontramos el proceso, solicitamos los nuevos datos
            cout << "Ingrese el nuevo nombre del proceso: ";
            cin >> temp->nombre;
            cout << "Ingrese la nueva prioridad del proceso: ";
            cin >> temp->prioridad;
            cout << "Proceso modificado exitosamente.\n";
            return;
        }
        temp = temp->siguiente; // Avanzamos al siguiente proceso en la listaS
    }
    // Cuando encuentre el ID que busquemos lo modificará
    cout << "Proceso no encontrado.\n";
    // Nos informará si no lo encuentra
}

void Menu() {
    cout << "\n***Menu de Gestion***" << endl;
    cout << "[1]. Gestion de Procesos" << endl;
    cout << "[2]. Gestion de Memoria" << endl;
    cout << "[3]. Gestion de CPU" << endl;
    cout << "[4]. Salir" << endl;
}

void Menu2() {
    cout << "\n***Gestion de Procesos***" << endl;
    cout << "[1]. Registrar proceso" << endl;
    cout << "[2]. Imprimir procesos" << endl;
    cout << "[3]. Buscar procesos" << endl;
    cout << "[4]. Eliminar proceso" << endl;
    cout << "[5]. Modificar proceso" << endl;
    cout << "[6]. Salir" << endl;
    cout << "*************************" << endl;
}

void Menu3() {
    cout << "\n***Gestion de Memoria***" << endl;
    cout << "[1]. Asignar a memoria" << endl;
    cout << "[2]. Eliminar de memoria" << endl;
    cout << "[3]. Liberar memoria" << endl;
    cout << "[4]. Visualizar memoria" << endl;
    cout << "[5]. Salir" << endl;
    cout << "*************************" << endl;
}

void Menu4() {
    cout << "\n***Gestion de CPU***" << endl;
    cout << "[1]. Verificar orden de ejecucion" << endl;
    cout << "[2]. Ejecutar procesos" << endl;
    cout << "[3]. Salir" << endl;
    cout << "*************************" << endl;
}

int main() {

    Proceso* listaProcesos = NULL; // Inicializa la lista de procesos como vacía
    
    int op, op1, op2, op3, op4, NumEl, id, prioridad;
    string nombre;
    
    do {
        
        Menu(); // Muestra el menú de opciones al usuario

        do {

            cout << "Ingrese una opcion: "; cin >> op; // Solicita al usuario que ingrese una opción
            if (op < 1 || op > 4) { // Verifica si la opción es válida
                cout << "Opcion invalida. Por favor, intente de nuevo." << endl; // Mensaje de error si la opción no es válida
            }

        } while (op < 1 || op > 4); // Bucle para asegurar que la opción ingresada sea válida

        switch (op) { // Estructura de control que maneja las opciones del menú
            case 1:
                do {
                    Menu2(); // Muestra el menú de gestión de procesos

                    do {

                        cout << "Ingrese una opcion: "; cin >> op2; // Solicita al usuario que ingrese una opción

                        if (op2 < 1 || op2 > 6) { // Verifica si la opción es válida
                            cout << "Opcion invalida. Por favor, intente de nuevo." << endl; // Mensaje de error si la opción no es válida
                        }

                    } while (op2 < 1 || op2 > 6); // Bucle para asegurar que la opción ingresada sea válida

                    switch (op2) {
                        case 1:
                            // Pedimos al usuario cuantos procesos desea registrar
                            cout << "Cuantos procesos desea registrar? "; cin >> NumEl;

                            // Ingresamos los datos de cada proceso
                            for (int i = 0; i < NumEl; i++) {
                            cout << "\nRegistro del proceso " << (i + 1) << endl;
                            // Pedimos al usuario que ingrese los datos del proceso
                            cout << "Ingrese el ID del proceso: "; cin >> id;
                            cout << "Ingrese el nombre del proceso: "; cin >> nombre;
                            cout << "Ingrese la prioridad del proceso: "; cin >> prioridad;

                            // Llamamos a la función para agregar el proceso a la lista
                            agregarAlFinal(listaProcesos, id, nombre, prioridad);
                            }
                            break;
                        case 2:
                            cout << "Imprimiendo procesos registrados..." << endl;
                            imprimirProcesos(listaProcesos);
                            break;
                        case 3:
                            cout << "Ingrese el ID del proceso a buscar: "; cin >> id;
                            buscarProceso(listaProcesos, id);
                            break;
                        case 4:
                            cout << "Ingrese el ID del proceso a eliminar: "; cin >> id;
                            eliminarProceso(listaProcesos, id);
                            break;
                        case 5:
                            cout << "Ingrese el ID del proceso a modificar: "; cin >> id;
                            modificarProceso(listaProcesos, id);
                            break;
                        case 6:
                            cout << "Saliendo del menu de gestion de procesos." << endl;
                            break;
                    }
                
                } while (op2 != 6); // Bucle para continuar mostrando el menú de gestión de procesos hasta que se elija salir
                
                break;
            case 2:
                do {
                    Menu3();
                    do {
                        cout << "Ingrese una opcion: "; cin >> op3;
                        if (op3 < 1 || op3 > 5) {
                            cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                        }
                    } while (op3 < 1 || op3 > 5);
                    switch (op3) {
                        case 1:
                            cout << "\n" << endl;
                            imprimirProcesos(listaProcesos);
                            insertar(listaProcesos);
                            break;
                        case 2:
                            eliminarDePila();
                            break;
                        case 3:
                            liberarMemoria();
                            cout << "Memoria liberada." << endl;
                            break;
                        case 4:
                            visualizarPila();
                            break;
                        case 5:
                            cout << "Saliendo del menu de gestion de memoria." << endl;
                    }
                } while (op3 != 5);
                break;
            case 3:
                do {
                    Menu4();
                    do {
                        cout << "Ingrese una opcion: "; cin >> op4;
                        if (op4 < 1 || op4 > 3) {
                            cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                        }
                    } while (op4 < 1 || op4 > 3);
                    switch (op4) {
                        case 1:
                            cout << "Verificando orden de ejecucion..." << endl;
                            break;
                        case 2:
                            cout << "Ejecutando procesos..." << endl;
                            break;
                        case 3:
                            cout << "Saliendo del menu de gestion de memoria." << endl;
                            break;
                    }
                } while (op4 != 3);
                break;
            case 4:
                cout << "Saliendo del sistema de gestion de procesos." << endl;
                break;
        }

    } while (op != 4);

}
