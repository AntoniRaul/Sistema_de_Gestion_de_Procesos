#include <iostream>
#include <string>

using namespace std;
//ESTRUCTURA PRINCIPAL


//Representa un proceso con ID, nombre, prioridad y puntero al siguiente
struct Proceso 
{
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
};
Proceso* listaProcesos = NULL;


void eliminarProceso(int id) {
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
void buscarProceso(int id) {
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

    int op;
    
    do {
        cout << "\n***Menu de Gestion***" << endl;
        cout << "[1]. Registrar proceso" << endl;
        cout << "[2]. Buscar procesos" << endl;
        cout << "[3]. Eliminar proceso" << endl;
        cout << "[4]. Modificar proceso" << endl;
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
                cout << "Registrar proceso seleccionado." << endl;
                // Aquí iría la lógica para registrar un proceso
                break;
            case 2:
                cout << "Buscar procesos seleccionado." << endl;
                // Aquí iría la lógica para buscar procesos
                break;
            case 3:
                cout << "Eliminar proceso seleccionado." << endl;
                // Aquí iría la lógica para eliminar un proceso
                break;
            case 4:
                cout << "Modificar proceso seleccionado." << endl;
                // Aquí iría la lógica para modificar un proceso
                break;
            case 6:
                cout << "Saliendo del sistema de gestion de procesos." << endl;
                break;S
        }

    }    while (op != 6); // Fin del bucle do-while
}
