#include "particula.h"


int main(int argc, char **argv) {
    const int height=200, width=200;
    windowOpen(width,height, "Dibujar partículas",true);
    
    Particula nave(Vector2D(100,100),
                   Vector2D(50,-45,Vector2D::Uds::Grados),
                   Vector2D(40,90,Vector2D::Uds::Grados));
    nave.tipo(1);
    nave.color(CGreen);
    nave.radio(30);
    nave.direccion(30);
    nave.dibujar(true);
    
    Particula aster1(Vector2D(40,50),
                     Vector2D(70,45,Vector2D::Uds::Grados),
                     Vector2D(10,135,Vector2D::Uds::Grados));
    aster1.tipo(2);
    aster1.color(CCyan);
    aster1.radio(20);
    aster1.dibujar(true);
    
    Particula aster2(Vector2D(150,50), Vector2D(40,-30,Vector2D::Uds::Grados),
                     Vector2D(20,-110,Vector2D::Uds::Grados));
    aster2.tipo(2);
    aster2.color(CCyan);
    aster2.radio(10);
    aster2.dibujar(true);
    
    Particula disp(Vector2D(50,150), Vector2D(40,-30,Vector2D::Uds::Grados),
                   Vector2D(20,-110,Vector2D::Uds::Grados));
    disp.tipo(3);
    disp.color(CRed);
    disp.radio(3);
    disp.dibujar(true);
    
    eventWaitKeyboard();

    return 0;
}