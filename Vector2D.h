#ifndef VECTOR2D_H
#define VECTOR2D_H

#define FMTCARTESIANAS 1  //001
#define FMTPOLARESG 2     //010
#define FMTPOLARESR 4     //100

#include <string>
#include <iostream>
using namespace std;

class Vector2D {

    private:
        double coordx, coordy;

        
    public:
        enum class Uds { Grados, Radianes };

        //Constructores
        Vector2D();
        Vector2D(double mod, double ang, Uds unid);
        Vector2D(double x, double y);

        //Metodos get
        double x() const;
        double y() const;
        double mod() const;
        double ang() const;
        double ang(Uds unid) const;

        //Metodos set
        void x(double x);
        void y(double y);
        void mod(double mod);
        void ang(double grad);
        void ang(double angulo, Uds unid);

        //Operaciones con vectores
        void multiplicar(double num);

        void sumar(const Vector2D &v2);

        void restar(const Vector2D &v2);

        std::string to_string(int fmt=FMTCARTESIANAS|FMTPOLARESG) const;

        //Sobrecarga de operadores
        Vector2D operator+(const Vector2D& vector) const;
            
        Vector2D operator-(const Vector2D& vector) const;
        
        Vector2D operator*(double num) const;
        
        Vector2D operator/(double num) const;
        
        double operator*(const Vector2D& vector) const;
};

double distancia(const Vector2D &v1, const Vector2D &v2);

//Operaciones mediante funciones
Vector2D sumar(const Vector2D &v1, const Vector2D &v2);

Vector2D restar(const Vector2D &v1, const Vector2D &v2);

Vector2D multiplicar(const Vector2D &v1, double num);

Vector2D multiplicar(double num, const Vector2D &v1);

double multiplicar(const Vector2D &v1, const Vector2D &v2);

//Funciones sobrecarga
Vector2D operator*(double num, const Vector2D& vector);
    
istream& operator>>(istream& f, Vector2D& vector);
        
ostream& operator<<(ostream& f, const Vector2D& vector);


#endif