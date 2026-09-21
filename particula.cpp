
#include <string>
#include <cmath>
#include "matematicas.h"
#include "particula.h"

using namespace BiGS;

const BiGS::Image* Particula::imgNave = nullptr;
const BiGS::Image* Particula::imgAsteroide = nullptr;

void Particula::setImgNave(const BiGS::Image *img) {
    imgNave = img;
}

void Particula::setImgAsteroide(const BiGS::Image *img) {
    imgAsteroide = img;
}

//CONSTRUCTORES
Particula::Particula() : pos(0.0, 0.0), vel(0.0, 0.0), acel(0.0, 0.0), direc(0.0, 0.0), rad(0), difunt(false) {}

Particula::Particula(Vector2D p, Vector2D v) : pos(p.x(),p.y()), vel(v.x(),v.y()), acel(0.0, 0.0), direc(0.0, 0.0), rad(0), difunt(false) {}

Particula::Particula(Vector2D p, Vector2D v, Vector2D a, Vector2D d, double r, BiGS::Color c, int t) : 
            pos(p.x(),p.y()), vel(v.x(),v.y()), acel(a.x(), a.y()), direc(d), rad(r), col(c), tipe(t) , difunt(false) {}

//METODOS GET
Vector2D Particula::posicion() const{
    return pos;
}

Vector2D Particula::velocidad() const{
    return vel;
}

Vector2D Particula::aceleracion() const{
    return acel;
}

Vector2D Particula::direccion() const{
    return direc;
}

double Particula::radio() const{
    return rad;
}

double Particula::densidad() const{
    return dens;
}

double Particula::masa() const{
    double m;
    m = dens * PI * rad*rad;
    return m;
}

double Particula::vmod() const{
    return vel.mod();
} 
double Particula::vang() const{
    return vel.ang();
}

double Particula::amod() const {
    return acel.mod();
} 
double Particula::aang() const{
    return acel.ang();
}

int Particula::tipo() const{
    return tipe;
}

bool Particula::esDisparo(const Particula &p) {
    return p.tipo() == 3;
}

bool Particula::difunto() const {
    return difunt;
}

double Particula::tvida() const{
    return t_vida;
}
   
double Particula::tiniciovida() const{
    return t_inicioVida;
}

//METODOS SET
void Particula::posicion(const Vector2D &p){
    pos = p;
}
void Particula::posicion(double x, double y){
    pos.x(x);
    pos.y(y);
}
void Particula::velocidad(const Vector2D &v){
    vel = v;
}
void Particula::aceleracion(const Vector2D &a){
    acel = a;
}
void Particula::velocidad(double m, double a){
    vel.x(m*cos(a*CONVEGR));
    vel.y(m*sin(a*CONVEGR));
}
void Particula::aceleracion(double m, double a){
    acel.x(m*cos(a*CONVEGR));
    acel.y(m*sin(a*CONVEGR));
}

void Particula::vmod(double m){
    vel.mod(m);
} 
void Particula::vang(double a){
    vel.ang(a);
}

void Particula::amod(double m){
    acel.mod(m);
} 
void Particula::aang(double a){
    acel.ang(a);
}

void Particula::radio(double r){
    rad = r;
}

void Particula::densidad(double d){
 dens = d;
}

void Particula::direccion(double a){
    double angu = a*CONVEGR;
    double direcx, direcy;

    direcx = rad * cos(angu);
    direcy = rad * sin(angu);

    direc.x(direcx);
    direc.y(direcy);
}

void Particula::girar(double ang){
    double anguloActual = direc.ang();
    double nuevoAngulo = anguloActual + ang;
    direccion(nuevoAngulo);
}

void Particula::tipo(int t){
    tipe = t;
}

void Particula::color(BiGS::Color c){
    col = c;
}

std::string Particula::to_string() const{
    std::string r="";

    r = "La posicion es " + pos.Vector2D::to_string(FMTCARTESIANAS) + "\n la velocidad es " + vel.Vector2D::to_string(FMTCARTESIANAS) 
    + "\n y la aceleracion es " + acel.Vector2D::to_string(FMTCARTESIANAS) + "\n" + "el radio es " + std::to_string(rad);

    return r;

}

void Particula::dibujar(bool flechas){
    if (tipe == 1) { // Nave
        if (imgNave != nullptr && !BiGS::imageEmpty(*imgNave)) {
            float escx = (2.0f * rad) / BiGS::imageWidth(*imgNave);
            float escy = (2.0f * rad) / BiGS::imageHeight(*imgNave);
            float anguloRad = direc.ang(Vector2D::Uds::Radianes);

            BiGS::imageDraw(*imgNave, pos.x() - rad, pos.y() - rad, escx, escy, anguloRad);
        } else {
            float anguloRad = direc.ang(Vector2D::Uds::Radianes);
            BiGS::drawTriangleEqui(pos.x(), pos.y() - rad, 2.0f * rad, CWhite, CTransparent, 2, anguloRad);
        }
    } else if (tipe == 2) { // Asteroide
        if (imgAsteroide != nullptr && !BiGS::imageEmpty(*imgAsteroide)) {
            float escx = (2.0f * rad) / BiGS::imageWidth(*imgAsteroide);
            float escy = (2.0f * rad) / BiGS::imageHeight(*imgAsteroide);
            float anguloRad = vel.ang(Vector2D::Uds::Radianes);

            BiGS::imageDraw(*imgAsteroide, pos.x() - rad, pos.y() - rad, escx, escy, anguloRad);
        } else {
            BiGS::drawCircle(pos.x(), pos.y(), rad, CRed, CTransparent, 2);
        }
    } else { // Disparos
        BiGS::drawCircle(pos.x(), pos.y(), rad, CBlue, CBlue);
    }

    if (flechas) {
        float tpunta = 5, tbase = 1;
        drawArrow(pos.x(), pos.y(), pos.x() + direc.x(), pos.y() + direc.y(), tbase, tpunta, CBlue);
        drawArrow(pos.x(), pos.y(), pos.x() + vel.x(), pos.y() + vel.y(), tbase, tpunta, CYellow);
        drawArrow(pos.x(), pos.y(), pos.x() + acel.x(), pos.y() + acel.y(), tbase, tpunta, CRed);
    }
}

void Particula::difunto(bool d) {
    difunt = d;
}

void Particula::tvida(double t){
 t_vida = t;
}

void Particula::tiniciovida(double t){
    t_inicioVida = t;
}

//Cinematica
void Particula::avanzaMRU(double dt){
    double nueva_posx, nueva_posy;

    nueva_posx = pos.x() + vel.x() * dt;
    nueva_posy = pos.y() + vel.y() * dt;
    
    pos.x(nueva_posx);
    pos.y(nueva_posy);
}

void Particula::avanzaMUA(double dt){
    double nueva_posx, nueva_posy, nueva_velx, nueva_vely;

    nueva_posx = pos.x() + vel.x() * dt + 0.5*acel.x()*dt*dt;
    nueva_posy = pos.y() + vel.y() * dt + 0.5*acel.y()*dt*dt;
    nueva_velx = vel.x() + acel.x() * dt;
    nueva_vely = vel.y() + acel.y() * dt;

    pos.x(nueva_posx);
    pos.y(nueva_posy);
    vel.x(nueva_velx);
    vel.y(nueva_vely);
}

void corrige_velocidad(Particula &a1, Particula &a2) {
    Vector2D v1 = a1.velocidad();
    Vector2D v2 = a2.velocidad();
    if ((v1.x()-v2.x())*(a2.posicion().x()-a1.posicion().x())
        + (v1.y()-v2.y())*(a2.posicion().y()-a1.posicion().y()) >= 0) {
      double sum = a1.masa() + a2.masa();
      Vector2D difp12 = a1.posicion() - a2.posicion();
      Vector2D difp21 = a2.posicion() - a1.posicion();
      double dot1 = difp12 * (v1-v2);
      double dot2 = (v2-v1) * difp21;
      double norma1 = difp12.mod();
      norma1 *= norma1;
      double norma2 = difp21.mod();
      norma2 *= norma2;
      Vector2D nueva_v1 = v1 - (2*a2.masa()/sum) * dot1 * (1.0/norma1) * difp12;
      Vector2D nueva_v2 = v2 - (2*a1.masa()/sum) * dot2 * (1.0/norma2) * difp21;
      a1.velocidad(nueva_v1);
      a2.velocidad(nueva_v2);
    }
}