#include <iostream>
#include <string>

using namespace std;
//ESTRUCTURA PRINCIPAL

//Representa un proceso con ID, nombre, prioridad y puntero al siguiente
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

int main() {

    Proceso* listaProcesos = NULL; // Inicializa la lista de procesos como vacía
    int op, NumEl, id, prioridad;
    string nombre;
    
    do {
        cout << "\n***Menu de Gestion***" << endl;
        cout << "[1]. Registrar proceso" << endl;
        cout << "[2]. Imprimir procesos" << endl;
        cout << "[3]. Buscar procesos" << endl;
        cout << "[4]. Eliminar proceso" << endl;
        cout << "[5]. Modificar proceso" << endl;
        cout << "[6]. Salir" << endl;
        cout << "*************************" << endl;

        do {

            cout << "Ingrese una opcion: "; cin >> op; // Solicita al usuario que ingrese una opción

            if (op < 1 || op > 6) { // Verifica si la opción es válida
                cout << "Opcion invalida. Por favor, intente de nuevo." << endl; // Mensaje de error si la opción no es válida
            }

        } while (op < 1 || op > 6); // Bucle para asegurar que la opción ingresada sea válida

        switch (op) { // Estructura de control que maneja las opciones del menú
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
                break;
            case 6:
                cout << "Saliendo del sistema de gestion de procesos." << endl;
                break;
        }

        system("pause"); // Pausa la ejecución para que el usuario pueda ver los resultados
        system("cls"); // Limpia la consola para una mejor visualización del menú
        
    } while (op != 6); // Fin del bucle do-while
}
