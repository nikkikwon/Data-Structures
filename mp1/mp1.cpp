#include <string>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
//Read in inputFile,
//Rotate the image 180 degrees,
//Write the rorated image out as outputFile

  PNG input;
  PNG output;
  
  input.readFromFile(inputFile);
  output.readFromFile(inputFile);
  unsigned int width = input.width();
  unsigned int height = input.height();


  for (unsigned int x = 0; x < width; x++)
  {
    for (unsigned int y = 0; y < height; y++)
    {
      HSLAPixel * ptr1 = input.getPixel(x,y);
      HSLAPixel * ptr2 = output.getPixel(width-x-1, height-y-1);
     
      ptr2 -> h = ptr1 -> h; 
      ptr2 -> s = ptr1 -> s;
      ptr2 -> l = ptr1 -> l;
      ptr2 -> a = ptr1 -> a;

    }  

  }

  output.writeToFile(outputFile);
}















