#include "listaparticulas.h"
#include "clasificacion.h"
#include "matematicas.h"
#include "bigs_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cmath>

using namespace std;
using namespace BiGS;

void inicializaNave(Particula &p, double ancho, double alto, double NaveR){
    p.radio(NaveR);
    p.posicion(ancho/2, alto/2);
    p.vmod(0);
    p.amod(0);
    p.vang(-90);
    p.aang(-90);
    p.direccion(-90);
    p.color(CWhite);
    p.tipo(1);
}

Vector2D posAsteroide(Particula &nave, double ancho, double alto){
    Vector2D posicion;
    double posx, posy;

    do {
        posx = aleatorio(0, ancho);
        posy = aleatorio(0, alto);
        posicion = Vector2D(posx, posy);
    } while (distancia(nave.posicion(), posicion) < 50);
        
    return posicion;
}

void inicializaAsteroides(Particula &p, Particula &nave, double ancho, double alto, double AstVMin, double AstVMax, 
                         double AstRMin, double AstRMax, double AstDMin, double AstDMax){
    p.radio(aleatorio(AstRMin,AstRMax));
    p.posicion(posAsteroide(nave, ancho, alto));
    p.vmod(aleatorio(AstVMin, AstVMax));
    p.vang(aleatorio(0,359));
    p.aceleracion(0,0);
    p.densidad(aleatorio(AstDMin,AstDMax));
    p.color(CRed);
    p.tipo(2);
}
 
char * aMinusculas(char * &cad){
    char * aux = cad;
    while(*cad != '\0'){
        *cad = tolower(*cad);
        cad ++;
    }
    return aux;
}

bool colisionan(Particula &p1, Particula &p2){
    bool colision = false;
    if(distancia(p1.posicion(), p2.posicion())  <=  p1.radio() + p2.radio())
        colision = true;
    return colision;
}

void rebote(ListaParticulas &l){
    for(int i=0; i < l.size(); i++){
        for (int j=0; j<l.size(); j++){
            if(i!=j && l.get(i).tipo() == 2 && l.get(j).tipo() == 2
                && distancia(l.get(i).posicion(), l.get(j).posicion())  <=  l.get(i).radio() + l.get(j).radio()){
                corrige_velocidad(l.get(i), l.get(j));
            }
        }
    }
}

//funcion para crear disparos
void crearDisparo(ListaParticulas &l, Particula &disparo, const Particula &nave, double DispTVida, double DispVMin) {
    Vector2D dir = nave.direccion();
    double mod = dir.mod();
    int radio = 2;
    if (mod != 0)
        dir = dir / mod;
    else
        dir = Vector2D(1, 0);

    double vmod = max(DispVMin, nave.velocidad().mod() * 1.2);
    Vector2D vel = dir * vmod;
    Vector2D pos = nave.posicion() + dir * (nave.radio() + 5 + radio);

    disparo = Particula(pos, vel, Vector2D(0, 0), dir, radio, BiGS::CBlue, 3);
    disparo.tvida(DispTVida);
    disparo.tiniciovida(BiGS::timeGet());

    l.inserta(disparo, l.size());
    
}


void eliminarDisparos(ListaParticulas &l, double t) {
    for (int i = 0; i < l.size(); ++i) {
        Particula &p = l.get(i);
        if (p.esDisparo(p) && (t - p.tiniciovida()) > p.tvida()) {
            p.difunto(true);
        }
    }
}

void pasoPantalla(ListaParticulas &l, double ancho, double alto) 
{
    for(int i = 0; i<l.size() ; i++){

        if (l.get(i).posicion().x() > ancho + l.get(i).radio())
            l.get(i).posicion(Vector2D( -l.get(i).radio(), l.get(i).posicion().y()));

        else if (l.get(i).posicion().x() < -l.get(i).radio())
            l.get(i).posicion(Vector2D(l.get(i).radio() + ancho, l.get(i).posicion().y()));

        if (l.get(i).posicion().y() > alto + l.get(i).radio())
            l.get(i).posicion(Vector2D(l.get(i).posicion().x(), -l.get(i).radio()));

        else if (l.get(i).posicion().y() < -l.get(i).radio())
            l.get(i).posicion(Vector2D(l.get(i).posicion().x(), l.get(i).radio() + alto));
    }
}

void incrementoAcel(Particula &nave, double incr){
    nave.aceleracion(nave.aceleracion().mod() + incr, nave.aceleracion().mod());
}

///////////// MAIN ///////////////////////
int main(int argc, char **argv){
    srand(time(NULL));
    if (argc % 2 == 0) {
        cout << "Uso incorrecto de argumentos. Deben venir en pares -param valor" << endl;
        return 1;
    }

    //Inicializar PARÁMETROS
    double AstN = 3, AstRMin = 20, AstRMax = 55, AstRDestruido = 15, AstVMin = 10, AstVMax = 100, AstDMin = 1, AstDMax = 5;
    double NaveR = 32, NaveVMax = 300, NaveAMax = 300;
    double DispMax = 5, DispVMin = 150, DispTVida = 10, destr = 0;
    int puntos = 0;
    string jugador, ficheroRanking;
    bool borde = true;
    bool fin_partida = false;
    bool ganar = false;
    bool useRanking = false;
    double Ancho = 800, Alto = 600;

    for (int i = 1; i < argc; i = i + 2){
        string arg = aMinusculas(argv[i]);
        if(arg != "-jugador" && arg != "-ranking"){
            double val;
            cad2num(argv[i + 1], val);

            if (arg == "-num"){
                AstN = val;
            }else if (arg == "-disparos"){
                DispMax = val;
            }else if (arg == "-tvida"){
                DispTVida = val;
            }else{
                cout << "Argumento desconocido: " << arg << endl;
                return 2;
            }
        }else if(arg == "-jugador"){
            jugador = argv[i + 1];
        }else if(arg == "-ranking"){
            ficheroRanking = argv[i + 1];
            useRanking = true;
        }
        
    }
    windowOpen(Ancho, Alto, "Asteroides", true, DRAWMODE_DELAYED);

    // Carga de imágenes una sola vez y tras abrir la ventana
    BiGS::Image spriteNave = BiGS::imageLoad("nave.png");
    BiGS::Image spriteAsteroide = BiGS::imageLoad("asteroide.png");
    BiGS::Image fondo = BiGS::imageLoad("fondo.png");

    Particula::setImgNave(&spriteNave);
    Particula::setImgAsteroide(&spriteAsteroide);

    ////Inicializar la lista con nave y asteroides
    ListaParticulas l;
    Particula nave;
    inicializaNave(nave, Ancho, Alto, NaveR);
    l.inserta(nave, 0);

    for (int i = 1; i <= AstN; i++) {
        bool insertado;
        Particula asteroide;

        do {
            inicializaAsteroides(asteroide, nave, Ancho, Alto, AstVMin, AstVMax, AstRMin, AstRMax, AstDMin, AstDMax);

            insertado = true;
            int j = 0;

            while (insertado && j < l.size()) {
                if (colisionan(asteroide, l.get(j))) {
                    insertado = false;
                }

                j++;
            }
        } while (!insertado);

        l.inserta(asteroide, i);
    }
    // bucle del juego
    while (!BiGS::closeRequested()){
        double dt = BiGS::timeFromLastCall();
        if (dt > 0.05) dt = 0.05;

        Particula &nave = l.get(0);

        // Vector unitario hacia donde apunta la nave
        Vector2D dir = nave.direccion();
        if (dir.mod() != 0) {
            dir = dir / dir.mod();
        } else {
            dir = Vector2D(0, -1);
        }

        // === ACELERACIÓN (UP) ===
        if (BiGS::isKeyPressed(ALLEGRO_KEY_UP)) {
            nave.aceleracion(dir * NaveAMax);
        }
        // === FRENADO (DOWN) ===
        else if (BiGS::isKeyPressed(ALLEGRO_KEY_DOWN)) {
            nave.aceleracion(nave.velocidad() * -0.5);
        }
        // === SUELTA TECLAS ===
        else {
            nave.aceleracion(Vector2D(0, 0));
        }

        // === GIRO ===
        if (BiGS::isKeyPressed(ALLEGRO_KEY_LEFT)) {
            nave.girar(-180 * dt);
        } else if (BiGS::isKeyPressed(ALLEGRO_KEY_RIGHT)) {
            nave.girar(180 * dt);
        }

        // Friccion suave en el espacio y tope de velocidad
        Vector2D vel = nave.velocidad();
        vel = vel * (1.0 - 0.2 * dt);
        if (vel.mod() > NaveVMax) {
            vel = (vel / vel.mod()) * NaveVMax;
        }
        nave.velocidad(vel);

        BiGS::Event e;

        while (BiGS::eventNext(e)) {
            if (e.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (e.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    int disparos_activos = 0;
                for (int i = 0; i < l.size(); ++i) {
                    Particula &p = l.get(i);
                    if (p.tipo() == 3 && !p.difunto()) {
                        disparos_activos++;
                    }
                }
        
                if (disparos_activos < DispMax) {
                    Particula disparo;
                    crearDisparo(l, disparo, nave, DispTVida, DispVMin);
                    cout << "Disparo creado" << endl;
                } else {
                    cout << "Máximo número de disparos alcanzado" << endl;
                }

                } else if (e.keyboard.keycode == ALLEGRO_KEY_B) {
                    borde = !borde;
                    cout << "cambio de rebote" << endl;
                }
            }
        }

        if(borde){
            choqueBorde(l, Ancho, Alto);
        } else{
            pasoPantalla(l, Ancho, Alto);
        }

        // actualiza estado con el tiempo real transcurrido
        for (int i = 0; i < l.size(); i++){
            Particula &p = l.get(i);
            p.avanzaMUA(dt);
        }

        double t_actual = BiGS::timeGet();
        eliminarDisparos(l, t_actual);

        for (int i = 0; i < l.size() && !fin_partida; ++i) {
            for (int j = i + 1; j < l.size() && !fin_partida; ++j) {
                Particula &p1 = l.get(i);
                Particula &p2 = l.get(j);

                if (p1.difunto() || p2.difunto())
                    continue;

                if (colisionan(p1, p2)) {

                    if (p1.tipo() == 2 && p2.tipo() == 2) {
                        rebote(l);
                    }

                    // Disparo contra asteroide
                    else if ((p1.tipo() == 3 && p2.tipo() == 2) || (p1.tipo() == 2 && p2.tipo() == 3)) {
                        Particula &disparo = (p1.tipo() == 3) ? p1 : p2;
                        Particula &asteroide = (p1.tipo() == 2) ? p1 : p2;
                    
                        disparo.difunto(true);
                    
                        if (asteroide.radio() <= 15) {
                            asteroide.difunto(true);
                            destr = destr + 1;
                        } else {
                            asteroide.difunto(true);
                            destr = destr + 1;
                            Vector2D dir = asteroide.direccion();
                            double mod = dir.mod();
                            if (mod != 0)
                                dir = dir / mod;
                            else
                                dir = Vector2D(1, 0); 
                    
                            Vector2D dir1(-dir.y(), dir.x());
                            Vector2D dir2(dir.y(), -dir.x());
                    
                            double r = asteroide.radio() / 2;
                            Vector2D vel = asteroide.velocidad();
                    
                            // Nueva velocidad para los fragmentos
                            double velMod = vel.mod();
                            Vector2D vel1 = dir1 * (velMod != 0 ? velMod : 30); // valor por defecto si vel=0
                            Vector2D vel2 = dir2 * (velMod != 0 ? velMod : 30);
                    
                            // Separación inicial para que no colisionen instantáneamente
                            Vector2D offset = dir1 * (r + 1);  // separación mínima
                            Vector2D pos1 = asteroide.posicion() + offset;
                            Vector2D pos2 = asteroide.posicion() - offset;
                    
                            Particula a1(pos1, vel1, Vector2D(0, 0), dir1, r, CRed, 2);
                            Particula a2(pos2, vel2, Vector2D(0, 0), dir2, r, CRed, 2);
                    
                            l.inserta(a1, l.size());
                            l.inserta(a2, l.size());
                        }
                        puntos = puntos + asteroide.radio();
                        if(destr >= AstRDestruido){
                            ganar = true;
                        }
                    }

                    // Disparo contra disparo
                    else if (p1.tipo() == 3 && p2.tipo() == 3) {
                        p1.difunto(true);
                        p2.difunto(true);
                    }

                    // Colisión de nave con asteroide
                    else if ((p1.tipo() == 1 && p2.tipo() == 2) || (p1.tipo() == 2 && p2.tipo() == 1)) {
                        fin_partida = true;
                    }
                    
                    else if ((p1.tipo() == 1 && p2.tipo() == 3) || (p1.tipo() == 3 && p2.tipo() == 1)){
                        fin_partida = true;
                    }
                }
            }
        }
        

        // Eliminar difuntos
        for (int i = 0; i < l.size(); ) {
            if (l.get(i).difunto()) {
                l.borra(i);
            } else {
                ++i;
            }
        }

        bool quedan_asteroides = false;
        for (int i = 0; i < l.size(); ++i) {
            if (l.get(i).tipo() == 2) {
                quedan_asteroides = true;
                break;
            }
        }

        if (!quedan_asteroides && !fin_partida) {
            ganar = true;
        }

        if(!fin_partida && !ganar){ 
            if (!BiGS::imageEmpty(fondo)) {
                BiGS::imageDrawR(fondo, 0, 0, Ancho, Alto);
            } else {
                BiGS::clear(BiGS::CBlack); 
            }
            
            for (int i = 0; i < l.size(); i++){
                Particula &p = l.get(i);
                if (i==0)
                    p.dibujar(true);
                else
                    p.dibujar();
            }

            for (int i = 0; i < l.size(); ) {
                if (l.get(i).difunto()) {
                    l.borra(i);
                } else
                    ++i;
            }

            int disp_activos = 0;
            for (int i = 0; i < l.size(); ++i) {
                if (l.get(i).tipo() == 3 && !l.get(i).difunto()) {
                    disp_activos++;
                }
            }
            int disp_restantes = DispMax - disp_activos;

            BiGS::Color fondoCaja = BiGS::colorRGBA(20, 20, 40, 180);
            BiGS::drawRectangle(15, 15, 230, 95, BiGS::CCyan, fondoCaja, 2);

            // 3. Textos del panel
            string txtJugador = "Piloto: " + (jugador.empty() ? "Anonimo" : jugador);
            string txtPuntos  = "Puntos: " + to_string(puntos);
            string txtBalas   = "Municion: " + to_string(disp_restantes) + " / " + to_string((int)DispMax);

            BiGS::txtDraw(txtJugador.c_str(), 25, 25, BiGS::CWhite);
            BiGS::txtDraw(txtPuntos.c_str(),  25, 48, BiGS::CYellow);
            BiGS::txtDraw(txtBalas.c_str(),   25, 71, (disp_restantes > 0 ? BiGS::CGreen : BiGS::CRed));

            BiGS::refresh();
            BiGS::timeDelay(5);

        } else if (fin_partida) {
            BiGS::drawRectangle(Ancho/2 - 200, Alto/2 - 70, Ancho/2 + 200, Alto/2 + 70, BiGS::CRed, BiGS::colorRGBA(10, 10, 10, 220), 3);
            BiGS::txtDraw("GAME OVER", Ancho/2 - 45, Alto/2 - 30, BiGS::CRed);
            BiGS::txtDraw("Pulsa una tecla para salir...", Ancho/2 - 130, Alto/2 + 20, BiGS::CWhite);
            BiGS::refresh();
            
            cout << "\n===============================" << endl;
            cout << "HAS PERDIDO" << endl;
            BiGS::eventWaitKeyboard();
            break;

        } else if (ganar) {
            BiGS::drawRectangle(Ancho/2 - 200, Alto/2 - 70, Ancho/2 + 200, Alto/2 + 70, BiGS::CGreen, BiGS::colorRGBA(10, 10, 10, 220), 3);
            BiGS::txtDraw("YOU WIN!", Ancho/2 - 40, Alto/2 - 30, BiGS::CGreen);
            BiGS::txtDraw("Pulsa una tecla para salir...", Ancho/2 - 130, Alto/2 + 20, BiGS::CWhite);
            BiGS::refresh();

            cout << "\n===============================" << endl;
            cout << "HAS GANADO! ENHORABUENA" << endl;
            BiGS::eventWaitKeyboard();
            break;
        }
    }

    // Gestión del ranking al finalizar
    if (useRanking) {
        Clasificacion ranking;

        // Cargar puntuaciones anteriores 
        ifstream entrada(ficheroRanking);
        if (entrada.is_open()) {
            int pts;
            string nom;
            while (entrada >> pts >> nom) {
                ranking.agregarPuntuacion(nom, pts);
            }
            entrada.close();
        }

        // Añadir la puntuacion de esta partida
        if (jugador.empty()) {
            jugador = "Anonimo";
        }
        ranking.agregarPuntuacion(jugador, puntos);

        // Ordenar y guardar de nuevo
        ranking.ordenarRanking();
        ranking.guardarEnFichero(ficheroRanking);

        // Mostrar por consola
        cout << "Tu puntuacion final: " << puntos << " puntos" << endl;
        ranking.mostrarRanking();
        cout << "===============================\n" << endl;
    }

    return 0;
}




