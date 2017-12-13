/* Your code here! */

#ifndef DSETS_H
#define DSETS_H

#include <vector>
using namespace std;

class DisjointSets
{
private: 
    vector<int> s;
public:
	int find(int i);
	void addelements(int n);
	void setunion(int a, int b);
};

#endif







