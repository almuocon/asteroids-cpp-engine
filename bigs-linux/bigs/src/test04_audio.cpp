#include <iostream>
#include "bigs.h"

using namespace std;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(400,200,"BiGS: test04_audio",true);
  //BiGS::logEvents();

  // Texto justificado
  BiGS::txtDraw("Reproduciendo sonido",10,10,BiGS::CWhite,FONT_DEFAULT,ALIGN_LEFT);
  // Actualizar ventana
  BiGS::refresh();

  BiGS::Audio audio;

  // **************************************
  audio = BiGS::audioLoad("data/file_example_OOG_1MG.ogg");
  cout << "Comienza reproducción" << endl;
  BiGS::audioPlay(audio,1);
  BiGS::timeDelay(2000);   // Esperar 2s

  cout << "Detener audio" << endl;
  BiGS::audioStop(1);
  BiGS::timeDelay(1000);   // Esperar 1s

  cout << "Comienza reproducción 2" << endl;
  BiGS::audioPlay(audio,2);
  BiGS::timeDelay(1234);
  cout << "Comienza reproducción 3" << endl;
  BiGS::audioPlay(audio,3);
  BiGS::timeDelay(2543);
  cout << "Comienza reproducción 4" << endl;
  BiGS::audioPlay(audio,4);
  BiGS::timeDelay(1764);

  cout << "Detener audios 3 y 4" << endl;
  BiGS::audioStop(3);
  BiGS::audioStop(4);
  BiGS::timeDelay(3000);

  cout << "Comienza reproducción 3" << endl;
  BiGS::audioPlay(audio,3);
  BiGS::timeDelay(3500);
  cout << "Detener todos los audios" << endl;
  BiGS::audioStop();
  BiGS::timeDelay(2500);

  // **************************************
  cout << "Reproduciendo en bucle" << endl;
  audio = BiGS::audioLoad("data/explosion1.ogg");
  BiGS::audioPlay(audio,3,1,0,1,PLAY_LOOP);
  BiGS::timeDelay(2500);

  cout << "Ya puedes cerrar la ventana" << endl;
  while (!BiGS::closeRequested()) {
    /*cout << "esperando ..." << i << endl;
    i++;
    if (i%10000 == 0)
      BiGS::audioPlay(audio);*/

    BiGS::timeDelay(10);
  }

  return 0;
}