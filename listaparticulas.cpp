#include "listaparticulas.h"
#include <cassert>

ListaParticulas::ListaParticulas() : lista(nullptr), num(0) {}

ListaParticulas::~ListaParticulas() {
    delete[] lista;
    lista = nullptr,
    num = 0;
}

ListaParticulas::ListaParticulas(const ListaParticulas &orig){
    lista = new Particula[orig.num];
    for (int i=0; i<orig.num; ++i){
        lista[i] = orig.lista[i];
    }
    num = orig.num;
}

ListaParticulas &ListaParticulas::operator=(const ListaParticulas &orig) {
    if (this != &orig) {
        delete[] lista;
        num = orig.num;
        lista = nullptr;
        if (num > 0) {
            lista = new Particula[num];
            for (int i = 0; i < num; ++i) {
                lista[i] = orig.lista[i];
            }
        }
    }
    return *this;
}

int ListaParticulas::size() const {
    return num;
}

void ListaParticulas::set(const Particula &p, int pos) {
    assert(pos >= 0 && pos < num);
    lista[pos] = p;
}

Particula & ListaParticulas::get(int pos) const {
    assert(pos >= 0 && pos < num);
    return lista[pos];
}

void ListaParticulas::borra (int pos){
    assert(pos >= 0 && pos < num);
    if (num == 1){
        delete[] lista;
        lista = nullptr;
        num = 0;
        return;
    }

    Particula *aux = lista;
    lista = new Particula[num - 1];

    for (int i = 0; i < pos; i++)
        lista[i] = aux[i];
    
    for (int i = pos; i < num - 1; i++)
        lista[i] = aux[i+1];

    num --;
    delete [] aux;
}

void ListaParticulas::inserta(const Particula &p, int pos){
    Particula* aux = lista;
    lista = new Particula[num+1];
    
    if (pos < 0 || pos > num)
      pos = num;

    for (int i = 0; i<pos; i++) 
        lista[i] = aux[i];

    lista[pos] = p;

    for (int i = pos; i<num; i++) 
        lista[i+1] = aux[i];  

    num++;
    delete [] aux;
}

// Detectar colisiones con bordes de la ventana
void choqueBorde(ListaParticulas &l, double width, double height){
    for(int i = 0; i<l.size(); i++){
        if(l.get(i).posicion().x() + l.get(i).radio() >= width) {
            l.get(i).posicion(Vector2D(width - l.get(i).radio() , l.get(i).posicion().y()));
            l.get(i).vang(180 - l.get(i).vang());
        }
        if(l.get(i).posicion().x() - l.get(i).radio() <= 0) {
            l.get(i).posicion(Vector2D(l.get(i).radio() , l.get(i).posicion().y()));
            l.get(i).vang(180 - l.get(i).vang());
        }
    
        if(l.get(i).posicion().y() - l.get(i).radio() <= 0) {
            l.get(i).posicion(Vector2D(l.get(i).posicion().x() , l.get(i).radio()));
            l.get(i).vang(-l.get(i).vang());
        }
        if(l.get(i).posicion().y() + l.get(i).radio() >= height) {
            l.get(i).posicion(Vector2D(l.get(i).posicion().x() , height - l.get(i).radio()));
            l.get(i).vang( -l.get(i).vang());
        }
    }
}