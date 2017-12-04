/* Your code here! */

#include "dsets.h"

void DisjointSets::addelements(int n)
{
    for(int i = 0; i < n; i++)
    {
		s.push_back(-1);
	}
}

int DisjointSets::find(int i)
{
	if(s[i] < 0)
		return i;
	else
		return find(s[i]);
}

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


