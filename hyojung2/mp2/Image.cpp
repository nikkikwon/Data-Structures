#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using namespace cs225;

    void Image::lighten()
    {
       for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->l = pixel->l + 0.1;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->l) < 0 )
            pixel->l = 0;
 	   if ((pixel->l) >1 )
            pixel->l = 1;  
         }
       }
     }

    void Image::lighten(double amount)
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->l = pixel->l + amount;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->l) < 0 )
            pixel->l = 0;
 	   if ((pixel->l) >1 )
            pixel->l = 1;  
         }
       }
    }
    void Image::darken()
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->l = pixel->l - 0.1;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->l) < 0 )
            pixel->l = 0;
 	   if ((pixel->l) >1 )
            pixel->l = 1;  
         }
       }
    }
    void Image::darken(double amount)
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->l = pixel->l - amount;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->l) < 0 )
            pixel->l = 0;
 	   if ((pixel->l) >1 )
            pixel->l = 1;  
         }
       }
    }
    void Image::saturate()
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->s = pixel->s + 0.1;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->s) < 0 )
            pixel->s = 0;
 	   if ((pixel->s) >1 )
            pixel->s = 1;  
         }
       }
    }
    void Image::saturate(double amount)
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->s = pixel->s + amount;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->s) < 0 )
            pixel->s = 0;
 	   if ((pixel->s) >1 )
            pixel->s = 1;  
         }
       }
    }
    void Image::desaturate()
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->s = pixel->s - 0.1;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->s) < 0 )
            pixel->s = 0;
 	   if ((pixel->s) >1 )
            pixel->s = 1;  
         }
       }
    }
    void Image::desaturate(double amount)
    {
      for (unsigned x = 0; x < width(); x++) 
       {
         for (unsigned y = 0; y < height(); y++) 
         {
           HSLAPixel *pixel = getPixel(x, y);
           pixel->s = pixel->s - amount;
 	   
	   //make sure the luminance keep the range of [0,1]
	   if ((pixel->s) < 0 )
            pixel->s = 0;
 	   if ((pixel->s) >1 )
            pixel->s = 1;  
         }
       }
    }
    void Image::grayscale()
    {
      for (unsigned x = 0; x < width(); x++) 
      {
        for (unsigned y = 0; y < height(); y++) 
        {
          HSLAPixel *pixel = getPixel(x, y); 
          pixel->s = 0;
        }
      }
    }
    
    void Image::rotateColor(double degrees)
    {
      for (unsigned int x = 0; x < width(); x++)
      {
        for (unsigned int y = 0; y < height(); y++)
        {
          HSLAPixel * pixel = getPixel(x,y);
          pixel->h = pixel->h + degrees;
          while ((pixel->h) > 360) 
          {
	    pixel->h = (pixel->h)-360;
	  }
          while ((pixel->h) < 0)
          {
 	    pixel->h = (pixel->h)+360;
	  }
        }  
      }    
    }

    void Image::illinify()
    {
      for (unsigned x = 0; x < width(); x++) 
      {
        for (unsigned y = 0; y < height(); y++) 
        {
          HSLAPixel *pixel = getPixel(x, y);

          if ( (pixel -> h) <= 112.0 || (pixel -> h) >= 293  )
            pixel -> h = 11.0;

          else 
 	    pixel -> h = 216.0;
        }
      }

    }

    void Image::scale(double factor)
    {
      Image original = *this;    

      resize(width() * factor ,height() * factor);

      for (unsigned int i=0; i < width() ; i++ )
      {
        for (unsigned int j=0; j < height() ; j++ )
        {
	  HSLAPixel *pixel = getPixel(i, j);
	 
          unsigned int newx=(unsigned int)i/factor;
          unsigned int newy=(unsigned int)j/factor;

	  HSLAPixel *pixelOriginal = original.getPixel(newx,newy);

	  pixel->h = pixelOriginal -> h;
          pixel->s = pixelOriginal -> s;
          pixel->l = pixelOriginal -> l;
 	  pixel->a = pixelOriginal -> a;
        }	
      }    
    }

    void Image::scale(unsigned w, unsigned h)
    {
      double factor;
      if (w < h)
        factor = w/width();
      else 
        factor = h/height();

      Image original = *this;    

      resize(width() * factor ,height() * factor);

      for (unsigned int i=0; i < width() ; i++ )
      {
        for (unsigned int j=0; j < height() ; j++ )
        {
	  HSLAPixel *pixel = getPixel(i, j);
	  unsigned int newx=(unsigned int)i/factor;
          unsigned int newy=(unsigned int)j/factor;

	  HSLAPixel *pixelOriginal = original.getPixel(newx,newy);

	  pixel->h = pixelOriginal -> h;
          pixel->s = pixelOriginal -> s;
          pixel->l = pixelOriginal -> l;
 	  pixel->a = pixelOriginal -> a;
        }	
      }    
    }
    


