#ifndef BIGS_IMAGE__H
#define BIGS_IMAGE__H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "bigs_defs.h"

namespace BiGS {

class Image {
  private:
    ALLEGRO_BITMAP *im;

  public:
    Image();
    Image(const Image &orig);
    ~Image();
    Image &operator=(const Image &orig);

    bool load(const char *fich);
    float width() const;
    float height() const;
    BiGS::Color pixel(int x, int y) const;
    bool empty() const;

    void draw(float x, float y, float escx=1.0, float escy=1.0, float ang=0.0) const;
    void drawR(float x1, float y1, float x2, float y2, float ang=0.0) const;

};

}  // namespace

#endif