/*
____________________________________________________________________________
 ,-----.  ,--. ,----.    ,---.      BiGS: Biblioteca Gráfica Simple
 |  |) /_ `--''  .-./   '   .-'     (C) 2024. Javier Martínez Baena 
 |  .-.  \,--.|  | .---.`.  `-.               (jbaena@ugr.es)
 |  '--' /|  |'  '--'  |.-'    |    Dpto Ciencias de la Computación e I. A.
 `------' `--' `------' `-----'     Universidad de Granada
____________________________________________________________________________

Biblioteca para el desarrollo de aplicaciones gráficas (sencillas) implementada sobre Allegro. Su utilización queda circunscrita a la realización de prácticas para la asignatura Metodología de la Programación del Grado en Ingeniería Informática de la UGR. No se permite su uso o distribución para otros fines sin autorización expresa del autor.
*/

#ifndef BIGS__H
#define BIGS__H

#include <iostream>
#include <string>
// Es obligatorio incluir allegro.h aunque no se utilice nada de él:
//   https://liballeg.org/a5docs/trunk/getting_started.html
//   Sección "The main function"
#include <allegro5/allegro.h>
#include "bigs_defs.h"
#include "bigs_image.h"

// *******************************************************
// BiGS : Biblioteca Gráfica Simple
namespace BiGS {

  // *****************************************************************
  Color colorRGB(unsigned char r, unsigned char g, unsigned char b);
  Color colorRGBf(float r, float g, float b);
  Color colorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  Color colorRandom(bool transp=false);

  // *****************************************************************
  void windowOpen(int w, int h, const char *tit="BiGS app", bool antialias=false, int mode=DRAWMODE_INSTANT);
  int windowWidth();
  int windowHeight();

  // *****************************************************************
  void clear(Color c=CBlack);
  void drawPoint(float x, float y, const Color &c);
  void drawLine(float x1, float y1, float x2, float y2, const Color &c, float g=1, float ang=0.0);
  void drawRectangle(float x1, float y1, float x2, float y2, const Color &c, const Color &cr=CTransparent, float g=1, float ang=0.0);
  void drawCircle(float x, float y, float r, const Color &c, const Color &cr=CTransparent, float g=1);
  void drawEllipse(float x, float y, float rx, float ry, const Color &c, const Color &cr=CTransparent, float g=1, float ang=0.0);
  void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color &c, const Color &cr=CTransparent, float g=1, float ang=0.0);
  void drawTriangleEqui(float x, float y, float lado, const Color &c, const Color &cr=CTransparent, float g=1, float ang=0.0);
  void drawArrow(float x1, float y1, float x2, float y2, float tbase, float tpunta, const Color &c, float g=1, float ang=0.0);

  void refresh();

  // *****************************************************************
  Image imageLoad(const char *fich);
  float imageWidth(const Image &i);
  float imageHeight(const Image &i);
  Color imagePixel(const Image &i, int x, int y);
  bool imageEmpty(const Image &i);
  void imageDraw(const Image &i, float x, float y, float escx=1.0, float escy=1.0, float ang=0.0);
  void imageDrawR(const Image &i, float x1, float y1, float x2, float y2, float ang=0.0);

  // *****************************************************************
  void txtDraw(const char *txt, float x, float y, Color c, Font f=FONT_DEFAULT, int alinea=ALIGN_LEFT, int ancho=0, float ang=0);
  void txtDrawMultiline(const char *txt, float x, float y, float maxw, Color c, Font f=FONT_DEFAULT, int alinea=ALIGN_LEFT, float lineh=0);
  int txtLineHeight(Font f=FONT_DEFAULT);
  int txtFontAscent(Font f=FONT_DEFAULT);
  int txtFontDescent(Font f=FONT_DEFAULT);
  int txtTextWidth(const char *c, Font f=FONT_DEFAULT);
  void txtTextDimensions(const char *c, int &dx, int &dy, int &w, int &h, Font f=FONT_DEFAULT);
  Font txtLoadFont(const char *f, int tam=12);

  // *****************************************************************
  // Gestión de audio
  Audio audioLoad(const char *f);
  void audioPlay(Audio a, int id, float vol=1, float bal=0, float vel=1, PlayMode m=PLAY_ONCE);
  void audioStop(int id=-1);

  // *****************************************************************
  // Gestión de eventos

  // Comportamiento del botón de cierre de la ventana
  //   On : Al pulsarlo se cierra (por defecto)
  //   Off : Al pulsarlo no se cierra. Requiere procesar evento en la app
  void closeOnCloseOn();
  void closeOnCloseOff();
  bool closeRequested();                // Devuelve true si se ha pulsado el cierre de ventana (y closeOnClose=Off)
  
  void logEvents(bool f=true);          // Mostrar o no eventos
  bool eventPresent();                  // Devuelve si hay eventos pendientes de procesar o no
  bool eventNext(Event &ev);            // Devuelve el siguiente evento, si no hay devuelve false
  Event eventWait();                    // Devuelve el siguiente evento, si no hay queda bloqueado
  Event eventWaitKeyboard();            // Devuelve el próximo evento que sea de teclado (descarta otros), si no hay se queda bloqueado
  Event eventWaitMouse();               // Devuelve el próximo evento que sea de ratón (descarta otros), si no hay se queda bloqueado
  void eventFlush();

  std::string eventKeyName(int k);
  std::string to_string(const Event &e);

  bool isKeyPressed(int k);             // Devuelve true si la tecla está pulsada

  // *****************************************************************
  // Gestión de tiempo
  void timeDelay(long int ms);   // En milisegundos
  double timeFromLastCall();     // En microsegundos
  double timeGet();              // Devuelve tiempo transcurrido en microsegundos desde el inicio del programa

};

#endif
