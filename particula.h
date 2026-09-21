#ifndef PARTICULA__H
#define PARTICULA__H

#include <string>
#include "Vector2D.h"
#include "bigs.h"
#include "bigs_image.h"

using namespace BiGS;

class Particula{

    private:
        Vector2D pos, vel, acel, direc;
        double dens, rad, t_inicioVida, t_vida;
        BiGS::Color col;
        int tipe;  // 1:nave, 2:asteroide, 3:disparo
        bool difunt;
        static const BiGS::Image *imgNave;
        static const BiGS::Image *imgAsteroide;
        
    public:
        //Constructores
        Particula();
        Particula(Vector2D p, Vector2D v);
        Particula(Vector2D p, Vector2D v, Vector2D a, Vector2D d=Vector2D(0.0,0.0), double r=0, BiGS::Color color=CRed, int t=2);

        //Metodos get
        Vector2D posicion() const;
        Vector2D velocidad() const;
        Vector2D aceleracion() const;
        Vector2D direccion() const;

        double radio() const;
        double densidad() const;
        double masa() const;

        double vmod() const;
        double vang() const;
        double amod() const;
        double aang() const;

        int tipo() const;

        bool esDisparo(const Particula &p);
        bool difunto() const;

        double tvida() const;
        double tiniciovida() const;

        //Metodos set
        void posicion(const Vector2D &p);
        void posicion(double x, double y);

        void velocidad(const Vector2D &v);
        void aceleracion(const Vector2D &a);

        void velocidad(double m, double a);
        void aceleracion(double m, double a);

        void vmod(double m);
        void vang(double a);

        void amod(double m);
        void aang(double a);

        void radio(double r);
        void densidad(double d);

        void direccion(double a);
        void girar(double ang);

        void tipo(int t);
        void color(BiGS::Color c);

        std::string to_string() const;

        void dibujar(bool flechas=false);
        static void setImgNave(const BiGS::Image *img);
        static void setImgAsteroide(const BiGS::Image *img);

        void difunto(bool d);
        void tvida(double t);
        void tiniciovida(double t);

        //Cinematica
        void avanzaMRU(double dt);
        void avanzaMUA(double dt);

};

void corrige_velocidad(Particula &a1, Particula &a2);

#endif