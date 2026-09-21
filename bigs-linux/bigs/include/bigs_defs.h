#ifndef BIGS_DEFS__H
#define BIGS_DEFS__H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

namespace BiGS {
  
  // ***************************
  // Se utiliza en windowOpen()
  //  DRAWMODE_INSTANT = actualiza en cada operación (y mantiene lo previo)  (Modelo SIMPLE buffer de ALLEGRO)
  //  DRAWMODE_DELAYED = actualiza con refresh() (y mantiene lo previo) (Modelo doble buffer con lienzo/bitmap intermedio)
  //  DRAWMODE_BACKBUFFER = usa modelo doble-buffer de Allegro (actualiza con refresh() pero no mantiene lo previo)
  // Por defecto: DRAWMODE_DELAYED
  #define DRAWMODE_INSTANT 1
  #define DRAWMODE_DELAYED 2
  #define DRAWMODE_BACKBUFFER 3
  
  // ***************************
  // Eventos
  typedef ALLEGRO_EVENT Event;
  enum {
    KEY_DOWN            = ALLEGRO_EVENT_KEY_DOWN,
    KEY_CHAR            = ALLEGRO_EVENT_KEY_CHAR,
    KEY_UP              = ALLEGRO_EVENT_KEY_UP,
    MOUSE_MOVE          = ALLEGRO_EVENT_MOUSE_AXES,
    MOUSE_BUTTON_DOWN   = ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,
    MOUSE_BUTTON_UP     = ALLEGRO_EVENT_MOUSE_BUTTON_UP,
    MOUSE_ENTER         = ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY,
    MOUSE_LEAVE         = ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY,
    DISPLAY_EXPOSE      = ALLEGRO_EVENT_DISPLAY_EXPOSE,
    DISPLAY_CLOSE       = ALLEGRO_EVENT_DISPLAY_CLOSE,
    DISPLAY_FOCUS_IN    = ALLEGRO_EVENT_DISPLAY_SWITCH_IN,
    DISPLAY_FOCUS_OUT   = ALLEGRO_EVENT_DISPLAY_SWITCH_OUT,
    UNKOWN_EVENT        = 1000
  };

  // ***************************
  // Colores
  typedef ALLEGRO_COLOR Color;
  // Algunos colores preestablecidos
  extern Color CTransparent;
  extern Color CBlack;
  extern Color CWhite;
  extern Color CRed;
  extern Color CGreen;
  extern Color CBlue;
  extern Color CCyan;
  extern Color CMagenta;
  extern Color CYellow;

  // ***************************
  // Fuentes
  typedef int Font;
  #define FONT_DEFAULT 0
  #define ALIGN_LEFT       ALLEGRO_ALIGN_LEFT
  #define ALIGN_RIGHT      ALLEGRO_ALIGN_RIGHT
  #define ALIGN_CENTRE     ALLEGRO_ALIGN_CENTRE
  #define ALIGN_JUSTIFIED  99

  // ***************************
  // Audio
  typedef int Audio;
  //typedef int Channel;
  typedef ALLEGRO_PLAYMODE PlayMode;
  #define PLAY_ONCE  ALLEGRO_PLAYMODE_ONCE
  #define PLAY_LOOP  ALLEGRO_PLAYMODE_LOOP
  #define PLAY_BIDIR  ALLEGRO_PLAYMODE_BIDIR

} // namespace

#endif