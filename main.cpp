/*
  Proyecto: Agenda de Contactos Inteligente
  Estudiante: Valery Natalia Medina Ramos
  Correo: vmedinar@unal.edu.co
  Curso: Programación de Computadores
  Fecha: Julio 2025

  -------------------------------------------------
  Este programa permite registrar y visualizar contactos personales desde consola. Los contactos se podran cargar automáticamente desde un archivo de texto.

  Para compilar:
    g++ main.cpp -o agenda

  Para ejecutar:
    ./agenda (Linux/Mac) o agenda.exe (Windows)

  Archivo requerido:
    contactos.txt (en la misma carpeta)
  -------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Estructura para guardar cada contacto
struct Contacto {
    string nombre;
    string numero;
    string correo;
};

// Lista de contactos
vector<Contacto> agenda;

// Cargar contactos desde archivo de texto
void cargarArchivo() {
    ifstream archivo("contactos.txt");
    if (!archivo) {
        cout << "No se encontró el archivo de contactos.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        Contacto c;
        size_t p1 = linea.find(',');
        size_t p2 = linea.rfind(',');

        if (p1 == string::npos || p2 == string::npos || p1 == p2) {
            cout << "Formato inválido en una línea del archivo.\n";
            continue;
        }

        c.nombre = linea.substr(0, p1);
        c.numero = linea.substr(p1 + 1, p2 - p1 - 1);
        c.correo = linea.substr(p2 + 1);

        agenda.push_back(c);
    }

    archivo.close();
    cout << "Contactos cargados correctamente desde el archivo.\n";
}

// Agregar contacto desde consola
void agregarContacto() {
    Contacto nuevo;

    cout << "\n--- Agregar nuevo contacto ---\n";
    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Número: ";
    getline(cin, nuevo.numero);

    cout << "Correo: ";
    getline(cin, nuevo.correo);

    if (nuevo.nombre.empty() || nuevo.numero.empty() || nuevo.correo.find('@') == string::npos) {
        cout << "Error: Datos inválidos. No se guardó el contacto.\n";
        return;
    }

    agenda.push_back(nuevo);
    cout << "Contacto agregado correctamente.\n";
}

// Mostrar todos los contactos
void mostrarContactos() {
    if (agenda.empty()) {
        cout << "\nNo hay contactos registrados.\n";
        return;
    }

    cout << "\nLista de contactos:\n";
    for (size_t i = 0; i < agenda.size(); ++i) {
        cout << "\nContacto #" << i + 1 << ":\n";
        cout << "Nombre: " << agenda[i].nombre << endl;
        cout << "Teléfono: " << agenda[i].numero << endl;
        cout << "Correo: " << agenda[i].correo << endl;
    }
}

// Menú principal
void mostrarMenu() {
    int opcion;
    do {
        cout << "\n======= AGENDA DE CONTACTOS =======\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Ver contactos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                agregarContacto();
                break;
            case 2:
                mostrarContactos();
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

// Función principal
int main() {
    cargarArchivo(); // Cargar datos desde archivo antes de mostrar menú
    mostrarMenu();
    return 0;
}


