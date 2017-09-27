#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

class StickerSheet{

    public:
   
    StickerSheet (const Image &picture, unsigned max);
    ~StickerSheet ();
    StickerSheet (const StickerSheet &other);
    const StickerSheet& operator = (const StickerSheet &other);
    void changeMaxStickers (unsigned max);
    int addSticker (Image &sticker, unsigned x, unsigned y);
    bool translate (unsigned index, unsigned x, unsigned y);	
    void removeSticker (unsigned index);
    Image* getSticker (unsigned index) const;
    Image render() const;
    
    
    private:

    Image base_;
    Image **layer_;
    unsigned max_;
    unsigned *x_;
    unsigned *y_;
    void copy(const StickerSheet &other);
    void remove();
};
#endif
