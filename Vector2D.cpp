#include <cmath>
#include "Vector2D.h"
#include "matematicas.h"

using namespace std;

//Constructores

Vector2D::Vector2D(){
    coordx = 0.0;
    coordy = 0.0;
}

Vector2D::Vector2D(double mod, double ang, Uds unid){
    double angulo=ang;

    if(unid == Vector2D::Uds::Grados)
        angulo = angulo*CONVEGR;
    
    coordx = mod*cos(angulo);
    coordy = mod*sin(angulo);
}

Vector2D::Vector2D(double cx, double cy){
    coordx = cx;
    coordy = cy;
}

//METODOS
//Metodos get

double Vector2D::x() const{
    return coordx;
}

double Vector2D::y() const{
    return coordy;
}

double Vector2D::mod() const{
    double modulo;
    modulo = sqrt(coordx*coordx + coordy*coordy);
    
    return modulo;
}

double Vector2D::ang()const{
    double angulo;
    angulo = atan2(coordy, coordx) *CONVERG;
    
    return angulo;
}

double Vector2D::ang(Uds unid) const{
    double angulo;
    angulo = atan2(coordy, coordx);
    if(unid == Vector2D::Uds::Grados)
        angulo = angulo*CONVERG;

    return angulo;
}

//Metodos set

void Vector2D::x(double cx){
    coordx = cx;
}

void Vector2D::y(double cy){
    coordy = cy;
}

void Vector2D::mod(double modulo){
    double angulo = ang(Uds::Radianes);
    coordx = modulo*cos(angulo);
    coordy = modulo*sin(angulo);
}

void Vector2D::ang(double grados){
    double g = grados*CONVEGR;
    coordx = mod()*cos(g);
    coordy = mod()*sin(g);
}

void Vector2D::ang(double angulo, Uds unid){
    double ang=angulo;

    if(unid == Vector2D::Uds::Grados)
        ang = ang*CONVEGR;

    double modulo = mod();
    coordx = modulo*cos(ang);
    coordy = modulo*sin(ang);
}

//Operaciones con vectores

void Vector2D::multiplicar(double num){
    coordx = coordx*num;
    coordy = coordy*num;
}

void Vector2D::sumar(const Vector2D &v2){
    coordx = coordx + v2.x();
    coordy = coordy + v2.y();
}

void Vector2D::restar(const Vector2D &v2){
    coordx = coordx - v2.x();
    coordy = coordy - v2.y();
}

std::string Vector2D::to_string(int fmt) const{
    std::string r="";

    if(fmt & FMTCARTESIANAS)
        r+= "P=(" + std::to_string(this->x()) + "," + std::to_string(this->y()) + ") ";

    if(fmt & (FMTPOLARESG|FMTPOLARESR)){
        r+= "# @mod=" + std::to_string(this->mod()) + " ";
        
        if(fmt & FMTPOLARESR) 
        r+= "@rad=" + std::to_string(this->ang(Uds::Radianes)) + " ";

        if(fmt & FMTPOLARESG) 
        r+= "@deg=" + std::to_string(this->ang()) + " ";
    }

    return r;
}
//Sobrecarga
Vector2D Vector2D::operator+(const Vector2D& vector) const {
    return Vector2D(x() + vector.x(), y() + vector.y());
    }
    
Vector2D Vector2D::operator-(const Vector2D& vector) const {
    return Vector2D(x() - vector.x(), y() - vector.y());
}

Vector2D Vector2D::operator*(double num) const {
    return Vector2D(x() * num, y() * num); /* * escalar*/
}

Vector2D Vector2D::operator/(double num) const {
    return Vector2D(x() / num, y() / num);
}

double Vector2D::operator*(const Vector2D& vector) const {
    return x() * vector.x() + y() * vector.y(); //escalar
}
        
//FUNCIONES

double distancia(const Vector2D &v1, const Vector2D &v2) {
    double d;
    d = sqrt( (v2.x()-v1.x())*(v2.x()-v1.x())  +  (v2.y()-v1.y())*(v2.y()-v1.y()) );
    return d;
}

Vector2D sumar(const Vector2D &v1, const Vector2D &v2){
    Vector2D v3;
    
    v3.x(v1.x() + v2.x());
    v3.y(v1.y() + v2.y());

    return v3;
}

Vector2D restar(const Vector2D &v1, const Vector2D &v2){
    Vector2D v3;
    
    v3.x(v1.x() - v2.x());
    v3.y(v1.y() - v2.y());

    return v3;
}

Vector2D multiplicar(const Vector2D &v1, double num){
    Vector2D v3;
    
    v3.x(v1.x()*num);
    v3.y(v1.y()*num);

    return v3;
}

Vector2D multiplicar(double num, const Vector2D &v1){
    return multiplicar(v1,num);
}

double multiplicar(const Vector2D &v1, const Vector2D &v2){
    double prod;
    prod = v1.x()*v2.x() + v1.y()*v2.y();
    return prod;
}

//Funciones sobrecarga

Vector2D operator*(double num, const Vector2D& vector){
    return vector * num;
}
    
istream& operator>>(istream& f, Vector2D& vector) {
    char parentesis1, parentesis2, coma;
    double cx, cy;

    f >> parentesis1 >> cx >> coma >> cy >> parentesis2;
    if(parentesis1 == '(' && parentesis2 == ')' && coma == ','){
        vector.x(cx);
        vector.y(cy);
    }else
        f.clear(ios::failbit);

    return f;
}
        
ostream& operator<<(ostream& f, const Vector2D& vector) {
    f << '(' << vector.x() << "," << vector.y() << ')';
    return f;
}