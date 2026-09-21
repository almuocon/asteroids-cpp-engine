#ifndef LISTA_PARTICULAS__H
#define LISTA_PARTICULAS__H

#include "particula.h"

class ListaParticulas {
    private:
        Particula *lista;
        int num;

    public:
    ListaParticulas(); //constructor
    ~ListaParticulas(); //destructor
    ListaParticulas(const ListaParticulas &orig); //constructor de copia
    ListaParticulas &operator=(const ListaParticulas &orig); // operator =
    
    int size() const;
    void set(const Particula &p, int pos);
    Particula & get(int pos) const;
    void borra(int pos);
    void inserta(const Particula &p, int pos=-1);
};

void choqueBorde(ListaParticulas &l, double width, double height);

#endif