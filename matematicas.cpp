#include <cstdlib>
#include "matematicas.h"

bool cad2num(const char *c, double &n) {
    double signo = 1;
    double valor = 0;
    int decimales = -1;
    bool tiene_digitos = false;

    // signo
    if (*c == '-') {
        signo = -1;
        ++c;
    } else if (*c == '+') {
        ++c;
    }

    // Procesar caracteres
    while (*c != '\0') {
        if (*c >= '0' && *c <= '9') {
            tiene_digitos = true;
            if (decimales >= 0) 
                ++decimales;
            valor = valor * 10 + (*c - '0');

        } else if (*c == '.' && decimales == -1) {
            decimales = 0;
        } else {
            return false; // Carácter inválido
        }
        ++c;
    }

    if (!tiene_digitos) return false; // Cadena vacía 
    
    // Aplicar decimales
    while (decimales > 0) {
        valor = valor/10;
        decimales--;
    }
    
    n = signo * valor;
    return true;
}

double aleatorio(int min, int max){
    return (rand() % (max - min)) + min;
}