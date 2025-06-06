#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> // Para usar funciones de Windows como Sleep()
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

// Cola para gestionar la memoria

Proceso* cola[MAX]; // Arreglo que representa la cola de memoria
int frente = -1; // Índice del primer elemento en la cola
int final = -1; // Índice del último elemento en la cola

// Funcion para encolar elementos de la memoria

void encolar() {
    if (tope == -1) { // Verifica si la pila está vacía
        cout << "La pila de memoria está vacía. No se puede encolar." << endl;
        return;
    }
    Proceso* nuevo = pila[tope]; // Toma el proceso del tope de la pila
    
    if (frente == -1) { // Verifica si la cola está vacía
        frente = final = 0; // Si la cola está vacía, inicializa el frente
        cola[0] = nuevo; // Agrega el nuevo proceso al frente de la cola
        return;
    } 
    
    int pos = frente; // Comienza desde el frente de la cola
    while (pos <= final && cola[pos]->prioridad >= nuevo->prioridad) { // Compara las prioridades de los procesos
        pos++; // Encuentra la posición correcta para insertar el nuevo proceso según su prioridad
    }

    // Desplazar los elementos para hacer espacio
    for (int i = final + 1; i > pos; i--) { // Organiza la cola
        cola[i] = cola[i - 1]; // Mueve los elementos hacia la derecha
    }
    cola[pos] = nuevo; // Inserta el nuevo proceso en la posición encontrada
    final++; // Incrementa el índice del final de la cola
}

// Funcion que elimina elementos de la cola por ID

void eliminarDeColaPorID(int idEliminar) {
    if (frente == -1) { // Verifica si la cola está vacía
        return;
    }
    int pos = -1; // Variable para almacenar la posición del proceso a eliminar
    for (int i = frente; i <= final; i++) { // Recorre la cola desde el frente hasta el final
        if (cola[i]->id == idEliminar) { // Busca el proceso con el ID especificado
            pos = i; // Guarda la posición del proceso a eliminar
            break;
        }
    }
    if (pos == -1) return; // Si no se encontró el proceso, sale de la función
    for (int i = pos; i < final; i++) { // Desplaza los elementos hacia la izquierda para llenar el hueco
        cola[i] = cola[i + 1]; // Mueve los elementos hacia la izquierda
    }
    final--; // Decrementa el índice del final de la cola
    if (final < frente) frente = final = -1; // Si la cola queda vacía, reinicia los índices
}

// Funcion para borrar todos los elementos de la cola

void vaciarCola() {
    frente = final = -1; // Reinicia los índices de la cola para indicar que está vacía
}

// Ejecutar Procesos en la cola

void ejecutarProcesosEnCola() {
    if (frente == -1) { // Verifica si la cola está vacía
        cout << "No hay procesos en la cola para ejecutar." << endl;
        return;
    }
    cout << "Ejecutando procesos en orden de prioridad:" << endl;
    while (frente != -1) { // Mientras haya procesos en la cola
        cout << "Ejecutando -> ID: " << cola[frente]->id // Imprime el ID del proceso que se está ejecutando
             << ", Nombre: " << cola[frente]->nombre // Imprime el nombre del proceso
             << ", Prioridad: " << cola[frente]->prioridad << endl; // Imprime la prioridad del proceso
        Sleep(1000); // Pausa de 1 segundo
        if (frente == final) { // Verifica si es el último proceso en la cola
            frente = final = -1; // Cola vacía
        } else {
            frente++; // Avanza al siguiente proceso en la cola
        }
    }
    cout << "Todos los procesos han sido ejecutados." << endl;
}

//  Funcion para visualizar la cola de memoria

void visualizarCola() {
    if (frente == -1) { // Verifica si la cola está vacía
        cout << "La cola de CPU está vacía." << endl;
        return;
    } else {
        cout << "Orden de ejecucion" << endl;
        for (int i = frente; i <= final; i++) { // Recorre la cola desde el frente hasta el final
            cout << "ID: " << cola[i]->id << ", Nombre: " << cola[i]->nombre << ", Prioridad: " << cola[i]->prioridad << endl; // Imprime los detalles de cada proceso
        }
    }
}

// Funcion para agregar elementos a la pila

void insertar(Proceso*& listaProcesos){
    if (tope == MAX - 1) { // Verifica si la pila está llena
        cout << "Memoria llena. No se puede insertar mas elementos." << endl;
    } else {
        int id2;
        cout << "Ingrese el ID del proceso a asignar a la memoria: "; cin >> id2;
        Proceso* temp = listaProcesos; // Crea un puntero temporal para recorrer la lista de procesos
        while (temp != NULL) { // Recorre la lista de procesos
            if (temp->id == id2) { // Verifica si el ID del proceso coincide con el ID ingresado
                pila[++tope] = temp; // Agrega el proceso a la pila
                cout << "Proceso con ID " << id2 << " agregado a la memoria." << endl; 
                encolar(); // Llama a la función para encolar el proceso en la cola de memoria
                return; // Sale de la función una vez que se ha agregado el proceso
            }
            temp = temp->siguiente; // Avanza al siguiente proceso en la lista
        }
        cout << "No se encontró un proceso con ese ID." << endl;
    }
}

// Funcion para eliminar procesos de la pila

void eliminarDePila() {
    if (tope == -1) { // Verifica si la pila está vacía
        cout << "La pila de memoria está vacía. No se puede eliminar ningún proceso." << endl;
        return;
    }
    cout << "Procesos en la pila de memoria:" << endl;
    for (int i = 0; i <= tope; i++) { // Recorre la pila e imprime los IDs de los procesos
        cout << "ID: " << pila[i]->id << ", Nombre: " << pila[i]->nombre << ", Prioridad: " << pila[i]->prioridad << endl;
    }
    int idEliminar;
    cout << "Ingrese el ID del proceso que desea quitar de la pila: ";
    cin >> idEliminar;

    int pos = -1; // Variable para almacenar la posición del proceso a eliminar
    for (int i = 0; i <= tope; i++) { // Recorre la pila desde el inicio hasta el tope
        if (pila[i]->id == idEliminar) { // Busca el proceso con el ID especificado
            pos = i; // Guarda la posición del proceso a eliminar
            break;
        }
    }
    if (pos == -1) {
        cout << "No se encontró un proceso con ese ID en la pila." << endl; // Mensaje si no se encuentra el proceso
        return;
    }
    Proceso* procesoEliminado = pila[pos]; // Guarda el proceso que se va a eliminar
    // Desplazar los elementos para llenar el hueco
    for (int i = pos; i < tope; i++) { // Desplaza los elementos hacia la izquierda
        pila[i] = pila[i + 1]; // Mueve los elementos hacia la izquierda
    }
    tope--; // Decrementa el índice del tope de la pila
    cout << "Proceso con ID " << procesoEliminado->id << " eliminado de la memoria." << endl;
    eliminarDeColaPorID(idEliminar); // <-- sincroniza la cola
}

// Funcion para liberar la memoria de los procesos en la pila

void liberarMemoria() {
    if (tope == -1) { // Verifica si la pila está vacía
        cout << "La pila de memoria está vacía. No hay procesos para liberar." << endl;
        return;
    }
    // Solo vacía la pila, no elimina los procesos de la lista enlazada
    tope = -1; // Reinicia el tope de la pila a -1 para indicar que está vacía
    cout << "Todos los procesos han sido quitados de la memoria (pila) exitosamente." << endl;
    vaciarCola(); // <-- sincroniza la cola
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

void cargarProcesos(Proceso*& listaProcesos) {
    ifstream archivo("procesos.txt");
    int id, prioridad;
    string nombre;
    while (archivo >> id >> nombre >> prioridad) {
        agregarAlFinal(listaProcesos, id, nombre, prioridad);
    }
    archivo.close();
}

void guardarProcesos(Proceso* listaProcesos) {
    ofstream archivo("procesos.txt");
    Proceso* temp = listaProcesos;
    while (temp) {
        archivo << temp->id << " " << temp->nombre << " " << temp->prioridad << endl;
        temp = temp->siguiente;
    }
    archivo.close();
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
    
    cargarProcesos(listaProcesos); // Carga los procesos desde el archivo al iniciar el programa

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
                            do {
                                cout << "Ingrese el ID del proceso: "; cin >> id;

                                if (id <= 0) { // Verifica que el ID sea un número positivo
                                    cout << "El ID debe ser un número positivo. Intente de nuevo." << endl;
                                }
                            } while (id <= 0);

                            cout << "Ingrese el nombre del proceso: "; cin >> nombre;

                            do {
                                cout << "Ingrese la prioridad del proceso (1-10): "; cin >> prioridad;

                                if (prioridad < 1 || prioridad > 10) { // Verifica que la prioridad esté en el rango válido
                                    cout << "La prioridad debe estar entre 1 y 10. Intente de nuevo." << endl;
                                }
                            } while (prioridad < 1 || prioridad > 10);

                            // Llamamos a la función para agregar el proceso a la lista
                            agregarAlFinal(listaProcesos, id, nombre, prioridad);
                            guardarProcesos(listaProcesos); // Guardar después de agregar
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
                            imprimirProcesos(listaProcesos);
                            cout << "Ingrese el ID del proceso a eliminar: "; cin >> id;
                            eliminarProceso(listaProcesos, id);
                            guardarProcesos(listaProcesos); // Guardar después de eliminar
                            break;
                        case 5:
                            imprimirProcesos(listaProcesos);
                            cout << "Ingrese el ID del proceso a modificar: "; cin >> id;
                            modificarProceso(listaProcesos, id);
                            guardarProcesos(listaProcesos); // Guardar después de modificar
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
                            visualizarCola();
                            break;
                        case 2:
                            ejecutarProcesosEnCola();
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
        system("pause"); // Pausa la ejecución para que el usuario pueda ver los resultados antes de limpiar la consola
        system("cls"); // Limpia la consola para una mejor visualización del menú
    } 
    while (op != 4);
}
