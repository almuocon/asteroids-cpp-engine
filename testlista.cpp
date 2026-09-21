#include <iostream>
#include "listaparticulas.h"
using namespace std;
// Paso por valor para forzar la
// llamada al constructor de copia
void mostrar(ListaParticulas l) {
    ListaParticulas tmp;
    tmp = l; // Forzar el uso de operator=
    for (int i=0; i<tmp.size(); ++i)
        cout << tmp.get(i).to_string() << endl;
}

int main() {
    ListaParticulas l;
    Particula p;

    for (int i=0; i<10; ++i) {
        p.radio(10+i);
        l.inserta(p);
    }
    mostrar(l);
    l.borra(3);
    l.borra(7);
    cout << "Borrados el 3 y el 7:" << endl;
    mostrar(l);

    p.radio(100);
    l.inserta(p,0);
    cout << "Insertado en 0:" << endl;
    mostrar(l);

    p.radio(200);
    l.inserta(p,5);
    cout << "Insertado en 5:" << endl;
    mostrar(l);

    l.borra(l.size()-1);
    cout << "Borrado el último:" << endl;
    mostrar(l);
    
    return 0;
}