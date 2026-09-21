#include <iostream>
#include "Vector2D.h"
using namespace std;

void error() {
    cout << "Error en la lectura de datos. "
    "Los vectores se escriben con el "
    "formato (x,y)" << endl;
    exit(EXIT_FAILURE);
}

int main() {
    Vector2D v1, v2;
    cout << "Dime un primer vector v1: ";
    cin >> v1;
    if (!cin) error();
    cout << "Dime un segundo vector v2: ";
    cin >> v2;
    if (!cin) error();
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    Vector2D v3;
    v3 = v1+v2;
    cout << "v1 + v2 = " << v3 << endl;
    cout << "v1 - v2 = " << (v1-v2) << endl;
    cout << "v1 * 4 = " << (v1*4) << endl;
    cout << "4 * v1 = " << (4*v1) << endl;
    cout << "|v1| = " << v1.mod() << endl;
    cout << "v1 / 4 = " << (v1/4) << endl;
}