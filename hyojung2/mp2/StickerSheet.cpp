#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"

using namespace std;
using namespace cs225;

    StickerSheet:: StickerSheet (const Image &picture, unsigned max)
    {
      //base_ = picture;

      //Image base=picture;
      max_ = max;
      layer_=new Image*[max];

      x_=new unsigned int[max];
      y_=new unsigned int[max];

      for (unsigned int i=0; i < max; i++)
      {
	layer_[i]=NULL; 
        x_[i]=0;
	y_[i]=0;
      } 
      layer_[0]=new Image;
      *layer_[0]=picture;
    }

    StickerSheet:: ~StickerSheet ()
    {   
      remove(); 
    }
    
    void StickerSheet:: remove()
    {
      for (unsigned int i=0; i < max_; i++)
      {
	delete layer_[i];
        layer_[i]=NULL;
      }
      delete[] layer_;
      delete[] x_;
      delete[] y_;

      layer_=NULL;
      x_=NULL;
      y_=NULL;
    }

    StickerSheet:: StickerSheet (const StickerSheet &other)
    {
        copy(other);  
    }

    void StickerSheet:: copy(const StickerSheet &other)
    {

      //base_ = other.base_;
      max_ = other.max_;

      layer_=new Image*[max_];
      x_=new unsigned int[max_];
      y_=new unsigned int[max_];
   
      for (unsigned int i=0; i < max_; i++)
      {
	layer_[i]=NULL;
 	x_[i]=0;
	y_[i]=0;
      }
      
      for (unsigned int i=0; i < max_; i++)
      {
        if(other.layer_[i] != NULL)
        {
	  layer_[i]= new Image;
          *layer_[i]= *(other.layer_[i]);
 	  x_[i]= other.x_[i];
 	  y_[i]= other.y_[i];
          	
	}                
      }

    }
 
   const StickerSheet& StickerSheet:: operator = (const StickerSheet &other)
    {
      if (this == &other)
	return *this;
      else
      {
	remove();
        copy(other);
        return *this; 
      }       
    }
 
// CHECKED!
   
    void StickerSheet:: changeMaxStickers (unsigned max)
    {
      //no need to do anything when the updated max same as orig
      if (max_== max)
        return;

      //make another copy of current instance's x_,y_ array.
      //StickerSheet temp(this->base_, this->max_);

      StickerSheet temp(*(this->layer_[0]), this->max_);
      temp=*this;
     
      //remove the previously allocated memory of x_,y_of current instance      
      remove(); 

      max_= max;
          
      layer_=new Image*[max];
      x_=new unsigned int[max];
      y_=new unsigned int[max];
    
      for (unsigned int i=0; i < max; i++)
      {
        layer_[i]=NULL;
	x_[i]=0;
	y_[i]=0;
      } 
      //put base pic in (done below?)
      //layer_[0]=temp.layer_[0];

      if (temp.max_ < max)
      {
	for (unsigned int i = 0; i < temp.max_; i++)
	{
          layer_[i]=temp.layer_[i];
	  x_[i]=temp.x_[i];
	  y_[i]=temp.y_[i];
	}
      }
      //new maximum is smaller than the previous one
      else
      {
	for(unsigned int i = 0; i < max; i++)
 	{
	  layer_[i]=temp.layer_[i];
	  x_[i]=temp.x_[i];
	  y_[i]=temp.y_[i];
	}
      }
      //remove mem allocated for temp
      for (unsigned int i=0; i < temp.max_; i++)
      {  
        delete layer_[i];
	layer_[i]=NULL;
      }
      delete[] layer_;
      delete[]temp.x_;
      delete[]temp.y_;

      temp.layer_=NULL;
      temp.x_=NULL;
      temp.y_=NULL; 
    }


    int StickerSheet:: addSticker (Image &sticker, unsigned x, unsigned y)
    {
      for(unsigned int index=0; index < max_; index++)
      {
	if (layer_[index]== NULL)
	{
	  layer_[index] = new Image;
          (*layer_[index])=sticker;
	  x_[index]=x; 
	  y_[index]=y;
	  return index;
	}
      }
      return -1;
     
    }

    bool StickerSheet:: translate (unsigned index, unsigned x, unsigned y)
    {
      if (index > max_)
        return false;
      if (layer_[index]==NULL)
	return false;

      x_[index]=x;
      y_[index]=y;
      return true;	
    }
	
    void StickerSheet:: removeSticker (unsigned index)
    {
      delete layer_[index];
      layer_[index]=NULL;
    }
  
    Image* StickerSheet:: getSticker (unsigned index) const
    {
      if (index > max_)
        return NULL;
      if (layer_[index]==NULL)
	return NULL;
      return layer_[index];    
    }
    
    Image StickerSheet:: render() const
    {
   
      unsigned int height=0;
      unsigned int width=0;

      for(unsigned int i=0; i < max_; i++)
      {
	if(layer_[i] != NULL)
   	{
	  if( x_[i] + layer_[i] -> width() > width )
	    width = x_[i] + layer_[i] -> width(); 

	  if( y_[i] + layer_[i] -> height() > height )
	    height = y_[i] + layer_[i] -> height();
	}
      }  

      //make an image with width and height adjusted(base image and stickers all considered)

      Image output;
      output.resize(width, height);
      

      for(unsigned int i =0; i < max_; i++)
      {
	if(layer_[i] != NULL)
	{
	  unsigned int wid = layer_[i]->width();
	  unsigned int hei = layer_[i]->height();
	  unsigned int xval=x_[i];
	  unsigned int yval=y_[i];
	
	  for(unsigned int x = 0; x < wid; x++ )
	  {
	    for(unsigned y = 0; y < hei; y++)
	    {
		HSLAPixel *pixelout = output.getPixel(x+xval, y+yval);
		HSLAPixel *pixel = (*layer_[i]).getPixel(x,y);
		if( (*pixel).l != 1)
			*(pixelout)=*(pixel);
 	    }
	  }
	}
      }
 
   return output;
   }
								








