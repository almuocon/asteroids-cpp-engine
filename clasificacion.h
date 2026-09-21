#ifndef CLASIFICACION_H
#define CLASIFICACION_H

#include <string>

class Clasificacion {
private:
    std::string* nombres;
    int* puntuaciones;
    int capacidad;
    int tamano;

public:
    Clasificacion();
    ~Clasificacion();
    void agregarPuntuacion(const std::string& nombre, int puntuacion);
    void sumarPuntuaciones();
    void ordenarRanking();
    void mostrarRanking() const;
    void guardarEnFichero(const std::string& ruta) const;
};

#endif // CLASIFICACION_H