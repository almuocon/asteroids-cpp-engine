#include <iostream>
#include "bigs.h"

using namespace std;

/*void f(const BiGS::Image &i) {
  BiGS::Image x = i;
  i.draw(100,100,2,2);
}*/

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(500,400,"BiGS: test02_image",true);
  //BiGS::logEvents();

  // Imágenes (con rotaciones y escalados)
  BiGS::Image im1 = BiGS::imageLoad("./data/cpp2.png"); 
  //BiGS::imageDraw(im1,10,10);
  im1.draw(10,10);

  float width = BiGS::imageWidth(im1);
  float height = BiGS::imageHeight(im1);

  //BiGS::imageDraw(im1,10,height+20,0.2,0.5);
  //BiGS::imageDraw(im1,20+width*0.2,height+20,0.8,0.4);
  im1.draw(10,height+20,0.2,0.5);
  im1.draw(20+width*0.2,height+20,0.8,0.4);

  //BiGS::imageDraw(im1,width+40,10,1,1,0.4);
  //BiGS::imageDraw(im1,width+40,height+20,0.5,0.5,0.8);
  //BiGS::imageDraw(im1,width+40,height+40+height*0.5,0.5,0.5,1.2);
  im1.draw(width+40,10,1,1,0.4);
  im1.draw(width+40,height+20,0.5,0.5,0.8);
  im1.draw(width+40,height+40+height*0.5,0.5,0.5,1.2);

  //BiGS::imageDrawR(im1,370,10,400,120);
  //BiGS::imageDrawR(im1,410,10,450,30);
  im1.drawR(370,10,400,120);
  im1.drawR(410,10,450,30);

  //BiGS::imageDrawR(im1,370,150,400,260,0.5);
  im1.drawR(370,150,400,260,0.5);

  // Actualizar ventana
  BiGS::refresh();

  /*BiGS::Image xx(im1);
  xx.draw(200,200,2,2,0);
  BiGS::refresh();*/

  /*BiGS::Image xx;
  xx = im1;
  xx.draw(200,200,2,2,0);
  BiGS::refresh();*/

  /*f(im1);
  im1.draw(200,200,2,2,0);
  BiGS::refresh();*/

  BiGS::eventFlush();
  cout << "Esperando evento" << endl;
  BiGS::eventWait();

  /*BiGS::Image i1,i2,i3;
  i1 = im1;


  i2 = im1;
  //BiGS::imageFree(im1);
  i3 = i1;
  im1 = i2;
  //BiGS::imageFree(i1);

  //f(im1);
  //im1.draw(200,200,2,2,0);
  BiGS::refresh();
*/
  while (!BiGS::closeRequested()) {
    BiGS::timeDelay(10);
  }

  //BiGS::imageFree(im1);

  return 0;
}