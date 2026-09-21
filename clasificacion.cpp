#include "clasificacion.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Clasificacion::Clasificacion() : nombres(nullptr), puntuaciones(nullptr), capacidad(10), tamano(0) {
    nombres = new string[capacidad];
    puntuaciones = new int[capacidad];
}

Clasificacion::~Clasificacion() {
    delete[] nombres;
    delete[] puntuaciones;
}

void Clasificacion::agregarPuntuacion(const string& nombre, int puntuacion) {
    if (tamano >= capacidad) {
        int nuevaCapacidad = capacidad * 2;
        string* nuevosNombres = new string[nuevaCapacidad];
        int* nuevasPuntuaciones = new int[nuevaCapacidad];

        for (int i = 0; i < tamano; ++i) {
            nuevosNombres[i] = nombres[i];
            nuevasPuntuaciones[i] = puntuaciones[i];
        }

        delete[] nombres;
        delete[] puntuaciones;
        nombres = nuevosNombres;
        puntuaciones = nuevasPuntuaciones;
        capacidad = nuevaCapacidad;
    }

    nombres[tamano] = nombre;
    puntuaciones[tamano] = puntuacion;
    ++tamano;
}

void Clasificacion::sumarPuntuaciones() {
    int nuevoTamano = 0;
    string* nombresUnicos = new string[tamano];
    int* puntuacionesSumadas = new int[tamano];

    for (int i = 0; i < tamano; ++i) {
        bool encontrado = false;
        for (int j = 0; j < nuevoTamano; ++j) {
            if (nombres[i] == nombresUnicos[j] && !encontrado) {
                puntuacionesSumadas[j] += puntuaciones[i];
                encontrado = true;
            }
        }
        if (!encontrado) {
            nombresUnicos[nuevoTamano] = nombres[i];
            puntuacionesSumadas[nuevoTamano] = puntuaciones[i];
            ++nuevoTamano;
        }
    }

    delete[] nombres;
    delete[] puntuaciones;
    nombres = nombresUnicos;
    puntuaciones = puntuacionesSumadas;
    tamano = nuevoTamano;
    capacidad = nuevoTamano;
}

void Clasificacion::ordenarRanking() {
    for (int i = 0; i < tamano - 1; ++i) {
        for (int j = 0; j < tamano - i - 1; ++j) {
            if (puntuaciones[j] < puntuaciones[j + 1]) {
                // Swap nombres
                std::string tempNombre = nombres[j];
                nombres[j] = nombres[j + 1];
                nombres[j + 1] = tempNombre;
                int tempPuntuacion = puntuaciones[j];
                puntuaciones[j] = puntuaciones[j + 1];
                puntuaciones[j + 1] = tempPuntuacion;
            }
        }
    }
}

void Clasificacion::mostrarRanking() const {
    cout << "El ranking de jugadores es este:" << endl;
    for (int i = 0; i < tamano; ++i) {
        cout << nombres[i] << " - " << puntuaciones[i] << " puntos" << endl;
    }
}

void Clasificacion::guardarEnFichero(const string& ruta) const {
    ofstream archivo(ruta);
    if (archivo.is_open()) {
        for (int i = 0; i < tamano; ++i) {
            archivo << puntuaciones[i] << " " << nombres[i] << "\n";
        }
        archivo.close();
    }
}