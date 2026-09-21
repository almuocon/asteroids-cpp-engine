#include <iostream>
#include "bigs.h"

using namespace std;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(600,600,"BiGS: test03_font",true,DRAWMODE_INSTANT);
  //BiGS::logEvents();

  // Texto justificado
  BiGS::txtDraw("¡Hola, mundo!",10,10,BiGS::CWhite,FONT_DEFAULT,ALIGN_LEFT);
  BiGS::txtDraw("¡Hola, mundo!",160,25,BiGS::CRed,FONT_DEFAULT,ALIGN_RIGHT);
  BiGS::txtDraw("¡Hola, mundo!",80,40,BiGS::CGreen,FONT_DEFAULT,ALIGN_CENTRE);
  BiGS::txtDraw("¡Hola, mundo (y van 4)!",10,55,BiGS::CBlue,FONT_DEFAULT,ALIGN_JUSTIFIED,200);
  BiGS::refresh();

  // Texto multilínea
  BiGS::txtDrawMultiline("Esto es un texto de prueba con varias líneas",10,70,100,BiGS::CCyan,FONT_DEFAULT,ALIGN_LEFT);
  BiGS::txtDrawMultiline("Esto es un texto de prueba con varias líneas",110,110,100,BiGS::CMagenta,FONT_DEFAULT,ALIGN_RIGHT);
  BiGS::txtDrawMultiline("Esto es un texto de prueba con varias líneas",110,160,100,BiGS::CMagenta,FONT_DEFAULT,ALIGN_RIGHT);
  BiGS::refresh();

  // Espaciado entre líneas (altura de cada línea)
  BiGS::txtDrawMultiline("Esto es un texto de prueba con varias líneas",10,200,100,BiGS::CGreen,FONT_DEFAULT,ALIGN_LEFT,5);
  BiGS::txtDrawMultiline("Esto es un texto de prueba con varias líneas",10,230,100,BiGS::CRed,FONT_DEFAULT,ALIGN_LEFT,20);
  BiGS::refresh();

  // Cargar fuentes TTF
  BiGS::Font frob = BiGS::txtLoadFont("data/roboto.ttf",16);
  BiGS::Font flc24 = BiGS::txtLoadFont("data/lastchristmas.otf",24);
  BiGS::Font flc36 = BiGS::txtLoadFont("data/lastchristmas.otf",36);
  BiGS::Font flc48 = BiGS::txtLoadFont("data/lastchristmas.otf",48);
  BiGS::Font fe = BiGS::txtLoadFont("data/ethnocentric.otf",14);
  //Font flcd = BiGS::txtLoadFont("data/open24display.ttf",36);
  BiGS::Font flcd = BiGS::txtLoadFont("data/technology.ttf",36);
  BiGS::txtDraw("Tipo de letra Roboto",220,10,BiGS::CYellow,frob,ALIGN_LEFT);
  BiGS::txtDraw("Last Christmas",220,35,BiGS::CGreen,flc24,ALIGN_LEFT);
  BiGS::txtDraw("Last Christmas",220,65,BiGS::CBlue,flc36,ALIGN_LEFT);
  BiGS::txtDraw("Last Christmas",220,105,BiGS::CRed,flc48,ALIGN_LEFT);

  BiGS::txtDrawMultiline("Esto es un texto de prueba con varias líneas con el tipo de fuente EthnoCentric",220,160,300,BiGS::CMagenta,fe,ALIGN_LEFT);
  BiGS::refresh();

  // Rotación del texto
  int nrot = 5;
  float an = 3.1415926535 / 2;
  for (int i=0; i<nrot; i++)
    BiGS::txtDraw("Texto rotado",240,310,BiGS::colorRandom(),flcd,ALIGN_LEFT,0,i*an/nrot);

  // Actualizar ventana
  BiGS::refresh();

  while (!BiGS::closeRequested()) {
    BiGS::timeDelay(10);
  }

  return 0;
}