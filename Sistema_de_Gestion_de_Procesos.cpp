#include <iostream>
#include <string>

using namespace std;

void registrarProceso() {
    // Aquí iría la lógica para registrar un proceso
    cout << "Función para registrar un proceso." << endl;
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
