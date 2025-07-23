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
        cout << "1. Agregar contacto\n";
        cout << "2. Ver contactos\n";
        cout << "3. Buscar contacto\n";
        cout << "4. Modificar contacto\n";
        cout << "5. Eliminar contacto\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();  // limpia salto de línea

        switch (opcion) {
            case 1: agregarContacto(); break;
            case 2: mostrarContactos(); break;
            case 3: buscarContactoPorNombre(); break;
            case 4: modificarContactoPorNombre(); break;
            case 5: eliminarContactoPorNombre(); break;
            case 0: cout << "Saliendo del programa...\n"; break;

            default: cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

//FUNCIÓN PRINCIPAL
int main() {
    cargarDesdeArchivo();  // Se leen contactos al iniciar
    mostrarMenu();         
    return 0;

//FUNCIÓN: agregarContacto

void agregarContacto() {
    Contacto nuevo;

    cout << "\nAGREGAR NUEVO CONTACTO:\n";
    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Número: ";
    getline(cin, nuevo.numero);

    cout << "Correo: ";
    getline(cin, nuevo.correo);

    // Validaciones
    if (nuevo.nombre.empty() || nuevo.numero.empty()) {
        cout << "Error: nombre y número son obligatorios.\n";
        return;
    }
    if (nuevo.correo.find('@') == string::npos) {
        cout << "Error: correo inválido.\n";
        return;
    }

    // Todo correcto se agrega
    agenda.push_back(nuevo);
    guardarEnArchivo();                 
    cout << "Contacto agregado correctamente.\n";
}
//FUNCIÓN: mostrarContactos

void mostrarContactos() {
    if (agenda.empty()) {
        cout << "\nNo hay contactos registrados.\n";
        return;
    }

    cout << "\nLISTA DE CONTACTOS\n";
    for (size_t i = 0; i < agenda.size(); ++i) {
        cout << i + 1 << ") " << agenda[i].nombre
             << " | "   << agenda[i].numero
             << " | "   << agenda[i].correo << '\n';
    }
}
//FUNCIÓN: aMinusculasManual

char aMinusculaManual(char c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}

//FUNCIÓN: normalizar

string normalizar(const string& textoOriginal) {
    string resultado = textoOriginal;
    for (char& c : resultado) c = aMinusculaManual(c);
    return resultado;
}

//FUNCIÓN: encontrarIndicePorNombre

int encontrarIndicePorNombre(string nombreBuscado) {
    string clave = normalizar(nombreBuscado);

    for (size_t i = 0; i < agenda.size(); ++i) {
        if (normalizar(agenda[i].nombre) == clave)
            return static_cast<int>(i);   
    }
    return -1;   // Cuando no se encuentra el contacto
}

//FUNCIÓN: buscarContactoPorNombre

void buscarContactoPorNombre() {
    cout << "\nNombre a buscar: ";
    string clave;
    getline(cin, clave);

    int posicion = encontrarIndicePorNombre(clave);

    if (posicion == -1) {
        cout << "Contacto no encontrado.\n";
    } else {
        const Contacto& c = agenda[posicion];
        cout << "Encontrado:  "
             << c.nombre  << " | "
             << c.numero  << " | "
             << c.correo  << '\n';
    }
}
//FUNCIÓN: modificarContactoPorNombre

void modificarContactoPorNombre() {
    cout << "\nNombre del contacto a modificar: ";
    string nombreObjetivo;
    getline(cin, nombreObjetivo);

    int posicion = encontrarIndicePorNombre(nombreObjetivo);
    if (posicion == -1) {
        cout << "Contacto no encontrado.\n";
        return;
    }

    Contacto& c = agenda[posicion];

    cout << "Número actual: " << c.numero  << "\n";
    cout << "Correo actual: " << c.correo  << "\n";

    cout << "Nuevo número  (enter): ";
    string nuevoNum; getline(cin, nuevoNum);

    cout << "Nuevo correo  (enter): ";
    string nuevoMail; getline(cin, nuevoMail);

    if (!nuevoNum.empty()) c.numero = nuevoNum;
    if (!nuevoMail.empty() && nuevoMail.find('@') != string::npos)
        c.correo = nuevoMail;

    guardarEnArchivo();
    cout << "Contacto modificado.\n";
}
//FUNCIÓN: eliminarContactoPorNombre
 
void eliminarContactoPorNombre() {
    cout << "\nNombre del contacto a eliminar: ";
    string nombreObjetivo;
    getline(cin, nombreObjetivo);

    int posicion = encontrarIndicePorNombre(nombreObjetivo);
    if (posicion == -1) {
        cout << "Contacto no encontrado.\n";
        return;
    }

    // Se confirma la eliminación
    cout << "¿Está seguro/a de eliminar a "
         << agenda[posicion].nombre << "? (s/n): ";
    char confirma; cin >> confirma; cin.ignore();

    if (confirma == 's' || confirma == 'S') {
        agenda.erase(agenda.begin() + posicion);
        guardarEnArchivo();
        cout << "Contacto eliminado.\n";
    } else {
        cout << "Operación cancelada.\n";
    }
}

//FUNCIÓN: guardarEnArchivo

void guardarEnArchivo() {
    ofstream archivo(ARCHIVO, ios::trunc);

    for (const Contacto& c : agenda) {
        archivo << c.nombre << ','
                << c.numero << ','
                << c.correo << '\n';
    }

    archivo.close();
}

//FUNCIÓN: cargarDesdeArchivo

void cargarDesdeArchivo() {
    ifstream archivo(ARCHIVO); 
    if (!archivo) {
        // Si no existe, se crea un archivo vacío automáticamente
        ofstream nuevo(ARCHIVO);
        nuevo.close();
        cout << "Archivo de contactos creado (estaba ausente).\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t p1 = linea.find(',');
        size_t p2 = linea.rfind(',');

        if (p1 == string::npos || p2 == string::npos || p1 == p2) {
            cout << "Línea con formato inválido (omitida).\n";
            continue;               
        }

        Contacto c;
        c.nombre = linea.substr(0, p1);
        c.numero = linea.substr(p1 + 1, p2 - p1 - 1);
        c.correo = linea.substr(p2 + 1);

        agenda.push_back(c);        
    }

    archivo.close();
    cout << "Contactos cargados correctamente desde el archivo.\n";
}

    return 0;
}

