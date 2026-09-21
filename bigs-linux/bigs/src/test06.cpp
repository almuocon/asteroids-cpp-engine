#include <iostream>
#include "bigs.h"

using namespace std;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  //BiGS &bigs = BiGS::getInstance();

  BiGS::logEvents();
  BiGS::windowOpen(400,400,"BiGS: test01");

  BiGS::Event ev;

  /*while (!BiGS::closeRequested()) {  
    BiGS::eventNext(ev);
  }*/

  /*int i=0;
  while (!BiGS::closeRequested()) {
    i++;
    cout << i << endl;
    ev = BiGS::eventWait();
  }*/
 
  /*int i=0;
  while (!BiGS::closeRequested()) {
    i++;
    cout << i << endl;
    ev = BiGS::eventWaitKeyboard();
  }*/


  while (!BiGS::closeRequested()) {  
    if (BiGS::isKeyPressed(ALLEGRO_KEY_A))
      cout << "Está pulsada la A" << endl;
    if (BiGS::isKeyPressed(ALLEGRO_KEY_B))
      cout << "Está pulsada la B" << endl;
    BiGS::timeDelay(10);
  }

  return 0;
}