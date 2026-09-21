#include <cmath>
#include <ctime>
#include <cassert>
#include "listaparticulas.h"
#include "matematicas.h"
#include "bigs.h"

using namespace BiGS;

void NumColor(int n, Color &col){
    assert(n>=1 && n<=8);
    if (n == 1)
        col = CWhite;
    else if (n == 2)
        col = CRed;
    else if (n == 3)
        col = CGreen;
    else if (n == 4)
        col = CBlue;
    else if (n == 5)
        col = CCyan;
    else if (n == 6)
        col = CMagenta;
    else if (n == 7)
        col = CYellow;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    if (argc != 10) {
        cout << "Me has pasado un numero de argumentos incorrecto" << endl;
    } else {
        double Ancho, Alto, N, Rmin, Rmax, Vmin, Vmax, Amin, Amax;
        bool ok = true;
    
        ok = ok && cad2num(argv[1], Ancho);
        ok = ok && cad2num(argv[2], Alto);
        ok = ok && cad2num(argv[3], N);
        ok = ok && cad2num(argv[4], Rmin);
        ok = ok && cad2num(argv[5], Rmax);
        ok = ok && cad2num(argv[6], Vmin);
        ok = ok && cad2num(argv[7], Vmax);
        ok = ok && cad2num(argv[8], Amin);
        ok = ok && cad2num(argv[9], Amax);
    
        windowOpen(Ancho,Alto,"rebotes",true,DRAWMODE_DELAYED);

        ListaParticulas l;
        //Crear partículas
        for (int i = 0 ; i<N ; i++){
            double r = aleatorio(Rmin,Rmax);
            double x = aleatorio(0.1+r,Ancho-r);
            double y = aleatorio(0.1+r,Alto-r);
            double vang = aleatorio(0,359);
            double vmod = aleatorio(Vmin,Vmax);
            double aang = aleatorio(0,359);
            double amod = aleatorio(Amin,Amax);
            double densidad = aleatorio(1,10);
            Color col;
            NumColor(aleatorio(1,7), col);

            Particula p = Particula(Vector2D(x,y), 
                                    Vector2D(vmod, vang, Vector2D::Uds::Grados), 
                                    Vector2D(amod, aang, Vector2D::Uds::Grados), 
                                    Vector2D(vmod, vang, Vector2D::Uds::Grados), 
                                    r);
            p.densidad(densidad);
            p.color(col);
            l.inserta(p, i);                    
        }

        // Esperamos a que el usuario pulse Cerrar Ventana (X)
        while (!BiGS::closeRequested()) {
            // Calcular tiempo transcurrido desde la anterior iteración
            double dift = BiGS::timeFromLastCall();
            
            // Detectar colisiones con bordes de la ventana
            choqueBorde(l, Ancho, Alto);

            //Detectar colisiones con otras particulas
            for(int i=0; i < N; i++){
                for (int j=0; j<N; j++)
                    if(i!=j && distancia(l.get(i).posicion(), l.get(j).posicion())  <=  l.get(i).radio() + l.get(j).radio()){
                        corrige_velocidad(l.get(i), l.get(j));
                    }
            }

            //Avanzar particulas
            for (int i=0 ; i<N; i++)
                l.get(i).avanzaMUA(dift); 

            BiGS::clear(BiGS::CBlack); // Borrar la pantalla

            // Dibujar partículas
            for (int i=0 ; i<l.size(); i++)
                l.get(i).dibujar(true); 
            
            BiGS::refresh(); // Refrescar pantalla
            BiGS::timeDelay(5); // Esperar un poco
        }
    }
    return 0;
}