#include <ctime>
#include "matematicas.h"
#include "particula.h"
#include "bigs.h"

using namespace BiGS;

int main(int argc, char **argv) {
    srand(time(NULL));
    const int height=200, width=200;
    windowOpen(width,height,"Partícula rebotando",true,DRAWMODE_DELAYED);
    
    // Crear partícula aleatoria p
    double r = aleatorio(10,30);
    double x = aleatorio(0+r,width-r);
    double y = aleatorio(0+r,height-r);
    double vang = aleatorio(0,360);
    double vmod = aleatorio(10,40);
    double aang = aleatorio(0,360);
    double amod = aleatorio(0,20);
    
    Particula p = Particula(Vector2D(x,y), Vector2D(vmod, vang, Vector2D::Uds::Grados), Vector2D(amod, aang, Vector2D::Uds::Grados), 
              Vector2D(vmod, vang, Vector2D::Uds::Grados), r);
    
    // Esperamos a que el usuario pulse Cerrar Ventana (X)
    while (!BiGS::closeRequested()) {
        // Calcular tiempo transcurrido desde la anterior iteración
        double dift = BiGS::timeFromLastCall();
        
        // Detectar colisiones con bordes de la ventana
        if(p.posicion().x() + p.radio() >= width) {
            p.posicion(Vector2D(width - p.radio() , p.posicion().y()));
            p.vang(180 - p.vang());
        }
        if(p.posicion().x() - p.radio() <= 0) {
            p.posicion(Vector2D(p.radio() , p.posicion().y()));
            p.vang(180 - p.vang());
        }
    
        if(p.posicion().y() - p.radio() <= 0) {
            p.posicion(Vector2D(p.posicion().x() , p.radio()));
            p.vang(-p.vang());
        }
        if(p.posicion().y() + p.radio() >= height) {
            p.posicion(Vector2D(p.posicion().x() , height - p.radio()));
            p.vang( -p.vang());
        }
        
        p.avanzaMUA(dift); // Calcular nueva posición de la partícula
        BiGS::clear(BiGS::CBlack); // Borrar la pantalla
        p.dibujar(true); // Dibujar partícula
        BiGS::refresh(); // Refrescar pantalla
        BiGS::timeDelay(5); // Esperar un poco
    }
    return 0;
}