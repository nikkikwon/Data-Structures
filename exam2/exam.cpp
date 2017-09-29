// Your code here!
#include "exam.h"
using namespace exam;

   Matrix exam:: flip_rows(const Matrix &m)
   {

     int row,col;
     row = m.get_num_rows();
     col = m.get_num_columns();
     int start, end, temp;
     int count = col/2;

     Matrix result(row, col);
  
     for(int i=0; i<row; i++)
     { 
        for(int j=0; j<col; j++) 
	{

            result.set_coord(i,j,(i + j) % 10);

        }
     }




     for (int x=0; x<row; x=x+2)
     {
       for (int y=0; y<col; y++)
       {
         if (col == 1 || row ==1 || col == 0 || row == 0)
          break;

         start = m.get_coord(x,y);
         temp = start;
         end = m.get_coord(x+1,y);
         result.set_coord(x,y, end);
         result.set_coord(x+1,y,temp);
       }
     count = count-1;
     if (count ==0)
       break;
     }

   return result;     
   }


