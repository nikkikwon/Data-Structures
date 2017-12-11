// your code here
#include "LNode.h"
#include <iostream>

void LNode::lookAtMeEven(Node **arr,int n)
{   
	for(int i = 0; i < n; i = i + 2)
	{
		arr[i]->setLookingAt(arr[i]);		
	}
}
LNode::~LNode() { }
