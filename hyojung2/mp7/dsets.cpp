/* Your code here! */

#include "dsets.h"


/**
*  This function creates n unconnected root nodes at the end of the vector.
**/
void DisjointSets::addelements(int n)
{
    for(int i = 0; i < n; i++)
    {
		s.push_back(-1);
	}
}

/**
*  This function should compress paths and works as described in lecture. 
*  It finds and returns the representative element. 
**/
int DisjointSets::find(int i)
{
	if(s[i] < 0)
		return i;
	else
		return s[i] = find(s[i]);
}

/**
*  This function implements union-by-size. It first gets representative(root element) of the 
*  disjoint set then apply union-by-size algorithm. 
**/
void DisjointSets::setunion(int a, int b)
{
	int r1 = find(a);
	int r2 = find(b);
    int newSize = s[r1] + s[r2];
    
    if(s[r1] <= s[r2])
    {
		s[r2] = r1;
		s[r1] = newSize;
    }
    else
    {
		s[r1] = r2;
		s[r2] = newSize;
	}
}


