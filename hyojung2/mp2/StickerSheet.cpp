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
      //created var for base pic Image base_
      base_ = picture;

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
      //layer_[0]=new Image;
      //*layer_[0]=picture;
    }


    StickerSheet:: ~StickerSheet()
    {   
//error here 
     remove(); 
    }
    
    void StickerSheet:: remove()
    {
      for (unsigned int i=0; i < max_; i++)
      {
//'delete' to delete previously layer_[i]=new image; assigned image pointer(HEAP)
        if(layer_ != NULL)
	    {
	      delete layer_[i];
          layer_[i]=NULL;
    	}
      }
      delete[] layer_;
      layer_=NULL;

      if (x_ != NULL)
      {
        delete[] x_;
        x_=NULL;
      }
     
      if (y_ != NULL)
      {
        delete[] y_;
        y_=NULL;
      }     
    }

    StickerSheet:: StickerSheet (const StickerSheet &other)
    {
        copy(other);  
    }

    void StickerSheet:: copy(const StickerSheet &other)
    {

      //base_ = other.base_;
      base_=other.base_;
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
      //changed from this->max_ to max;

      StickerSheet temp(base_, max_);
      temp=*this;
   
      //remove the previously allocated memory of x_,y_of current instance
      //remove(); to this.remove() this -> remove();      
      remove(); 

      max_= max;
       
      //put base pic in (done below?)  
      base_=temp.base_; 

      layer_=new Image*[max_];
      x_=new unsigned int[max_];
      y_=new unsigned int[max_];
     
      for (unsigned int i=0; i < max_; i++)
      {
        layer_[i]=NULL;
	    x_[i]=0;
	    y_[i]=0;
      } 
 
    
      //layer_[0]=temp.layer_[0];

      if (temp.max_ < max_)
      {
       // layer_=new Image*[max];
       // x_=new unsigned int[max];
       //y_=new unsigned int[max];
   
	    for (unsigned int i = 0; i < temp.max_; i++)
    	{
          //layer_[i]=temp.layer_[i];
          if(temp.layer_[i] != NULL)
          {
             layer_[i]= new Image;
             *layer_[i]= *(temp.layer_[i]);
          }
          else
             layer_[i] = NULL;

	      x_[i]=temp.x_[i];
	      y_[i]=temp.y_[i];
	    }
      }
      //new maximum is smaller than the previous one
      else
      {
	    for(unsigned int i = 0; i < max_; i++)
 	    {
	      //layer_[i]=temp.layer_[i];
          if (temp.layer_[i] != NULL)
          {
            layer_[i]= new Image;
            *layer_[i]= *(temp.layer_[i]);
          }
          else
              layer_[i] = NULL;

	      x_[i]=temp.x_[i];
	      y_[i]=temp.y_[i];
    	}
      }

      //remove mem allocated for temp
      //deleted previous and added temp.remove();
      temp.remove();
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
      output.resize(base_.width(), base_.height());
      Image basenew = base_;

      for(unsigned int x = 0; x < output.width(); x++ )
	  {
	    for(unsigned y = 0; y < output.height(); y++)
	    {
		HSLAPixel *pixelout = output.getPixel(x, y);
		HSLAPixel *pixel = (basenew).getPixel(x,y);
		if( (*pixel).l != 1)
			*(pixelout)=*(pixel);
 	    }
	  }
      

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
								








