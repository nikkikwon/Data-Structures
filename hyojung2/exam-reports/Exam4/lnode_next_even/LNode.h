// Your code here
#ifndef LNODE_H
#define LNODE_H
#include "Node.h"
#include <string>

using namespace std;

class LNode : public Node {
    private:
       
    public:
    	void lookAtMeEven(Node **arr,int n);
	//destructor
	~LNode();
	
};

#endif

