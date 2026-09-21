#include <iostream>
#include <cmath>
#include "bigs.h"

using namespace std;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(600,600,"BiGS: test02_draw", true, DRAWMODE_INSTANT);
  //BiGS::logEvents();

  // Puntos
  for (int x=10; x<590; x+=10)
    BiGS::drawPoint(x,10,BiGS::colorRGB(100+rand()%150,100+rand()%150,100+rand()%150));

  int maxx=80;
  int maxy=80;
  for (int i=0; i<maxx; i++)
    for (int j=0; j<maxy; j++)
      BiGS::drawPoint(10+i,510+j,BiGS::colorRGB(i/(float)maxx*255,j/(float)maxy*255,(maxx-i)/(float)(maxx)*255));

  // Líneas
  for (int i=0; i<10; i++)
    BiGS::drawLine(10,20+i*(i/2.0+5),50,20+i*(i/2.0+5),BiGS::CRed,1+i);

  int max=20;
  for (int i=0; i<max; i++)
    BiGS::drawLine(10,130+i*10,100,130+((max-1)*10-i*10),BiGS::colorRandom());

  // Círculos y blending
  BiGS::drawCircle(60,400,50,BiGS::CWhite,BiGS::colorRGBA(255,0,0,0),5);
  BiGS::drawCircle(110,400,50,BiGS::CMagenta,BiGS::colorRGBA(0,255,0,0),5);
  BiGS::drawCircle(85,450,50,BiGS::CCyan,BiGS::colorRGBA(0,0,255,0),5);

  // Rectángulos
  for (int i=0; i<5; i++)
    BiGS::drawRectangle(70+i*5,20+i*5,150-i*5,70-i*5,BiGS::CCyan);
  
  BiGS::drawRectangle(70,80,100,110,BiGS::CRed,BiGS::CBlue);
  BiGS::drawRectangle(120,80,140,110,BiGS::CRed,BiGS::CBlue,4);

  // Elipses aleatorias
  for (int i=0; i<20; ++i) {
    BiGS::drawEllipse(200+rand()%350,40+rand()%100,5+rand()%20,5+rand()%20,
                     BiGS::colorRGB(100+rand()%150,100+rand()%150,100+rand()%150));
    BiGS::drawEllipse(200+rand()%350,40+rand()%100,5+rand()%20,5+rand()%20,
                    BiGS::colorRGB(100+rand()%150,100+rand()%150,100+rand()%150),
                    BiGS::colorRGB(100+rand()%150,100+rand()%150,100+rand()%150));
    BiGS::drawEllipse(200+rand()%350,40+rand()%100,5+rand()%20,5+rand()%20,
                    BiGS::colorRGB(100+rand()%150,100+rand()%150,100+rand()%150),
                    BiGS::colorRGBA(100+rand()%150,100+rand()%150,100+rand()%150,100+rand()%150));
    BiGS::drawEllipse(200+rand()%350,40+rand()%100,5+rand()%20,5+rand()%20,
                    BiGS::colorRGB(100+rand()%150,100+rand()%150,100+rand()%150),
                    BiGS::CTransparent,1+rand()%6);
    BiGS::drawEllipse(200+rand()%350,40+rand()%100,5+rand()%20,5+rand()%20,
                    BiGS::colorRandom(),
                    BiGS::colorRandom(true),1+rand()%6);
  }

  // Triángulos
  BiGS::drawTriangle(130,170,250,170,225,220,BiGS::colorRandom(),BiGS::colorRandom(),3);
  BiGS::drawTriangle(140,200,210,190,200,230,BiGS::colorRandom(),BiGS::colorRandom(true),2);
  BiGS::drawTriangle(160,240,230,250,225,290,BiGS::colorRandom(),BiGS::colorRandom(),1);
  BiGS::drawTriangle(150,280,240,260,200,310,BiGS::colorRandom(),BiGS::colorRandom(true),4);
  BiGS::drawTriangle(160,310,220,300,200,200,BiGS::colorRandom(),BiGS::colorRandom(true),2);

  // Rotaciones de líneas
  max=10;
  double mang = 3.1415926535 / 2;
  for (int i=0; i<max; i++)
    BiGS::drawLine(270,210,350,210,BiGS::colorRandom(),1,i*mang/(max-1));

  // Rotaciones de rectángulos
  max=4;
  mang = 3.1415926535 / 2;
  for (int i=0; i<max; i++)
    BiGS::drawRectangle(380,180,440,230,BiGS::colorRandom(),BiGS::colorRandom(true),1,i*mang/(max));

  // Rotaciones de elipses
  max=4;
  mang = 3.1415926535 / 2;
  for (int i=0; i<max; i++)
    BiGS::drawEllipse(510,200,40,20,BiGS::colorRandom(),BiGS::colorRandom(true),1,i*mang/(max));

  // Rotaciones de triángulos
  max=8;
  mang = 3.1415926535 / 2;
  for (int i=0; i<max; i++)
    BiGS::drawTriangle(270,350,300,270,330,350,BiGS::colorRandom(),BiGS::colorRandom(),1,i*mang/(max));

  // Triángulos equiláteros
  max = 6;
  for (int i=0; i<max; i++)
    BiGS::drawTriangleEqui(250,400,100,BiGS::colorRandom(),BiGS::colorRandom(),1,i*mang/max);
  BiGS::drawCircle(250,400,3,BiGS::CWhite,BiGS::CWhite,1);

  // Flechas
  BiGS::drawArrow(400,400,500,500,0,20,BiGS::CRed,1,0);
  BiGS::drawArrow(400,500,500,400,2,20,BiGS::CRed,1,0);
  BiGS::drawArrow(400,450,500,450,4,20,BiGS::CRed,1,0);

  // Actualizar ventana
  BiGS::refresh();

  while (!BiGS::closeRequested()) {
    BiGS::timeDelay(10);
  }

  return 0;
}