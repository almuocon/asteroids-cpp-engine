#include "bigs.h"

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(300,180,"BiGS: ¡Hola, mundo!");
  BiGS::drawRectangle(80,70,220,100,BiGS::CRed);
  BiGS::txtDraw("¡Hola, mundo!",100,80,BiGS::CGreen);
  BiGS::eventWaitKeyboard();
  return 0;
}