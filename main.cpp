#include <iostream>   
#include <vector>     
#include <string>     
#include <fstream>    
using namespace std;

//ESTRUCTURA DE DATOS (Se usa un struct para representar cada contacto)
struct Contacto {
    string nombre;
    string numero;
    string correo;
};

//VARIABLES GLOBALES: agenda y ARCHIVO
vector<Contacto> agenda;
const string ARCHIVO = "contactos.txt";

//DECLARACIÓN DE FUNCIONES
void cargarDesdeArchivo();       // lee contactos al iniciar
void guardarEnArchivo();         // guarda contactos modificados
void agregarContacto();          // Opción 1 
void mostrarContactos();         // Opción 2
void buscarContactoPorNombre();  // Opción 3
void modificarContactoPorNombre(); // Opción 4
void eliminarContactoPorNombre();  // Opción 5
int encontrarIndicePorNombre(string); // Ayuda interna
void mostrarMenu();              // Menú principal

//FUNCIÓN: mostrarMenu (solo opción de salir)
void mostrarMenu() {
    int opcion;
    do {
        cout << "\nAGENDA DE CONTACTOS\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();  // limpia salto de línea

        switch (opcion) {
            case 0: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

//FUNCIÓN PRINCIPAL
int main() {
    mostrarMenu();         
    return 0;
}

