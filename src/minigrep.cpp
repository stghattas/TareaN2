#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib> // Para usar system("color ...") en Windows

using namespace std;

// Función para buscar coincidencias en una línea y marcarlas
void buscarCoincidencias(string& linea, const string& palabraBuscada, bool ignorarMayusculas, const string& color) {
    size_t pos = 0;
    string palabra = palabraBuscada;
    if (ignorarMayusculas) {
        // Convertir ambas cadenas a minúsculas para ignorar mayúsculas y minúsculas
        transform(linea.begin(), linea.end(), linea.begin(), ::tolower);
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
    }
    while ((pos = linea.find(palabra, pos)) != string::npos) {
        // Marcar la coincidencia con el color especificado
        if (color == "rojo") {
            cout << "\033[1;31m"; // Rojo brillante
        } else if (color == "azul") {
            cout << "\033[1;34m"; // Azul brillante
        } else if (color == "amarillo") {
            cout << "\033[1;33m"; // Amarillo brillante
        } else if (color == "verde") {
            cout << "\033[1;32m"; // Verde brillante
        } else if (color == "naranja") {
            cout << "\033[38;5;208m"; // Naranja (color ANSI de 256 colores)
        } else if (color == "morado") {
            cout << "\033[38;5;165m"; // Morado (color ANSI de 256 colores)
        } else {
            cout << "\033[1;31m"; // Por defecto, rojo brillante
        }
        cout << linea.substr(pos, palabra.length()) << "\033[0m";
        pos += palabra.length();
    }
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <ruta del ejecutable> <ruta del archivo> <palabra> [-i] [-c color]" << endl;
        return 1;
    }

    string archivo = argv[1];
    string palabraBuscada = argv[2];
    bool ignorarMayusculas = false;
    string color = "rojo"; // Color por defecto

    // Verificar opciones adicionales
    for (int i = 3; i < argc; ++i) {
        string opcion = argv[i];
        if (opcion == "-i") {
            ignorarMayusculas = true;
        } else if (opcion == "-c" && i + 1 < argc) {
            color = argv[i + 1];
            // Avanzar el índice para saltar el valor del color
            ++i;
        }
    }

    ifstream archivoEntrada(archivo);
    if (!archivoEntrada) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return 1;
    }

    string linea;
    int numLineasConCoincidencias = 0;
    int numCoincidenciasTotales = 0;

    while (getline(archivoEntrada, linea)) {
        size_t pos = 0;
        
        // Buscar todas las ocurrencias de la palabra en la linea
        buscarCoincidencias(linea, palabraBuscada, ignorarMayusculas, color);

        // Si se encontraron coincidencias en la linea, entonces:
        if (linea.find(palabraBuscada) != string::npos) {
            numLineasConCoincidencias++;
            // Contar el numero de coincidencias en la línea
            while ((pos = linea.find(palabraBuscada, pos)) != string::npos) {
                pos += palabraBuscada.length();
                numCoincidenciasTotales++;
            }
        }
        cout << endl;
    }

    archivoEntrada.close();

    cout << "Numero de lineas con coincidencias: " << numLineasConCoincidencias << endl;
    cout << "Numero total de coincidencias encontradas: " << numCoincidenciasTotales << endl;

    return 0;
}

